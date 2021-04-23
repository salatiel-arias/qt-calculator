#include "keypadButton.h"

KeypadButton::KeypadButton(int id, QWidget *parent)
    :QPushButton(parent),
    id_{id}
{
    connect(this, SIGNAL(clicked()), this, SLOT(reemitClicked()));
}


void KeypadButton::reemitClicked()
{
    emit clicked(id_);
}

int KeypadButton::getID()
 {
     return id_;
 }
