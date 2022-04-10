#pragma once


class ChangeAbleFloat{
public:
    ChangeAbleFloat(float value = 0);
    ~ChangeAbleFloat() = default;

    void SetValueByPercent(int percent);

    void SetValue(float value) {Value = value;}
    void SetMinValue(float minValue) {MinValue = minValue;}
    void SetMaxValue(float maxValue) {MaxValue = maxValue;}

    float GetValue() const {return Value;}

private:
    float Value;
    float MinValue;
    float MaxValue;
};

