#ifndef femto_evolve_hh
#define femto_evolve_hh

class FemtoEvolve {

public:
  FemtoEvolve();
  ~FemtoEvolve();
  
  void Init(std::map<std::string, std::vector<float>>);
  void Run();

  float Alpha(float square);

  std::map<std::string, std::vector<float>> kinematics;
  
 private:
  int index_cache;

  std::fstream outfile;
  
  std::vector<float> dq;
  std::vector<float> _u;

  
  float Integral(float x, float u);
  float Stage(float q, float u, float x);

  void RungeKutta();
  
};

#endif
