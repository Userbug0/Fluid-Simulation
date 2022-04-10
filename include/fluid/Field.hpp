#ifndef FIELD_HPP
#define FIELD_HPP

#include <SFML/Graphics.hpp>

#include <../../include/core/ClickAble.hpp>
#include <../../include/core/ChangeAble.hpp>


class Field: public ClickAble
{
public:
    enum ColorMode{White, Pink, Aqua};
private:
    class Cell{
    private:
        sf::RectangleShape ToDraw;

    public:
        Cell(const sf::Vector2f& position, int size);
        ~Cell(){}

        void Render(sf::RenderWindow* window) {window->draw(ToDraw);}
        void SetColor(const sf::Color& color){ToDraw.setFillColor(color);}
    };

    int Size;
    std::vector<Cell> Cells;

    ChangeAbleFloat VelocityPerMove;
    ChangeAbleFloat DensityPerMove;

    sf::Color MakeColor(float density);
    ColorMode CurrentMode;
public:
    float* VelocityX;
    float* VelocityY;
    float* PrevVelocityX;
    float* PrevVelocityY;
    float* Density;
    float* PrevDensity;

    Field();
    virtual ~Field();

    void SetColorMode(int mode) {CurrentMode = static_cast<ColorMode>(mode);}


    void SetVelocity(int percent) {VelocityPerMove.SetValueByPercent(percent);}
    void SetDensity(int percent) {DensityPerMove.SetValueByPercent(percent);}

    void Clear();

    void Render(sf::RenderWindow* window) override;
    void OnMouseMoved(const sf::Vector2i& mpos, const sf::Vector2i& prevMousePos) override;
    void OnMousePressed(const sf::Vector2i& mpos) override {}
    void OnMouseReleased(const sf::Vector2i& mpos) override {}
    bool Inside(const sf::Vector2i& mpos) override;

    void AddVelocity(int x, int y, float velX, float velY);
    void AddDensity(int x, int y, float denisty);

    int GetSize() {return Size;}

};

#endif // FIELD_HPP
