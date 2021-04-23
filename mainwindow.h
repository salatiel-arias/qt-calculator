#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QTextBrowser>
#include <vector>
#include <memory>
#include <iostream>

#include "keypadButton.h"
#include "calcEngine.h"

#define BUTTON_WIDTH        40
#define BUTTON_HEIGHT       30
#define EQ_BUTTON_HEIGHT    70
#define DISPLAY_WIDTH       205
#define DISPLAY_HEIGHT      60
#define WINDOW_PADDING      20
#define BUTTON_DELTA_X      55
#define BUTTON_DELTA_Y      40 
#define WINDOW_WIDTH        245
#define WINDOW_HEIGHT       260
#define BUTTON_GRID_Y_ORIG  210 
#define EQUAL_BUTTON        10
#define PLUS_BUTTON         11
#define MINUS_BUTTON        12

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QWidget *centralwidget;
    QPushButton *testButton;
    std::vector<KeypadButton*> digitButtons;
    QTextBrowser *calcDisplay;
    calculator::CalcEngine *calcEngine;

    void createLayout();

private slots:
    void digitClicked(int id);
    void updateDisplay(QString disp);

};


#endif // MAINWINDOW_H
