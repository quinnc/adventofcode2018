
#include <cstdio>

#include <iostream>
#include <fstream>

#include "parser.h"

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
	Parser logick;

	//inputf >> curr_line;
	
	while (std::getline(inputf, curr_line))
	{
		numLines++;
			
		
		logick.Process(curr_line);
	}


	logick.PrintResults();
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
