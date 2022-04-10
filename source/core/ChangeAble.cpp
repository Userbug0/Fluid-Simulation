#include <../../include/core/ChangeAble.hpp>


ChangeAbleFloat::ChangeAbleFloat(float value):
    Value(value)
{}


ChangeAbleFloat::ChangeAbleFloat():
   Value(0), MinValue(0), MaxValue(0)
{}


void ChangeAbleFloat::SetValueByPercent(int percent)
{
    SetValue(percent * (MaxValue - MinValue) / 100 + MinValue);
}

