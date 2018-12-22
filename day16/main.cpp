
#include <cstdio>

#include <iostream>
#include <fstream>
#include <utility>

#include “opcodes.h”

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

	//inputf >> curr_line;
	
	while (std::getline(inputf, curr_line))
	{
		numLines++;

		out << __FUNCTION__ << “:” << __LINE__ << “ - read in line ==“ << curr_line << “==“ << ends;
			
		int numMatchingOpCodes = 0;
		
		for (int i=0; i < numCodes; i++)
		{
			ops[i].Init(curr_line);

			ops[i].
		d3p1.Process(curr_line);
	}


	d3p1.PrintResults();
	cout << "Number of lines read = " << numLines << endl;

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
	opsList.push_back(make_pair(“addi”, new AddI());
	opsList.push_back(make_pair(“addr”, new AddR());
	
	opsList.push_back(make_pair(“mulr”, new MultR());
	opsList.push_back(make_pair(“muli”, new MultI());

	opsList.push_back(make_pair(“banr”, new BanR());
	opsList.push_back(make_pair(“bani”, new BanI());

	opsList.push_back(make_pair(“borr”, new BorR());
	opsList.push_back(make_pair(“bori”, new BorI());

	opsList.push_back(make_pair(“setr”, new SetR());
	opsList.push_back(make_pair(“seti”, new SetI());

	opsList.push_back(make_pair(“gtir”, new R());
	opsList.push_back(make_pair(“muli”, new MultI());
	opsList.push_back(make_pair(“muli”, new MultI());

}