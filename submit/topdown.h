#ifndef _TOPDOWN_H_
#define _TOPDOWN_H_

#include "input.h"
#include "pq.h"
#include <queue>
#include <deque>
#include <vector>

using namespace std;

class PQElement_Topdown_Compare {
  public:
    bool operator() (const PQElement &lhs, const PQElement &rhs) const {
      return lhs.delta < rhs.delta; // sorts for max delta
    }
};

typedef priority_queue<PQElement, deque<PQElement>, PQElement_Topdown_Compare> TopDownPQ;

void topdown(
    HittingSetData &data, 
    vector<bool> &set_antenna, 
    int &num_covered_base_stations);
void topdown_init(
    HittingSetData &data, 
    vector<bool> &set_antenna, 
    int &num_covered_base_stations);

void topdown_int(
    HittingSetData &data, 
    vector<int> &set_antenna, 
    int &num_covered_base_stations);
void topdown_int_init(
    HittingSetData &data, 
    vector<int> &set_antenna, 
    int &num_covered_base_stations);

#endif /* _TOPDOWN_H_ */
