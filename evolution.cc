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
/*
float stage(float x, float u){
    return x + u;
}

float integral(std::function<float(float, float)> function, float start, float stop){
     float integral = 0.;

    for(auto j = start; j < stop; j++){
        float dx = 0.001;
        integral += function(0.001*j, 2)*dx;
    }

    return integral;
}

void runge_kutta(std::function<float(float, float)> fun, std::vector<float> v){
    float h = 0.1;
    float y = 1.;

    for(auto i = 0; i < (int)v.size(); i++){
        float x = h*v[i];
        
        float k1 = fun(x, y);
        float k2 = fun(x + 0.5*h, y + 0.5*h*k1);
        float k3 = fun(x + 0.5*h, y + 0.5*h*k2);
        float k4 = fun(x + h, y + h*k3);

        y += (h/6.)*(k1 + 2.*k2 + 2.*k3 + k4);

        std::cout << "x: " << x << "  >> Y(x_i): " << y << std::endl;
    }

};
*/
int main(int argc, char *argv[]){
    float vals[] = {1., 2., 3., 4., 5., 6., 7., 8., 9., 10.};

    std::vector<float> v(vals, vals + sizeof(vals) / sizeof(float));
    std::vector <float> x = read_data();

    //  std::function<float(float, float)> fn = stage;
    //  runge_kutta(fn, v);

    std::cout << "Instance created." << std::endl;
    FemtoEvolve *evolve = new FemtoEvolve();

    std::cout << "Initializing ...." << std::endl;
    evolve->Init(v);

    std::cout << "Running ..." << std::endl;
    evolve->Run();

    return 0;
}
