#include <../../include/core/TextRenderer.hpp>
#include <iostream>


TextRenderer::TextRenderer(const sf::Vector2f& position, const std::string& text, int size)
{
    if(!Font.loadFromFile("D:/C++/OpenSans Fonts/OpenSans-Bold.ttf"))
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


TextRenderer::~TextRenderer()
{
}
