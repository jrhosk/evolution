#ifndef data_file_cc
#define data_file_cc

#include <sstream> 

#include "DataFile.hh"

#define X_INDEX 0
#define QS_INDEX 1

void DataFile::ReadCSV(){
  bool bFirstLineRead = false;
  //  std::fstream input;
  //input.open("data/evodata.csv", std::fstream::in);

  //  if(!input.is_open()){
  //  perror("Not open.");
  //}

  std::string line;
  
  while(!eof()){
    if(!bFirstLineRead){
      
      std::getline(*this, line);
      boost::split(LineVector, line, boost::is_any_of(","));

      bFirstLineRead = true;

      std::cout << "HEADER LINE: " << LineVector.front() << "\t" << LineVector.back() << std::endl;
    } else {
      std::getline(*this, line);
      boost::split(LineVector, line, boost::is_any_of(","));

      this->x.push_back(atof(LineVector[X_INDEX].c_str()));
      this->qSquared.push_back(atof(LineVector[QS_INDEX].c_str()));
    }
  }
  
}

void DataFile::PrintCSV() const {
  for(auto i = 0; i < (int)(this->x.size()); i++){
    std::cout << this->x[i] << "\t" << this->qSquared[i] << std::endl;
  }
}

std::vector <double> DataFile::GetXVector() const
{
  return this->x;
}

std::vector <double> DataFile::GetQSquaredVector() const
{
  return this->qSquared;
}

#endif
