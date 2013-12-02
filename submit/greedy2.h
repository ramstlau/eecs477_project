#ifndef _GREEDY2_H_
#define _GREEDY2_H_

int assess_profit(HittingSetData &data, int bs_num, vector<int> &covered, vector<int> &onecovered, vector<int> &dc);
void markCovered(HittingSetData &data, int setNum);
void printSortedRange(vector<Base_Station*> &sorted_range);
void greedy2(HittingSetData &data, vector<int> &set_antenna, int &num_covered_base_stations);

#endif /* _GREEDY2_H_ */
