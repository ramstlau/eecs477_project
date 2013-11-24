#include <vector>
#include <string>
using namespace std;

class HittingSetData {

	public:
  	int num_antennas, num_base_stations;
  	vector<vector<int> > antennas;
  	
  	HittingSetData();
  	void readData(string filename);
  	void printData();
};

//HittingSetData readData(string filename);
