#include "input.h"
#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <cstdlib>

HittingSetData::HittingSetData():
	 num_antennas(0), num_base_stations(0) {
 
}

void HittingSetData::readData() {

  cin >> num_antennas >> num_base_stations;

  antennas.reserve(num_antennas);
  antennas.resize(num_antennas);
  base_stations.resize(num_base_stations);

  string line;
  ostringstream is;
  
  //calling getline twice is hacky
  getline(cin, line);
  getline(cin, line);

  for(unsigned int i = 0; i < antennas.size(); i++) {
    bool first = true;
    antennas.at(i).num = i;
    for(unsigned int j = 0; j < line.size(); j++) {
      char c = line.at(j);
      if(c == ' ') {
        if(!is.str().empty()) {
          if(first) {
            first = false;
            is.str(string());
            continue;
          }
          int bsNum = atoi(is.str().c_str());
          antennas.at(i).base_stations.push_back(bsNum);
          base_stations.at(bsNum).coverage.push_back(i);
          is.str(string());
        }
      }
      else
       is << c;
    }
    if(!is.str().empty()) {
      int bsNum = atoi(is.str().c_str());
      antennas.at(i).base_stations.push_back(bsNum);
      base_stations.at(bsNum).coverage.push_back(i);
      is.str(string());
    }
    
    getline(cin, line);
   
   }
   
   //initialize base station nums
   for(unsigned int k = 0; k < base_stations.size(); k++)
     {
       base_stations.at(k).num = k;
     }

   //initialize vector bool
   covered.resize(num_base_stations, false);
   
}
void HittingSetData::printData() {
  
  cout << num_antennas << " " << num_base_stations << endl;
  for (unsigned int i = 0; i < antennas.size(); i++) {
    for (unsigned int j = 0; j < antennas.at(i).base_stations.size(); j++) {
      cout << antennas.at(i).base_stations.at(j) << ' ';
    }
    cout << endl;
   }


}
void HittingSetData::printBaseStations(){

  for (unsigned int i = 0; i < base_stations.size(); i++) {
    for (unsigned int j = 0; j < base_stations.at(i).coverage.size(); j++) {
      cout << base_stations.at(i).coverage.at(j) << ' ';
    }
    cout << endl;
   }

}
