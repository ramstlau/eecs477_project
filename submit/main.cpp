#include "input.h"
#include "greedy1.h"
#include "greedy2.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
	
	HittingSetData data;
	data.readData();
	vector<int> set_antenna;
	int num_covered_base_stations = 0;
	
	greedy1(data, set_antenna, num_covered_base_stations);
	
	
	cout << set_antenna.size() << " ";
	printVector(set_antenna);
	cout << num_covered_base_stations << endl;
	  

	return 0;
}
