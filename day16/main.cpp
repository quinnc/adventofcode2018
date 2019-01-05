
#include <cstdio>

#include <iostream>
#include <fstream>
#include <utility>
#include <vector>

#include "opcodes.h"

using namespace std;

void usage (char * appname)
{
	cout << endl
	<< appname << " <filename>"
	<< endl
	<< "\t USAGE: " << endl
	<< "\t\t<filename> : name the input file as a parameter!"  << endl
	<< std::endl;
}

void InitOps (void);

typedef pair<string, OpCode*> OpPair_t;
typedef vector<OpPair_t> OpList_t;


OpList_t opList;
int numCodes;

int main (int argc, char** argv)
{
	if (argc != 2)
	{
		std::cout << endl
			<< "ERROR: expected 1 argument, provided " << argc-1;
		usage(argv[0]);
		return -1;
	}

	ifstream inputf;

	InitOps();
	
	inputf.open(argv[1]);
	if (!inputf.good())
	{
		cout << endl
			<< "ERROR: unable to open input file (" << argv[1] << ")" << endl;
		usage(argv[0]);
		return -1;
	}
	
	unsigned long numLines = 0;	
	string curr_line;
	
	int numberCommandsMoreThan3ops = 0;
	int numCommandsMatch2Ops = 0;
	int numCommandsMatch1Op = 0;
	int numCommandsMatchNoOps = 0;
	
	typedef std::pair<int, vector<int>> IndexesForThisOp;
	vector<IndexesForThisOp> matchingIndexes;

	while (std::getline(inputf, curr_line))
	{
		cout << __FUNCTION__ << ":" << __LINE__ << " - read in line ==" << curr_line << "==" << endl;
		if (curr_line.empty())
			continue;
		numLines++;
	
		int numMatchingOpCodes = 0;
		int matchedOpIndex = -1;
		int currOpCode = -1;
	
		string cmd_line;
		string resultsLine;

		std::getline(inputf, cmd_line);
		std::getline(inputf, resultsLine);

		cout << __FUNCTION__ << ":" << __LINE__ << " -cmd n line ==" << cmd_line << "==" << endl;
		cout << __FUNCTION__ << ":" << __LINE__ << " - result line ==" << resultsLine << "==" << endl;

		for (int i=0; i < numCodes; i++)
		{
			opList[i].second->Init(curr_line);
			opList[i].second->Exec(cmd_line);

			bool match = opList[i].second->DoResultsMatch(resultsLine);
			
			if ( match )
			{
				numMatchingOpCodes++;
				cout << __FUNCTION__ << ":" << __LINE__ << " - matched op=" << opList[i].first << endl;
				
				currOpCode = opList[i].second->ParsedOpNum();
				matchedOpIndex = i;
			}
		}

		cout << __FUNCTION__ << ":" << __LINE__ << " - num matching ops ==" << numMatchingOpCodes << "==" << endl;
		if (numMatchingOpCodes > 2)
		{
			numberCommandsMoreThan3ops++;
		}
		else if (numMatchingOpCodes == 2)
		{
			numCommandsMatch2Ops++;
		}
		else if (numMatchingOpCodes == 1)
		{
			numCommandsMatch1Op++;
			opList[matchedOpIndex].second->SetOpNum(currOpCode);
		}
		else
		{
			numCommandsMatchNoOps++;
		}
	}


	cout << "Number of lines read = " << numLines << endl;
	cout << __FUNCTION__ << ":" << __LINE__ << " - num that match 3 or more ops == " << numberCommandsMoreThan3ops 
		<< "== num that match 2 ops=" << numCommandsMatch2Ops 
		<< ", num that match 1 op = " << numCommandsMatch1Op
		<< ", num that match 0 =" << numCommandsMatchNoOps << endl;


	for (int i=0; i < numCodes; i++)
	{
		opList[i].second->PrintInfo();
	}

	if (inputf.eof())
	{
		cout << "Ended because of EOF" << endl;
		return 0;
	}
	// else
	cout << "Ended because of another error" << endl;
	return -2;
}



void InitOps (void)
{
	opList.push_back(make_pair("addi", new AddI()));
	opList.push_back(make_pair("addr", new AddR()));

	opList.push_back(make_pair("mulr", new MultR()));
	opList.push_back(make_pair("muli", new MultI()));

	opList.push_back(make_pair("banr", new BanR()));
	opList.push_back(make_pair("bani", new BandI()));

	opList.push_back(make_pair("borr", new BorR()));
	opList.push_back(make_pair("bori", new BorI()));

	opList.push_back(make_pair("setr", new SetR()));
	opList.push_back(make_pair("seti", new SetI()));

	opList.push_back(make_pair("gtir", new GtIR()));
	opList.push_back(make_pair("gtri", new GtRI()));
	opList.push_back(make_pair("gtrr", new GtRR()));

	opList.push_back(make_pair("eqir", new EqIR()));
	opList.push_back(make_pair("eqri", new EqRI()));
	opList.push_back(make_pair("eqrr", new EqRR()));

	numCodes = opList.size();
}
