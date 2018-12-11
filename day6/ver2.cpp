
#include <cstdio>
#include <iostream>
#include <utility>
#include <vector>
#include <set>

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

bool LOGGING_ON=true;
#define LOG(a) \
	if (LOGGING_ON)\
	{\
		a ;\
	}

#define DEBUG( OuT ) while(0) {;} 
//cout << OuT << endl;

void PrintMap (Map_t& map, long long maxX, long long maxY);

void LoadLocations(ifstream& infile, LocList& locations)
{
	string line;
		//infile.getline(line)a
	getline(infile, line);

	while (infile.good())
	{

		long long loc = line.find(',');
		//LOG (cout << " Parsing string [" << line << "], split location = " << loc << endl)
		long long x = atoi(line.substr(0,loc).c_str());
		long long y = atoi(line.substr(loc+2).c_str());


		//long long x, y;
		//infile >> x;
		//infile >> y;

		//cout << " Found x=" << x << ", y=" << y << endl;

		locations.push_back(make_pair(x, y));
		//cout << "    X=" << x << ", Y=" << y << endl;
		
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

	//cout << "MAX x = " << maxX << ", y=" << maxY << endl;

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
	LOG (cout << "IsWinner(): checking " << checkChar << "@" << checkDist << endl)
	LOG (cout << "    against-  b:" << bChar << "@" << bDist << ", c:" << cChar << "@" << cDist << ", d:" << dChar << "@" << dDist << endl)
	LOG (cout << endl)

	if (checkChar == '-')
	{
		return false;
	}

	if ( (CheckTwo (checkChar, checkDist, bChar, bDist)) &&
	 (CheckTwo (checkChar, checkDist, cChar, cDist)) &&
	 (CheckTwo (checkChar, checkDist, dChar, dDist)) )
	{
		return true;
	}

	return false;
}

void CopyMap (Map_t orig, Map_t& newMap, long long maxX, long long maxY)
{

	newMap = new char*[maxX];
	for (long long x = 0; x < maxX; x++)
	{
		newMap[x] = new char[maxY];
		for (long long y = 0; y < maxY; y++)
		{
			newMap[x][y] = orig[x][y];
		}
	}

}

void AddCurrAddressesAndRecurse(Map_t map, long long startX, long long startY, long long maxX, long long maxY, long long depth, LocList & locations)
{

	DEBUG ( " start = " << startX << "," << startY << ", depth=" << depth )
	if (depth == 0)
	{
		return;
	}

	map[startX][startY] = '+';

	long long cardinals[4][2] = { {startX-1, startY},
					{startX+1, startY},
					{startX, startY-1},
					{startX, startY+1} };

	for (int i=0; i < 4; i++)
	{
		long long xnow, ynow;
		
		xnow = cardinals[i][0];
		ynow = cardinals[i][1];
		
		//cout << " Cardinals: " << xnow << ", " << ynow << ", i=" << i << endl;
		
		if ( (xnow >= 0) && (xnow< maxX) &&
			(ynow >= 0) && (ynow < maxY) ) 
		{
			if  (depth == 1) 
			{ 
				if ( map[xnow][ynow] != '+')
				{
					locations.push_back(make_pair(xnow, ynow));
				}

			map[xnow][ynow] = '+';
			}
			else
			{
			map[xnow][ynow] = '+';
				AddCurrAddressesAndRecurse(map, xnow, ynow, maxX, maxY, depth-1, locations);
			}
		}
	}
}

char BuildListToCheck (Map_t map, long long startX, long long startY, long long maxX, long long maxY, long long & distToLocation)
{

	long long maxPath = maxX + maxY;

	for (long long depth = 1; depth <= maxPath; depth++)
	{
		LocList locationsToCheck;
		std::set<char> found;

		Map_t tmpMap;
		CopyMap(map, tmpMap, maxX, maxY);

		tmpMap[startX][startY] = '+';

		AddCurrAddressesAndRecurse(tmpMap, startX, startY, maxX, maxY, depth, locationsToCheck);
		//PrintMap(tmpMap, maxX, maxY);

		if (locationsToCheck.size() == 0)
		{
			cout << "  // searched the entire map and didn't find anything: " << startX << "," << startY << " depth=" << depth << endl;
			continue;
		}

		for (auto loc : locationsToCheck)
		{
			long long x = loc.first;
			long long y = loc.second;
			char ch = map[x][y];
			//cout << " SEARCHING: " << x << "," << y << " character there? = " << map[x][y] << endl;
			//found.insert(map[x][y]);

			if (IsLocation(map, x, y))
			{
				found.insert(ch);
			}
			else
			{
				found.insert('.');
			}
		}

		if (found.size() == 0)
		{
			//cout << " ERROR: location " <<startX << "," << startY << " depth=" << depth << " had a found size of 0!" << endl;
			continue;
		}

		if (found.size() == 1)
		{
			if (found.find('.') == found.end())
			{
				cout << " ERROR: only one found, but it wasn't the -!: " << *(found.begin()) << endl;
        	   	     	cout << " ERROR: location " <<startX << "," << startY << " depth=" << depth << endl;
 			}	
			// all bad
			continue;
		}

		if (found.size() == 2)
		{
			char ch;

			found.erase('.');
			ch = *(found.begin());
			
			// only one, so that's it
			//cout << " Only one other character set: " << startX << "," << startY << ", letter=" << ch << ", depth=" << depth << endl;

			distToLocation = depth;
			return ch;
		}

		if ( found.size() > 2 )
		{
			// two or more letters, equidistant
			// return '-'

			distToLocation = depth;
			return '.';
		}

		//cout << " ERROR 5: " << endl;
		
	}

	cout << " ERROR 6!" << endl;
	return '*';
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

void Ver2 (Map_t map, long long maxX, long long maxY)
{

	for (long long currX = 0; currX < maxX; currX++)
	{

		for (long long currY = 0; currY < maxY; currY++)
		{
			if (map[currX][currY] >= 'A' && map[currX][currY] <= 'Z')
			{
				continue;
			}

			char ch;
			long long distance;

			ch = BuildListToCheck (map, currX, currY, maxX, maxY, distance);

			DEBUG ( "at " << currX << "," << currY << " ch=" << ch << " --> " << (char)(ch - 'A' + 'a') << ", at distance=" << distance )
			
			if (ch >= 'A' && ch <= 'Z')
			{
				map[currX][currY] =( char) (ch - 'A' +'a');
			}
			else
			{
				map[currX][currY] = ch;
			}
		}

		//PrintMap (map, maxX, maxY);
	}
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

//	SetShortestOwner(map, maxX, maxY);

	Ver2(map, maxX, maxY);
	PrintMap (map, maxX, maxY);

	//FindLargestNonInfiniteRegion(map);

	return 0;

}
