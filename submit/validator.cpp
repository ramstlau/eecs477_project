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
	    //cout << "antenna : " << antenna << " : ";
	    for(unsigned int j = 0; j < data.antennas.at(antenna).base_stations.size(); j++)
	      {
	        int bs = data.antennas.at(antenna).base_stations.at(j);
	        //cout << bs << " ";
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
	  //cout << endl;
	  }
/*
	for(unordered_map<int, int>::iterator it = bs_coverage_freq.begin(); it != bs_coverage_freq.end(); it++)
	  cout << "base station: " << it->first << " has freq : "<< it->second << endl;
	cout << endl;
	//cout << "printing oc in validator : ";
	for(unordered_set<int>::iterator it = onecovered_bs.begin(); it != onecovered_bs.end(); it++)
	  {
	    //cout << *it << " ";
	    oc.push_back(*it); 
	  }
	//cout << endl;
	
	sort(oc.begin(), oc.end());
	//for(unordered_set<int>::iterator it = onecovered_bs.begin(); it != onecovered_bs.end(); it++)*/
	  
  if(num_covered_base_stations != onecovered_bs.size())
    throw (unsigned int)onecovered_bs.size();

	//return oc;


}
