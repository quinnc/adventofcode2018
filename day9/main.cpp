


#include <cstdio>
#include <iostream>
#include <list>
#include <vector>

using namespace std;


void Shift (list<long long int>::iterator & loc, long long int shiftAmt, list<long long int>& circle)
{
	if (shiftAmt < 0)
	{
		while (shiftAmt < 0)
		{
			if (loc == circle.begin())
			{
				loc = circle.end();
			}

			loc--;
			shiftAmt++;
		}
	}
	else if (shiftAmt > 0)
	{
		while (shiftAmt > 0)
		{
			loc++;
			shiftAmt--;
			if (loc == circle.end())
			{
				loc = circle.begin();
			}
		}
	}
	else
	{
		// shiftAmt == 0
		// just return
		return;
	}
}
			
void Show (list<long long int>::iterator curr, list<long long int> placed)
{
	for (auto it = placed.begin(); it != placed.end(); it++)
	{
		cout << " ";
		if (*curr == *it)
		{
			cout << "(" << *it << ")" ;
		}
		else
		{
			cout << " " << *it << " " ;
		}
	}
	cout << endl;
}

void ShowScores (vector<long long int> scores)
{
	long long int user = 1;
	long long int highest = 0;
	long long int highScoreElf = -1;

	for (auto score : scores)
	{
		if (score > highest)
		{
			highest = score;
			highScoreElf = user;
		}
		//cout << "[  " << user << "  ] " << score << endl;
		user++;
	}

	cout << endl; 
	cout << " HIGHEST SCORE ==" << highest << "== elf=" << highScoreElf << endl;
}
		

int main (int argc, char** argv)
{
	if (argc != 3)
	{
		cout << endl;
		cout << "Wrong number of parameters." << endl;
		cout << "\t" << argv[0] << " [number of players] [highest marble]" << endl;
		cout << endl;
		return -1;
	}

	long long int numPlayers;
	long long int highestMarble;

	numPlayers = atoi(argv[1]);
	highestMarble = atoi(argv[2]);

	cout << " Game has " << numPlayers << " elves, going up to marble " << highestMarble << endl;

	long long int currMarble = 0;
	list<long long int> placedMarbles;
	list<long long int>::iterator currMarbleLoc;

	long long int currPlayer = 0;
	vector<long long int> scores(numPlayers);

	placedMarbles.push_back(currMarble);
	currMarbleLoc = placedMarbles.begin();
	currMarble++;

//      placedMarbles.push_back(currMarble);
  //      currMarbleLoc++;;
    //    currMarble++;
	

	while (currMarble <= highestMarble)
	{
		//Show (currMarbleLoc, placedMarbles);
		if (currMarble % 23 == 0)
		{
			scores[currPlayer] += currMarble;
			Shift(currMarbleLoc, -7, placedMarbles);
			scores[currPlayer] += *currMarbleLoc;
			currMarbleLoc = placedMarbles.erase(currMarbleLoc);
			if (currMarbleLoc == placedMarbles.end())
			{
				currMarbleLoc = placedMarbles.begin();
			}
		}
		else
		{
			Shift(currMarbleLoc, 2, placedMarbles);
			if (currMarbleLoc == placedMarbles.begin())
			{
				placedMarbles.push_back(currMarble);
				currMarbleLoc = placedMarbles.end();
				currMarbleLoc--;
			}
			else
			{
				currMarbleLoc = placedMarbles.insert(currMarbleLoc, currMarble);
			}
		}
		

		currMarble++;
		
		currPlayer++;
		if (currPlayer >= numPlayers)
		{
			currPlayer = 0;
		}
	}
	cout << "Current marble = " << currMarble << endl;
	cout << "Current player = " << currPlayer << endl;
	cout << "Value at current location = " << *currMarbleLoc << endl;

	ShowScores(scores);
	return 0;
}	
