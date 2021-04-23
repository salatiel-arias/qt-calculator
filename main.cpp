#include <QApplication>
#include <QFile>

#include "mainwindow.h"


int main(int argc, char *argv[])
{      
    QApplication a(argc, argv);
    //set style from file    
    QFile styleFile("darktheme.txt");
    styleFile.open(QFile::ReadOnly);
    QString style(styleFile.readAll());
    a.setStyleSheet(style);

    MainWindow w;
    w.show();    

    return a.exec();
}