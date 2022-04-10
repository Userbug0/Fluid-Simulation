#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <../../include/core/ClickAble.hpp>


class Button: public ClickAble
{
public:
    enum Commands {Nothing, Viscosity, Diffusion, Accuracy, Velocity, Density, Clear, ChangeColor};

private:
    Button::Commands ToReturn;

public:
    Button(Button::Commands command);
    virtual ~Button();
    //return -1 if do not change
    virtual int GetValueToChange() = 0;
    virtual Button::Commands GetCommand() {return ToReturn;}
};

#endif // BUTTON_HPP
