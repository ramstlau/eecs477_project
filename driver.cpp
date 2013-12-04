#include "input.h"
#include "greedy1.h"
#include "greedy2.h" 
#include "bruteforce2.h"
#include "pq.h"
#include "bottomup.h"
#include "topdown.h"
#include <iostream>
#include <ctime>
#include <utility>

typedef void (*Solver)(HittingSetData &data, vector<int> &set_antenna, int &num_covered_base_stations);

void print_time(const clock_t &begin, const clock_t &end, string period_name);
void single_algo(HittingSetData &data, vector<int> &set_antenna, int &num_covered_base_stations, Solver solver);
void all_algos(HittingSetData &data, vector<int> &set_antenna, int &num_covered_base_stations, vector<pair<string, Solver> > solvers);

int main(int argc, char *argv[])
{
        
  clock_t begin = clock();
  clock_t input_begin = clock();
  HittingSetData data;
  data.readData();
  cout << "data.num_antennas " << data.num_antennas << endl;
  //data.printBaseStations();
  vector<int> set_antenna;
  int num_covered_base_stations = 0;
  clock_t input_end = clock();
  print_time(input_begin, input_end, "Input"); 
  

  // Single solver
  clock_t algo_begin = clock();
  //Solver solver = &bottomup_int_input;
  Solver solver = &topdown_int_init;
  //Solver solver = &bruteforce2;
  single_algo(data, set_antenna, num_covered_base_stations, solver);
  clock_t algo_end = clock();
  print_time(algo_begin, algo_end, "Algorithm"); 

  // All solvers
  //vector<pair<string, Solver> > solvers;
  //solvers.push_back(make_pair<string, Solver>("Greedy 1", &greedy1));
  //solvers.push_back(make_pair<string, Solver>("Greedy 2", &greedy2));
  //all_algos(data, set_antenna, num_covered_base_stations, solvers);
  
  
  clock_t end = clock();
  print_time(begin, end, "Total Program"); 

  return 0;
}

void single_algo(HittingSetData &data, vector<int> &set_antenna, int &num_covered_base_stations, Solver solver) {

  solver(data, set_antenna, num_covered_base_stations);

  clock_t output_begin = clock();
  printVector(set_antenna);
  cout << num_covered_base_stations << endl;
  clock_t output_end = clock();
  print_time(output_begin, output_end, "Output"); 
}

void all_algos(HittingSetData &data, vector<int> &set_antenna, int &num_covered_base_stations, vector<pair<string, Solver> > solvers) {

  clock_t algo_begin, algo_end;
  for(pair<string, Solver> &p : solvers) {
    string solver_name = p.first;
    Solver solver = p.second;

    algo_begin = clock(); 
    solver(data, set_antenna, num_covered_base_stations);
    algo_end = clock();

    print_time(algo_begin, algo_end, solver_name);
    printVector(set_antenna);
    cout << num_covered_base_stations << endl << endl;
  }
}

void print_time(const clock_t &begin, const clock_t &end, string period_name) {
  double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  cout << period_name << " took: " << elapsed_secs << " seconds" << endl;
}
