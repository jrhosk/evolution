#ifndef DataFile_hh
#define DataFile_hh

#include <fstream>
#include <ostream>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <cstring>

// BOOST c++ libraries

#include <boost/any.hpp>
#include <boost/algorithm/string.hpp>

class DataFile: private std::fstream {

private:

  std::vector <double> x;
  std::vector <double> qSquared;

public:

  DataFile(const char* filename = 0, ios_base::openmode mode = ios_base::in) : std::fstream(filename, mode)
  {

    if( (good()) ){
      std::cout << "Opening file: " << filename<< std::endl;
    }
    else{
      std::cerr << "Error opening file: " << std::endl;
      exit(1);
    }
  };

  ~DataFile(){close();};

  void ReadCSV();
  void PrintCSV() const;

  //  int GetArraySize() const;

  std::vector <double> GetXVector() const;
  std::vector <double> GetQSquaredVector() const;

  std::vector<std::string> LineVector;
  
};

#endif

