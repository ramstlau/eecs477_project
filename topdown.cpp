#include "input.h"
#include "pq.h"
#include "topdown.h"
#include "coverage.h"
#include "bottomup2.h"
#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <deque>

using namespace std;

void topdown(
    HittingSetData &data, 
    vector<bool> &set_antenna, // continues from this set
    int &num_covered_base_stations)
{
  // Create PQ
  clock_t algo_begin = clock();
  Max_PQ pq;
  int creation_stamper = 0;
  vector<int> validity_table(data.antennas.size(), creation_stamper);

  // Build coverage map
  Coverage coverage(data, set_antenna);

  // Fill PQ
  for(int i=0; i<set_antenna.size(); i++) {
    if (set_antenna[i]) {    // in antenna set
      int delta = coverage.get_remove_delta(data.antennas[i].base_stations);
      if (delta >= 0) {
        pq.emplace(i, delta, creation_stamper); 
      }
    }
  }
  //cout << "pq size: " << pq.size() << endl;

  // RUN
  //cout << "starting algo running, pq size: " << pq.size() << endl;
  //cout << "initial score: " << coverage.score << endl;
  PQElement current;
  while(!pq.empty()) {   // TODO: force end when time runs out
    
    // CHECK TIME
    double elapsed_secs = double(clock() - algo_begin) / CLOCKS_PER_SEC;
    //cout << elapsed_secs << endl;
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
      set_antenna[current.antenna] = false; 
      coverage.remove_coverage(data, current.antenna);
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
        if (set_antenna[i]) {    // in antenna set
          int delta = coverage.get_remove_delta(data.antennas[i].base_stations);
          if (delta > 0) {        // make sure it's worth adding
                                   // allow 0's, might open up new benefits
            pq.emplace(i, delta, creation_stamper); 
          }
        }
      }
    }
  }
  //cout << "done running" << endl;
  //bottomup2(data, set_antenna, num_covered_base_stations);
  num_covered_base_stations = coverage.score;
}
void topdown_init(
    HittingSetData &data, 
    vector<bool> &set_antenna, // ignores this set
    int &num_covered_base_stations)
{
  set_antenna.resize(data.num_antennas, true);
  topdown(data, set_antenna, num_covered_base_stations);
}

void topdown_int(
    HittingSetData &data, 
    vector<int> &set_antenna, // continues from this set
    int &num_covered_base_stations)
{
  // INT -> BOOL
  vector<bool> converted(data.num_antennas, false);
  for(int &i : set_antenna) {
    converted[i] = true;
  }

  // ALGO
  topdown(data, converted, num_covered_base_stations);

  // BOOL -> INT
  set_antenna.clear();
  for(int i=0; i<converted.size(); i++) {
    if (converted[i]) {
      set_antenna.push_back(i);
    }
  }
}
void topdown_int_init(
    HittingSetData &data, 
    vector<int> &set_antenna, // ignores this set
    int &num_covered_base_stations)
{
  // ALGO
  vector<bool> converted(data.num_antennas, true);
  topdown(data, converted, num_covered_base_stations);

  // BOOL -> INT
  set_antenna.clear();
  for(int i=0; i<converted.size(); i++) {
    if (converted[i]) {
      set_antenna.push_back(i);
    }
  }
}

