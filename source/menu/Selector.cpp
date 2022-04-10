#include <../../include/menu/Selector.hpp>


Selector::Selector(const sf::Vector2f& position, Button::Commands command, const std::vector<std::string>& values):
    Button(command), Position(position), Values(values), CurrentIndex(0), Text(Position, Values[0], 20)
{
    Right.setRadius(Radius);
    Right.setFillColor(sf::Color::Yellow);
    Right.setPosition({Position.x + 80, Position.y + 6});
    Right.setPointCount(3);
    Right.rotate(90);

    Left.setRadius(Radius);
    Left.setFillColor(sf::Color::Yellow);
    Left.setPosition({Position.x - 22, Position.y + 20});
    Left.setPointCount(3);
    Left.rotate(270);

}


int Selector::GetValueToChange()
{
    return CurrentIndex;
}


void Selector::AddIndex()
{
    CurrentIndex++;
    if(CurrentIndex >= Values.size())
        CurrentIndex = 0;
}


void Selector::SubtractIndex()
{
    CurrentIndex--;
    if(CurrentIndex <= -1)
        CurrentIndex = Values.size() - 1;
}


void Selector::OnMousePressed(const sf::Vector2i& mpos)
{
    if(InsideRight(mpos)){
        AddIndex();
        Right.setFillColor(sf::Color::White);
    }
    else if(InsideLeft(mpos)){
        SubtractIndex();
        Left.setFillColor(sf::Color::White);
    }
}


void Selector::OnMouseReleased(const sf::Vector2i& mpos)
{
    if(InsideRight(mpos))
        Right.setFillColor(sf::Color::Yellow);

    else if(InsideLeft(mpos))
        Left.setFillColor(sf::Color::Yellow);

}


bool Selector::Inside(const sf::Vector2i& mpos)
{
    return InsideRight(mpos) || InsideLeft(mpos);
}


bool Selector::InsideRight(const sf::Vector2i& point)
{
    sf::Vector2f pos = sf::Vector2f(Position.x + 80, Position.y + 6) + sf::Vector2f(-Radius, Radius);
    float distSquared = (pos.x - point.x) * (pos.x - point.x) + (pos.y - point.y) * (pos.y - point.y);
    return Radius * Radius > distSquared;
}


bool Selector::InsideLeft(const sf::Vector2i& point)
{
    sf::Vector2f pos = sf::Vector2f(Position.x - 22, Position.y + 20) + sf::Vector2f(Radius, -Radius);
    float distSquared = (pos.x - point.x) * (pos.x - point.x) + (pos.y - point.y) * (pos.y - point.y);
    return Radius * Radius > distSquared;
}


void Selector::Render(sf::RenderWindow* window)
{
    window->draw(Right);
    window->draw(Left);

    Text.SetText(Values[CurrentIndex]);
    Text.Render(window);
}


Selector::~Selector()
{

}
