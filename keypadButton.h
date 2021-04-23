#ifndef H_KEYPADBUTTON
#define H_KEYPADBUTTON

#include <QPushButton>


class KeypadButton : public QPushButton 
{
    Q_OBJECT
    public:
    //constructor
    KeypadButton(int id, QWidget *parent);
    int getID();

    signals:
    void clicked(int id);

    private slots:
    void reemitClicked();

    private:
    int id_;

};


#endif