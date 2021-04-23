#include "calcEngine.h"
namespace calculator
{
/****************************************PUBLIC****************************************/
CalcEngine::CalcEngine()
:   counter_{0},
    buttonPressed_{false},
    passedId_{0},
    carrySign_{MathOp::Addition},
    term_{0, MathOp::Addition},
    watingForInput_ {false},
    calcEngine_On_{true},
    commingFromEqState_{false} 
{
    currentState_=std::bind(&CalcEngine::fillingTerm, this);
    //start calcEngineMain thread
    mainThread_ = std::thread(&CalcEngine::calcEngineMain, this);
}    

CalcEngine::~CalcEngine()
{
    mainThread_.join();
}

void CalcEngine::updateInput(int id)
{
    std::lock_guard<std::mutex>lck(buttonSignal_mutex_);
    //enters critical section
    buttonPressed_ = true;
    passedId_ = id;
}

/****************************************PRIVATE****************************************/

void CalcEngine::calcEngineMain() {
    while(calcEngine_On_) {
        currentState_();
       // std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

void CalcEngine::fillingTerm() {
    
    //enters critical section
    std::lock_guard<std::mutex>lck(buttonSignal_mutex_);
    //check if input was updated and if equal sign was pressed
    if(buttonPressed_) {
        //enter state: EqState
        if(passedId_== MathOp::Equal) {
        currentState_ = std::bind(&CalcEngine::eqState, this);
         //check if input is a digit
         } else if(passedId_ >= 0 && passedId_ <10 ) {
            //check if there if vallue was already filled...  
            if(term_.value != 0) term_.value = (term_.value*10) + passedId_;
            //if not then fill value for first time  
            else {
                //update sign for current term
                term_.value = passedId_;
            } 
            updateDisplay(QString::fromStdString(std::to_string(term_.value)));           
        }
        //if not a digit then pass sign using carrySign_ 
        //next state: KeepingCount
        else {
            carrySign_= static_cast<MathOp>(passedId_);
            currentState_ = std::bind(&CalcEngine::keepingCount, this);
        }
        buttonPressed_ = false;
    } 
}

void CalcEngine::keepingCount() {
    updateCounter();
    //go back to state: FillingTerm
    currentState_ = std::bind(&CalcEngine::fillingTerm, this);
}

void CalcEngine::eqState() {
    if(!watingForInput_) {
        updateCounter();
        updateDisplay(QString::fromStdString(std::to_string(counter_)));
        watingForInput_ = true;
    }
    //enters critical section
    std::lock_guard<std::mutex>lck(buttonSignal_mutex_);
    if(buttonPressed_) {
        buttonPressed_ = false;
        watingForInput_ = false;
        //react only if number or minus/puls sign pressed
        if(passedId_ >= 0 && passedId_ <10) {
            //go next state: StartingOver
            currentState_ = std::bind(&CalcEngine::startingOver, this);
        }
        if(static_cast<MathOp>(passedId_)!=MathOp::Equal) {
            //go to next state:: FillingTerm
            term_.value = 0;
            term_.sign = static_cast<MathOp>(passedId_);
            currentState_ = std::bind(&CalcEngine::keepingCount, this);
        } else {
            watingForInput_ = true;
        }
    
    }
}

void CalcEngine::startingOver() {
    counter_ = 0;
    term_ = {passedId_, MathOp::Addition};
    currentState_ = std::bind(&CalcEngine::fillingTerm, this); 
}

void CalcEngine::updateCounter(){
    if(term_.sign == MathOp::Addition) {
        counter_ += term_.value;
    } 
    if(term_.sign == MathOp::Substraction) {
        counter_ -= term_.value;
    }
    term_.value = 0;
    term_.sign = static_cast<MathOp> (passedId_);
    updateDisplay(QString::fromStdString(std::to_string(counter_)));
}

}//namespace calculator
