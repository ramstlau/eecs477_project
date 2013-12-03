#ifndef _BOTTOMUP_H_
#define _BOTTOMUP_H_

#include "input.h"
#include <queue>
#include <deque>
#include <vector>

using namespace std;

class PQElement {
  public:
    int creation_stamp;  // marks when this elt was made. These incr over time.
    int antenna;
    int delta;  // aka, change

  PQElement() {
    creation_stamp = -1;
    antenna = -1;
    delta = -1;
  }
  PQElement(const PQElement &src) {
    creation_stamp = src.creation_stamp;
    antenna = src.antenna;
    delta = src.delta;
  }
  PQElement(int _antenna, int _delta, int _creation_stamp) {
    antenna = _antenna;
    delta = _delta;
    creation_stamp = _creation_stamp;
  }
  bool is_valid( vector<int> validity_table ) {
    return validity_table[antenna] <= creation_stamp;
  }
};

class PQElement_Compare {
  public:
    bool operator() (const PQElement &lhs, const PQElement &rhs) const {
      return lhs.delta < rhs.delta;
    }
};

typedef priority_queue<PQElement, deque<PQElement>, PQElement_Compare> BotUpPQ;

void bottomup(
    HittingSetData &data, 
    vector<bool> &set_antenna, 
    int &num_covered_base_stations);
void bottomup_int_input(
    HittingSetData &data, 
    vector<int> &set_antenna, 
    int &num_covered_base_stations);

int get_delta(vector<int> &base_stations, int i, vector<int> *src);

void update_coverage(
    vector<int> *&src,
    vector<int> *&dest,
    vector<int> &base_stations);

#endif /* _BOTTOMUP_H_ */
