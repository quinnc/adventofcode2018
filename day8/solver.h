#ifndef _SOLVER_

#define _SOLVER_ 1

#include <fstream>
#include "data.h"

class Solver
{

public:
	void Process (ifstream& iStr);
	void PrintResults();
private:
	Data d;
};


#endif
