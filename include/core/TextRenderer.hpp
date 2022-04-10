#pragma once

#include <SFML/Graphics.hpp>


class TextRenderer
{
public:
    TextRenderer() = default;
    TextRenderer(const sf::Vector2f& position, const std::string& text, int size);
    ~TextRenderer() = default;

    void Render(sf::RenderWindow* window);

    void SetText(const std::string& text) {Text.setString(text);}

private:
    sf::Text Text;
    sf::Font Font;
};

