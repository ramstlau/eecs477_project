#ifndef _DRIVER_H_
#define _DRIVER_H_

#include <vector>
#include <cstdlib>
#include <utility> 

using namespace std;

void randomize_seed_data(HittingSetData &data, vector<int> &set_antenna) {
  srand(time(NULL));
  const int DENSITY = RAND_MAX / 4;
  for(int i=0; i<data.num_antennas; ++i) {
    if (rand() < DENSITY) {
      set_antenna.push_back(i);
    }
  }

}

#endif /* _INPUT_H_ */
