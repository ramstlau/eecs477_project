#include "input.h"
#include "bruteforce2.h"
#include <cassert>
#include <iostream>
#include <algorithm>
#include <utility>

using namespace std;

//int eval(const HittingSetData &data, const vector<bool> &selection);

void bruteforce2(
    HittingSetData &data, 
    vector<int> &set_antenna, 
    int &num_covered_base_stations)
{ 

  int num_antennas = data.antennas.size();
  vector<bool> selection(num_antennas+1, false);    // last index indicates completion

  int max_flip = 0;
  vector<int> best_set;
  int best_score = 0; // no selections will score 0
  cout << "initial best score: 0" << endl;
  
  while(!selection[num_antennas+1]) { 

    // FIND - could be made more efficient 
    int i=0;
    while(selection[i] == true) {   // find index that needs flip
      i++;
    }
    if (i > max_flip) {
      max_flip = i;
    }
    cout << "flipping: " << i << " -- max flip: " << max_flip << "/" << data.num_base_stations << endl;

    // FLIP
    selection[i] = true;
    for(int j=i-1; j>=0; j--) {
      selection[j] = false;
    }

    // EVAL
    int score = eval(data, selection);
    cout << "new score: " << score << " -- best score: " << best_score << endl;
    if (score > best_score) {
      best_score = score;
      //cout << "new best score: " << best_score << endl;
      set_antenna.clear();
      for(int i=0; i<selection.size(); i++) {
        if (selection[i]) {
          set_antenna.push_back(i);
        }
      }
    }
  }
  cout << "bruteforce2 is complete, best score: " << best_score << endl;
  num_covered_base_stations = best_score;
}

int eval(const HittingSetData &data, const vector<bool> &selection) {

  // src and dest swap each iteration since set_symmetric_difference
  // can't be done in place.
  vector<int> single_covering_1;
  vector<int> single_covering_2;
  vector<int> *src = &single_covering_1;
  vector<int> *dest = &single_covering_2;
  vector<int> doubly_counted;
  for(int i=0; i<selection.size(); i++) {

    if (selection[i]) {
      // remove all known doubly_covereds from base_stations
      vector<int> base_stations_not_dc;
      set_difference(
          data.antennas[i].base_stations.begin(), 
          data.antennas[i].base_stations.end(), 
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
          back_inserter(doubly_counted));
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
    }
  }
  //cout << "new score is " << dest->size() << endl;
  return src->size();
}
