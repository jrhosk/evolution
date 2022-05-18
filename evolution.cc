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
  std::map <std::string, std::vector<double>> values;

  std::cout << "Reading data file..." << std::endl;
  
  DataFile *data = new DataFile("data/kinematics.csv");
  data->ReadCSV();
  //  data->PrintCSV();


  std::cout << "Instance created." << std::endl;
  FemtoEvolve *evolve = new FemtoEvolve();

  std::cout << "Initializing ...." << std::endl;
  evolve->Init(data->GetValueMap(), true);

  std::cout << "Running ..." << std::endl;
  evolve->Run();

  return 0;
}
