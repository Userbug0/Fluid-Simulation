#pragma once

#include <SFML/Graphics.hpp>

#include "../../include/menu/Button.hpp"
#include "../../include/core/TextRenderer.hpp"


class ClickButton : public Button
{
public:
    ClickButton(const sf::Vector2f& position, const sf::Vector2f& size, Button::Commands command, const std::string& text);
    virtual ~ClickButton() = default;

    int GetValueToChange() override {return -1;}

    void Render(sf::RenderWindow* window) override;
    void OnMouseMoved(const sf::Vector2i& mpos, const sf::Vector2i& prevMousePos) override{}
    void OnMousePressed(const sf::Vector2i& mpos) override;
    void OnMouseReleased(const sf::Vector2i& mpos) override;
    bool Inside(const sf::Vector2i& mpos) override;

private:
    sf::Vertex Horizontal[4];
    sf::Vertex Vertical[4];
    sf::Vector2f Position;
    sf::Vector2f Size;

    TextRenderer Text;
};

