#include "input.h"
#include "greedy1.h"
#include "greedy2.h" 
#include <iostream>

int main(int argc, char *argv[])
{
        
  HittingSetData data;
  data.readData();
  cout << "data.num_antennas " << data.num_antennas << endl;
  vector<int> set_antenna;
  int num_covered_base_stations = 0;

  //data.printBaseStations();
  
  greedy2(data, set_antenna, num_covered_base_stations);
  

  printVector(set_antenna);
  cout << num_covered_base_stations << endl;
    

  return 0;
}
