#ifndef _SOLVER_

#define _SOLVER_ 1

#include <fstream>
#include "data.h"

class Solver
{

public:
	void Process (std::ifstream& iStr);
	void PrintResults();
private:
	Data d;
};


#endif
