#include "../../include/menu/Slider.hpp"


Slider::Slider(const sf::Vector2f& start, const sf::Vector2f& end, Button::Commands command, const std::string& text):
    Button(command), Start(start), End(end), CurrentPos((start.x + end.x + 1) / 2, (start.y + end.y) / 2), Circle(Radius),
    Info({Start.x, Start.y - 30}, text, 15), Text(text)
{
    sf::Vector2f offset = {0, (float)(Thickness * 0.5)};

    Line[0].position = Start - offset;
    Line[1].position = End - offset;
    Line[2].position = End + offset;
    Line[3].position = Start + offset;

    for(int i = 0; i < 4; i++)
        Line[i].color = sf::Color::Yellow;

    Circle.setPointCount(100);
    Circle.setFillColor(sf::Color::Yellow);
    Circle.setPosition(CurrentPos - sf::Vector2f(Radius, Radius));
}


void Slider::OnMouseMoved(const sf::Vector2i& mpos, const sf::Vector2i& prevMousePos)
{
    CurrentPos.x += mpos.x - prevMousePos.x;
    if(CurrentPos.x < Start.x){
        CurrentPos.x = Start.x;
    }
    else if(CurrentPos.x > End.x){
        CurrentPos.x = End.x;
    }
}


bool Slider::Inside(const sf::Vector2i& mpos)
{
    float distance = std::sqrt((CurrentPos.x - mpos.x) * (CurrentPos.x - mpos.x) + \
                               (CurrentPos.y - mpos.y) * (CurrentPos.y - mpos.y));
    return distance < Radius;
}


inline int Slider::GetValueToChange()
{
    return (100 * (CurrentPos.x - Start.x) / (End.x - Start.x));
}


void Slider::Render(sf::RenderWindow* window)
{
    window->draw(Line, 4, sf::Quads);

    Circle.setPosition(CurrentPos - sf::Vector2f(Radius, Radius));
    window->draw(Circle);

    int p = GetValueToChange();

    Info.SetText(Text + ": " + std::to_string(p) + "%");
    Info.Render(window);
}

