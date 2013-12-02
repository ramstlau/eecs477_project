#ifndef _BRUTEFORCE2_H_
#define _BRUTEFORCE2_H_

int eval(const HittingSetData &data, const vector<bool> &selection);
void bruteforce2(
    HittingSetData &data, 
    vector<int> &set_antenna, 
    int &num_covered_base_stations);

#endif /* _BRUTEFORCE2_H_ */

