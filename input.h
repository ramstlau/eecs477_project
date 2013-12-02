#ifndef _INPUT_H_
#define _INPUT_H_

#include <vector>
#include <string>
#include <unordered_set>
using namespace std;

struct Antenna {
	int num;
	vector<int> base_stations;
};

struct Base_Station {
	int num;
	vector<int> coverage; //which antennas cover them 
};
class HittingSetData {

	public:
  	int num_antennas, num_base_stations;
  	vector<Antenna> antennas;
  	
  	//greedy2  might entertain idea of having this global for greedy2

  	vector<bool> covered;
  	vector<Base_Station> base_stations;	//used for sorting 
  	unordered_set<int> selected_antennas;
  	
  	HittingSetData();
  	void readData();
  	void printData();
  	void printBaseStations();
};
#endif /* _INPUT_H_ */
