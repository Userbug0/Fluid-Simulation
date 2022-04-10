#ifndef TEXTRENDERER_HPP
#define TEXTRENDERER_HPP

#include <SFML/Graphics.hpp>


class TextRenderer
{
private:
    sf::Text Text;
    sf::Font Font;

public:
    TextRenderer(){}
    TextRenderer(const sf::Vector2f& position, const std::string& text, int size);
    ~TextRenderer();

    void Render(sf::RenderWindow* window);

    void SetText(const std::string& text) {Text.setString(text);}

};

#endif // TEXTRENDERER_HPP
