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

struct Trial
{
	int num_covered_base_stations;
	vector<int> set_antenna;
};
int main(int argc, char *argv[])
{
	clock_t algo_begin = clock();
	HittingSetData data;
	data.readData();
  
  	vector<Trial> trials;
  	Trial trial1;

	//try with topdown first
  	topdown_int_init(data, trial1.set_antenna, trial1.num_covered_base_stations, algo_begin);  
  		
  	//try with maxdelta2
  	double elapsed_secs = double(clock() - algo_begin) / CLOCKS_PER_SEC;
  	while(elapsed_secs < 10)
  	  {
  	    Trial trialx;
  	    
  	    randomize_seed_data(data, trialx.set_antenna);  	
  	    maxdelta2_int(data, trialx.set_antenna, trialx.num_covered_base_stations, algo_begin);
  	    
  	    trials.push_back(trialx);
  	    
  	    elapsed_secs = double(clock() - algo_begin) / CLOCKS_PER_SEC;
  	  }
  	

  	
  	//find maximum result
  	int max_trial = -1;
  	int max_bs_count = -1;
  	
  	for(unsigned int i = 0; i < trials.size(); i++)
  	  {
  	    //cout << "trial " << i << " : " << trials.at(i).num_covered_base_stations << endl;
  	    if(trials.at(i).num_covered_base_stations > max_bs_count)
  	      {
  	        max_trial = i;
  	        max_bs_count = trials.at(i).num_covered_base_stations;
  	      }
  	  
  	  }
  	
  	vector<int> set_antenna;
  	int num_covered_base_stations = trials.at(max_trial).num_covered_base_stations;
  	set_antenna.swap(trials.at(max_trial).set_antenna);
  	
  	//finish
  	cout << set_antenna.size() << ' ';
  	printVector(set_antenna);
  	cout << num_covered_base_stations << endl;
  	//cout << "selected trial " << max_trial << " out of " << trials.size() << endl;
	
	return 0;
}
