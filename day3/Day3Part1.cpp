#include <cstdio>
#include <iostream>
#include <vector>

#include "Day3Part1.h"
using namespace std;

void Day3Part1::Process (const string& line)
{
	int x, y, x_dist, y_dist;

	if (ParseLine (line, x, y, x_dist, y_dist))
	{
		for (int curr_x = x; curr_x < (x+x_dist); curr_x++)
		{
			for (int curr_y = y; curr_y < (y+y_dist); curr_y++)
			{
				Swatch currSwatch = make_pair(curr_x, curr_y);
				this->fabricClaims[currSwatch]++;
			}
		}
	}
	else
	{
		cout << "Unable to parse line: " << line << endl;
	}
}

void Day3Part1::PrintResults ()
{
	this->multiusers = 0;
	for (const auto& s : this->fabricClaims)
	{
		if (s.second > 1)
			this->multiusers++;
	}

	cout << "Number of square inches that were requested by multiple elves: " << this->multiusers << endl; 
}


bool Day3Part1::ParseLine (const string& line, int& x, int& y, int& x_dist, int& y_dist)
{
	// first split on the spaces
	// e.g. #1 @ 1,3: 4x4

//	cout << " line to parse = " << line << endl;

	std::vector<string> sections;
	int curr_start = 0;
	int curr_section = 0;
	int curr_end = 0;

	while (curr_end != std::string::npos && curr_start < line.size() && curr_section < 10)
	{
		curr_end = line.find(' ', curr_start);
		//cout << "curr_start = " << curr_start << endl;
		//cout << "curr end   = " << curr_end << endl;
		//cout << " section   = " << curr_section << endl;


		sections.push_back(line.substr(curr_start, (curr_end - curr_start)));
		//cout << " found substring = " << sections[curr_section] << endl;
		curr_section++;
		curr_start = curr_end + 1;
	}

#if 0
	for (unsigned int i = 0; i < sections.size(); i++)
	{
		cout << " section " << i << " : [" << sections[i] << "]" << endl;
	}
#endif
	if (sections.size() != 4)
		return false;

	if (curr_section != sections.size())
		return false;

	// section 3 contains the base coords
	int commaloc = sections[2].find(',');
	int colonloc = sections[2].find(':', commaloc);

	x = atoi(sections[2].substr(0,commaloc).c_str());
	y = atoi(sections[2].substr(commaloc+1, (commaloc-colonloc)).c_str());

	// section 4 contains the distances
	int xloc = sections[3].find('x');
	x_dist = atoi(sections[3].substr(0,xloc).c_str());
	y_dist = atoi(sections[3].substr(xloc+1).c_str());

	if (x_dist == 0 || y_dist == 0)
		return false;

	if (x < 0 || x > 1000 || y < 0 || y > 1000)
		return false;

	return true;
}
