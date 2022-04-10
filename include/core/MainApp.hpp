#pragma once

#include "../../include/core/Engine.hpp"


class MainApp
{
public:
    MainApp();
    ~MainApp();

    void Start();

private:
    Engine* MyEngine;
};

