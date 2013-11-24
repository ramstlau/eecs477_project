#include "input.h"
#include <iostream>
#include <fstream>
#include <set>
#include <sstream>

HittingSetData::HittingSetData():
	 num_antennas(0), num_base_stations(0) {
 
}

void HittingSetData::readData(string filename) {
  cout.sync_with_stdio(false);
  ifstream fin;
  fin.open(filename);
  if (!fin.is_open()) {
    throw "Could not open file";
  }

  fin >> num_antennas >> num_base_stations;
  antennas.reserve(num_antennas);
  antennas.resize(num_antennas);
  cout << "vector size " << antennas.size() << endl;

  string line;
  ostringstream is;
  
  //calling getline twice is hacky
  getline(fin, line);
  getline(fin, line);
  //cout << line << line.size() << endl;
  for(unsigned int i = 0; i < antennas.size(); i++) {
    bool first = true;
    for(unsigned int j = 0; j < line.size(); j++) {
      char c = line.at(j);
      if(c == ' ') {
        if(!is.str().empty()) {
          if(first) {
            first = false;
            is.str(string());
            continue;
          }
          antennas.at(i).push_back(atoi(is.str().c_str()));
          is.str(string());
        }
      }
      else
       is << c;
    }
    if(!is.str().empty()) {
      antennas.at(i).push_back(atoi(is.str().c_str()));
      is.str(string());
    }
    
    getline(fin, line);
   
   }
   
   fin.close();

}
void HittingSetData::printData() {
  cout << "Dimensions: " << antennas.size() << endl;
  for (unsigned int i = 0; i < antennas.size(); i++) {
  	cout << "loop: ";
    for (unsigned int j = 0; j < antennas.at(i).size(); j++) {
      cout << antennas.at(i).at(j) << ' ';
    }
    cout << endl;
   }


}
