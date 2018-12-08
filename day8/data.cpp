#include <iostream>
#include <fstream>
#include <cstdio>

#include "data.h"
using namespace std;

void Data::StartNew (ifstream& iStr)
{
	iStr >> this->numChildren;
	iStr >> this->numMetadatas;

	for (int i = 0; i < this->numChildren; i++)
	{
		Data * child = new Data();

		this->children.push_back(child);

		child->StartNew(iStr);
	}

	for (int j = 0; j < this->numMetadatas; j++)
	{
		int currMeta;
		iStr >> currMeta;
		this->metadatas.push_back(currMeta);
	}
}

int Data::SumMetadatas()
{
	int sum = 0;

	for (int i = 0; i < this->numMetadatas; i++)
	{
		sum += this->metadatas[i];
	}

	for (int j = 0; j < this->numChildren; j++)
	{
		sum += this->children[j]->SumMetadatas();
	}

	return sum;
}

int Data::NodeValue ()
{

	int sum = 0;
	if (this->numChildren == 0)
	{
	        for (int i = 0; i < this->numMetadatas; i++)
        	{
                	sum += this->metadatas[i];
        	}
	}
	else
	{
		// else has children
	        for (int i = 0; i < this->numMetadatas; i++)
       		{
			int currChild = this->metadatas[i];
			currChild--;	
			if (currChild >= this->numChildren)
			{
				//cout << " Curr child=" << currChild << ", but only have " << this->numChildren << endl;
				continue;
			}

                	sum += this->children[currChild]->NodeValue();
	 		//cout << " Sum is now = " << sum << endl;       
		}
	}
	return sum;
}
