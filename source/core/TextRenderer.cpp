#include <iostream>

#include "../../include/core/TextRenderer.hpp"


TextRenderer::TextRenderer(const sf::Vector2f& position, const std::string& text, int size)
{
    if(!Font.loadFromFile("Resources//OpenSans-Bold.ttf"))
        std::cerr << "Could not load the font\n";
    Text.setFont(Font);
    Text.setString(text);
    Text.setCharacterSize(size);
    Text.setPosition({position.x, position.y});
}


void TextRenderer::Render(sf::RenderWindow* window)
{
    window->draw(Text);
}

