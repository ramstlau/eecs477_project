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
  for(int i=0; i<selection.size(); i++) {

    if (selection[i]) {
      // DEBUG, TODO
      //cout << "adding seleciton: " << i << endl;
      //for(auto it = src->begin(); it != src->end(); ++it) {
        //cout << *it << ' ';
      //}

      // TODO TODO: Need to track a doubly counted list - can't re-add later
      dest->clear();
      set_symmetric_difference(
          src->begin(), 
          src->end(), 
          data.antennas[i].base_stations.begin(), 
          data.antennas[i].base_stations.end(), 
          back_inserter(*dest));
      swap(src, dest); 
    }
  }
  //cout << "new score is " << dest->size() << endl;
  return dest->size();
}
