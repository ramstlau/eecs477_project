#ifndef _TOPDOWN_H_
#define _TOPDOWN_H_

#include "input.h"
#include "pq.h"
#include <queue>
#include <deque>
#include <vector>
#include <ctime>

using namespace std;

void topdown(
    HittingSetData &data, 
    vector<bool> &set_antenna, 
    int &num_covered_base_stations,
    clock_t &algo_begin);
void topdown_init(
    HittingSetData &data, 
    vector<bool> &set_antenna, 
    int &num_covered_base_stations,
    clock_t &algo_begin);

void topdown_int(
    HittingSetData &data, 
    vector<int> &set_antenna, 
    int &num_covered_base_stations,
    clock_t &algo_begin);
void topdown_int_init(
    HittingSetData &data, 
    vector<int> &set_antenna, 
    int &num_covered_base_stations,
    clock_t &algo_begin);

#endif /* _TOPDOWN_H_ */
