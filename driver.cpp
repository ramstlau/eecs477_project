#include "input.h"
#include "driver.h"
#include "greedy1.h"
#include "greedy2.h" 
#include "bruteforce2.h"
//#include "bottomup.h"
#include "bottomup2.h"
#include "topdown.h"
#include "maxdelta.h"
#include "maxdelta2.h"
#include "maxdelta3.h"
#include "simanneal.h"
#include "pq.h"
#include "coverage.h"
#include "validator.h"
#include <iostream>
#include <ctime>
#include <time.h>
#include <utility>

typedef void (*Solver)(HittingSetData &data, vector<int> &set_antenna, int &num_covered_base_stations, clock_t &algo_begin);

void print_time(const clock_t &begin, const clock_t &end, string period_name);
void single_algo(HittingSetData &data, vector<int> &set_antenna, int &num_covered_base_stations, Solver solver);
void all_algos(HittingSetData &data, vector<int> &set_antenna, int &num_covered_base_stations, vector<pair<string, Solver> > solvers);


int main(int argc, char *argv[])
{
        
  clock_t begin = clock();
  clock_t input_begin = clock();
  HittingSetData data;
  data.readData();
  //cout << "data.num_antennas " << data.num_antennas << endl;
  //data.printBaseStations();
  vector<int> set_antenna;
  int num_covered_base_stations = 0;
  clock_t input_end = clock();
  print_time(input_begin, input_end, "Input"); 

  // RANDOMIZE THE SEED DATA
  //randomize_seed_data(data, set_antenna);

  // SINGLE SOLVER
  //Solver solver = &greedy2;
  //Solver solver = &bottomup2_int;
  //Solver solver = &topdown_int_init;
  //Solver solver = &maxdelta3_int;
  Solver solver = &simanneal_int;
  //Solver solver = &bruteforce2;
  single_algo(data, set_antenna, num_covered_base_stations, solver);
  // PIPE OUTPUT FOR CONTINUATION
  //Solver solver2 = &maxdelta2_int;
  //single_algo(data, set_antenna, num_covered_base_stations, solver2);

  // MULTIPLE SOLVERS
  //vector<pair<string, Solver> > solvers;
  //solvers.push_back(make_pair<string, Solver>("Greedy 1", &greedy1));
  //solvers.push_back(make_pair<string, Solver>("Greedy 2", &greedy2));
  // bottomup is broken, don't include
  //solvers.push_back(make_pair<string, Solver>("Bottomup2", &bottomup2_int));
  //solvers.push_back(make_pair<string, Solver>("Topdown", &topdown_int_init));
  //solvers.push_back(make_pair<string, Solver>("Maxdelta", &maxdelta_int));
  //solvers.push_back(make_pair<string, Solver>("Maxdelta2", &maxdelta2_int));
  //solvers.push_back(make_pair<string, Solver>("Maxdelta3", &maxdelta3_int));
  //all_algos(data, set_antenna, num_covered_base_stations, solvers);
  
  clock_t end = clock();
  print_time(begin, end, "Total Program"); 

  return 0;
}

void single_algo(HittingSetData &data, vector<int> &set_antenna, int &num_covered_base_stations, Solver solver) {

  clock_t algo_begin = clock();
  solver(data, set_antenna, num_covered_base_stations, algo_begin);

  clock_t output_begin = clock();
  cout << set_antenna.size() << ' ';
  printVector(set_antenna);
  cout << num_covered_base_stations << endl;
  clock_t output_end = clock();
  print_time(output_begin, output_end, "Output"); 
}

void all_algos(HittingSetData &data, vector<int> &set_antenna, int &num_covered_base_stations, vector<pair<string, Solver> > solvers) {

  clock_t algo_begin, algo_end;
  vector<int> set_antenna_copy;
  int num_covered_base_stations_copy = num_covered_base_stations;
  for(pair<string, Solver> &p : solvers) {
    set_antenna_copy = set_antenna;
    string solver_name = p.first;
    Solver solver = p.second;

    algo_begin = clock(); 
    solver(data, set_antenna_copy, num_covered_base_stations_copy, algo_begin);
    unsigned int score = num_covered_base_stations_copy;
    try {
      validate(data, set_antenna_copy, score);
    } catch(...) {
      cout << "VALIDATOR FAILED" << endl;
    }
    algo_end = clock();

    print_time(algo_begin, algo_end, solver_name);
    //cout << set_antenna.size() << " ";
    //printVector(set_antenna);
    cout << num_covered_base_stations_copy << endl << endl;
  }
}

void print_time(const clock_t &begin, const clock_t &end, string period_name) {
  double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  cout << period_name << " took: " << elapsed_secs << " seconds" << endl;
}
