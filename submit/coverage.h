#include "input.h"
#include "pq.h"
#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>

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
        if (set_antennas[i]) {
          add_coverage(data, i);
        }
      }
    }
    void add_coverage(HittingSetData &data, int &antenna) {
      for(int &i : data.antennas[antenna].base_stations) {
        if(coverage[i] == 1) {
          --score;
        }
        ++coverage[i];
        if(coverage[i] == 1) {
          ++score;
        }
      }
    }
    void remove_coverage(HittingSetData &data, int &antenna) {
      for(int &i : data.antennas[antenna].base_stations) {
        if(coverage[i] == 1) {
          --score;
        }
        --coverage[i];
        if(coverage[i] == 1) {
          ++score;
        }
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
    void print() {
      for(int i=0; i<coverage.size(); ++i) {
        cout << i << ": " << coverage[i] << endl;
      }
    }
};
