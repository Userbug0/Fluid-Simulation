#include "../../include/fluid/Field.hpp"
#include "../../include/core/Settings.hpp"


Field::Cell::Cell(const sf::Vector2f& position, int size):
    ToDraw({(float)size, (float)size})
{
    ToDraw.setPosition(position - sf::Vector2f(size / 2, size / 2));
}


Field::Field():
    Size(Settings::FLUIDSIZE / Settings::SCALE + 1), VelocityPerMove(2000),
    DensityPerMove(135), CurrentMode(ColorMode::White), Desc(Size * Size)
{
    VelocityPerMove.SetMinValue(500);
    VelocityPerMove.SetMaxValue(3500);

    DensityPerMove.SetMinValue(25);
    DensityPerMove.SetMaxValue(255);

    sf::Vector2f position;

    for(int i = 0; i < Size; i++){
        for(int j = 0; j < Size; j++){
            position = {(float)j * Settings::SCALE + Settings::MENUWIDTH, (float)i * Settings::SCALE};
            Cells.push_back(Cell(position, Settings::SCALE));
        }
    }
}


bool Field::Inside(const sf::Vector2i& mpos)
{
    return mpos.x > (signed)Settings::MENUWIDTH && mpos.x < (signed)(Settings::MENUWIDTH + Settings::FLUIDSIZE) && \
           mpos.y > 0 && mpos.y < (signed)Settings::FLUIDSIZE;
}


void Field::OnMouseMoved(const sf::Vector2i& mpos, const sf::Vector2i& prevMousePos)
{
    sf::Vector2i pos;
    pos.x = (mpos.x - Settings::MENUWIDTH) / Settings::SCALE;
    pos.y = mpos.y / Settings::SCALE;
    int velX = (int)VelocityPerMove.GetValue() * (pos.x - (prevMousePos.x - Settings::MENUWIDTH) / Settings::SCALE) * Settings::SCALE;
    int velY = (int)VelocityPerMove.GetValue() * (pos.y - prevMousePos.y / Settings::SCALE) * Settings::SCALE;
    float d = DensityPerMove.GetValue();

    AddDensity(pos.x, pos.y, d);
    AddVelocity(pos.x, pos.y, velX, velY);
    AddDensity(pos.x - 1, pos.y, d);
    AddVelocity(pos.x - 1, pos.y, velX, velY);
    AddDensity(pos.x + 1, pos.y, d);
    AddVelocity(pos.x + 1, pos.y, velX, velY);
    AddDensity(pos.x, pos.y - 1, d);
    AddVelocity(pos.x, pos.y - 1, velX, velY);
    AddDensity(pos.x, pos.y + 1, d);
    AddVelocity(pos.x, pos.y + 1, velX, velY);
}


void Field::Clear()
{
    int n = Size * Size;
    for(int i = 0; i < n; i++){
        Desc.VelocityX[i] = 0;
        Desc.VelocityY[i] = 0;
        Desc.PrevVelocityX[i] = 0;
        Desc.PrevVelocityY[i] = 0;
        Desc.Density[i] = 0;
        Desc.PrevDensity[i] = 0;
    }
}


void Field::AddDensity(int x, int y, float density)
{
    Desc.Density[x + Size * y] += density;
}


void Field::AddVelocity(int x, int y, float velX, float velY)
{
    int index = x + Size * y;
    Desc.VelocityX[index] += velX;
    Desc.VelocityY[index] += velY;
}


sf::Color Field::MakeColor(float density)
{
    sf::Color result;
    if(density < 3)
        result = {0, 0, 0};
    else
    {
        if(density > 255)
            density = 255;
        uint8_t dens = (uint8_t)density;
        if(CurrentMode == ColorMode::White)
            result = { dens, dens, dens };
        else if(CurrentMode == ColorMode::Pink)
            result = { dens, 0, dens };
        else if(CurrentMode == ColorMode::Aqua)
            result = {0, dens, dens };
    }

    return result;
}


void Field::Render(sf::RenderWindow* window)
{
    int index;
    float d;
    sf::Color color;
    for(int i = 0; i < Size; i++){
        for(int j = 0; j < Size; j++){
            index = j + i * Size;
            d = Desc.Density[index];
            color = MakeColor(d);
            Cells[index].SetColor(color);
            Cells[index].Render(window);
        }
    }
}
