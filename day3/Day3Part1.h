#ifndef _Day3Part1_
#define _Day3Part1_ 1

#include <utility>
#include <map>

typedef std::pair<int,int> Swatch;
typedef std::map<Swatch,bool> Fabric;

class Day3Part1
{
public:
	void Process(const string & curr_line);
	void PrintResults();

private:
	Fabric fabricClaims;
	int multiusers;

	bool ParseLine (const string& line, int& x, int& y, int& x_dist, int& y_dist);	
}
	
#endif

