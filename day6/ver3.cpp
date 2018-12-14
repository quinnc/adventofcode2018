
#include <cstdio>
#include <iostream>
#include <utility>
#include <vector>
#include <set>

#include <fstream>
#include <map>
#include <iomanip>

#include <pthread.h>

using namespace std;

void printUsage ()
{
	cout << endl;
	cout << "USAGE:" << endl;
	cout << "\t [appname] [filename]" << endl;
	cout << endl;
}

typedef vector<pair<long long,long long>> LocList;

class MapPoint
{
public:
	// -1 if not a Location
	// 0..* if a Location
	int id;
	
	// -3 not checked yet
	// -2 already under search
	// -1 if multiple equidistant locations
	// 0..* number of location that is closest
	int nearestLoc;

	// distance to the nearest location
	// -1 : unset
	// -2 : multiple equidistant locations
	// 0  : this is a location
	// >0 : distance to the nearest location
	long long distance;

	MapPoint() : id(-1),nearestLoc(-3),distance(-1) {}

	void SetNewLocation() 
	{
		id = MAX_LOC;
		nearestLoc= MAX_LOC;
		distance=0;
		MAX_LOC++;
	}

	void Copy (const MapPoint& rhs)
	{
		id = rhs.id;
		nearestLoc = rhs.nearestLoc;
		distance = rhs.distance;
	}

	void SetChecked()
	{
		nearestLoc = -2;
	}

	bool IsChecked()
	{
		return (nearestLoc == -2);
	}

	bool IsLocation()
	{
		return (id >= 0);
	}


private:
	static int MAX_LOC;
};

int MapPoint::MAX_LOC=0;

typedef MapPoint** Map_t;

bool LOGGING_ON=false;
#define LOG(a) \
	if (LOGGING_ON)\
	{\
		a ;\
	}

#define DEBUG( OuT ) if (LOGGING_ON) { cout << OuT << endl; } \
	else {  while(0) {;} }

void PrintMap (Map_t& map, long long maxX, long long maxY);

void LoadLocations(ifstream& infile, LocList& locations)
{
	string line;
	getline(infile, line);
	
	DEBUG( "c: `" << __LINE__ )
	while (infile.good())
	{
		long long loc = line.find(',');
		long long x = atoi(line.substr(0,loc).c_str());
		long long y = atoi(line.substr(loc+2).c_str());
		DEBUG ( " extracted location: " << x << "," << y )
		locations.push_back(make_pair(x, y));
		getline(infile, line);
	}

	DEBUG ( "d " << __LINE__ )
}

void FindMaxes (LocList& locations, long long& maxX, long long& maxY, long long& minX, long long& minY)
{
	DEBUG ( __FUNCTION__ << ":" << __LINE__ )
	maxX = -1;
	maxY = -1;
	minX = -1;
	minY = -1;

	for (auto p : locations)
	{
		if ( (minX == -1) || (p.first < minX))
		{
			minX = p.first;
		}

		if ( (minY == -1) || (p.second < minY) )
		{
			minY = p.second;
		}

		if (p.first > maxX)
		{
			maxX = p.first;
		}

		if (p.second > maxY)
		{
			maxY = p.second;
		}
	}
        cout << __FUNCTION__ << ":" << __LINE__ << " max: " << maxX << " & " << maxY << endl;
}

typedef long long Count_t;

void FindLargestNonInfiniteRegion(Map_t map_, long long maxX, long long maxY, int& letter, long long& size)
{
	DEBUG ( "before map the asdf" )
	std::map<int, Count_t> locationAreaSizes;
	for (int x = 0; x < maxX; x++)
	{
		for (int y=0; y < maxY; y++)
		{
			locationAreaSizes[map_[x][y].nearestLoc]++;
		}
	}
	
	for (auto a : locationAreaSizes)
	{
		DEBUG( " location=" << a.first << ", number of squares that is closest=" << a.second )
	}

	for (int x=0; x < maxX; x++)
	{
		locationAreaSizes[map_[x][0].nearestLoc] = -11;
		locationAreaSizes[map_[x][maxY-1].nearestLoc] = -12;
	}

	for (int y=0; y < maxY; y++)
	{
		locationAreaSizes[map_[0][y].nearestLoc] = -13;
		locationAreaSizes[map_[maxX-1][y].nearestLoc] = -13;
	}		


	size = -1;
	letter = -1;

	for (auto a: locationAreaSizes)
	{
		if (a.second > size)
		{
			size = a.second;
			letter = a.first;
		}
	}

	DEBUG( "max: " << size << " @ " << letter )
}

