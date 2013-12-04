#include "input.h"
#include "pq.h"
#include "bottomup.h"
#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <deque>

using namespace std;

void bottomup(
    HittingSetData &data, 
    vector<bool> &set_antenna, // continues from this set
    int &num_covered_base_stations)
{
  //cout << "bottomup running" << endl;
  // Create PQ
  BotUpPQ pq;
  int creation_stamper = 0;
  vector<int> validity_table(data.antennas.size(), creation_stamper);

  // Build coverage map
  vector<int> single_covering_1;
  vector<int> single_covering_2;
  vector<int> doubly_counted;
  vector<int> *src = &single_covering_1;
  vector<int> *dest = &single_covering_2;
  for(int i=0; i<set_antenna.size(); i++) {
    if (set_antenna[i]) {
      update_coverage(src, dest, doubly_counted, data.antennas[i].base_stations);
    }
  }

  // Fill PQ
  for(Antenna &a : data.antennas) {
    pq.emplace(a.num, a.base_stations.size(), creation_stamper);
    //cout << "emplaced: " << a.num << ' ' << a.base_stations.size() << ' ' << creation_stamper << endl;
  }
  //cout << "pq size: " << pq.size() << endl;

  // RUN
  //cout << "starting algo running" << endl;
  PQElement current = pq.top();
  pq.pop();
  while(!pq.empty()) {   // TODO: force end when time runs out
    
    //cout << "found " << current.antenna << " -- validity: " << current.creation_stamp << " -- delta: " << current.delta << endl;
    if(current.is_valid(validity_table)) {
      // update set & increment creation_stamper
      creation_stamper++;
      set_antenna[current.antenna] = true; 
      update_coverage(src, dest, doubly_counted, data.antennas[current.antenna].base_stations);
      // update validity table
      //cout << "updating validity table to " << creation_stamper << endl;
      for(int &i : data.antennas[current.antenna].base_stations) {
        Base_Station &bs = data.base_stations[i]; // each affected base station
        for(int &j : bs.coverage) {               // mark update to covering antennas
          validity_table[j] = creation_stamper;
        }
      }
      // add updated to PQ
      for(int i=0; i<set_antenna.size(); i++) {
        if (!set_antenna[i]) {    // not already in antenna set
          int delta = get_delta(data.antennas[i].base_stations, i, src);
          if (delta > 0) {        // make sure it's worth adding
            pq.emplace(i, delta, creation_stamper); 
          }
        }
      }
    }
    // GET NEXT
    if (!pq.empty()) {
      current = pq.top();
      pq.pop();
    }
  }
  //cout << "done running" << endl;
  num_covered_base_stations = src->size();
}

void bottomup_int_input(
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
  bottomup(data, converted, num_covered_base_stations);

  // BOOL -> INT
  set_antenna.clear();
  for(int i=0; i<converted.size(); i++) {
    if (converted[i]) {
      set_antenna.push_back(i);
    }
  }
}
