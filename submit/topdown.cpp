#include "input.h"
#include "pq.h"
#include "topdown.h"
#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <deque>

using namespace std;

class Coverage {
  public:
    vector<int> coverage;
    int score;
    Coverage(int num_base_stations) {
      coverage.resize(num_base_stations, 0);
      score = 0;
    }
    Coverage(
        HittingSetData &data, 
        vector<bool> &set_antennas) 
    {
      score = 0;
      coverage.resize(data.num_base_stations, 0);
      for(int i=0; i<set_antennas.size(); ++i) {
        for(int &j : data.antennas[i].base_stations) {
          add_coverage(j);
        }
      }
    }
    void add_coverage(int &antenna)
    {
      if(coverage[antenna] == 1) {
        --score;
      }
      ++coverage[antenna];
      if(coverage[antenna] == 1) {
        ++score;
      }
    }
    void remove_coverage(int &antenna)
    {
      if(coverage[antenna] == 1) {
        --score;
      }
      --coverage[antenna];
      if(coverage[antenna] == 1) {
        ++score;
      }
    }
    int get_remove_delta(vector<int> &base_stations) {
      int delta = 0;
      for(int &i : base_stations) {
        if(coverage[i] == 1) {
          delta--;
        }
        if(coverage[i]-1 == 1) {
          delta++;
        }
      }
      return delta;
    }
    int get_add_delta(vector<int> &base_stations) {
      int delta = 0;
      for(int &i : base_stations) {
        if(coverage[i] == 1) {
          delta--;
        }
        if(coverage[i]+1 == 1) {
          delta++;
        }
      }
      return delta;
    }
};
int get_topdown_delta(
    HittingSetData &data, 
    vector<int> &base_stations, 
    vector<int> &coverage);

void topdown(
    HittingSetData &data, 
    vector<bool> &set_antenna, // continues from this set
    int &num_covered_base_stations)
{
  //cout << "bottomup running" << endl;
  // Create PQ
  TopDownPQ pq;
  int creation_stamper = 0;
  vector<int> validity_table(data.antennas.size(), creation_stamper);

  // Build coverage map
  Coverage coverage(data, set_antenna);
  //vector<int> dest = coverage;
  //for(int i=0; i<set_antenna.size(); i++) {
    //if (set_antenna[i]) {
      //add_coverage(coverage, data.antennas[i].base_stations);
    //}
  //}

  // Fill PQ
  for(int i=0; i<set_antenna.size(); i++) {
    if (set_antenna[i]) {    // in antenna set
      int delta = coverage.get_remove_delta(data.antennas[i].base_stations);
      //cout << "adding to PQ: " << i << " -- delta: " << delta << endl;
      if (delta > 0) {        // make sure it's worth adding
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
    // GET NEXT
    if (!pq.empty()) {
      current = pq.top();
      pq.pop();
    }
    
    cout << "found " << current.antenna << " -- validity: " << current.creation_stamp << " -- delta: " << current.delta << endl;
    if(current.is_valid(validity_table)) {
      // update set & increment creation_stamper
      creation_stamper++;
      set_antenna[current.antenna] = false; 
      coverage.remove_coverage(current.antenna);
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
        if (set_antenna[i]) {    // in antenna set
          int delta = coverage.get_remove_delta(data.antennas[i].base_stations);
          //cout << "adding to PQ: " << i << " -- delta: " << delta << endl;
          if (delta > 0) {        // make sure it's worth adding
            pq.emplace(i, delta, creation_stamper); 
          }
        }
      }
    }
  }
  //cout << "done running" << endl;
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

