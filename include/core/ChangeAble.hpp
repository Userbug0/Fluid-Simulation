#ifndef CHANGEABLE_HPP
#define CHANGEABLE_HPP


class ChangeAbleFloat{
private:
    float Value;
    float MinValue;
    float MaxValue;

public:
    ChangeAbleFloat();
    ChangeAbleFloat(float value);
    ~ChangeAbleFloat(){}

    void SetValueByPercent(int percent);

    void SetValue(float value) {Value = value;}
    void SetMinValue(float minValue) {MinValue = minValue;}
    void SetMaxValue(float maxValue) {MaxValue = maxValue;}

    float GetValue() const {return Value;}
};

#endif // CHANGEABLE_HPP
