#include "input.h"
#include "pq.h"
#include "maxdelta2.h"
#include "coverage.h"
#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <deque>

using namespace std;

void maxdelta2(
    HittingSetData &data, 
    vector<bool> &set_antenna, // continues from this set
    int &num_covered_base_stations)
{
  // Create PQ
  clock_t algo_begin = clock();
  PQElement2 current;

  // Build coverage map
  Coverage coverage(data, set_antenna);

  // Fill PQ
  for(int i=0; i<set_antenna.size(); i++) {
    if (set_antenna[i]) { // in set
      int delta = coverage.get_remove_delta(data.antennas[i].base_stations);
      //cout << "remove: " << delta;
      if (delta > current.delta) {
        current = PQElement2(i, delta, false); // remove
      }
    } else { // not in set
      int delta = coverage.get_add_delta(data.antennas[i].base_stations);
      //cout << "add: " << delta;
      if (delta > current.delta) {
        current = PQElement2(i, delta, true); // add
      }
    }
    //cout << " versus " << current.delta << endl;
  }

  // RUN
  int iterations = 0;
  while(current.delta >= 0) {
    ++iterations;
    
    // CHECK TIME
    double elapsed_secs = double(clock() - algo_begin) / CLOCKS_PER_SEC;
    if (elapsed_secs > 10) {
      break;
    }
    
    // UPDATE set & coverage
    if (current.add) {
      set_antenna[current.antenna] = true; 
      coverage.add_coverage(data, current.antenna);
    } else { // remove
      set_antenna[current.antenna] = false; 
      coverage.remove_coverage(data, current.antenna);
    }

    // GET NEXT
    current = PQElement2();
    for(int i=0; i<set_antenna.size(); i++) {
      if (set_antenna[i]) { // in set
        int delta = coverage.get_remove_delta(data.antennas[i].base_stations);
        if (delta > current.delta) {
          current = PQElement2(i, delta, false); // add
        }
      } else { // not in set
        int delta = coverage.get_add_delta(data.antennas[i].base_stations);
        if (delta > current.delta) {
          current = PQElement2(i, delta, true); // add
        }
      }
    }
  }
  num_covered_base_stations = coverage.score;
  cout << "num iterations: " << iterations << endl;
}

void maxdelta2_int(
    HittingSetData &data, 
    vector<int> &set_antenna, // continues from this set
    int &num_covered_base_stations)
{
  // INT -> BOOL
  vector<bool> converted(data.num_antennas, false);
  for(int &i : set_antenna) {
    //cout << i << " is added" << endl;
    converted[i] = true;
  }

  // ALGO
  maxdelta2(data, converted, num_covered_base_stations);

  // BOOL -> INT
  set_antenna.clear();
  for(int i=0; i<converted.size(); i++) {
    if (converted[i]) {
      set_antenna.push_back(i);
    }
  }
}
