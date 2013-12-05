#include "input.h"
#include "greedy1.h"
#include "greedy2.h"
#include "pq.h"
#include "bottomup2.h"
#include "topdown.h"
#include "maxdelta.h"
#include "maxdelta2.h"
#include "driver.h"
#include <iostream>
#include <ctime>

using namespace std;

int main(int argc, char *argv[])
{
	clock_t algo_begin = clock();
	HittingSetData data;
	data.readData();
  
	vector<int> set_antenna1, set_antenna2;
  	int num_covered_base_stations1 = 0, num_covered_base_stations2 = 0;

	//try with topdown first
  	topdown_int_init(data, set_antenna1, num_covered_base_stations1, algo_begin);  
  		
  	//try with maxdelta2
  	randomize_seed_data(data, set_antenna2);  	
  	maxdelta2_int(data, set_antenna2, num_covered_base_stations2, algo_begin);
  	
  	vector<int> set_antenna;
  	int num_covered_base_stations = 0;
  	
  	if(num_covered_base_stations1 > num_covered_base_stations2)
  	  {
  	    set_antenna.swap(set_antenna1);
  	    num_covered_base_stations = num_covered_base_stations1;
  	  }
  	else
  	  {
  	    set_antenna.swap(set_antenna2);
  	    num_covered_base_stations = num_covered_base_stations2;
  	  }
  	
  	//finish
  	cout << set_antenna.size() << ' ';
  	printVector(set_antenna);
  	cout << num_covered_base_stations << endl;
	//cout << (num_covered_base_stations1 > num_covered_base_stations2) << endl;
	
	return 0;
}
