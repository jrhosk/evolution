#ifndef femto_evolve_hh
#define femto_evolve_hh

class FemtoEvolve {

public:
  FemtoEvolve();
  ~FemtoEvolve();
  
  void Init(std::map<std::string, std::vector<double>>, bool);
  void Run();

  double Alpha(double square);

  std::map<std::string, std::vector<double>> kinematics;
  
 private:
  std::fstream outfile;

  double endpoint;
  double integral;

  // Structure to organize current iteration state information
  struct IterationState {
    int index;

    std::vector<double> u;
    std::vector<double> cache;
    
  };

  IterationState iteration;
  
  std::vector<double> dq;
  std::vector<double> dy;
  
  double Integral(double u);
  double Stage(double q, double u, double x);

  void RungeKutta();
  
};

#endif
