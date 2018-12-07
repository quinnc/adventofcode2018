
#include <cstdio>

#include <iostream>
#include <fstream>

using namespace std;

void usage (char * appname)
{
	cout << endl
	<< argv[0] << " <filename>"
	<< endl
	<< "\t USAGE: "
	<< "\t\t<filename> : name the input file as a parameter!" 
	<< std::endl;
}

int main (int argc, char** argv)
{
	if (argc != 2)
	{
		std::cout << endl
			<< "ERROR: expected 1 argument, provided " << argc;
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
	
	int curr_loc = 0;
	int lines = 0;
	
	cout << endl << endl << curr_loc ;
	
	while (inputf.good())
	{
		//char * line = new char(100) {0};
		//int curr_motion;
		//inputf.readline(line, 99);
		
		inputf >> curr_motion;
		curr_loc += curr_motion;
		cout << "  + " << curr_motion << " = " << curr_loc;
		lines++;
		
	}

	cout << endl;
	cout << "Final location: " << curr_loc << endl;
	cout << "Total lines processed: " << lines;
	if (inputf.eof())
	{
		cout << "Ended because of EOF" << endl;
		return 0;
	}
	// else
	cout << "Ended because of another error" << endl;
	return -2;
}
