#include <../../include/fluid/Fluid.hpp>


Fluid::Fluid(float viscosity, float diffusion, Field* grid):
    Size(grid->GetSize()), Viscosity(viscosity), Diffusion(diffusion), Iterations(5.f), Grid(grid)
{
    Viscosity.SetMinValue(0);
    Viscosity.SetMaxValue(1);

    Diffusion.SetMinValue(0);
    Diffusion.SetMaxValue(3);

    Iterations.SetMinValue(2.f);
    Iterations.SetMaxValue(7.f);
}


void Fluid::Update(double dt)
{
    float* velX = Grid->VelocityX;
    float* velY = Grid->VelocityY;
    float* prevVelX = Grid->PrevVelocityX;
    float* prevVelY = Grid->PrevVelocityY;
    float* density = Grid->Density;
    float* prevDensity = Grid->PrevDensity;

    Diffuse(1, prevVelX, velX, Viscosity.GetValue(), dt);
    Diffuse(2, prevVelY, velY, Viscosity.GetValue(), dt);

    StayIncompressible(prevVelX, prevVelY, velX, velY);

    Advect(1, velX, prevVelX, prevVelX, prevVelY, dt);
    Advect(2, velY, prevVelY, prevVelX, prevVelY, dt);

    StayIncompressible(velX, velY, prevVelX, prevVelY);

    Diffuse(0, prevDensity, density, Diffusion.GetValue(), dt);
    Advect(0, density, prevDensity, velX, velY, dt);
}


void Fluid::Advect(int param, float* arr, float* prevArr, float* velX, float* velY, double dt)
{
    float i0, i1, j0, j1;

    float dtx = dt * (Size - 2);
    float dty = dt * (Size - 2);

    float s0, s1, t0, t1;
    float tmp1, tmp2, x, y;

    float Sizefloat = Size;
    float ifloat, jfloat;
    int i, j;

    for(j = 1, jfloat = 1; j < Size - 1; j++, jfloat++) {
        for(i = 1, ifloat = 1; i < Size - 1; i++, ifloat++) {
            tmp1 = dtx * velX[IX(i, j)];
            tmp2 = dty * velY[IX(i, j)];
            x = ifloat - tmp1;
            y = jfloat - tmp2;

            if(x < 0.5f) x = 0.5f;
            if(x > Sizefloat + 0.5f) x = Sizefloat + 0.5f;
            i0 = floorf(x);
            i1 = i0 + 1.0f;
            if(y < 0.5f) y = 0.5f;
            if(y > Sizefloat + 0.5f) y = Sizefloat + 0.5f;
            j0 = floorf(y);
            j1 = j0 + 1.0f;

            s1 = x - i0;
            s0 = 1.0f - s1;
            t1 = y - j0;
            t0 = 1.0f - t1;

            int i0i = i0;
            int i1i = i1;
            int j0i = j0;
            int j1i = j1;

            arr[IX(i, j)] = \
                s0 * (t0 * prevArr[IX(i0i, j0i)] + t1 * prevArr[IX(i0i, j1i)]) + \
                s1 * (t0 * prevArr[IX(i1i, j0i)] + t1 * prevArr[IX(i1i, j1i)]);
        }
    }
    Collide(param, arr);
}


void Fluid::StayIncompressible(float* velX, float* velY, float* p, float* div)
{
    for (int j = 1; j < Size - 1; j++) {
        for (int i = 1; i < Size - 1; i++) {
            div[IX(i, j)] = -0.5f * (velX[IX(i+1, j)] - velX[IX(i-1, j)] + velY[IX(i  , j+1)] - velY[IX(i  , j-1)]) / Size;
            p[IX(i, j)] = 0;
        }
    }
    Collide(0, div);
    Collide(0, p);
    LinearSolve(0, p, div, 1, 6);

    for (int j = 1; j < Size - 1; j++) {
        for (int i = 1; i < Size - 1; i++) {
            velX[IX(i, j)] -= 0.5f * (  p[IX(i+1, j)] - p[IX(i-1, j)]) * Size;
            velY[IX(i, j)] -= 0.5f * (  p[IX(i, j+1)] - p[IX(i, j-1)]) * Size;
        }
    }
    Collide(1, velX);
    Collide(2, velY);
}


void Fluid::Diffuse(int param, float* arr, float* prevArr, float diff, double dt)
{
    float a = dt * diff * (Size - 2) * (Size - 2);
    LinearSolve(param, arr, prevArr, a, 1 + 6 * a);
}


void Fluid::Collide(int param, float* arr)
{
    for(int i = 1; i < Size - 1; i++) {
        arr[IX(i, 0)] = param == 2 ? -arr[IX(i, 1)] : arr[IX(i, 1)];
        arr[IX(i, Size - 1)] = param== 2 ? -arr[IX(i, Size - 2)] : arr[IX(i, Size - 2)];
    }
    for(int j = 1; j < Size - 1; j++) {
        arr[IX(0  , j)] = param == 1 ? -arr[IX(1  , j)] : arr[IX(1  , j)];
        arr[IX(Size - 1, j)] = param == 1 ? -arr[IX(Size - 2, j)] : arr[IX(Size - 2, j)];
    }

    arr[IX(0, 0)] = 0.5f * (arr[IX(1, 0)] + arr[IX(0, 1)]);
    arr[IX(0, Size - 1)] = 0.5f * (arr[IX(1, Size - 1)] + arr[IX(0, Size - 2)]);
    arr[IX(Size - 1, 0)] = 0.5f * (arr[IX(Size - 2, 0)] + arr[IX(Size - 1, 1)]);
    arr[IX(Size - 1, Size - 1)] = 0.5f * (arr[IX(Size - 2, Size - 1)] + arr[IX(Size - 1, Size - 2)]);
}


void Fluid::LinearSolve(int param, float* arr, float* prevArr, float a, float c)
{
    float cRecip = 1 / c;
    int iter = (int)Iterations.GetValue();
    for(int k = 0; k < iter; k++){
        for(int j = 1; j < Size - 1; j++){
            for(int i = 1; i < Size - 1; i++){
                arr[IX(i, j)] = \
                (prevArr[IX(i, j)] + a*(arr[IX(i+1, j)] + arr[IX(i-1, j)] + arr[IX(i  , j+1)] + arr[IX(i  , j-1)])) * cRecip;
            }
        }
        Collide(param, arr);
    }
}


Fluid::~Fluid()
{

}
