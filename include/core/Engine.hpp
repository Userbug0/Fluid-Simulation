#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <SFML/Graphics.hpp>

#include <../../include/fluid/Field.hpp>
#include <../../include/fluid/Fluid.hpp>
#include <../../include/menu/ButtonHandler.hpp>
#include <../../include/core/TextRenderer.hpp>


class Engine
{
private:
    sf::RenderWindow* Window;
    Field* Grid;
    Fluid* MyFluid;
    ButtonHandler* Menu;

    sf::Color BackgroundColor;
    bool Running;

    sf::Vector2i PrevMousePos;
    bool MousePressed;
    void OnMouseMoved();
    void OnMousePressed();
    void OnMouseReleased();

    TextRenderer InfoFPS;
    TextRenderer InfoSqaures;

    void SetValueByCommand();
public:
    Engine(const std::string& title, const sf::Color& bgColor);
    ~Engine();

    void Start();

    void Update(const sf::Time& frameTime);
    void Render();
    void HandleEvent();

    bool isRunning(){return Running;}
};


#endif // ENGINE_HPP
