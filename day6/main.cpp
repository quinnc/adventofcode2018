
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

typedef vector<pair<long long,long long>> LocList;

typedef char** Map_t;

void LoadLocations(ifstream& infile, LocList& locations)
{
	string line;
		//infile.getline(line)a
	getline(infile, line);

	while (infile.good())
	{

		long long loc = line.find(',');
		cout << " Parsing string [" << line << "], split location = " << loc << endl;
		long long x = atoi(line.substr(0,loc).c_str());
		long long y = atoi(line.substr(loc+2).c_str());


		//long long x, y;
		//infile >> x;
		//infile >> y;

		//cout << " Found x=" << x << ", y=" << y << endl;

		locations.push_back(make_pair(x, y));
		cout << "    X=" << x << ", Y=" << y << endl;
		
		//infile.getline(line);
		getline(infile, line);
	}

	
}

void FindMaxes (LocList& locations, long long& maxX, long long& maxY)
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


void FindLargestNonInfiniteRegion(Map_t map, char& letter, long long& size)
{

	letter = 'z';
	size = -1;
}

bool IsLocation (Map_t map, long long x, long long y)
{
	return (map[x][y] >= 'A' && map[x][y] <= 'Z');
}


bool CheckTwo (char checkChar, long long checkDist, char bChar, long long bDist)
{
	// checkChar isn't -

	if (checkChar == bChar && checkDist <= bDist)
	{
		return true;
	}

	if ( (checkDist < bDist) || (bDist < 0) )
	{
		return true;
	}

	return false;
}


bool IsWinner (char checkChar, long long checkDist, char bChar, long long bDist, char cChar, long long cDist, char dChar, long long dDist)
{
	cout << "checking " << checkChar << "@" << checkDist << endl;
	cout << "  b:" << bChar << "@" << bDist << ", c:" << cChar << "@" << cDist << ", d:" << dChar << "@" << dDist << endl;
	if (checkChar == '-')
		return false;

	if ( (CheckTwo (checkChar, checkDist, bChar, bDist)) &&
	 (CheckTwo (checkChar, checkDist, cChar, cDist)) &&
	 (CheckTwo (checkChar, checkDist, dChar, dDist)) )
	{
		return true;
	}

	return false;
} 

