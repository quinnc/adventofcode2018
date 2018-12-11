
#include <cstdio>

#include <iostream>

#include <fstream>
#include <iomanip>
#include <set>

using namespace std;

void ZeroGrid (long long grid[300][300])
{
       for (int x=0; x<300;x++)
        {
                for (int y=0; y<300;y++)
                {
			grid[x][y] = 0;
                }
        }
}

void printGrid (long long int grid[300][300])
{

       for (int x=0; x<300;x++)
        {
                for (int y=0; y<300;y++)
                {
 			cout << setw(4) << grid[x][y] << "  ";
		}
		cout << endl;
	}
}

void FindMaxVariableSize (long long values[300][300], int subgridSz, long long& max, int& xOfMax, int& yOfMax)
{
	long long sums[300][300];
	int x, y;

	ZeroGrid(sums);

	for (x=0; x< (300-subgridSz+1);x++)
	{
		for (y=0; y< (300-subgridSz+1); y++)
		{
                       for (int xp = 0; xp < subgridSz; xp++)
                        {
                                for (int yp=0; yp < subgridSz; yp++)
                                {
                                        sums[x][y] += values[x+xp][y+yp];
                                }
                        }
		}
	}

	cout << "    Generated sums for subgrid size=" << subgridSz << endl;

	max = 0;
        for (x=0; x< (300-subgridSz+1);x++)
        {
                for (y=0; y< (300-subgridSz+1); y++)
                {
			if (sums[x][y] > max)
			{
				max = sums[x][y];
				xOfMax = x;
				yOfMax = y;
			}
		}
	}
	
	cout << "    Found the max value for subgrid size=" << subgridSz << endl;			
}

struct Triplet
{
	long long int val;
	int x;
	int y;
	int subsize;

	bool operator< (const Triplet& right)
	{
		return this->val < right.val;
	}
};

bool CompareJustSum (const Triplet& left, const Triplet& right)
{
	return left.val < right.val;
}

struct TripletCompare
{
	bool operator() (const Triplet& left, const Triplet& right)
	{
		return CompareJustSum(left, right);
	}
};


int main (int argc, char** argv)
{
	long long values[300][300];
	ZeroGrid(values);

	int gsn;
	int subszMin, subszMax;

	cout << "Type the Grid Serial Number:" << endl;
	cin >> gsn ;

	cout << "Type the start sub size: " << endl;
	cin >> subszMin;

	cout << "Type the largest sub size: " << endl;
	cin >> subszMax;

	cout << " USING GRID SERIAL = " << gsn << ". Checking sub grids from " << subszMin << "x" << subszMin << " to " << subszMax << "x" << subszMax << endl;

	for (int x=0; x< 300; x++)
	{
		for (int y=0; y<300; y++)
		{
			long long rack = x+10;
			long long pwrLvl;
	
			pwrLvl = rack * y;
			pwrLvl += gsn;

			pwrLvl *= rack;

			int hundDigit= ( (pwrLvl % 1000) / 100 );
			
			values[x][y] = hundDigit - 5;

			if (values[x][y] > 100000)
			{
				cout << " LARGE CALC: " << values[x][y] << " at " << x << "," << y << endl;
			}
		}
	}

	cout << " Created the values array..." << endl;
	std::set<Triplet, TripletCompare> maxSums;

	for (int sz=subszMin; sz <= subszMax; sz++)
	{
		Triplet currTrip;
		FindMaxVariableSize(values, sz, currTrip.val, currTrip.x, currTrip.y);
		currTrip.subsize = sz;
		maxSums.insert(currTrip);
	}
	
	cout << " Filled the list of maximums..." << endl;


	for (auto v : maxSums)
	{
		cout << "    " << v.x << "," << v.y << "," << v.subsize << "  summed value=" << v.val << endl;
	}

	cout << "size sums= " << maxSums.size() << endl;
	std::set<Triplet>::iterator last = maxSums.end();
	last--;
	cout << " LAST: " << last->val << " coord=" << last->x << "," << last->y << endl;
	cout << " FIRST: " << maxSums.begin()->val << " coord=" << maxSums.begin()->x << "," << maxSums.begin()->y << endl;


			

	return 0;
}

