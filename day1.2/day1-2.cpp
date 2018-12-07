
#include <cstdio>

#include <iostream>
#include <fstream>
#include <vector>

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
	
	int curr_loc = 0;
	int lines = 0;
	std::vector<int> totals_history;
	std::vector<int> motion_history;
	bool found_history_match = false;
	int match_value = -99;

	totals_history.push_back(curr_loc);		
	cout << endl << endl << curr_loc ;
	
		int curr_motion;
		inputf >> curr_motion;
	while (inputf.good())
	{
		motion_history.push_back(curr_motion);

		curr_loc += curr_motion;
		auto i = totals_history.cbegin();
		while (i != totals_history.cend() && (*i) != curr_loc)
			i++;

		if (i != totals_history.cend())
		
		{
			if (! found_history_match)
			{
				found_history_match = true;
				match_value = curr_loc;
			}
		}

		else
		{
			totals_history.push_back(curr_loc);
		}
		cout << "  + " << curr_motion << " = " << curr_loc;
		lines++;
		
		inputf >> curr_motion;
		if (lines % 10 == 0)
			cout << endl;

	}

	while (!found_history_match)
	{
		for (auto p_curr_motion = motion_history.cbegin(); p_curr_motion != motion_history.cend(); p_curr_motion++)
		{
	             curr_loc += (*p_curr_motion);
                auto i = totals_history.cbegin();
                while (i != totals_history.cend() && (*i) != curr_loc)
                        i++;

                if (i != totals_history.cend())
                {
                        if (! found_history_match)
                        {
                                found_history_match = true;
                                match_value = curr_loc;
                        }
                }
               else
                {
                        totals_history.push_back(curr_loc);
                }
              cout << "  + " << curr_motion << " = " << curr_loc;
                lines++;

                inputf >> curr_motion;
                if (lines % 10 == 0)
                        cout << endl;
		if (found_history_match)
			break;
		}
        }


	cout << endl;
	cout << "Final location: " << curr_loc << endl;
	cout << "Total lines processed: " << lines << endl;
	cout << "First location repetition: " << match_value << endl;
	cout << "Found a repetition? " << found_history_match << endl;	
	if (inputf.eof())
	{
		cout << "Ended because of EOF" << endl;
		return 0;
	}
	// else
	cout << "Ended because of another error" << endl;
	return -2;
}
