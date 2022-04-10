#include "../../include/core/Engine.hpp"

#include "../../include/core/Settings.hpp"
#include "../../include/core/ChangeAble.hpp"
#include "../../include/menu/Button.hpp"


Engine::Engine(const std::string& title, const sf::Color& bgColor):
    BackgroundColor(bgColor), Running(true), MousePressed(false), InfoFPS({0, 0}, "FPS: " + std::to_string(Settings::FPS), 15),
    InfoSqaures({0, 15}, "Squares: " + std::to_string(Settings::FLUIDSIZE * Settings::FLUIDSIZE \
                                                      / (Settings::SCALE * Settings::SCALE)), 15)
{
    sf::ContextSettings params;
    params.antialiasingLevel = 8;

    Window = new sf::RenderWindow(sf::VideoMode(Settings::FLUIDSIZE + Settings::MENUWIDTH, Settings::FLUIDSIZE), \
                                  title, sf::Style::Close, params);
    Window->setFramerateLimit(Settings::FPS);

    Grid = new Field();
    MyFluid = new Fluid(0.1f, 0.2f, Grid);
    Menu = new ButtonHandler();
}


void Engine::Update(const sf::Time& frameTime)
{
    HandleEvent();

    MyFluid->Update(0.00001);

    Render();
}


void Engine::Render()
{
    Window->clear(BackgroundColor);

    Grid->Render(Window);
    Menu->Render(Window);

    InfoFPS.Render(Window);
    InfoSqaures.Render(Window);

    Window->display();
}


void Engine::OnMouseMoved()
{
    sf::Vector2i mpos = sf::Mouse::getPosition(*Window);
    if(Grid->Inside(mpos)){
        Grid->OnMouseMoved(mpos, PrevMousePos);
    }
    else if(Menu->Inside(mpos)){
        Menu->OnMouseMoved(mpos, PrevMousePos);
        SetValueByCommand();
    }

    PrevMousePos = mpos;
}


void Engine::OnMousePressed()
{
    sf::Vector2i mpos = sf::Mouse::getPosition(*Window);
    if(Grid->Inside(mpos)){
        Grid->OnMousePressed(mpos);
    }
    else if(Menu->Inside(mpos)){
        Menu->OnMousePressed(mpos);
        SetValueByCommand();
    }

    PrevMousePos = mpos;
    MousePressed = true;
}


void Engine::OnMouseReleased()
{
    sf::Vector2i mpos = sf::Mouse::getPosition(*Window);
    if(Grid->Inside(mpos))
        Grid->OnMouseReleased(mpos);
    else if(Menu->Inside(mpos)){
        SetValueByCommand();
    }
    Menu->OnMouseReleased(mpos);

    MousePressed = false;
}


void Engine::SetValueByCommand()
{
    Button::Commands command = Menu->GetCurrentCommand();
    if(command != Button::Commands::Nothing){
        int p = Menu->GetValueToChange();
        if(command == Button::Commands::Viscosity)
            MyFluid->SetViscosity(p);
        else if(command == Button::Commands::Diffusion)
            MyFluid->SetDiffusion(p);
        else if(command == Button::Commands::Accuracy)
            MyFluid->SetIterations(p);
        else if(command == Button::Commands::Velocity)
            Grid->SetVelocity(p);
        else if(command == Button::Commands::Density)
            Grid->SetDensity(p);
        else if(command == Button::Commands::ChangeColor)
            Grid->SetColorMode(p);
        else if(command == Button::Commands::Clear)
            Grid->Clear();
    }
}


void Engine::HandleEvent()
{
    sf::Event event;

    while(Window->pollEvent(event)){
        if(event.type == sf::Event::Closed)
            Running = false;

        else if(event.type == sf::Event::MouseButtonReleased)
            OnMouseReleased();

        else if(event.type == sf::Event::MouseButtonPressed)
            OnMousePressed();

        else if(MousePressed == true)
            OnMouseMoved();
    }
}


void Engine::Start()
{
    Window->clear(BackgroundColor);

    Window->display();
}


Engine::~Engine()
{
    delete Grid;

    delete MyFluid;

    delete Menu;

    delete Window;
}
