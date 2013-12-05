#ifndef _MAXDELTA3_H_
#define _MAXDELTA3_H_

#include "input.h"
#include "pq.h"
#include <queue>
#include <deque>
#include <vector>

using namespace std;

void maxdelta3(
    HittingSetData &data, 
    vector<bool> &set_antenna, 
    int &num_covered_base_stations);
void maxdelta3_int(
    HittingSetData &data, 
    vector<int> &set_antenna, 
    int &num_covered_base_stations);

#endif /* _MAXDELTA3_H_ */
