#include "input.h"
#include "greedy1.h"
#include "greedy2.h" 
#include <iostream>
#include <ctime>

void print_time(const clock_t &begin, const clock_t &end, string period_name);

int main(int argc, char *argv[])
{
        
  clock_t input_begin = clock();
  HittingSetData data;
  data.readData();
  cout << "data.num_antennas " << data.num_antennas << endl;
  //data.printBaseStations();
  vector<int> set_antenna;
  int num_covered_base_stations = 0;
  clock_t input_end = clock();
  print_time(input_begin, input_end, "Input"); 
  
  clock_t algo_begin = clock();
  greedy1(data, set_antenna, num_covered_base_stations);
  clock_t algo_end = clock();
  print_time(algo_begin, algo_end, "Algorithm"); 
  
  clock_t output_begin = clock();
  printVector(set_antenna);
  cout << num_covered_base_stations << endl;
  clock_t output_end = clock();
  print_time(output_begin, output_end, "Output"); 

  print_time(input_begin, output_end, "Total Program"); 

  return 0;
}

void print_time(const clock_t &begin, const clock_t &end, string period_name) {
  double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  cout << period_name << " took: " << elapsed_secs << " seconds" << endl;
}
