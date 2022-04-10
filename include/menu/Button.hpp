#pragma once

#include "../../include/core/ClickAble.hpp"


class Button: public ClickAble
{
public:
    enum Commands { Nothing, Viscosity, Diffusion, Accuracy, Velocity, Density, Clear, ChangeColor };

    Button(Button::Commands command): ToReturn(command) {};
    virtual ~Button() = default;

    //return -1 if do not change
    virtual int GetValueToChange() = 0;
    virtual Button::Commands GetCommand() {return ToReturn;}

private:
    Button::Commands ToReturn;
};

