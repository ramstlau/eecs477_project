#include "input.h"
#include <cassert>

using namespace std;

int main(int argc, char *argv[])
{
	assert(argc == 2);
	
	HittingSetData data;
	data.readData(argv[1]);
	
	data.printData();





	return 0;
}
