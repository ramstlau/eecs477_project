#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <sstream>

using namespace std;

struct HittingSetData {
  int num_antennas, num_base_stations;
  vector<vector<int> > antennas;
};

HittingSetData readData(string filename) {
  std::cout.sync_with_stdio(false);
  ifstream fin;
  fin.open(filename);
  if (!fin.is_open()) {
    throw "Could not open file";
  }

  HittingSetData data;
  fin >> data.num_antennas >> data.num_base_stations;
  data.antennas.reserve(data.num_antennas);

  string line;
  while (getline(fin, line)) {
    std::istringstream is(line);
    data.antennas.push_back( 
      std::vector<int>( std::istream_iterator<int>(is), 
        std::istream_iterator<int>()
      ) 
    );
   }

  return data;
}

int main() {
  HittingSetData data = readData("test4.dat");
  for (vector<int> & v : data.antennas) {
    for (int & i : v) {
      cout << i << ' ';
    }
    cout << endl;
  }
}