void CopyMap (Map_t orig, Map_t& newMap, long long maxX, long long maxY)
{

	newMap = new MapPoint*[maxX];
	for (long long x = 0; x < maxX; x++)
	{
		newMap[x] = new MapPoint[maxY];
		for (long long y = 0; y < maxY; y++)
		{
			newMap[x][y].Copy( orig[x][y] );
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

	map[startX][startY].SetChecked();

	long long cardinals[4][2] = { {startX-1, startY},
					{startX+1, startY},
					{startX, startY-1},
					{startX, startY+1} };

	for (int i=0; i < 4; i++)
	{
		long long xnow, ynow;
		
		xnow = cardinals[i][0];
		ynow = cardinals[i][1];
		
		//DEBUG ( " Cardinals: " << xnow << ", " << ynow << ", i=" << i )
		
		if ( (xnow >= 0) && (xnow< maxX) &&
			(ynow >= 0) && (ynow < maxY) ) 
		{
			if  (depth == 1) 
			{ 
				if ( ! map[xnow][ynow].IsChecked())
				{
					locations.push_back(make_pair(xnow, ynow));
					map[xnow][ynow].SetChecked();
				}
				// else already searching in this directory, don't bother
			}
			else
			{
				if (! map[xnow][ynow].IsChecked())
				{
B
					map[xnow][ynow].SetChecked();
				AddCurrAddressesAndRecurse(map, xnow, ynow, maxX, maxY, depth-1, locations);
			}
		}
	}
}

int BuildListToCheck (Map_t tmpMap, long long startX, long long startY, long long maxX, long long maxY, long long & distToLocation)
{

	long long maxPath = maxX + maxY;
	DEBUG ( " Building list of points to check: starting from " << startX << "," << startY << ", going down to a depth of " << distToLocation )
	tmpMap[startX][startY].SetChecked();

	for (long long depth = 1; depth <= maxPath; depth++)
	{
		LocList locationsToCheck;
		std::set<int> found;

		AddCurrAddressesAndRecurse(tmpMap, startX, startY, maxX, maxY, depth, locationsToCheck);

		if (locationsToCheck.size() == 0)
		{
			DEBUG ( " Searched the entire map and didn't find anything: " << startX << "," << startY << " depth=" << depth )
			continue;
		}

		for (auto loc : locationsToCheck)
		{
			long long x = loc.first;
			long long y = loc.second;
			//DEBUG ( " inserting " << map[x][y].id << " into the list" )
			found.insert(tmpMap[x][y].id);
		}

		if (found.size() == 0)
		{
			DEBUG ( " ERROR: location " <<startX << "," << startY << " depth=" << depth << " had a found size of 0!" )
			continue;
		}

		if (found.size() == 1)
		{
			// all bad
			DEBUG ( "only one entry in the list " << *(found.begin()) )
			continue;
		}

		if (found.size() == 2)
		{
			int ch;

			found.erase(-1);
			DEBUG ( "after erased -1, size=" << found.size() )
			ch = *(found.begin());
			
			// only one, so that's it
			//cout << " Only one other character set: " << startX << "," << startY << ", letter=" << ch << ", depth=" << depth << endl;

			distToLocation = depth;
			return ch;
		}

		if ( found.size() > 2 )
		{
			distToLocation = depth;
			return -1;
		}

		cout << " ERROR 5: " << endl;
		
	}

	distToLocation = -99;

	cout << " ERROR 6!" << endl;
	return -2;
}


void BuildMap (LocList& locations, Map_t& map, long long maxX, long long maxY, long long minX, long long minY)
{
	for (auto p : locations)
	{
		map[p.first-minX][p.second-minY].SetNewLocation();
	}
}

void PrintMap (Map_t& map, long long maxX, long long maxY)
{
	cout << " Map of location ids:";
        for (long long y = 0; y < maxY; y++)
        {	
		cout << endl;

                for (long long x = 0; x < maxX; x++)
                {
                        cout << setw(3) << map[x][y].id;
                }
        }

	cout << endl;
	cout << endl << " Map of nearest locations:"; 
       for (long long y = 0; y < maxY; y++)
        {
                cout << endl;

                for (long long x = 0; x < maxX; x++)
                {
                        cout << setw(3) << map[x][y].nearestLoc;
                }
        }

        cout << endl;
	cout << endl << " Map of distances to nearest locations: ";
       for (long long y = 0; y < maxY; y++)
        {
                cout << endl;

                for (long long x = 0; x < maxX; x++)
                {
                        cout << setw(3) << map[x][y].distance;
                }
        }

        cout << endl;
}

Map_t * globalMap;

struct threadParam
{
	long long currX;
	long long maxX;
	long long maxY;
};

void * threadRoutine (void * param)
{
	threadParam* data = (threadParam*)(param);
	
	for (long long currY = 0; currY < data->maxY; currY++)
	{
		if (data->currX == currY || (currY % 10) == 0)
		{
			cout << " Searching for nearest location to map coordinates " << data->currX << "," << currY << " thread=" << pthread_self() << endl;
		}
		if ((*globalMap)[data->currX][currY].IsLocation())
		{
			DEBUG ("current point is a drop location " << data->currX << "," << currY )
			continue;
		}

		int ch;
		long long distance = (data->maxX > data->maxY)?data->maxX:data->maxY;
		DEBUG ( __FUNCTION__ << ":" << __LINE__ << " (" << pthread_self() << ")" )


		Map_t tmpMap;
		CopyMap((*globalMap), tmpMap, data->maxX, data->maxY);
		ch = BuildListToCheck (tmpMap, data->currX, currY, data->maxX, data->maxY, distance);
		
		for (int xdel = 0; xdel<data->maxX; xdel++)
		{
			delete [] (tmpMap[xdel]);
		}
		delete [] tmpMap;

		DEBUG ( "at " << data->currX << "," << currY << " ch=" << ch << " --> " << (char)(ch - 'A' + 'a') << ", at distance=" << distance )
		(*globalMap)[data->currX][currY].nearestLoc = ch;
		(*globalMap)[data->currX][currY].distance = distance;
	}

	return nullptr;
}

void Ver2 (Map_t map, long long maxX, long long maxY)
{
	globalMap = &map;

	for (long long currX = 0; currX < maxX; currX += 8)
	{
		pthread_t threads[8];
		threadParam params[8];
		int xoffset = 0;
		for (xoffset = 0; xoffset < 8; xoffset++)
		{
			if ( (currX + xoffset) < maxX)
			{
				params[xoffset].currX = currX+xoffset;
				params[xoffset].maxX = maxX;
				params[xoffset].maxY = maxY;
	
				int r;
		//		int *r2 = new int;

				r = pthread_create ( &(threads[xoffset]), NULL, threadRoutine, (void *)(&(params[xoffset])));
		//		pthread_join (threads[xoffset], (void**)&r2);
		//		delete r2;
			}
			else 
			{
				break;
			}
		}

#if 1
		for (int offset = 0; offset < xoffset; offset++)
		{
			// created above, now wait for them all to finish
			pthread_join (threads[offset], NULL);
		}
#endif	
	}
}

int main (int argc, char** argv)
{
	DEBUG ( __FUNCTION__ << ":" << __LINE__ )
	if (argc != 2)
	{
		printUsage();
		return -1;
	}

	ifstream infile;

	DEBUG ( __FUNCTION__ << ":" << __LINE__ )
	infile.open(argv[1]);

	if (!infile.good())
	{
		printUsage();
		return -1;
	}
	DEBUG ( __FUNCTION__ << ":" << __LINE__ )
	LocList locations;
	LoadLocations(infile, locations);
	DEBUG ( __FUNCTION__ << ":" << __LINE__ )
	long long maxX = -1;
	long long maxY = -1;
	long long minX = -1;
	long long minY = -1;
	FindMaxes(locations, maxX, maxY, minX, minY);
	cout << " Original size " << maxX << " by " << maxY << endl;
	cout << " First location offset " << minX << " and " << minY << endl;

	maxX = maxX - minX+1;
	maxY = maxY - minY+1;;
	cout << " Tracked map is " << maxX << " by " << maxY << endl;

	Map_t map = new MapPoint*[maxX];
	for (long long i=0; i < maxX; i++)
	{
		map[i] = new MapPoint[maxY];
	}
	DEBUG ( __FUNCTION__ << ":" << __LINE__ )
	BuildMap(locations, map, maxX, maxY, minX, minY);
	DEBUG ( __FUNCTION__ << ":" << __LINE__ )
	//PrintMap(map, maxX, maxY);

	Ver2(map, maxX, maxY);
	DEBUG ( __FUNCTION__ << ":" << __LINE__ )
	//PrintMap (map, maxX, maxY);

	DEBUG ( __FUNCTION__ << ":" << __LINE__ )
	int areaId;
	long long areaCnt;
	FindLargestNonInfiniteRegion(map, maxX, maxY, areaId, areaCnt);
	cout << " Largest non-infinite region: " << areaId << ", size=" << areaCnt << endl;

	
	DEBUG ( __FUNCTION__ << ":" << __LINE__ )
	return 0;

}
