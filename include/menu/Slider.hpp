#ifndef SLIDER_HPP
#define SLIDER_HPP

#include <SFML/Graphics.hpp>

#include <../../include/menu/Button.hpp>
#include <../../include/core/TextRenderer.hpp>


class Slider: public Button
{
private:
    sf::Vector2f Start;
    sf::Vector2f End;
    sf::Vector2f CurrentPos;

    const int Thickness = 4;
    const int Radius = 10;

    sf::Vertex Line[4];
    sf::CircleShape Circle;

    TextRenderer Info;
    std::string Text;

public:
    Slider(const sf::Vector2f& start, const sf::Vector2f& end, Button::Commands command, const std::string& text);
    virtual ~Slider();

    int GetValueToChange() override;

    void Render(sf::RenderWindow* window) override;
    void OnMouseMoved(const sf::Vector2i& mpos, const sf::Vector2i& prevMousePos) override;
    void OnMousePressed(const sf::Vector2i& mpos) override {Circle.setFillColor(sf::Color::White);}
    void OnMouseReleased(const sf::Vector2i& mpos) override {Circle.setFillColor(sf::Color::Yellow);}
    bool Inside(const sf::Vector2i& mpos) override;
};

#endif // SLIDER_HPP
