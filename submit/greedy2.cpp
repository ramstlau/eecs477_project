#include "input.h"
#include "greedy1.h"
#include <cassert>
#include <algorithm>
#include <iostream>
#include <cassert>

bool compare2(Base_Station *b1, Base_Station *b2)
{
	return(b1->coverage.size() < b2->coverage.size());

}
int assess_profit(HittingSetData &data, int bs_num, vector<int> &covered, vector<int> &onecovered, vector<int> &dc)
{
	int selected = -1;
	double p_min = 0.5;
	vector<int> edc_min(data.num_base_stations), adc_min(data.num_base_stations);
	
	for(unsigned int i = 0; i < data.base_stations.at(bs_num).coverage.size(); i++)					
	//asses_profit function: selects most profitable antenna & returns it
	  {

	    if(data.selected_antennas.find(data.base_stations.at(bs_num).coverage.at(i)) != data.selected_antennas.end())
	      continue;
	    vector<int> edc(data.num_base_stations), adc(data.num_base_stations);

	    double p = profitable_calculate(data, data.base_stations.at(bs_num).coverage.at(i), covered, onecovered, dc, edc, adc);

	    if(p < p_min)
	      {
	        p_min = p;
	        selected = data.base_stations.at(bs_num).coverage.at(i);
	        edc_min.swap(edc);
	        adc_min.swap(adc);
	      }
	  }

	if(selected != -1)
	  profitable_add(data, selected, covered, onecovered, dc, edc_min, adc_min);

	return selected;
}
void markCovered(HittingSetData &data, int setNum)
{
	for(unsigned int i = 0; i < data.antennas.at(setNum).base_stations.size(); i++)
	  {
	    data.covered.at(data.antennas.at(setNum).base_stations.at(i)) = true;
	  
	  }

}
void printSortedRange(vector<Base_Station*> &sorted_range)
{
	for(unsigned int i = 0; i < sorted_range.size(); i++)
	  {
	    cout << sorted_range.at(i)->num << " ";
	  
	  }
	  
	  cout << endl;

}
void greedy2(HittingSetData &data, vector<int> &set_antenna, int &num_covered_base_stations)
{
	//sort base stations from lower coverage to higher coverage.
	vector<Base_Station*> sorted_range;
	sorted_range.resize(data.num_base_stations);
	vector<Base_Station>::iterator it = data.base_stations.begin();
	for(unsigned int i = 0; i < sorted_range.size(); i++)
	  {
	    sorted_range.at(i) = &(*it);
	    it++;
	  }
	
	sort(sorted_range.begin(), sorted_range.end(), compare2);

	//select lowest coverage.
	
	//covered = onecovered = selected.base_stations, dc = empty
	int j = 0;
	while(sorted_range.at(j)->coverage.size() == 0 || sorted_range.at(j)->coverage.empty())
		j++;

	//for the lowest covered base station, select most profitable antenna
	vector<int> covered, onecovered, dc; 
	int selected = assess_profit(data, sorted_range.at(j)->num, covered, onecovered, dc);
	assert(selected != -1);

	markCovered(data, selected);
	
	set_antenna.push_back(selected);
	data.selected_antennas.insert(selected);

	for(unsigned int i = j+1; i < sorted_range.size(); i++)
	  {
	    //if not covered: (bit vector for basestations)
	    //		walk through antennas that cover it, select most profitable antenna  asses_profit function should do both of these
	    //		mark all antennas covered by this antenna as covered
	    
	    if(!data.covered.at(sorted_range.at(i)->num) && !sorted_range.at(i)->coverage.empty())
	      {
	      	selected = assess_profit(data, sorted_range.at(i)->num, covered, onecovered, dc);

	      	if(selected == -1)
	      	  continue;
	      	set_antenna.push_back(selected);
	      	data.selected_antennas.insert(selected);

	      	markCovered(data, selected);
	      }
	      
	  }
	  
	num_covered_base_stations = onecovered.size();

}
