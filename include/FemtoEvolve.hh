#ifndef femto_evolve_hh
#define femto_evolve_hh

class FemtoEvolve {

public:
  FemtoEvolve();
  ~FemtoEvolve();
  
  void Init(std::vector<float>);
  void Run();
  
 private:
  int index_cache;

  std::fstream outfile;
  
  std::vector<float> grid;
  std::vector<float> dgrid;
  std::vector<float> _u;
  
  float Alpha(float square, float lambda);
  float Integral(float x, float u);
  float Stage(float x, float u);

  void RungeKutta();
  
};

#endif
