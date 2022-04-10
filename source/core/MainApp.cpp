#include <SFML/Graphics.hpp>

#include "../../include/core/MainApp.hpp"


MainApp::MainApp()
{
    MyEngine = new Engine("SMOKE WEED EVERY DAY", {0, 0, 0});
}


void MainApp::Start()
{
    sf::Clock clock;

    MyEngine->Start();
    while(MyEngine->isRunning()){
        MyEngine->Update(clock.getElapsedTime());

        clock.restart();
    }
}


MainApp::~MainApp()
{
    delete MyEngine;
}
