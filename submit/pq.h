#ifndef _PQ_H_
#define _PQ_H_

#include "input.h"
#include <queue>
#include <deque>
#include <vector>

using namespace std;

// Element for Max_PQ
// Uses a creation_stamp to determine if element is still valid
struct PQElement {
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
  bool is_valid( vector<int> &validity_table ) {
    return validity_table[antenna] <= creation_stamp;
  }
};

// Element for Max_PQ2
// Doesn't need a creation_stamp - PQ is reset each round
struct PQElement2 {
  int antenna;
  int delta; // aka, change
  bool add; // true -> add, false -> remove

  PQElement2() {
    antenna = -1;
    delta = -1;
    add = false;
  }
  PQElement2(const PQElement2 &src) {
    antenna = src.antenna;
    delta = src.delta;
    add = src.add;
  }
  PQElement2(int _antenna, int _delta, bool _add) {
    antenna = _antenna;
    delta = _delta;
    add = _add;
  }
};

class PQElement_Max_Compare {
  public:
    bool operator() (const PQElement &lhs, const PQElement &rhs) const {
      return lhs.delta < rhs.delta;
    }
};
class PQElement2_Max_Compare {
  public:
    bool operator() (const PQElement2 &lhs, const PQElement2 &rhs) const {
      return lhs.delta < rhs.delta;
    }
};

typedef priority_queue<PQElement, deque<PQElement>, PQElement_Max_Compare> Max_PQ;
typedef priority_queue<PQElement2, deque<PQElement2>, PQElement2_Max_Compare> Max_PQ2;

#endif /* _PQ_H_ */
