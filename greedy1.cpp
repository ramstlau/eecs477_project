#include "input.h"
#include <cassert>
#include <algorithm>
#include <iostream>

using namespace std;

bool compare1(Antenna *a1, Antenna *a2)
{
	return(a1->base_stations.size() > a2->base_stations.size());

}

void printVector(vector<int> &v)
{
	for(unsigned int i = 0; i < v.size(); i++)
	  {
	    cout << v.at(i) << " ";
	  }
	  
	  cout << endl;

}
double profitable_calculate(HittingSetData &data, int setNum, vector<int> &covered, vector<int> &onecovered, vector<int> &dc, vector<int> &existingdc, vector<int> &adddc)
{
	//cout << "existingdc calculation begins: " << endl;
	vector<int>::iterator it2 = set_intersection(dc.begin(), dc.end(), 
			      data.antennas.at(setNum).base_stations.begin(), data.antennas.at(setNum).base_stations.end(),
			      existingdc.begin());
 	existingdc.erase(it2, existingdc.end()); 
 	//cout << "existingdc calculation ends, and addc calculation begins " << endl;
 	it2 = set_intersection(onecovered.begin(), onecovered.end(), 
			       data.antennas.at(setNum).base_stations.begin(), data.antennas.at(setNum).base_stations.end(),
			 				    adddc.begin());
 	adddc.erase(it2, adddc.end()); //this should be put into dc
 	//cout << "addc calculation ends" << endl;
 	
 	double p = (double)(existingdc.size() + adddc.size())/(double)data.antennas.at(setNum).base_stations.size();
 	
 	return p;

}
void profitable_add(HittingSetData &data, int setNum, vector<int> &covered, vector<int> &onecovered, vector<int> &dc, vector<int> &existingdc, vector<int> &adddc)
{
		//update dc, TODO: this could alternatively be a push_back + for loop operation
		vector<int>newdc(data.num_base_stations);
		vector<int>::iterator it2 = set_union(dc.begin(), dc.end(), adddc.begin(), adddc.end(), newdc.begin());
		newdc.erase(it2, newdc.end());	

	
		//update onecovered: symmetric difference between shrink and onecovered
		vector<int> shrink(data.num_base_stations);	
        	it2 = set_difference(
        			     data.antennas.at(setNum).base_stations.begin(), 
        			     data.antennas.at(setNum).base_stations.end(), 
			 	     dc.begin(), dc.end(),
			 	     shrink.begin());
       
       		shrink.erase(it2, shrink.end()); //this should be the shrunk set without dcs

		vector<int> newonecovered(data.num_base_stations);
		it2 = set_symmetric_difference(onecovered.begin(), onecovered.end(), 
			 		       shrink.begin(), shrink.end(),
			 		       newonecovered.begin());
			 		       
       		newonecovered.erase(it2, newonecovered.end()); //this should be the new onecovered set

       		
		//update covered
		vector<int>newcovered(data.num_base_stations);
		it2 = set_union(covered.begin(), covered.end(), 
			 	data.antennas.at(setNum).base_stations.begin(), data.antennas.at(setNum).base_stations.end(),
			 	newcovered.begin());
       		newcovered.erase(it2, newcovered.end());
       		
       		dc.swap(newdc);
       		covered.swap(newcovered);
       		onecovered.swap(newonecovered);
}
bool profitable(HittingSetData &data, int setNum, vector<int> &covered, vector<int> &onecovered, vector<int> &dc)
{
	bool ret = false;
	//calculate intersection between old dc and data set, existingdc
	vector<int> existingdc(data.num_base_stations);
 	
	//calculate intersection between, old onecovered and data set, newdc
       	vector<int> adddc(data.num_base_stations);

 	double p = profitable_calculate(data, setNum, covered, onecovered, dc, existingdc, adddc);
 	if(p < 0.5) //update covered, onecovered, dc
 	  {
		ret = true;
		profitable_add(data, setNum, covered, onecovered, dc, existingdc, adddc);
	  }				   

	return ret;
}
void greedy1(HittingSetData &data, vector<int> &set_antenna, int &num_covered_base_stations)
{
	//sort antennas from higher coverage to lower coverage.
	vector<Antenna*> sorted_range;
	sorted_range.resize(data.num_antennas);
	vector<Antenna>::iterator it = data.antennas.begin();
	for(unsigned int i = 0; i < sorted_range.size(); i++)
	  {
	    sorted_range.at(i) = &(*it);
	    it++;
	  }
	
	sort(sorted_range.begin(), sorted_range.end(), compare1);
	
	/*for(unsigned int i = 0; i < sorted_range.size(); i++)
	  {
	    cout << sorted_range.at(i)->num << " " << sorted_range.at(i)->base_stations.size() << endl;
	  }
	cout << endl;*/
	
	//select highest coverage.
	
	//covered = onecovered = selected.base_stations, dc = empty
	set_antenna.push_back(sorted_range.at(0)->num);
	vector<int> covered(sorted_range.at(0)->base_stations), onecovered(sorted_range.at(0)->base_stations), dc; 
	//cout << "beginning: onecovered : ";
	//printVector(onecovered);	
	
	//walk through sorted vector, add antennas if they are profitable
	//	profitable: calculate add this antenna and |shinked data - newdc|/|data|.
	//		    if over half of its base stations are uncovered*, 
	//		    less than half of base stations are in dc 

	for(unsigned int i = 1; i < sorted_range.size(); i++)
	  {
	    if(profitable(data, sorted_range.at(i)->num, covered, onecovered, dc))
	      set_antenna.push_back(sorted_range.at(i)->num);
	  }
	  
	//cout << "after: onecovered : ";
	//printVector(onecovered);
	num_covered_base_stations = onecovered.size();

}
