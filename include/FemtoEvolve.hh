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

  int index;
  
  float endpoint;
  float integral;
  
  std::vector<double> dq;
  std::vector<double> dy;
  std::vector<double> cache;
  std::vector<double> u;
  
  double Integral(double u);
  double Stage(double q, double u, double x);

  void RungeKutta();
  
};

#endif
