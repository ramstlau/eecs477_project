#include "input.h"
#include "pq.h"
#include "bottomup.h"
#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <deque>

using namespace std;

int get_delta(
    vector<int> *src,
    vector<int> &base_stations, 
    vector<int> &doubly_counted);

void update_coverage(
    vector<int> *&src,
    vector<int> *&dest,
    vector<int> &doubly_counted,
    vector<int> &base_stations);

void bottomup(
    HittingSetData &data, 
    vector<bool> &set_antenna, // continues from this set
    int &num_covered_base_stations)
{
  //cout << "bottomup running" << endl;
  // Create PQ
  clock_t algo_begin = clock();
  Max_PQ pq;
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
  PQElement current;
  while(!pq.empty()) {   // TODO: force end when time runs out

    // CHECK TIME
    double elapsed_secs = double(clock() - algo_begin) / CLOCKS_PER_SEC;
    if (elapsed_secs > 10) {
      break;
    }

    // GET NEXT
    current = pq.top();
    pq.pop();
    
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
          int delta = get_delta(src, data.antennas[i].base_stations, doubly_counted);
          if (delta >= 0) {        // make sure it's worth adding
            pq.emplace(i, delta, creation_stamper); 
          }
        }
      }
    }
  }
  //cout << "done running" << endl;
  num_covered_base_stations = src->size();
}

void bottomup_int(
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
    //cout << i << ' ';
    if (converted[i]) {
      set_antenna.push_back(i);
    }
  }
  //cout << endl;
}

void update_coverage(
    vector<int> *&src, 
    vector<int> *&dest,
    vector<int> &doubly_counted, 
    vector<int> &base_stations)
{
  //cout << "UPDATE:" << endl;
  //cout << "src: " << src->size() << endl;
  //cout << "dest: " << dest->size() << endl;
  //cout << "stations: " << base_stations.size() << endl;
  
  // remove all known doubly_covereds from base_stations
  vector<int> base_stations_not_dc;
  set_difference(
      base_stations.begin(), 
      base_stations.end(), 
      doubly_counted.begin(), 
      doubly_counted.end(), 
      back_inserter(base_stations_not_dc));
  //cout << "non-dc stations: " << base_stations_not_dc.size() << endl;

  // add new double counts to doubly_counted
  // no need to remove from base_stations_not_dc, symmetric difference will remove
  set_intersection(
      src->begin(), 
      src->end(), 
      base_stations_not_dc.begin(), 
      base_stations_not_dc.end(), 
      back_inserter(doubly_counted));   // this creates duplicates, might be able to improve
  //cout << "new dc: " << doubly_counted.size() << endl;

  set_symmetric_difference( // still need symmetric difference instead of union
                            // because new dc's weren't removed from base_stations
      src->begin(), 
      src->end(), 
      base_stations_not_dc.begin(), 
      base_stations_not_dc.end(), 
      back_inserter(*dest));

  src->clear();
  swap(src, dest); 

  //cout << "AFTER:" << endl;
  //cout << "src: " << src->size() << endl;
  //cout << "dest: " << dest->size() << endl;
}

int get_delta(
    vector<int> *src,
    vector<int> &base_stations, 
    vector<int> &doubly_counted)
{
  // remove all known doubly_covereds from base_stations
  vector<int> base_stations_not_dc;
  set_difference(
      base_stations.begin(), 
      base_stations.end(), 
      doubly_counted.begin(), 
      doubly_counted.end(), 
      back_inserter(base_stations_not_dc));

  vector<int> dest;
  set_symmetric_difference( // still need symmetric difference instead of union
                            // because new dc's weren't removed from base_stations
      src->begin(), 
      src->end(), 
      base_stations_not_dc.begin(), 
      base_stations_not_dc.end(), 
      back_inserter(dest));

  int old_coverage = src->size();
  int new_coverage = dest.size();

  return (new_coverage - old_coverage);
}
