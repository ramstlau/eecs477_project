#include "input.h"
#include <cassert>
#include <algorithm>
#include <iostream>

using namespace std;

void bruteforce(HittingSetData &data, int setNum, int level, vector<int> &set_antenna, vector<int> &set_base, vector<int> &covered, int &coveredNum)
{	  

	//return if invalid
	if(setNum > data.num_antennas -1)
		return;
		
	        cout << "set covered is: ";
        for(unsigned int i = 0; i < covered.size(); i++)
	  {
	    cout << covered.at(i) << " ";  
	  }
	  cout << endl;
	cout << "data.antennas... is: ";
        for(unsigned int i = 0; i < data.antennas.at(setNum).size(); i++)
	  {
	    cout << data.antennas.at(setNum).at(i) << " ";  
	  }
	  cout << endl;
	//put current set into R

	//calculate new coveredNum
	vector<int> newSet2(data.num_base_stations);
	vector<int>::iterator it2 = set_symmetric_difference(covered.begin(), covered.end(), 
			 				    data.antennas.at(setNum).begin(), data.antennas.at(setNum).end(),
			 				    newSet2.begin());
       newSet2.erase(it2, newSet2.end());
       

       coveredNum = newSet2.size();
       cout << "the symettric difference : ";
       for(unsigned int i = 0; i < newSet2.size(); i++)
	  {
	    cout << newSet2.at(i) << " ";  
	  }
	cout << endl;
       vector<int> newSet(data.num_base_stations);
       //calculate new set of base stations
       vector<int>::iterator it = set_union(set_base.begin(), set_base.end(), 
			 	     data.antennas.at(setNum).begin(), data.antennas.at(setNum).end(),
			 	     newSet.begin());
       newSet.erase(it, newSet.end());
       
       //covered needs to be the set_base - symetric union for the next call
       covered.resize(data.num_base_stations);
       vector<int>::iterator it3 = set_difference(newSet.begin(), newSet.end(), 
			 	     newSet2.begin(), newSet.end(),
			 	     covered.begin());
 	covered.erase(it3, covered.end());
       
       cout << "set num " << setNum << " level " << level << " set_antenna size " << set_antenna.size() << " set_base size " << set_base.size() << " coveredNum " << coveredNum << endl;
       if(level >= data.num_antennas -1)
	  {
	     if(newSet.size() >= set_base.size())
	       {
	       	 //add antenna to set
		 set_antenna.at(level) = setNum;
		 set_base.swap(newSet);
	       }
	    
	    return;
	  }
	
	//add antenna to set
	set_antenna.at(level) = setNum;
	
	//make copies for recursive calls
	vector<int> b1(newSet), b2(newSet), a1(set_antenna), a2(set_antenna), n1(covered), n2(covered);
	int nn1 = coveredNum, nn2 = 0;
	
	//include next set in R
	bruteforce(data, setNum+1, level+1, a1, b1, n1, nn1);
	
	//cout << " came back here" << endl;
	//disclude next set in R
	bruteforce(data, setNum+2, level+1, a2, b2, n2, nn2);
	
	//select which one did better
	if(nn1 > nn2)
	  {
	    newSet.swap(b1);
	    set_antenna.swap(a1);
	    covered.swap(n1);
	    coveredNum = nn1;
	  }
	else
	  {
	    newSet.swap(b2);
	    set_antenna.swap(a2);
	    covered.swap(n2);
	    coveredNum = nn2;
	  }

	for(unsigned int i = 0; i < set_antenna.size(); i++)
	  {
	    cout << set_antenna.at(i) << " ";  
	  }
	  cout << endl;
	set_base.swap(newSet);

}

void bruteforce_helper(HittingSetData &data, int setNum, int level, vector<int> &set_antenna)
{
	//make copies for recursive calls
	vector<int> b1(data.antennas.at(setNum)), b2, a1(set_antenna), a2(set_antenna), n1(data.antennas.at(setNum)), n2;
	int nn1 = data.antennas.at(setNum).size(), nn2 = 0;
	a1.at(level) = setNum;
	
	cout << "brute force called 1"  << endl;
	bruteforce(data, setNum+1, level+1, a1, b1, n1, nn1);
	
	cout << "brute force called 2 " << endl;
	bruteforce(data, setNum+2, level+1, a2, b2, n2, nn2);
	
        //select which one did better
	if(n1 > n2)
	  {
	    set_antenna.swap(a1);
	  }
	else
	  {
	    set_antenna.swap(a2);
	  }

	return;
}

int main(int argc, char *argv[])
{
	assert(argc == 2);
	
	HittingSetData data;
	data.readData(argv[1]);
	cout << "data.num_antennas" << data.num_antennas << endl;
	vector<int> set_antenna;
	set_antenna.resize(6, -1);
	
	cout << "bruteforce_helper called" << endl;
	bruteforce_helper(data, 0, 0, set_antenna);

	for(unsigned int i = 0; i < set_antenna.size(); i++)
	  {
	    cout << set_antenna.at(i) << " ";  
	  }
	  

	return 0;
}
