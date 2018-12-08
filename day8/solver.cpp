#include "solver.h"

#include <cstdio>
#include <iostream>

using namespace std;

void Solver::Process (ifstream& iStr)
{
	d.StartNew(iStr);

}

void Solver::PrintResults()
{
	
	int sum = d.SumMetadatas();
	cout << " Sum of all the metadatas is: " << sum << endl;
}


