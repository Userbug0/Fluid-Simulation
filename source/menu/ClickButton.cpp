#include "../../include/menu/ClickButton.hpp"
#include "../../include/core/Settings.hpp"


ClickButton::ClickButton(const sf::Vector2f& position, const sf::Vector2f& size, Button::Commands command, const std::string& text):
    Button(command), Position(position), Size(size), Text({Position.x + size.x / 5, Position.y + size.y / 5}, text, 15)
{
    Horizontal[0] = sf::Vertex({Position.x, Position.y});
    Horizontal[1] = sf::Vertex({Position.x + Size.x, Position.y});
    Horizontal[2] = sf::Vertex({Position.x + Size.x, Position.y + Size.y});
    Horizontal[3] = sf::Vertex({Position.x, Position.y + Size.y});

    Vertical[0] = sf::Vertex({Position.x, Position.y});
    Vertical[1] = sf::Vertex({Position.x, Position.y + Size.y});
    Vertical[2] = sf::Vertex({Position.x + Size.x, Position.y + Size.y});
    Vertical[3] = sf::Vertex({Position.x + Size.x, Position.y});

    for(auto& v: Horizontal)
        v.color = sf::Color::Yellow;
    for(auto& v: Vertical)
        v.color = sf::Color::Yellow;
}


bool ClickButton::Inside(const sf::Vector2i& mpos)
{
    return mpos.x > Position.x && mpos.x < Position.x + Size.x && \
           mpos.y > Position.y && mpos.y < Position.y + Size.y;
}


void ClickButton::OnMousePressed(const sf::Vector2i& mpos)
{
    for(auto& v: Horizontal)
        v.color = sf::Color::White;
    for(auto& v: Vertical)
        v.color = sf::Color::White;
}


void ClickButton::OnMouseReleased(const sf::Vector2i& mpos)
{
    for(auto& v: Horizontal)
        v.color = sf::Color::Yellow;
    for(auto& v: Vertical)
        v.color = sf::Color::Yellow;
}


void ClickButton::Render(sf::RenderWindow* window)
{
    window->draw(Horizontal, 4, sf::Lines);
    window->draw(Vertical, 4, sf::Lines);
    Text.Render(window);
}

