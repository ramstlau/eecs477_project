#include "input.h"
#include "pq.h"
#include "maxdelta3.h"
#include "coverage.h"
#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <deque>

using namespace std;

void maxdelta3(
    HittingSetData &data, 
    vector<bool> &set_antenna, // continues from this set
    int &num_covered_base_stations)
{
  // Create PQ
  clock_t algo_begin = clock();
  PQElement2 current;

  // Build coverage map
  Coverage coverage(data, set_antenna);

  // RUN
  //int iterations = 0;
  vector<int> swap_blacklist;
  bool change_since_blacklist_clear;
  while(true) {
    if (swap_blacklist.size() > data.num_antennas) {
      if (change_since_blacklist_clear) {
        swap_blacklist.clear();
        change_since_blacklist_clear = false;
      } else {
        break;
      }
    }
    //++iterations;
    
    // CHECK TIME
    double elapsed_secs = double(clock() - algo_begin) / CLOCKS_PER_SEC;
    if (elapsed_secs > 10) {
      break;
    }
    
    // GET CURRENT
    vector<PQElement2> to_change;
    current.delta = -1000;
    for(int i=0; i<set_antenna.size(); i++) {
      if (set_antenna[i]) { // in set
        int delta = coverage.get_remove_delta(data.antennas[i].base_stations);
        if (delta > current.delta /*&& find(
              swap_blacklist.begin(), 
              swap_blacklist.end(), 
              i) == swap_blacklist.end()*/) {
          // overwrite
          current.antenna = i;
          current.delta = delta;
          current.add = false;
        }
      } else { // not in set
        int delta = coverage.get_add_delta(data.antennas[i].base_stations);
        if (delta > current.delta /*&& find(
              swap_blacklist.begin(), 
              swap_blacklist.end(), 
              i) == swap_blacklist.end()*/) {
          // overwrite
          current.antenna = i;
          current.delta = delta;
          current.add = true;
        }
      }
    }
    
    // UPDATE set & coverage
    if (current.delta > 0) {
      to_change.push_back(current);
    
    // CURRENT ISN'T WORTH, CHECK FOR SWAPS
    } else {
      int best_combo_delta = -1000;
      for(int i=0; i<set_antenna.size(); ++i) {
        if (current.delta && find(
              swap_blacklist.begin(), 
              swap_blacklist.end(), 
              i) != swap_blacklist.end()) {
          continue;
        }
        if (set_antenna[i]) { // in set
          int delta = coverage.get_remove_delta(data.antennas[i].base_stations);
          current.antenna = i;
          current.delta = delta;
          current.add = false;
        } else { // not in set
          int delta = coverage.get_add_delta(data.antennas[i].base_stations);
          current.antenna = i;
          current.delta = delta;
          current.add = true;
        }
        // *TEMPORARILY* ADD CURRENT
        Coverage copy = coverage;
        if (current.add) {
          set_antenna[current.antenna] = true; 
          copy.add_coverage(data, current.antenna);
        } else { // remove
          set_antenna[current.antenna] = false; 
          copy.remove_coverage(data, current.antenna);
        }
        // FIND SWAP
        PQElement2 swap;
        for(int i=0; i<set_antenna.size(); i++) {
          if (set_antenna[i]) { // in set
            int delta = copy.get_remove_delta(data.antennas[i].base_stations);
            if (delta > swap.delta) {
              // overwrite
              swap.antenna = i;
              swap.delta = delta;
              swap.add = false;
            }
          } else { // not in set
            int delta = copy.get_add_delta(data.antennas[i].base_stations);
            if (delta > swap.delta) {
              // overwrite
              swap.antenna = i;
              swap.delta = delta;
              swap.add = true;
            }
          }
        }
        if (swap.delta + current.delta > best_combo_delta) {
          best_combo_delta = swap.delta + current.delta;
          if (swap.delta + current.delta > 0) { // disallow = to prevent loops
            change_since_blacklist_clear = true;
          }
          // ADD ELTS FOR CHANGE
          //cout << "BEST: " << current.antenna << ' ' << swap.antenna << endl;
          //cout << "DELTAS: " << current.delta << ' ' << swap.delta << endl;
          to_change.clear();
          to_change.push_back(current);
          to_change.push_back(swap);
        } 

        // UNDO TEMPORARY ADD
        if (current.add) {
          set_antenna[current.antenna] = false; 
        } else { // remove
          set_antenna[current.antenna] = true; 
        }

        if (swap.delta + current.delta <= 0) { // = because we don't want loops
          swap_blacklist.push_back(current.antenna);
        }
      }
      if (best_combo_delta < 0) {
        num_covered_base_stations = coverage.score;
        return;
      }
    }

    // MAKE CHANGES
    //cout << to_change.size() << endl;
    if (to_change.size() == 2) {
      cout << to_change[0].delta << " + " << to_change[1].delta << endl;
    }
    for(PQElement2 &elt : to_change) {
      //cout << "PERM CHANGE: " << elt.antenna << endl;
      if (elt.add) {
        set_antenna[elt.antenna] = true; 
        coverage.add_coverage(data, elt.antenna);
      } else { // remove
        set_antenna[elt.antenna] = false; 
        coverage.remove_coverage(data, elt.antenna);
      }
    }
  }
  num_covered_base_stations = coverage.score;
  return;
}

void maxdelta3_int(
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
  maxdelta3(data, converted, num_covered_base_stations);

  // BOOL -> INT
  set_antenna.clear();
  for(int i=0; i<converted.size(); i++) {
    if (converted[i]) {
      set_antenna.push_back(i);
    }
  }
}
