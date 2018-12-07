
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

void CharCounter (const string& in, bool& hasDoubleChar, bool& hasTripleChar)
{
	hasDoubleChar = false;
	hasTripleChar = false;

	int letterCounts[26] = {0};

	for (size_t idx = 0; idx < in.size(); idx++)
	{
		char curr = in[idx];
		letterCounts[(int)(curr - 'a')]++;
	}

	for (int i = 0; i < 26; i++)
	{
		if (letterCounts[i] == 2)
			hasDoubleChar = true;
		if (letterCounts[i] == 3)
			hasTripleChar = true;

		cout << " " << (char)(i+'a') << "=>" << letterCounts[i];
	}

	cout << endl;

}

int IndexOfFirstDiff (const string& strA, const string& strB)
{
        if (strA.size() != strB.length())
                return -2;

        for (unsigned int i = 0; i < strA.size(); i++)
        {
                if (strA[i] != strB[i])
			return i;
        }

	return -1;
}

bool IsOnlyDifferentByOne (const string& strA, const string& strB)
{
	if (strA.size() != strB.length())
		return false;

	int numdiffs = 0;
	for (unsigned int i = 0; i < strA.size(); i++)
	{
		if (strA[i] != strB[i])
			numdiffs++;
	}

	if (numdiffs == 0)
		cout << " **** WARNING ++++ EXACTLY THE SAME STRINGS: " << strA << " <=> " << strB << endl;

	return (numdiffs == 1);
}
		

bool FindOffByOnePair (const std::vector<string>& listOfStrings, int startIndex, int& nearMatchAIndex, int& nearMatchBIndex)
{
	if (startIndex >= listOfStrings.size() - 1)
	{
		// if this is the last index, return 
              nearMatchAIndex = -99;
                nearMatchBIndex = -101;
                return false;
        }

	for (unsigned int i=startIndex+1; i < listOfStrings.size(); i++)
	{
		if (IsOnlyDifferentByOne(listOfStrings[startIndex], listOfStrings[i]))
		{
			nearMatchAIndex = startIndex;
			nearMatchBIndex = i;
			return true;
		}
	}

	startIndex++;
	// else no near matches for this start index between the next and the end, so move on
	return FindOffByOnePair (listOfStrings, startIndex, nearMatchAIndex, nearMatchBIndex);	
}

void FindCommonChars (const string& strA, const string& strB, string& common)
{
	common = "";

	for (unsigned int i = 0; i < strA.size(); i++)
	{
		if (strA[i] == strB[i])
			common += strA[i];
	}
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
	
	unsigned long numLines = 0;	
	string curr_line;
	std::vector<string> lineList;

	inputf >> curr_line;
	while (inputf.good())
	{
		numLines++;
		lineList.push_back(curr_line);
		inputf >> curr_line; 
	}

	int start = 0;
	int match1 =-21, match2 = -22;
	string common;
	bool foundi = false;
	
	foundi = FindOffByOnePair(lineList, start, match1, match2);
	cout << " found a almost match? " << foundi << " locations: " << match1 << ", " << match2 << endl;

	FindCommonChars(lineList[match1], lineList[match2], common);
	cout << "Original strings <" << lineList[match1] << "> <" << lineList[match2] << ">, common characters: " << common << endl;

}
