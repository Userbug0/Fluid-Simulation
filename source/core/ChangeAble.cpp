#include "../../include/core/ChangeAble.hpp"


ChangeAbleFloat::ChangeAbleFloat(float value):
   Value(value), MinValue(0), MaxValue(0)
{

}


void ChangeAbleFloat::SetValueByPercent(int percent)
{
    SetValue(percent * (MaxValue - MinValue) / 100 + MinValue);
}

