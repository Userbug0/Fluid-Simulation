#pragma once

#include <SFML/Graphics.hpp>

#include "../../include/core/ClickAble.hpp"
#include "../../include/core/ChangeAble.hpp"

#include <vector>


struct FluidDesc
{
    FluidDesc(size_t size)
        : VelocityX(size), VelocityY(size),
          PrevVelocityX(size), PrevVelocityY(size),
          Density(size), PrevDensity(size) {}

    std::vector<float> VelocityX;
    std::vector<float> VelocityY;
    std::vector<float> PrevVelocityX;
    std::vector<float> PrevVelocityY;
    std::vector<float> Density;
    std::vector<float> PrevDensity;
};

class Field: public ClickAble
{
public:
    enum ColorMode { White, Pink, Aqua };

    Field();
    virtual ~Field() = default;

    void SetColorMode(int mode) { CurrentMode = static_cast<ColorMode>(mode); }
    void SetVelocity(int percent) { VelocityPerMove.SetValueByPercent(percent); }
    void SetDensity(int percent) { DensityPerMove.SetValueByPercent(percent); }

    void Clear();

    void Render(sf::RenderWindow* window) override;
    void OnMouseMoved(const sf::Vector2i& mpos, const sf::Vector2i& prevMousePos) override;
    void OnMousePressed(const sf::Vector2i& mpos) override {}
    void OnMouseReleased(const sf::Vector2i& mpos) override {}
    bool Inside(const sf::Vector2i& mpos) override;

    void AddVelocity(int x, int y, float velX, float velY);
    void AddDensity(int x, int y, float denisty);

    int GetSize() { return Size; }
    FluidDesc& GetFluidDesc() { return Desc; }
    const FluidDesc& GetFluidDesc() const { return Desc; }

private:
    class Cell {
    public:
        Cell(const sf::Vector2f& position, int size);
        ~Cell() {}

        void Render(sf::RenderWindow* window) { window->draw(ToDraw); }
        void SetColor(const sf::Color& color) { ToDraw.setFillColor(color); }

    private:
        sf::RectangleShape ToDraw;
    };

    int Size;
    std::vector<Cell> Cells;
    FluidDesc Desc;

    ChangeAbleFloat VelocityPerMove;
    ChangeAbleFloat DensityPerMove;

    sf::Color MakeColor(float density);
    ColorMode CurrentMode;
};