char FindNearestLocations (Map_t map, long long maxX, long long maxY, long long currX, long long currY, long long& dist, long long limit)
{
	char letterUp, letterDown;
	char letterLeft, letterRight;

	long long distUp = dist;
	long long int distDown =dist;
	long long distLeft = dist;
	long long int distRight = dist;

	cout << "   Search @ " << currX << "," << currY << ", distance from start = " << dist << endl;
	cout << "   Value @ location: " << map[currX][currY] << endl;

	map[currX][currY] = '+';

	if (dist < 0)
	{
		cout << " * ERROR * dist < 0" << endl;
		return '-';
	}

	if ( (dist + 1) > limit)
	{
		cout << " REACHED LIMIT=" << limit << endl;

		dist = -1;
		return '-';
	}

	if ( ( (currX - 1) > 0) && (map[currX-1][currY] != '+') )
	{
		distLeft++;
		if (IsLocation(map, currX-1, currY))
		{
			letterLeft = map[currX-1][currY] + ('a' - 'A');
		}
		else 
		{
			letterLeft = FindNearestLocations(map, maxX, maxY, currX-1, currY, distLeft, limit);
		}
	}
	else
	{
		letterLeft = '-';
		distLeft = -1;
	}

	if (distLeft > 0)
	{
		limit = (distLeft < limit)?distLeft:limit;
	}

	if ( ( (currX + 1) < maxX) && (map[currX+1][currY] != '+') )
	{
		distRight++;
		if (IsLocation(map, currX+1, currY))
		{
			letterRight = map[currX+1][currY] + ('a' - 'A');
		}
		else
		{
			letterRight = FindNearestLocations (map, maxX, maxY, currX+1, currY, distRight, limit);
		} 
	}
	else
	{
		distRight= -1;
		letterRight = '-';
	}

	if (distRight > 0)
	{
		limit = (distRight < limit)?distRight: limit;
	}

	if ( ( (currY - 1) > 0) && (map[currX][currY-1] != '+') )
	{
		distDown++;
		if (IsLocation(map, currX, currY-1))
		{
			letterDown = map[currX][currY-1] + ('a' - 'A');
		}
		else
		{
			letterDown = FindNearestLocations(map, maxX, maxY, currX, currY-1, distDown, limit);
		}
	}
	else
	{
		distDown = -1;
		letterDown = '-';
	}

	if (distDown > 0)
	{
		limit = (distDown < limit)?distDown:limit;
	}


	if ( ( (currY+1) < maxY) && (map[currX][currY+1] != '+') )
	{
		distUp++;
		if (IsLocation(map, currX, currY+1))
		{
			letterUp = map[currX][currY+1] + ('a' - 'A');
		}
		else
		{
			letterUp = FindNearestLocations (map, maxX, maxY, currX, currY+1, distUp, limit);
		}
	}
	else
	{
		distUp = -1;
		letterUp = '-';
	}



	cout << "Down: " << letterDown << " @ " << distDown << endl;
	cout << "Up  : " << letterUp   << " @ " << distUp   << endl;
	cout << "Left: " << letterLeft << " @ " << distLeft << endl;
	cout << "Rigt: " << letterRight<< " @ " << distRight<< endl;

	// only left is valid, so must be it
	if (IsWinner(letterLeft, distLeft, letterRight, distRight, letterUp, distUp, letterDown, distDown))
	{
		// found a valid letter to the left and all others are longer or invalid
		cout << " LEFT woni" << endl;
		dist = distLeft;
		return letterLeft;
	}


	// only right is valid, so must be it
	if (IsWinner (letterRight, distRight, letterLeft, distLeft, letterUp, distUp, letterDown, distDown))
	{
		cout << " RIGHT won" << endl;
		dist = distRight;
		return letterRight;
	}

	// only down is valid
	if (IsWinner (letterDown, distDown, letterRight, distRight, letterLeft, distLeft, letterUp, distUp))
	{
		cout << " DOWN won" << endl;
		dist = distDown;
		return letterDown;
	}

	// only up
	if (IsWinner (letterUp, distUp, letterRight, distRight, letterLeft, distLeft, letterDown, distDown))
	{
		cout << " UP won" << endl;
		dist = distUp;
		return letterUp;
	}

	cout << "// no clear winner" << endl;
	long long distUpDown;
	long long distLeftRight;

	// winner up/down:
	if (distUp < 0)
	{
		distUpDown = distDown;
	}
	else if (distDown < 0)
	{
		distUpDown = distUp;
	}
	else
	{
		distUpDown = (distUp < distDown?distUp:distDown);
	}

	// winner left right
	if (distLeft < 0)
	{
		distLeftRight = distRight;
	}
	else if (distRight < 0)
	{
		distLeftRight = distLeft;
	}
	else
	{
		distLeftRight = (distLeft < distRight? distLeft: distRight);
	}

	// overall winner
	if (distLeftRight < 0)
	{
		dist = distUpDown;
	}
	else if (distUpDown < 0)
	{
		dist = distLeftRight;
	}
	else
	{
		dist = (distUpDown < distLeftRight? distUpDown : distLeftRight);
	}
	
	cout << "  RETURING '-' @ " << dist << endl;
	return '-';
	
}


void SetShortestOwner (Map_t & map, long long maxX, long long maxY)
{
	for (long long x = 0; x < maxX; x++)
	{
		for (long long y = 0; y < maxY; y++)
		{
			if (map[x][y] >= 'A' && map[x][y] <= 'Z')
			{
				continue;
			}

			// stepwise search for a location capital letter
			// if find one at a distance, set to lower letter
			// if find more than one at a distance, set to -
			long long dist = 0;
			Map_t tmpMap;

			tmpMap = new char*[maxX];
			for (int i= 0; i< maxX; i++)
			{
				tmpMap[i] = new char[maxY];
				for (int y = 0; y < maxY; y++)
				{
					tmpMap[i][y] = map[i][y];
				}
			}

			map[x][y] = FindNearestLocations(tmpMap, maxX, maxY, x, y, dist, maxX+maxY);
			cout << "**** RESULT: " << x << "," << y << " = letter=" << map[x][y] << " distance=" << dist<< endl;
		}
	}
}

void BuildMap (LocList& locations, Map_t& map, long long maxX, long long maxY)
{
	for (long long x = 0; x < maxX; x++)
	{
		for (long long y = 0; y < maxY; y++)
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

void PrintMap (Map_t& map, long long maxX, long long maxY)
{
        for (long long y = 0; y < maxY; y++)
        {	
		cout << endl;

                for (long long x = 0; x < maxX; x++)
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

	long long maxX, maxY = -1;
	FindMaxes(locations, maxX, maxY);

	maxX += 2;
	maxY += 2;

	Map_t map = new char*[maxX];
	for (long long i=0; i < maxX; i++)
	{
		map[i] = new char[maxY];
	}
	BuildMap(locations, map, maxX, maxY);
	PrintMap(map, maxX, maxY);

	SetShortestOwner(map, maxX, maxY);
	PrintMap (map, maxX, maxY);

	//FindLargestNonInfiniteRegion(map);

	return 0;

}
