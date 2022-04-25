#ifndef femto_evolve_hh
#define femto_evolve_hh

class FemtoEvolve {

public:
  FemtoEvolve();
  ~FemtoEvolve();
  
  void Init(std::map<std::string, std::vector<float>>, bool);
  void Run();

  float Alpha(float square);

  std::map<std::string, std::vector<float>> kinematics;
  
 private:
  std::fstream outfile;
  
  std::vector<float> dq;
  std::vector<float> cache;
  
  float Integral(float x, float u);
  float Stage(float q, float u, float x);

  void RungeKutta();
  
};

#endif
