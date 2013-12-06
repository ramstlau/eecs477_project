#include "input.h"
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void validate(HittingSetData &data, vector<int> &set_antennas, unsigned int &num_covered_base_stations)
{
	unordered_map<int, int> bs_coverage_freq;
	unordered_set<int> onecovered_bs;
	vector<int> oc;
	
	for(unsigned int i = 0; i < set_antennas.size(); i++)
	  {
	    int antenna = set_antennas.at(i);
	    for(unsigned int j = 0; j < data.antennas.at(antenna).base_stations.size(); j++)
	      {
	        int bs = data.antennas.at(antenna).base_stations.at(j);
	        if(bs_coverage_freq.find(bs) == bs_coverage_freq.end())
	          {
	            bs_coverage_freq[bs] = 1;
	            onecovered_bs.insert(bs);
	            
	          }
	        else
	          {
	            bs_coverage_freq[bs]++;
	            onecovered_bs.erase(bs);
	          }
	      
	      }

	  }

	  
  if(num_covered_base_stations != onecovered_bs.size())
    throw (unsigned int)onecovered_bs.size();



}
