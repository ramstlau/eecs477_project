#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <sstream>

using namespace std;

struct HittingSetData {
  // Problem Data
  int num_antennas, num_base_stations;
  vector<vector<int> > antennas;
  vector<int> base_stations; // value is the # of antennas covering this station

  // Solution Data
  set<int> sol_antennas;
  int num_base_stations_covered;

  // Methods
  HittingSetData() {
    num_base_stations_covered = 0;
  }
  void readData(string filename);
  void addAntenna(int i);
  void removeAntenna(int i);
  void printSolution();
};

void HittingSetData::readData(string filename) {
  std::cout.sync_with_stdio(false);
  ifstream fin;
  fin.open(filename);
  if (!fin.is_open()) {
    throw "Could not open file";
  }

  HittingSetData data;
  fin >> num_antennas >> num_base_stations;
  antennas.reserve(num_antennas);
  base_stations.resize(num_base_stations, 0);

  // Setup antennas
  string line;
  while (getline(fin, line)) {
    std::istringstream is(line);
    antennas.push_back( 
      std::vector<int>( std::istream_iterator<int>(is), 
        std::istream_iterator<int>()
      ) 
    );
  }
}

void HittingSetData::addAntenna(int i) {
  if (sol_antennas.emplace(i).second) {
    for (int &b : antennas[i]) {
      if (base_stations[b]++ == 1) {
        num_base_stations_covered--;
      }
      if (base_stations[b] == 1) {
        num_base_stations_covered++;
      }
    }
  }
}
void HittingSetData::removeAntenna(int i) {
  sol_antennas.erase(i);
  for (int &b : antennas[i]) {
    if (base_stations[b]-- == 1) {
      num_base_stations_covered--;
    }
    if (base_stations[b] == 1) {
      num_base_stations_covered++;
    }
  }
}

void HittingSetData::printSolution() {
  cout << sol_antennas.size();
  auto it=sol_antennas.begin();
  while (it != sol_antennas.end()) {
    cout << " " << *it++;
  }
  cout << endl << num_base_stations_covered << endl;
}

int main() {
  HittingSetData data;
  data.readData("test4.dat");
  data.addAntenna(1);
  data.addAntenna(2);
  data.printSolution();
  data.addAntenna(8);
  data.removeAntenna(8);
  data.printSolution();
}
