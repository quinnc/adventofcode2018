
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


void Minimize (char chToClear, vector<char>& orig)
{
	vector<char> copyToRemoveCh(orig);
	vector<char> reCollapsed;
	char upperChToClear = toupper(chToClear);

	auto it = copyToRemoveCh.begin();
	while (it != copyToRemoveCh.end())
	{
		char upperItCh = toupper(*it);
		if (upperItCh == upperChToClear)
		{
			it = copyToRemoveCh.erase(it);
		}
		else
		{	
			it++;
		}
	}

	it = copyToRemoveCh.begin();
	while (it != copyToRemoveCh.end())
	{
               if (isalpha(*it))
                {
                if (reCollapsed.size() == 0)
                {
                        reCollapsed.push_back(*it);
                }
                else
                {
                        char prevPoly = reCollapsed.back();
                        char prevPolyUpper = toupper(prevPoly);
                        char newCharUpper = toupper(*it);

                        if (prevPoly == *it)
                        {
                                // add to chain and get next
                                reCollapsed.push_back(*it);
                        }
                        else if (prevPolyUpper == newCharUpper)
                        {
                                // they aren't the same normally, but when convert to the same case they are
                                // == annialation
                                reCollapsed.pop_back();
                        }
                        else
                        {
                                // not exactly the same
                                // nor differing only by case
                                // therefore completely different letters, so add to the chain
                                reCollapsed.push_back(*it);
                        }
                }
                }
		it++;
	}

	cout << " letter [" << chToClear << "] ==> " << reCollapsed.size() << endl;

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
	
	vector<char> polyChain;
	char newChar;

	newChar = inputf.get();
	while (inputf.good())
	{
		if (isalpha(newChar))
		{
		if (polyChain.size() == 0)
		{
			polyChain.push_back(newChar);
		}
		else 
		{
			char prevPoly = polyChain.back();
			char prevPolyUpper = toupper(prevPoly);
			char newCharUpper = toupper(newChar);

			if (prevPoly == newChar)
			{
				// add to chain and get next
				polyChain.push_back(newChar);
			}
			else if (prevPolyUpper == newCharUpper)
			{
				// they aren't the same normally, but when convert to the same case they are
				// == annialation
				polyChain.pop_back();
			}
			else
			{
				// not exactly the same
				// nor differing only by case
				// therefore completely different letters, so add to the chain
				polyChain.push_back(newChar);
			}
		}
		}
		newChar = inputf.get();
	}

	if (inputf.eof())
	{
		cout << "Ended because of EOF" << endl;
	}
	else
	{
		cout << "Ended because of another error" << endl;
	}

#if 0
	cout << "Chain: [";
	for (int i = 0; i < polyChain.size(); i++)
	{
		cout << polyChain[i];
	}
	cout << "]" << endl;
#endif
	cout << " Final chain length = " << polyChain.size() << endl;
	
	for (char testCh = 'a'; testCh <= 'z'; testCh++)
	{
		Minimize(testCh, polyChain);
	}
	cout << endl;
	return 0;
}
