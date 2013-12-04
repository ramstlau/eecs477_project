#include "input.h"
#include "pq.h"
#include "bottomup2.h"
#include "topdown.h"
#include "coverage.h"
#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <deque>

using namespace std;

void bottomup2(
    HittingSetData &data, 
    vector<bool> &set_antenna, // continues from this set
    int &num_covered_base_stations)
{
  //cout << "bottomup2 running" << endl;
  // Create PQ
  Max_PQ pq;
  int creation_stamper = 0;
  vector<int> validity_table(data.antennas.size(), creation_stamper);

  // Build coverage map
  Coverage coverage(data, set_antenna);

  // Fill PQ
  //cout << "filling pq" << endl;
  for(int i=0; i<set_antenna.size(); i++) {
    //cout << i << endl;
    if (!set_antenna[i]) {
      int delta = coverage.get_add_delta(data.antennas[i].base_stations);
      //cout << delta << endl;
      if (delta > 0) {
        //cout << "emplaced: " << i << " -- delta: " << delta << endl;
        pq.emplace(i, delta, creation_stamper);
      }
    }
  }
  //cout << "size of pq: " << pq.size() << endl;
  //coverage.print();

  // RUN
  //cout << "starting algo running" << endl;
  PQElement current;
  while(!pq.empty()) {   // TODO: force end when time runs out
    // GET NEXT
    current = pq.top();
    pq.pop();
    
    //cout << "found " << current.antenna << " -- validity: " << current.creation_stamp << " -- delta: " << current.delta << endl;
    if(current.is_valid(validity_table)) {
      // update set & increment creation_stamper
      creation_stamper++;
      set_antenna[current.antenna] = true; 
      coverage.add_coverage(data, current.antenna);
      cout << "new score: " << coverage.score << endl;
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
        if (!set_antenna[i]) {    // not already in antenna set
          int delta = coverage.get_add_delta(data.antennas[i].base_stations);
          if (delta > 0) {        // make sure it's worth adding
            pq.emplace(i, delta, creation_stamper); 
          }
        }
      }
    }
  }
  cout << "done running" << endl;
  num_covered_base_stations = coverage.score;
}

void bottomup2_int(
    HittingSetData &data, 
    vector<int> &set_antenna, // continues from this set
    int &num_covered_base_stations)
{
  // INT -> BOOL
  vector<bool> converted(data.num_antennas, false);
  for(int &i : set_antenna) {
    cout << i << " is added" << endl;
    converted[i] = true;
  }

  // ALGO
  bottomup2(data, converted, num_covered_base_stations);

  // BOOL -> INT
  set_antenna.clear();
  for(int i=0; i<converted.size(); i++) {
    if (converted[i]) {
      set_antenna.push_back(i);
    }
  }
  cout << endl;
}
