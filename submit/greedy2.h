#ifndef _GREEDY2_H_
#define _GREEDY2_H_

//Pseudo Code:
//  1. Sort base stations based on cardinality of antennas that cover it (low -> high)
//  2. Select the lowest base station, select an antenna that covers it, mark all base stations that it covers as covered.
//  3. Walk through sorted range from step one, if the base station is not covered yet, add the most profitable antenna that covers it.
//	Profitable: calculate for this antenna |# of base stations in this that don't receive signal upon adding this|/|# of total base stations that this covers|.
//		    Adding this is a profit if the division above is below 0.5. 
int assess_profit(HittingSetData &data, int bs_num, vector<int> &covered, vector<int> &onecovered, vector<int> &dc);
void markCovered(HittingSetData &data, int setNum);
void printSortedRange(vector<Base_Station*> &sorted_range);
void greedy2(HittingSetData &data, vector<int> &set_antenna, int &num_covered_base_stations);

#endif /* _GREEDY2_H_ */
