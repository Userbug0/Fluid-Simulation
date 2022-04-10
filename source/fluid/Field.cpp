#include <../../include/fluid/Field.hpp>
#include <../../include/core/Settings.hpp>


Field::Cell::Cell(const sf::Vector2f& position, int size):
    ToDraw({(float)size, (float)size})
{
    ToDraw.setPosition(position - sf::Vector2f(size / 2, size / 2));
}


Field::Field():
    Size(Settings::FLUIDSIZE / Settings::SCALE + 1), VelocityPerMove(1000),
    DensityPerMove(100), CurrentMode(ColorMode::White)
{
    VelocityPerMove.SetMinValue(500);
    VelocityPerMove.SetMaxValue(2000);

    DensityPerMove.SetMinValue(25);
    DensityPerMove.SetMaxValue(255);

    int n = Size * Size;
    VelocityX = new float[n];
    VelocityY = new float[n];
    PrevVelocityX = new float[n];
    PrevVelocityY = new float[n];
    Density = new float[n];
    PrevDensity = new float[n];

    Clear();

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
        VelocityX[i] = 0;
        VelocityY[i] = 0;
        PrevVelocityX[i] = 0;
        PrevVelocityY[i] = 0;
        Density[i] = 0;
        PrevDensity[i] = 0;
    }
}


void Field::AddDensity(int x, int y, float density)
{
    Density[x + Size * y] += density;
}


void Field::AddVelocity(int x, int y, float velX, float velY)
{
    int index = x + Size * y;
    VelocityX[index] += velX;
    VelocityY[index] += velY;
}


sf::Color Field::MakeColor(float density)
{
    sf::Color result;
    if(density < 3)
        result = {0, 0, 0};
    else{
        if(density > 255)
            density = 255;
        if(CurrentMode == ColorMode::White)
            result = {density, density, density};
        else if(CurrentMode == ColorMode::Pink)
            result = {density, 0, density};
        else if(CurrentMode == ColorMode::Aqua)
            result = {0, density, density};
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
            d = Density[index];
            color = MakeColor(d);
            Cells[index].SetColor(color);
            Cells[index].Render(window);

        }
    }
}


Field::~Field()
{
    delete[] VelocityX;
    delete[] VelocityY;
    delete[] PrevVelocityX;
    delete[] PrevVelocityY;
    delete[] Density;
    delete[] PrevDensity;
}
