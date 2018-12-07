
#include <cstdio>

#include <iostream>
#include <fstream>

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

void CharCounter (const string& in, bool& hasDoubleChar, bool& hasTripleChar)
{


	hasDoubleChar = false;
	hasTripleChar = false;
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
	
	unsigned long numStrWithDoubleChar = 0;
	unsigned long numStrWithTripleChar = 0;	
	unsigned long numLines = 0;	
	string curr_line;

	inputf >> curr_line;
	while (inputf.good())
	{
		numLines++;
		
		bool hasDouble = false;
		bool hasTriple = false;

		CharCounter (curr_line, hasDouble, hasTriple);
		if (hasDouble)
			numStrWithDoubleChar++;
		if (hasTriple)
			numStrWithTripleChar++;

		inputf >> curr_line; 
	}

	cout << endl;
	cout << "Final string counts: with doubles=" << numStrWithDoubleChar << ", with triple=" << numStrWithTripleChar << ", sum=" << numStrWithDoubleChar + numStrWithTripleChar << endl;
	cout << "Total lines processed: " << numLines << endl;

	if (inputf.eof())
	{
		cout << "Ended because of EOF" << endl;
		return 0;
	}
	// else
	cout << "Ended because of another error" << endl;
	return -2;
}
