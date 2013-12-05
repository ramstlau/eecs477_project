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
    int &num_covered_base_stations,
    clock_t &algo_begin)
{
  // Create PQ
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
    
    // UPDATE set & coverage
    if (current.delta > 0) {
      if (current.add) {
        set_antenna[current.antenna] = true; 
        coverage.add_coverage(data, current.antenna);
      } else { // remove
        set_antenna[current.antenna] = false; 
        coverage.remove_coverage(data, current.antenna);
      }
    }

    // GET NEXT
    current.delta = -1000;
    for(int i=0; i<set_antenna.size(); i++) {
      if (set_antenna[i]) { // in set
        int delta = coverage.get_remove_delta(data.antennas[i].base_stations);
        if (delta > current.delta && find(
              swap_blacklist.begin(), 
              swap_blacklist.end(), 
              i) == swap_blacklist.end()) {
          // overwrite
          current.antenna = i;
          current.delta = delta;
          current.add = false;
        }
      } else { // not in set
        int delta = coverage.get_add_delta(data.antennas[i].base_stations);
        if (delta > current.delta && find(
              swap_blacklist.begin(), 
              swap_blacklist.end(), 
              i) == swap_blacklist.end()) {
          // overwrite
          current.antenna = i;
          current.delta = delta;
          current.add = true;
        }
      }
    }
    // NEXT ISN'T WORTH, CHECK FOR SWAPS
    if (current.delta <= 0) {
      // TEMPORARY ADD
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
        // <note> This sometimes hinders performance
        //if (i == current.antenna) {
          //continue;
        //}
        // </note>
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
      if (swap.delta + current.delta >= 0) {
        if (swap.delta + current.delta > 0) { // disallow = to prevent loops
          change_since_blacklist_clear = true;
          //cout << "Gainful swap! deltas: " << current.delta << " + " << swap.delta << endl;
          //cout << "antennas: " << current.antenna << " & " << swap.antenna << endl;
          //double elapsed_secs = double(clock() - algo_begin) / CLOCKS_PER_SEC;
          //cout << "Time: " << elapsed_secs << endl;
        }
        // ADD SWAP
        if (swap.add) {
          set_antenna[swap.antenna] = true; 
          coverage.add_coverage(data, swap.antenna);
        } else { // remove
          set_antenna[swap.antenna] = false; 
          coverage.remove_coverage(data, swap.antenna);
        }
        // FIX COVERAGE OF CURRENT
        if (current.add) {
          coverage.add_coverage(data, current.antenna);
        } else { // remove
          coverage.remove_coverage(data, current.antenna);
        }
      } else { 
        // UNDO TEMPORARY ADD
        if (current.add) {
          set_antenna[current.antenna] = false; 
        } else { // remove
          set_antenna[current.antenna] = true; 
        }
      }
      if (swap.delta + current.delta <= 0) { // = because we don't want loops
        swap_blacklist.push_back(current.antenna);
      }
    }
  }
  num_covered_base_stations = coverage.score;
  //cout << "num iterations: " << iterations << endl;
}

void maxdelta2_int(
    HittingSetData &data, 
    vector<int> &set_antenna, // continues from this set
    int &num_covered_base_stations,
    clock_t &algo_begin)
{
  // INT -> BOOL
  vector<bool> converted(data.num_antennas, false);
  for(int &i : set_antenna) {
    //cout << i << " is added" << endl;
    converted[i] = true;
  }

  // ALGO
  maxdelta2(data, converted, num_covered_base_stations, algo_begin);

  // BOOL -> INT
  set_antenna.clear();
  for(int i=0; i<converted.size(); i++) {
    if (converted[i]) {
      set_antenna.push_back(i);
    }
  }
}
