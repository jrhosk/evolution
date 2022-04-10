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
  //
  // Here we initialize a vector, grid, that contains the values for x along
  // with a vector containing the initial values for the gpdHu.
  //
  
}
void FemtoEvolve::Run(){
  this->RungeKutta();
};

float FemtoEvolve::Alpha(float square, float lambda) {
  return 0.;
}

float FemtoEvolve::Stage(float x, float u){
  return 0.;
}

float FemtoEvolve::Integral(float x, float u){
  return 0.;;
}

void FemtoEvolve::RungeKutta(){
  int n = 1;

  float u = 0;
  float h = 0.;
  float q = log(0.09362);
  float dq = int(log(q) - log(1)/n);
    
    for(auto i = 0; i < n; i++){
      h = dq;
        
      float k1 = this->Stage(q, u);
      float k2 = this->Stage(q + 0.5*h, u + 0.5*h*k1);
      float k3 = this->Stage(q + 0.5*h, u + 0.5*h*k2);
      float k4 = this->Stage(q + h, u + h*k3);

      u += (h/6.)*(k1 + 2.*k2 + 2.*k3 + k4);
    }
}

#endif
