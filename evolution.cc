#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <cmath>
#include <functional>
#include <fstream>
#include <sstream>

#include <FemtoEvolve.hh>

std::vector <float> read_data(){
    std::vector <float> value;
    std::fstream input;
    std::string line;

    input.open("data/x_data.csv", std::fstream::in);

    if(!input.is_open()){
         perror("Not open.");
    }
    

    std::cout << "Opening data file." << std::endl;
    while(input.good()){
        std::getline(input, line);
        value.push_back(stof(line));
    }
    input.close();
    
    return value;
}

int main(int argc, char *argv[]){
    std::vector <float> x = read_data();


    std::cout << "Instance created." << std::endl;
    FemtoEvolve *evolve = new FemtoEvolve();

    std::cout << "Initializing ...." << std::endl;
    evolve->Init(x);

    std::cout << "Running ..." << std::endl;
    evolve->Run();

    return 0;
}
