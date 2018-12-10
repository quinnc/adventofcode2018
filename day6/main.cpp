
#include <cstdio>
#include <iostream>
#include <utility>
#include <vector>

#include <fstream>


using namespace std;

void printUsage ()
{
	cout << endl;
	cout << "USAGE:" << endl;
	cout << "\t [appname] [filename]" << endl;
	cout << endl;
}

typedef vector<pair<int,int>> LocList;

typedef char** Map_t;

void LoadLocations(ifstream& infile, LocList& locations)
{
	string line;
		//infile.getline(line)a
	getline(infile, line);

	while (infile.good())
	{

		int loc = line.find(',');
		cout << " Parsing string [" << line << "], split location = " << loc << endl;
		int x = atoi(line.substr(0,loc).c_str());
		int y = atoi(line.substr(loc+2).c_str());


		//int x, y;
		//infile >> x;
		//infile >> y;

		//cout << " Found x=" << x << ", y=" << y << endl;

		locations.push_back(make_pair(x, y));
		cout << "    X=" << x << ", Y=" << y << endl;
		
		//infile.getline(line);
		getline(infile, line);
	}

	
}

void FindMaxes (LocList& locations, int& maxX, int& maxY)
{
	maxX = -1;
	maxY = -1;

	for (auto p : locations)
	{
		if (p.first > maxX)
		{
			maxX = p.first;
		}

		if (p.second > maxY)
		{
			maxY = p.second;
		}
	}

	cout << "MAX x = " << maxX << ", y=" << maxY << endl;

}


void FindLargestNonInfiniteRegion(Map_t map, char& letter, int& size)
{

	letter = 'z';
	size = -1;
}

bool IsLocation (Map_t map, int x, int y)
{
	return (map[x][y] >= 'A' && map[x][y] <= 'Z');
}


char FindNearestLocations (Map_t& map, int maxX, int maxY, int currX, int currY)
{
	char letterUp, letterDown;
	char letterLeft, letterRight;

	if (currX - 1 > 0)
	{
		if (IsLocation(map, currX-1, currY))
		{
			letterLeft = map[currX-1][y];
		}
		else 
		{
			letterLeft = FindNearestLocations(map, maxX, maxY, currX-1, currY);
		}
	}
	else
	{
		letterLeft = '-';
	}

	if (currX + 1 < maxX)
	{
		if (IsLocation(map, currX+1, currY))
		{
			letterRight = map[currX+1][currY];
		}
		else
		{
			letterRight = FindNearestLocations (map, mapX, mapY, currX+1, currY);
		} 
	}
	else
	{
		letterRight = '-';
	}



}


void SetShortestOwner (Map_t & map, int maxX, int maxY)
{
	for (int x = 0; x < maxX; x++)
	{
		for (int y = 0; y < maxY; y++)
		{
			if (map[x][y] >= 'A' && map[x][y] <= 'Z')
			{
				continue;
			}

			// stepwise search for a location capital letter
			// if find one at a distance, set to lower letter
			// if find more than one at a distance, set to -

			FindNearestLocations(map, maxX, mapY, x, y);
}

void BuildMap (LocList& locations, Map_t& map, int maxX, int maxY)
{
	for (int x = 0; x < maxX; x++)
	{
		for (int y = 0; y < maxY; y++)
		{
			map[x][y] = '.';
		}
	}

	char currDest = 'A';
	for (auto p : locations)
	{
		map[p.first][p.second] = currDest;
		currDest ++;
	}
}

void PrintMap (Map_t& map, int maxX, int maxY)
{
        for (int y = 0; y < maxY; y++)
        {	
		cout << endl;

                for (int x = 0; x < maxX; x++)
                {
                        cout << " " << map[x][y];
                }
        }

	cout << endl;
}

int main (int argc, char** argv)
{

	if (argc != 2)
	{
		printUsage();
		return -1;
	}

	ifstream infile;

	infile.open(argv[1]);
	
	if (!infile.good())
	{
		printUsage();
		return -1;
	}

	LocList locations;
	LoadLocations(infile, locations);

	int maxX, maxY = -1;
	FindMaxes(locations, maxX, maxY);

	maxX += 2;
	maxY += 2;

	Map_t map = new char*[maxX];
	for (int i=0; i < maxX; i++)
	{
		map[i] = new char[maxY];
	}
	BuildMap(locations, map, maxX, maxY);
	PrintMap(map, maxX, maxY);

	SetShortestOwner(map);

	FindLargestNonInfiniteRegion(map);

	return 0;

}
