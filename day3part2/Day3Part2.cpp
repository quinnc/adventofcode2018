#include <cstdio>
#include <iostream>
#include <vector>

#include "Day3Part2.h"
using namespace std;

void Day3Part1::Process (const string& line)
{
	int x, y, x_dist, y_dist;
	int id;

	//cout << "A" << endl;
	if (ParseLine (line, id, x, y, x_dist, y_dist))
	{
		//cout << "B" << endl;

		bool allFirsts = true;
		for (int curr_x = x; curr_x < (x+x_dist); curr_x++)
		{
			//cout << "C curr x = " << curr_x << endl;

			for (int curr_y = y; curr_y < (y+y_dist); curr_y++)
			{
				//cout << "D curr y = " << curr_y << endl;

				Swatch currSwatch = make_pair(curr_x, curr_y);
				auto swatchThere = this->fabricClaims.emplace(currSwatch, id);
				//cout << " E " << endl;
				
				if (!swatchThere.second)
				{
					//cout << "F" << endl;
					allFirsts = false;
					unsharedIds.erase(swatchThere.first->second);
				}
				
				//cout << "F" << endl;
			}
		}

//		cout << " G' all firsts??? " << allFirsts << ", id=" << id << ", line=" << line << endl;
		if (allFirsts)
		{
	//		cout << " list of unshared ids before=" << this->unsharedIds.size() << endl;
			this->unsharedIds[id] = id;
	//		cout << " size of unshared ids after adding current = " << this->unsharedIds.size() << endl;
		}

	//	cout << "G" << endl;
	}
	else
	{
		//cout << "Unable to parse line: " << line << endl;
	}

	//cout << " H" << endl;
}

void Day3Part1::PrintResults ()
{

	for (const auto& id : this->unsharedIds)
	{
		cout << " ID without any shared fabric: " << id.second << endl;
	}

}


bool Day3Part1::ParseLine (const string& line, int& id, int& x, int& y, int& x_dist, int& y_dist)
{
	// first split on the spaces
	// e.g. #1 @ 1,3: 4x4

	//cout << " line to parse = " << line << endl;

	std::vector<string> sections;
	int curr_start = 0;
	int curr_section = 0;
	int curr_end = 0;

	id = -1;
	x = -1;
	y = -1;
	x_dist = -1;
	y_dist = -1;


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
		//cout << " section " << i << " : [" << sections[i] << "]" << endl;
	}
#endif
	if (sections.size() != 4)
		return false;

	if (curr_section != sections.size())
		return false;

	// section 1 contains the id
	id = atoi(sections[0].substr(1).c_str());

	//cout << "id = " << id << endl;
	if (id <= 0)
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
