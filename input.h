#include <vector>
#include <string>
using namespace std;

struct Antenna {
	int num;
	vector<int> base_stations;
};

class HittingSetData {

	public:
  	int num_antennas, num_base_stations;
  	vector<Antenna> antennas;
  	
  	HittingSetData();
  	void readData();
  	void printData();
};

