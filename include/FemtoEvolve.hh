#ifndef femto_evolve_hh
#define femto_evolve_hh

class FemtoEvolve {

public:
  FemtoEvolve();
  ~FemtoEvolve();
  
  void Init(std::vector<float>);
  void Run();
  
 private:
  std::vector<float> grid;
  std::vector<float> _u;
  
  float Alpha(float square, float lambda);
  float Integral(std::function<float(float, float)>, float start, float stop);
  float Stage(float x, float u);

  void RungeKutta();
  
};

#endif
