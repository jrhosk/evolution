#ifndef femto_evolve_cc
#define femto_evolve_cc

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <functional>
#include <fstream>
#include <sstream>

#include <FemtoEvolve.hh>
#include <gpd.hh>


FemtoEvolve::FemtoEvolve(){

}

FemtoEvolve::~FemtoEvolve(){

}

void FemtoEvolve::Init(std::vector<float> arr){
  this->grid = arr;
};

void FemtoEvolve::Run(){
  this->RungeKutta();
};

float FemtoEvolve::Alpha(float square, float lambda) {
    return 4*3.141/(9*log(square/pow(lambda, 2)));
}

float FemtoEvolve::Stage(float x, float u){
  float alpha = 0.2;
  float integral = 1;
  float zeta = 0.;
  float t = 0.;

  for(auto i = 0; i < (int)this.grid.size(); i++) this->_u.push_back(gpdHu(x, zeta, t));
  
  return ((4./3.)*alpha/(2*3.141))*( integral + u*(2*log(1 - x) + 1.5));
}

float FemtoEvolve::Integral(std::function<float(float, float)> function, float start, float stop){
  float integral = 0;

  for(auto j=start; j < stop; j++){
    float dx = 0.001;
    integral += function(0.001*j, 2)*dx;
  }

  return integral;
}

void FemtoEvolve::RungeKutta(){
    float h = 0.1;
    float y = 1.;

    std::cout << "Grid size: " << this->grid.size() << std::endl;
    
    for(auto i = 0; i < (int)this->grid.size(); i++){
        float x = h*this->grid[i];
        
        float k1 = this->Stage(x, y);
        float k2 = this->Stage(x + 0.5*h, y + 0.5*h*k1);
        float k3 = this->Stage(x + 0.5*h, y + 0.5*h*k2);
        float k4 = this->Stage(x + h, y + h*k3);

        y += (h/6.)*(k1 + 2.*k2 + 2.*k3 + k4);

        std::cout << "x: " << x << "  >> Y(x_i): " << y << std::endl;
    }
}

#endif
