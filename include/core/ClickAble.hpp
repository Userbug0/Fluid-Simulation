#pragma once

#include <SFML/Graphics.hpp>


class ClickAble
{
public:
    ClickAble() = default;
    virtual ~ClickAble() = default;

    virtual void OnMouseMoved(const sf::Vector2i& mpos, const sf::Vector2i& prevMousePos) = 0;
    virtual void OnMousePressed(const sf::Vector2i& mpos) = 0;
    virtual void OnMouseReleased(const sf::Vector2i& mpos) = 0;

    virtual bool Inside(const sf::Vector2i& mpos) = 0;

    virtual void Render(sf::RenderWindow* window) = 0;
};

