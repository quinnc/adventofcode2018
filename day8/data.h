#ifndef _DATA_
#define _DATA_ 1

#include <vector>
class Data;

class Data
{
public:
	void StartNew (ifstream & istr);
	int SumMetadatas ();

private:	
// header
	int numChildren;
	int numMetadatas;

	std::vector<Data*> children;
	std::vector<int> metadatas;
};
#endif

