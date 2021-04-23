#ifndef H_CALCENGINE
#define H_CALCENGINE

#include <QObject>
#include <QThread>
#include <functional>
#include <thread>
#include <mutex>
#include <iostream>

#define EQUAL_BUTTON        10
#define PLUS_BUTTON         11
#define MINUS_BUTTON        12
#define EMPTY_ID            0xff

namespace calculator
{
    enum MathOp {
        Equal =10,
        Addition=11,
        Substraction=12,        
        Empty
    };
    enum State {
        FillingTerm,
        KeepingCount,
        EqState,
        StartingOver
    };
    struct Term{
        int value;
        MathOp sign;
    };



class CalcEngine : public QObject {
    
    Q_OBJECT

    public:
    CalcEngine();
    ~CalcEngine();
    void updateInput(int id);

    signals:
    void updateDisplay(QString disp);
    
    private:
    unsigned int counter_;
    std::mutex buttonSignal_mutex_;
    bool buttonPressed_;
    int passedId_;
    MathOp carrySign_;
    Term term_;
    bool watingForInput_;
    bool calcEngine_On_;
    bool commingFromEqState_;  
    std::function<void()> currentState_;
    std::thread mainThread_;
        
    void calcEngineMain();
    void fillingTerm();
    void keepingCount();
    void eqState();
    void startingOver();
    void updateCounter();

};

}


#endif