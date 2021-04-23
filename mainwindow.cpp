#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), 
        centralwidget{new QWidget(this)}, 
        calcDisplay{new QTextBrowser(centralwidget)},
        calcEngine{new calculator::CalcEngine()}
{   
    //create numbered buttons
    for(int id=0; id<13; id++)
    {
        digitButtons.push_back(new KeypadButton(id,centralwidget));
    }
    //set the central widget
    this->setCentralWidget(centralwidget);
    //connect numbered buttons passing its id
    for(auto it = digitButtons.begin(); it!=digitButtons.end(); it++)
    {
        connect((*it), SIGNAL(clicked(int)), this, SLOT(digitClicked(int)));
    } 
    //connect calculation done signal 
    //calcEngine->subscribe(std::bind(&MainWindow::updateDisplay, this, std::placeholders::_1));   
    connect(calcEngine, SIGNAL(updateDisplay(QString)), this, SLOT(updateDisplay(QString)));
    //call layout creator
    createLayout();    
}

MainWindow::~MainWindow()
{
    //delete something
    delete calcEngine;
}

void MainWindow::createLayout()
{
    //set window dimensions
    this->resize(245, 270);
    //set window style from a file
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
    this->setSizePolicy(sizePolicy);
    this->setMinimumSize(QSize(WINDOW_WIDTH, WINDOW_HEIGHT));
    this->setMaximumSize(QSize(WINDOW_WIDTH, WINDOW_HEIGHT));
    //set numbered buttons properties 
    int position_x = WINDOW_PADDING;
    int position_y = BUTTON_GRID_Y_ORIG;
    for(auto eachButton : digitButtons)
    {
        int id = eachButton->getID();        
        eachButton->setGeometry(QRect(position_x, position_y, BUTTON_WIDTH, BUTTON_HEIGHT));
        eachButton->setText(QString::fromStdString(std::to_string(id)));
        position_x += BUTTON_DELTA_X;
        if(id == 0 || id == 3 || id == 6) 
        {
            position_y -= BUTTON_DELTA_Y;
            position_x = WINDOW_PADDING;
        }
    }
    //set equal button properties
    digitButtons[EQUAL_BUTTON]->setGeometry(WINDOW_PADDING+(3*BUTTON_DELTA_X), BUTTON_GRID_Y_ORIG - BUTTON_DELTA_Y, BUTTON_WIDTH, BUTTON_HEIGHT+BUTTON_DELTA_Y);
    digitButtons[EQUAL_BUTTON]->setText("=");
    //set plus button properties
    digitButtons[PLUS_BUTTON]->setGeometry(WINDOW_PADDING+(3*BUTTON_DELTA_X), BUTTON_GRID_Y_ORIG - (2*BUTTON_DELTA_Y), BUTTON_WIDTH, BUTTON_HEIGHT);
    digitButtons[PLUS_BUTTON]->setText("+");
    //set minus button properties
    digitButtons[MINUS_BUTTON]->setGeometry(WINDOW_PADDING+(3*BUTTON_DELTA_X), BUTTON_GRID_Y_ORIG - (3*BUTTON_DELTA_Y), BUTTON_WIDTH, BUTTON_HEIGHT);
    digitButtons[MINUS_BUTTON]->setText("-");
    //set calc display
    calcDisplay->setGeometry(QRect(WINDOW_PADDING, WINDOW_PADDING, DISPLAY_WIDTH, DISPLAY_HEIGHT));
}

void MainWindow::digitClicked(int id)
{
    calcEngine->updateInput(id);

}

void MainWindow::updateDisplay(QString disp)
{
    calcDisplay->setText(disp);
    calcDisplay->setAlignment(Qt::Alignment::enum_type::AlignRight);
}

/*******************************************************************************************************************/

