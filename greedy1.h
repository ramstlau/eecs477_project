#ifndef _GREEDY1_H_
#define _GREEDY1_H_

double profitable_calculate(HittingSetData &data, int setNum, vector<int> &covered, vector<int> &onecovered, vector<int> &dc, vector<int> &existingdc, vector<int> &adddc);
void profitable_add(HittingSetData &data, int setNum, vector<int> &covered, vector<int> &onecovered, vector<int> &dc, vector<int> &existingdc, vector<int> &adddc);
void printVector(vector<int> &v);
void greedy1(HittingSetData &data, vector<int> &set_antenna, int &num_covered_base_stations);

#endif /* _GREEDY1_H_ */
