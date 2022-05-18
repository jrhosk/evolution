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

#include <boost/math/constants/constants.hpp>

#include <FemtoEvolve.hh>
#include <gpd.hh>

FemtoEvolve::FemtoEvolve(){
  
}

FemtoEvolve::~FemtoEvolve(){

}

void FemtoEvolve::Init(std::map<std::string, std::vector<double>> arr, bool outfile){
  //
  // Initialize map containing the kinematic variables x and Q2,
  // this provides a key:value pair where the value is a vector
  // of values.
  //

  if(outfile){
    this->outfile.open("output.csv", std::fstream::out | std::fstream::app);
    if(!this->outfile.is_open()) std::cerr << "Error opening output csv file." << std::endl;
    this->outfile << "x\tqs\tendpoint\tintegral\txu" << std::endl;
    //this->outfile << "x\tqs\txu" << std::endl;
  }
  
  this->kinematics = arr;

  //
  // Fill in cached values for integral term.
  //
  
  for(auto i = 0; i < (int)(this->kinematics["x"].size()); i++) {
    // this->iteration.cache.push_back(this->kinematics["x"][i]*gpdHu(this->kinematics["x"][i], 0., 0.));
    // this->iteration.u.push_back(this->kinematics["x"][i]*gpdHu(this->kinematics["x"][i], 0., 0.));

    this->iteration.cache.push_back(gpdHu(this->kinematics["x"][i], 0., 0.));
    this->iteration.u.push_back(gpdHu(this->kinematics["x"][i], 0., 0.));
    // std::cout << "cache: " << this->iteration.cache.back() << std::endl;
  }
  
  // Setup a vector containing the delta log(Q2) for each step in the
  // runge-kutta algorithm. As far as I can tell this should be done
  // as log(dq_f) - log(df_i)
  
  for(auto i = 0; i < (int)(this->kinematics["qs"].size() - 1); i++){
    this->dq.push_back(log(this->kinematics["qs"][i+1]) - log(this->kinematics["qs"][i]));
    this->dy.push_back(this->kinematics["x"][i+1] - this->kinematics["x"][i]);
  }
}
void FemtoEvolve::Run(){
  this->RungeKutta();
  if(this->outfile.is_open()) this->outfile.close();
};

double FemtoEvolve::Alpha(double square) {

  double mass_thresholds[] = {0., 0. , 0.};

  mass_thresholds[0] = pow(1.4, 2);
  mass_thresholds[1] = pow(4.5, 2);
  mass_thresholds[2] = pow(170., 2);
  
  double lambda_nf4 = 0.215;
  double alpha_inv = 0.;
  
  if(square <= mass_thresholds[0]){
    double nflavor = 3.;
    double lambda_nf3 = lambda_nf4*pow(mass_thresholds[0]/lambda_nf4, (2./27.));
    double beta0 = 11. - double(nflavor)*2./3.;

    alpha_inv = (beta0/4.)*log(square/pow(lambda_nf3, 2));
  } else if ( (square > mass_thresholds[0]) && (square <= mass_thresholds[1]) ){
    double nflavor = 4.;
    double beta0 = 11. - double(nflavor)*2./3.;

    alpha_inv = (beta0/4.)*log(square/pow(lambda_nf4, 2));
  } else if ( (square > mass_thresholds[1]) && (square <= mass_thresholds[2]) ){
    double nflavor = 5.;
    double lambda_nf5 = lambda_nf4*pow(mass_thresholds[1]/lambda_nf4, (-2./23.));
    double beta0 = 11. - double(nflavor)*2./3.;

    alpha_inv = (beta0/4.)*log(square/pow(lambda_nf5, 2));
  } else {
    double nflavor = 6.;
    double lambda_nf6 = lambda_nf4*pow(mass_thresholds[1]/lambda_nf4, (69./625.));
    double beta0 = 11. - double(nflavor)*2./3.;

    alpha_inv = (beta0/4.)*log(square/pow(lambda_nf4, 2));
  }

  double alpha = 1./alpha_inv;

  return alpha*boost::math::constants::pi<double>();
}

double FemtoEvolve::Stage(double q, double u, double x){
  // Calculate the endpoint value for the input variables. The input
  // double q represents the log(Q2) value.

  float coeff = (4./3.)*(Alpha(exp(q))/(2*boost::math::constants::pi<double>()));
  float endpoint = u*(2*log(1 - x) + 1.5);
  float integral = this->Integral(u);

  // For sanity checks
  this->endpoint = coeff*endpoint;
  this->integral = coeff*integral;
  
  return (4./3.)*(Alpha(exp(q))/(2*boost::math::constants::pi<double>()))*(this->Integral(u) + u*(2*log(1 - x) + 1.5) );
}

double FemtoEvolve::Integral(double u){
  double upper = 0.;
  double lower = 0.;
  double integral = 0.;
  double y = 0.; 
  
  int index = this->iteration.index;
  
  double x = this->kinematics["x"][index];

  for(auto i = index; i < (int)(this->kinematics["x"].size() - 1); i++){
    y = this->kinematics["x"][i+1];
    upper = (1 + std::pow(x/y, 2))*(this->iteration.cache[i]) - 2.*u;
    lower = 1 - x/y;

    integral += (dy[i]/y)*(upper/lower);
  }
  return integral;
 }

void FemtoEvolve::RungeKutta(){
  int n = this->kinematics["qs"].size();
  int m = this->kinematics["x"].size();
  
  // Set the initial value for x. We are doing this for
  // a single x value so I just use the first index value.
  double x = this->kinematics["x"][0]; // Only one choice for x at the moment

  // Set U(x, Q2) to xU(x, Q2) and use for runge-kutta.
  double u = 0.; // This needs to become a vector of size x.size()
  double h = 0.;
  double q = 0.;
    
  for(auto i = 0; i < (n - 1); i++){
    for(auto j = 0; j < (m - 1); j++){ // This should be where we iterate on the x part of the grid
      u = this->iteration.u[j];

      // Internal index for x iteration
      this->iteration.index = j; 
      
      x = this->kinematics["x"][j];

      // The grid steps are set to delta log(Q2).
      h = this->dq[i];
      
      // Variable Q2 is set to log(Q2)
      q = log(this->kinematics["qs"][i]);

      double k1 = this->Stage(q, u, x);
      double k2 = this->Stage(q + 0.5*h, u + 0.5*h*k1, x);
      double k3 = this->Stage(q + 0.5*h, u + 0.5*h*k2, x);
      double k4 = this->Stage(q + h, u + h*k3, x);
    
      u += (h/6.)*(k1 + 2.*k2 + 2.*k3 + k4);
      this->iteration.u[j] = u;
      
      this->outfile << x << "\t"
       		    << this->kinematics["qs"][i] << "\t"
		    << this->endpoint << "\t"
		    << this->integral << "\t"
       		    << this->iteration.u[j] << std::endl;

      // std::cout << x << "\t"
      // 		<< this->kinematics["qs"][i] << "\t"
      // 		<< this->u[j] << std::endl;    
    }
    // Cache the U(Q2, x) values for each x grid point
    this->iteration.cache = this->iteration.u;
    //    this->u.clear();
  }
}

#endif
