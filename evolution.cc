#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <cmath>
#include <functional>
#include <fstream>
#include <sstream>
#include <map>
#include <cstring>
#include <sstream>

#include <FemtoEvolve.hh>
#include <DataFile.hh>

int main(int argc, char *argv[]){
  std::map <std::string, std::vector<float>> values;

  // such a terrible way to do this ...
  // float qs[] = {
  //   0.093619999999999995,
  //   0.16796523857980172,
  //   0.30134929898707241,
  //   0.54065591647318556,  
  //   0.96999999999999975,
  //   1.1623483397359242,
  //   1.3928388277184118,
  //   1.6690349473383783,
  //   2.00000000000000000};
  
  // values["x"] = std::vector<float>(9, 0.20951355844953223);
  // values["qs"] = std::vector<float>(qs, qs + sizeof(qs) / sizeof(float) );

  std::cout << "Reading data file..." << std::endl;
  
  DataFile *data = new DataFile("data/kinematics.csv");
  data->ReadCSV();
  data->PrintCSV();

  /*
  std::cout << "Instance created." << std::endl;
  FemtoEvolve *evolve = new FemtoEvolve();

  std::cout << "Initializing ...." << std::endl;
  evolve->Init(values, true);

  std::cout << "Running ..." << std::endl;
  evolve->Run();
  */
  // for(auto i = 0; i < (int)(evolve->kinematics["qs"].size()); i++){
  //   std::cout << "Alpha: " << evolve->kinematics["qs"][i] << " " << evolve->Alpha(evolve->kinematics["qs"][i]) << std::endl;
  // }

  return 0;
}
