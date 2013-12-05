#include "input.h"
#include <cassert>
#include <algorithm>
#include <iostream>

using namespace std;

void bruteforce(HittingSetData &data, int setNum, int level, vector<int> &set_antenna, vector<int> &set_base, vector<int> &onecovered, vector<int> &dc, int &onecoveredNum)
{	  

	//return if invalid
	if(setNum > data.num_antennas -1)
		return;
	
	//TODO: only for debugging purposes, remove eventually
	cout << "set base is: ";
  for(unsigned int i = 0; i < set_base.size(); i++)
  {
    cout << set_base.at(i) << " ";  
  }
	cout << endl;	
	cout << "set onecovered is: ";
  for(unsigned int i = 0; i < onecovered.size(); i++)
  {
    cout << onecovered.at(i) << " ";  
  }
  cout << endl;
	cout << "data.antennas... is: ";
  for(unsigned int i = 0; i < data.antennas.at(setNum).size(); i++)
  {
    cout << data.antennas.at(setNum).at(i) << " ";  
  }
  cout << endl;
	cout << "don't cares are: ";
	for(unsigned int i = 0; i < dc.size(); i++)
  {
    cout << dc.at(i) << " ";  
  }
  cout << endl;
	  
	  
	//put current set into R
	//first shrink data set, take the don't cares out.
	vector<int> newSet2(data.num_base_stations);	

  vector<int>::iterator it2 = set_difference(
      data.antennas.at(setNum).begin(), 
      data.antennas.at(setNum).end(), 
      dc.begin(), 
      dc.end(),
      newSet2.begin());
       
  newSet2.erase(it2, newSet2.end()); //this should be the shrunk set without dcs
 
  //TODO: only for debugging purposes, remove eventually
  cout << "shrunk data.antennas... is: ";
  for(unsigned int i = 0; i < newSet2.size(); i++)
  {
    cout << newSet2.at(i) << " ";  
  }
	cout << endl;

	//given that we add this element, calculate the new onecovered set
	vector<int> newSet3(data.num_base_stations);
	it2 = set_symmetric_difference(
      onecovered.begin(), 
      onecovered.end(), 
      newSet2.begin(), 
      newSet2.end(),
      newSet3.begin());
  newSet3.erase(it2, newSet3.end()); //this should be the new onecovered set
       
  //TODO: only for debugging purposes, remove eventually
  cout << "the symettric difference : ";
  for(unsigned int i = 0; i < newSet3.size(); i++)
	{
	  cout << newSet3.at(i) << " ";  
	}
	cout << endl;
       
  //calculate intersection between, old onecovered and shrunk data set because this will go into dc
  vector<int> newSet4(data.num_base_stations);
  it2 = set_intersection(
      onecovered.begin(), 
      onecovered.end(), 
      newSet2.begin(), 
      newSet2.end(),
      newSet4.begin());
 	newSet4.erase(it2, newSet4.end()); //this should be put into dc
	
	//update dc, TODO: this could alternatively be a push_back + for loop operation
	newSet2.resize(data.num_base_stations);
	it2 = set_union(
      dc.begin(), 
      dc.end(), 
      newSet4.begin(), 
      newSet4.end(), 
      newSet2.begin());
	newSet2.erase(it2, newSet2.end());	 				   

  //given that we add the current element, calculate total new set of base stations
  vector<int> newSet(data.num_base_stations);
  vector<int>::iterator it = set_union(
      set_base.begin(), 
      set_base.end(), 
      data.antennas.at(setNum).begin(), 
      data.antennas.at(setNum).end(),
      newSet.begin());
  newSet.erase(it, newSet.end());
       
  //TODO: only for debugging purposes, remove eventually
  cout << "set num " << setNum << " level " << level << " set_antenna size " << set_antenna.size() << " set_base size " << set_base.size() << " onecoveredNum " << onecoveredNum << endl;
       		
  if(setNum >= data.num_antennas -1)
	{
	  //TODO: check this logic. 
	  //you only want to add the last element if the calculated oneCovered number is greater than it's previous
    if((int)newSet3.size() >= onecoveredNum)
    {
      //add antenna to set
      cout << "ADDS LAST ELEMENT\n";
      set_antenna.at(level) = setNum;
      set_base.swap(newSet);
      onecovered.swap(newSet3);
      onecoveredNum = onecovered.size();
      dc.swap(newSet2);
    }
    cout << "RETURNS UP FUNCITON CALL STACK\n";
    return;
	}
	
	//add antenna to set
	set_antenna.at(level) = setNum;
	onecovered.swap(newSet3);
	dc.swap(newSet2);
	onecoveredNum = onecovered.size();
	
	
	//make copies for recursive calls
	vector<int> b1(newSet), b2(newSet), a1(set_antenna), a2(set_antenna), n1(onecovered), n2(onecovered), dc1(dc), dc2(dc);
	int nn1 = onecoveredNum, nn2 = onecoveredNum;
	
	//given that you included current set, include next set in R?
	bruteforce(data, setNum+1, level+1, a1, b1, n1, dc1, nn1);

	//given that you included current set, disclude next set in R?
	bruteforce(data, setNum+2, level+1, a2, b2, n2, dc2, nn2);
	
	//select which one did better
	if(nn1 > nn2)
  {
    newSet.swap(b1);
    set_antenna.swap(a1);
    onecovered.swap(n1);
    onecoveredNum = nn1;
    dc.swap(dc1);
  }
	else
  {
    newSet.swap(b2);
    set_antenna.swap(a2);
    onecovered.swap(n2);
    onecoveredNum = nn2;
    dc.swap(dc2);
  }

	//TODO: only for debugging purposes, remove eventually
	cout << "printing out antennas in set ";
	for(unsigned int i = 0; i < set_antenna.size(); i++)
  {
    cout << set_antenna.at(i) << " ";  
  }
  cout << endl;
	set_base.swap(newSet);
	
	//TODO: only for debugging purposes, remove eventually
	cout << "returns one level up from " << level << endl;

}

void bruteforce_helper(HittingSetData &data, int setNum, int level, vector<int> &set_antenna)
{
	//make copies for recursive calls
	vector<int> b1(data.antennas.at(setNum)), b2, a1(set_antenna), a2(set_antenna), n1(data.antennas.at(setNum)), n2, dc1, dc2;
	int nn1 = data.antennas.at(setNum).size(), nn2 = 0;
	a1.at(level) = setNum;
	
	cout << "brute force called 1"  << endl;
	bruteforce(data, setNum+1, level+1, a1, b1, n1, dc1, nn1);
	
	cout << "brute force called 2 " << endl;
	bruteforce(data, setNum+2, level+1, a2, b2, n2, dc2, nn2);
	
  //select which one did better
  //TODO: check this logic
	if(nn1 > nn2)
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
