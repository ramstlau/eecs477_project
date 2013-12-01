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
          antennas.at(i).base_stations.push_back(atoi(is.str().c_str()));
          is.str(string());
        }
      }
      else
       is << c;
    }
    if(!is.str().empty()) {
      antennas.at(i).base_stations.push_back(atoi(is.str().c_str()));
      is.str(string());
    }
    
    getline(cin, line);
   
   }
   


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
