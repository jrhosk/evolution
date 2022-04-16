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

std::map <std::string, std::vector<float>> read_data(){
  std::map <std::string, std::vector<float>> value;
  std::fstream input;
  std::string line;

  char *token;
  
  input.open("data/quv_evol.csv", std::fstream::in);

  if(!input.is_open()){
    perror("Not open.");
  }


  std::cout << "Opening data file." << std::endl;

  while(!input.eof()){

    std::getline(input, line);
    token = new char[line.size() + 1];
    strcpy(token, line.c_str());

    token = strtok(token, ",");
    std::cout << atof(token) << std::endl;
    token = strtok(NULL, ",");
    std::cout << atof(token) << std::endl;
    token = strtok(NULL, ",");
    std::cout << atof(token) << std::endl;
    
  }
  input.close();
  
  return value;
}

int main(int argc, char *argv[]){
  std::map <std::string, std::vector<float>> values;

  // such a terrible way to do this ...
  float qs[] = {
    0.093619999999999995,
    0.16796523857980172,
    0.30134929898707241,
    0.54065591647318556,  
    0.96999999999999975,
    1.1623483397359242,
    1.3928388277184118,
    1.6690349473383783,
    2.00000000000000000};
  
  values["x"] = std::vector<float>(9, 0.20951355844953223);
  values["qs"] = std::vector<float>(qs, qs + sizeof(qs) / sizeof(float) );

  std::cout << "Instance created." << std::endl;
  FemtoEvolve *evolve = new FemtoEvolve();

  std::cout << "Initializing ...." << std::endl;
  evolve->Init(values);

  std::cout << "Running ..." << std::endl;
  evolve->Run();

  // for(auto i = 0; i < (int)(evolve->kinematics["qs"].size()); i++){
  //   std::cout << "Alpha: " << evolve->kinematics["qs"][i] << " " << evolve->Alpha(evolve->kinematics["qs"][i]) << std::endl;
  // }

  return 0;
}
