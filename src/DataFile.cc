#ifndef data_file_cc
#define data_file_cc

#include <sstream> 

#include "DataFile.hh"

#define X_INDEX 0
#define QS_INDEX 1

void DataFile::ReadCSV(){
  bool bFirstLineRead = false;

  std::string line;
  
  while(!eof()){
    if(!bFirstLineRead){
      
      std::getline(*this, line);
      boost::split(LineVector, line, boost::is_any_of(","));

      bFirstLineRead = true;

    } else {
      std::getline(*this, line);
      boost::split(LineVector, line, boost::is_any_of(","));

      this->values["x"].push_back(atof(LineVector[X_INDEX].c_str()));
      this->values["qs"].push_back(atof(LineVector[QS_INDEX].c_str()));
    }
  }
  
}

void DataFile::PrintCSV(){
  for(auto i = 0; i < (int)(this->values["x"].size()); i++){
    std::cout << this->values["x"][i] << "\t" << this->values["qs"][i] << std::endl;
  }
}

std::vector <double> DataFile::GetValue(const std::string column)
{
  return this->values[column];
}

std::map<std::string, std::vector <double>> DataFile::GetValueMap()
{
  return this->values;
}

#endif
