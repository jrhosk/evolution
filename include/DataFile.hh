#ifndef DataFile_hh
#define DataFile_hh

#include <fstream>
#include <ostream>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <cstring>
#include <map>

// BOOST c++ libraries

#include <boost/any.hpp>
#include <boost/algorithm/string.hpp>

class DataFile: private std::fstream {

private:

  std::map<std::string, std::vector <double>> values;

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
  void PrintCSV();

  //  int GetArraySize() const;

  std::vector <double> GetValue(const std::string);
  std::map<std::string, std::vector <double>> GetValueMap();
  
  std::vector<std::string> LineVector;
  
};

#endif

