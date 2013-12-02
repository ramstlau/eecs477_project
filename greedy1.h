#ifndef _GREEDY1_H_
#define _GREEDY1_H_

//Pseudo Code:
//  1. Sort antennas based on cardinality of base stations it covers (high -> low)
//  2. Select the highest one
//  3. Walk through sorted range from step one, adding an antenna if it is profitable:
//	Profitable: calculate for this antenna |# of base stations in this that don't receive signal upon adding this|/|# of total base stations that this covers|.
//		    Adding this is a profit if the division above is below 0.5. 

bool profitable(HittingSetData &data, int setNum, vector<int> &covered, vector<int> &onecovered, vector<int> &dc);
double profitable_calculate(HittingSetData &data, int setNum, vector<int> &covered, vector<int> &onecovered, vector<int> &dc, vector<int> &existingdc, vector<int> &adddc);
void profitable_add(HittingSetData &data, int setNum, vector<int> &covered, vector<int> &onecovered, vector<int> &dc, vector<int> &existingdc, vector<int> &adddc);
void printVector(vector<int> &v);
void greedy1(HittingSetData &data, vector<int> &set_antenna, int &num_covered_base_stations);

#endif /* _GREEDY1_H_ */
