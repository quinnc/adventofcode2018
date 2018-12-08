
#include "data.h"

void Data::StartNew (ifstream& istr)
{
	iStr >> this->numChildren;
	iStr >> this->numMetadatas;

	for (int i = 0; i < this->numChildren; i++)
	{
		Data * child = new Data();

		this->children.push_back(child);

		child.StartNew(istr);
	}

	for (int j = 0; j < this->newMetadatas; j++)
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

	for (int j = 0; i < this->numChildren; j++)
	{
		sum += this->children[i]->SumMetadatas();
	}

	return sum;
}
