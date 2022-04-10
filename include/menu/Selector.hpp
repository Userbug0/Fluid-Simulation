#ifndef SELECTOR_HPP
#define SELECTOR_HPP

#include <SFML/Graphics.hpp>

#include <../../include/menu/Button.hpp>
#include <../../include/core/TextRenderer.hpp>


class Selector : public Button
{
private:
    sf::CircleShape Right;
    sf::CircleShape Left;
    // radius of triangles
    const int Radius = 7;

    sf::Vector2f Position;

    std::vector<std::string> Values;
    int CurrentIndex;

    TextRenderer Text;

    void AddIndex();
    void SubtractIndex();
    bool InsideRight(const sf::Vector2i& point);
    bool InsideLeft(const sf::Vector2i& point);
public:
    Selector(const sf::Vector2f& position, Button::Commands command, const std::vector<std::string>& values);
    virtual ~Selector();

    int GetValueToChange() override;

    void Render(sf::RenderWindow* window) override;
    void OnMouseMoved(const sf::Vector2i& mpos, const sf::Vector2i& prevMousePos) override{}
    void OnMousePressed(const sf::Vector2i& mpos) override;
    void OnMouseReleased(const sf::Vector2i& mpos) override;
    bool Inside(const sf::Vector2i& mpos) override;
};

#endif // SELECTOR_HPP
