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
#include <map>

#include <FemtoEvolve.hh>
#include <gpd.hh>

#define PI 3.14159265


FemtoEvolve::FemtoEvolve(){
  
}

FemtoEvolve::~FemtoEvolve(){

}

void FemtoEvolve::Init(std::map<std::string, std::vector<float>> arr, bool outfile){
  //
  // Initialize map containing the kinematic variables x and Q2,
  // this provides a key:value pair where the value is a vector
  // of values.
  //

  if(outfile){
    this->outfile.open("output.csv", std::fstream::out | std::fstream::app);
    if(!this->outfile.is_open()) std::cerr << "Error opening output csv file." << std::endl;
  }
  
  this->kinematics = arr;

  // Setup a vector containing the delta log(Q2) for each step in the
  // runge-kutta algorithm. As far as I can tell this should be done
  // as log(dq_f) - log(df_i)
  
  for(auto i = 0; i < (int)(this->kinematics["qs"].size() - 1); i++){
    this->dq.push_back(log(this->kinematics["qs"][i+1]) - log(this->kinematics["qs"][i]));
  }
}
void FemtoEvolve::Run(){
  this->RungeKutta();
  if(this->outfile.is_open()) this->outfile.close();
};

float FemtoEvolve::Alpha(float square) {

  //  float mass_thresholds[] = {pow(1.4, 2), pow(4.5, 2) , pow(170, 2)};
  
  float mass_thresholds[] = {0., 0. , 0.};

  mass_thresholds[0] = pow(1.4, 2);
  mass_thresholds[1] = pow(4.5, 2);
  mass_thresholds[2] = pow(170., 2);
  
  float lambda_nf4 = 0.215;
  float alpha_inv = 0.;
  
  if(square <= mass_thresholds[0]){
    float nflavor = 3.;
    float lambda_nf3 = lambda_nf4*pow(mass_thresholds[0]/lambda_nf4, (2./27.));
    float beta0 = 11. - float(nflavor)*2./3.;

    alpha_inv = (beta0/4.)*log(square/pow(lambda_nf3, 2));
  } else if ( (square > mass_thresholds[0]) && (square <= mass_thresholds[1]) ){
    float nflavor = 4.;
    float beta0 = 11. - float(nflavor)*2./3.;

    alpha_inv = (beta0/4.)*log(square/pow(lambda_nf4, 2));
  } else if ( (square > mass_thresholds[1]) && (square <= mass_thresholds[2]) ){
    float nflavor = 5.;
    float lambda_nf5 = lambda_nf4*pow(mass_thresholds[1]/lambda_nf4, (-2./23.));
    float beta0 = 11. - float(nflavor)*2./3.;

    alpha_inv = (beta0/4.)*log(square/pow(lambda_nf5, 2));
  } else {
    float nflavor = 6.;
    float lambda_nf6 = lambda_nf4*pow(mass_thresholds[1]/lambda_nf4, (69./625.));
    float beta0 = 11. - float(nflavor)*2./3.;

    alpha_inv = (beta0/4.)*log(square/pow(lambda_nf4, 2));
  }

  float alpha = 1./alpha_inv;

  return alpha*PI;
}

float FemtoEvolve::Stage(float q, float u, float x){
  // Calculate the endpoint value for the input variables. The input
  // float q represents the log(Q2) value.
  return ( (4./3.)*(Alpha(exp(q))/(2*PI)) )*( u*(2*log(1 - x) + 1.5)  );
}

float FemtoEvolve::Integral(float y, float u){
  float x = 1; // needs to be the globally updated x
  float dy = 0;
  
  int i = 0; // Just so the code complies and we can test data file
  
  float upper = (1 + std::pow(x/y, 2))*this->cache[i] - 2*u;
  float lower = 1 - x/y;

  (dy/y)*(upper/lower);
  return 0.;
}

void FemtoEvolve::RungeKutta(){
  int n = this->kinematics["qs"].size();
  int m = this->kinematics["x"].size();
  
  // Set the initial value for x. We are doing this for
  // a single x value so I just use the first index value.
  float x = this->kinematics["x"][0]; // Only one choice for x at the moment

  // Set U(x, Q2) to xU(x, Q2) and use for runge-kutta.
  float u = 0.; // This needs to become a vector of size x.size()
  float h = 0.;
  float q = 0.;
    
  for(auto i = 0; i < (n - 1); i++){
    for(auto j = 0; j < m; m++){ // This should be where we iterate on the x part of the grid
      u = x*gpdHu(this->kinematics["x"][0], 0., 0.);
      x = this->kinematics["x"][i];

      // The grid steps are set to delta log(Q2).
      h = this->dq[i];

      // Variable Q2 is set to log(Q2)
      q = log(this->kinematics["qs"][i]);

      float k1 = this->Stage(q, u, x);
      float k2 = this->Stage(q + 0.5*h, u + 0.5*h*k1, x);
      float k3 = this->Stage(q + 0.5*h, u + 0.5*h*k2, x);
      float k4 = this->Stage(q + h, u + h*k3, x);
    
      u += (h/6.)*(k1 + 2.*k2 + 2.*k3 + k4);

      // Cache the U(Q2, x) values for each x grid point
      this->cache[j] = u;
      
      this->outfile << x << "\t"
		    << this->kinematics["qs"][i] << "\t"
		    << u << std::endl;
    
      std::cout <<  exp(q) << " " << u << std::endl;
    }

  }
}

#endif
