#pragma once

#include <SFML/Graphics.hpp>

#include "../../include/core/ClickAble.hpp"
#include "../../include/menu/Button.hpp"


class ButtonHandler: public ClickAble
{
public:
    ButtonHandler();
    virtual ~ButtonHandler();

    Button::Commands GetCurrentCommand();
    int GetValueToChange();

    void Render(sf::RenderWindow* window) override;
    void OnMouseMoved(const sf::Vector2i& mpos, const sf::Vector2i& prevMousePos) override;
    void OnMousePressed(const sf::Vector2i& mpos) override;
    void OnMouseReleased(const sf::Vector2i& mpos) override;
    bool Inside(const sf::Vector2i& mpos) override;

private:
    sf::Vertex ToDraw[4];

    std::vector<Button*> Buttons;
    int SelectedButton;

    void InitButtons();
};

