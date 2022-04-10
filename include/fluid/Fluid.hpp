#ifndef FLUID_HPP
#define FLUID_HPP

#include <../../include/fluid/Field.hpp>
#include <../../include/core/ChangeAble.hpp>


class Fluid
{
private:
    int Size;

    ChangeAbleFloat Viscosity;
    ChangeAbleFloat Diffusion;
    ChangeAbleFloat Iterations;

    Field* Grid;

    int IX(int x, int y) {return x + Size * y;}

    void Collide(int param, float* arr);
    void LinearSolve(int param, float* arr, float* prevArr, float a, float c);
    void Diffuse(int param, float* arr, float* prevArr, float diff, double dt);
    void StayIncompressible(float* velX, float* velY, float* p, float* div);
    void Advect(int param, float* arr, float* prevArr, float* velX, float* velY, double dt);

public:
    Fluid(float viscosity, float diffusion, Field* grid);
    ~Fluid();

    void SetViscosity(int percent) {Viscosity.SetValueByPercent(percent);}
    void SetDiffusion(int percent) {Diffusion.SetValueByPercent(percent);}
    void SetIterations(int percent) {Iterations.SetValueByPercent(percent);}

    void Update(double dt);
};


#endif // FLUID_HPP
