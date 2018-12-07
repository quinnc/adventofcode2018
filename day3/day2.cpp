
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

	int letterCounts[26] = {0};

	for (size_t idx = 0; idx < in.length(); idx++)
	{
		char curr = in[idx];
		letterCounts[(int)(curr - 'a')]++;
	}

	for (int i = 0; i < 26; i++)
	{
		if (letterCounts[i] == 2)
			hasDoubleChar = true;
		if (letterCounts[i] == 3)
			hasTripleChar = true;

		cout << " " << (char)(i+'a') << "=>" << letterCounts[i];
	}

	cout << endl;

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
	cout << "Final string counts: with doubles=" << numStrWithDoubleChar << ", with triple=" << numStrWithTripleChar << ", multiplied =" << numStrWithDoubleChar * numStrWithTripleChar << endl;
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
