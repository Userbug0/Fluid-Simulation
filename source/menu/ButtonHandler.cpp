#include "../../include/menu/ButtonHandler.hpp"

#include "../../include/core/Settings.hpp"
#include "../../include/menu/Slider.hpp"
#include "../../include/menu/ClickButton.hpp"
#include "../../include/menu/Selector.hpp"


ButtonHandler::ButtonHandler():
    SelectedButton(-1)
{
    ToDraw[0] = sf::Vertex({0, 0}, {0, 0, 0});
    ToDraw[1] = sf::Vertex({Settings::MENUWIDTH, 0}, {0, 0, 20});
    ToDraw[2] = sf::Vertex({Settings::MENUWIDTH, Settings::FLUIDSIZE}, {0, 0, 20});
    ToDraw[3] = sf::Vertex({0, Settings::FLUIDSIZE}, {0, 0, 0});

    InitButtons();
}


void ButtonHandler::InitButtons()
{
    float offset = Settings::MENUWIDTH / 8;
    sf::Vector2f start = {offset / 3, Settings::FLUIDSIZE / 5};
    sf::Vector2f end = {Settings::MENUWIDTH - offset, Settings::FLUIDSIZE / 5};
    sf::Vector2f step = {0, (float)Settings::FLUIDSIZE / 10};

    Buttons.push_back(new Slider(start, end, Button::Commands::Viscosity, "Viscosity"));

    start += step;
    end += step;
    Buttons.push_back(new Slider(start, end, Button::Commands::Diffusion, "Diffusion"));

    start += step;
    end += step;
    Buttons.push_back(new Slider(start, end, Button::Commands::Accuracy, "Accuracy"));

    start += step;
    end += step;
    Buttons.push_back(new Slider(start, end, Button::Commands::Velocity, "Velocity"));

    start += step;
    end += step;
    Buttons.push_back(new Slider(start, end, Button::Commands::Density, "Density"));

    start += step;
    start.x += Settings::MENUWIDTH / 3.5;
    Buttons.push_back(new Selector(start, Button::Commands::ChangeColor, {"White", "Pink", "Aqua"}));

    start = {Settings::MENUWIDTH / 3, Settings::FLUIDSIZE * 0.85};
    Buttons.push_back(new ClickButton(start, {Settings::MENUWIDTH / 3, Settings::MENUWIDTH / 6}, Button::Commands::Clear, "Clear"));

}


Button::Commands ButtonHandler::GetCurrentCommand()
{
    if(SelectedButton == -1)
        return Button::Commands::Nothing;
    return Buttons[SelectedButton]->GetCommand();
}


int ButtonHandler::GetValueToChange()
{
    if(SelectedButton == -1)
        return -1;
    return Buttons[SelectedButton]->GetValueToChange();
}

void ButtonHandler::OnMouseMoved(const sf::Vector2i& mpos, const sf::Vector2i& prevMousePos)
{
    if(SelectedButton != -1)
        Buttons[SelectedButton]->OnMouseMoved(mpos, prevMousePos);
}


void ButtonHandler::OnMousePressed(const sf::Vector2i& mpos)
{
    for(unsigned i = 0; i < Buttons.size(); i++){
        if(Buttons[i]->Inside(mpos)){
            Buttons[i]->OnMousePressed(mpos);
            SelectedButton = i;
            break;
        }
    }
}


void ButtonHandler::OnMouseReleased(const sf::Vector2i& mpos)
{
    if(SelectedButton != -1){
        Buttons[SelectedButton]->OnMouseReleased(mpos);
        SelectedButton = -1;
    }
}


bool ButtonHandler::Inside(const sf::Vector2i& mpos)
{
    return (mpos.x > 0 && mpos.x < (signed)Settings::MENUWIDTH && \
            mpos.y > 0 && mpos.y < (signed)Settings::FLUIDSIZE);
}


void ButtonHandler::Render(sf::RenderWindow* window)
{
    window->draw(ToDraw, 4, sf::Quads);
    for(auto& button: Buttons){
        button->Render(window);
    }
}


ButtonHandler::~ButtonHandler()
{
    for(auto& button: Buttons)
        delete button;
}
