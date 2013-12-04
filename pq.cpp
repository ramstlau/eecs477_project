#include "input.h"
#include "pq.h"
#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <deque>

using namespace std;

void update_coverage(
    vector<int> *&src, 
    vector<int> *&dest,
    vector<int> &doubly_counted, 
    vector<int> &base_stations)
{
  cout << "UPDATE:" << endl;
  cout << "src: " << src->size() << endl;
  cout << "dest: " << dest->size() << endl;
  cout << "stations: " << base_stations.size() << endl;
  
  // remove all known doubly_covereds from base_stations
  vector<int> base_stations_not_dc;
  set_difference(
      base_stations.begin(), 
      base_stations.end(), 
      doubly_counted.begin(), 
      doubly_counted.end(), 
      back_inserter(base_stations_not_dc));
  cout << "non-dc stations: " << base_stations_not_dc.size() << endl;

  // add new double counts to doubly_counted
  // no need to remove from base_stations_not_dc, symmetric difference will remove
  set_intersection(
      src->begin(), 
      src->end(), 
      base_stations_not_dc.begin(), 
      base_stations_not_dc.end(), 
      back_inserter(doubly_counted));   // this creates duplicates, might be able to improve
  cout << "new dc: " << doubly_counted.size() << endl;

  set_symmetric_difference( // still need symmetric difference instead of union
                            // because new dc's weren't removed from base_stations
      src->begin(), 
      src->end(), 
      base_stations_not_dc.begin(), 
      base_stations_not_dc.end(), 
      back_inserter(*dest));

  src->clear();
  swap(src, dest); 

  cout << "AFTER:" << endl;
  cout << "src: " << src->size() << endl;
  cout << "dest: " << dest->size() << endl;
}

int get_delta(vector<int> &base_stations, int i, vector<int> *src)
{
  vector<int> temp;
  set_symmetric_difference(
      src->begin(),
      src->end(),
      base_stations.begin(),
      base_stations.end(),
      back_inserter(temp));

  //cout << "src: " << endl;
  //for(int &i : *src) {
    //cout << i << ' ';
  //}
  //cout << endl;
  //cout << "new: " << endl;
  //for(int &i : base_stations) {
    //cout << i << ' ';
  //}
  //cout << endl;
  //cout << "temp: " << endl;
  //for(int &i : temp) {
    //cout << i << ' ';
  //}
  //cout << endl;

  int old_coverage = src->size();
  int new_coverage = temp.size();
  //cout << "old count: " << old_coverage << endl;
  //cout << "new count: " << new_coverage << endl;

  return (new_coverage - old_coverage);
}

