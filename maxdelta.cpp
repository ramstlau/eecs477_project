#include "input.h"
#include "pq.h"
#include "maxdelta.h"
#include "coverage.h"
#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <deque>

using namespace std;

void maxdelta(
    HittingSetData &data, 
    vector<bool> &set_antenna, // continues from this set
    int &num_covered_base_stations)
{
  //cout << "maxdelta running" << endl;
  // Create PQ
  clock_t algo_begin = clock();
  Max_PQ2 pq;
  int creation_stamper = 0;
  vector<int> validity_table(data.antennas.size(), creation_stamper);

  // Build coverage map
  Coverage coverage(data, set_antenna);

  // Fill PQ
  for(int i=0; i<set_antenna.size(); i++) {
    if (!set_antenna[i]) { // not in set
      int delta = coverage.get_add_delta(data.antennas[i].base_stations);
      if (delta > 0) {
        pq.emplace(i, delta, creation_stamper, true);
      }
    } else { // already in set
      int delta = coverage.get_remove_delta(data.antennas[i].base_stations);
      if (delta > 0) { // 0's can open up new benefits
        pq.emplace(i, delta, creation_stamper, false);
      }
    }
  }
  //cout << "size of pq: " << pq.size() << endl;
  //coverage.print();

  // RUN
  //cout << "starting algo running" << endl;
  PQElement2 current;
  while(!pq.empty()) {   // TODO: force end when time runs out
    
    // CHECK TIME
    double elapsed_secs = double(clock() - algo_begin) / CLOCKS_PER_SEC;
    if (elapsed_secs > 10) {
      break;
    }
    
    // GET NEXT
    current = pq.top();
    pq.pop();
    
    //cout << "found " << current.antenna << " -- validity: " << current.creation_stamp << " -- delta: " << current.delta << endl;
    if(current.is_valid(validity_table)) {
      // update set & increment creation_stamper
      creation_stamper++;
      if (current.add) {
        set_antenna[current.antenna] = true; 
        coverage.add_coverage(data, current.antenna);
      } else { // remove
        set_antenna[current.antenna] = false; 
        coverage.remove_coverage(data, current.antenna);
      }
      //cout << "new score: " << coverage.score << endl;
      // update validity table
      //cout << "updating validity table to " << creation_stamper << endl;
      for(int &i : data.antennas[current.antenna].base_stations) {
        Base_Station &bs = data.base_stations[i]; // each affected base station
        for(int &j : bs.coverage) {               // mark update to covering antennas
          validity_table[j] = creation_stamper;
        }
      }
      // re-add to PQ
      for(int i=0; i<set_antenna.size(); i++) {
        if (!set_antenna[i]) { // not in set
          int delta = coverage.get_add_delta(data.antennas[i].base_stations);
          if (delta >= 0) {
            pq.emplace(i, delta, creation_stamper, true);
          }
        } else { // already in set
          int delta = coverage.get_remove_delta(data.antennas[i].base_stations);
          if (delta > 0) { // 0's can open up new benefits
            pq.emplace(i, delta, creation_stamper, false);
          }
        }
      }
    }
  }
  //cout << "done running" << endl;
  num_covered_base_stations = coverage.score;
}

void maxdelta_int(
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
  maxdelta(data, converted, num_covered_base_stations);

  // BOOL -> INT
  set_antenna.clear();
  for(int i=0; i<converted.size(); i++) {
    if (converted[i]) {
      set_antenna.push_back(i);
    }
  }
  //cout << endl;
}
