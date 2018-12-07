

#include <cstdio>
#include <iostream>
#include <map>

#include <list>

#include "parser.h"

using namespace std;

list<char>::iterator  Parser::InsertTask (char task, list<char>::iterator startPos)
{
                // as long as the letters more, move to next
                // insert before the first letter you find that is higher

	for (auto curr = startPos; curr != opOrder.end(); curr++)
	{
		//cout << __LINE__ << ": curr=" << *curr << " new task=" << task << endl;
		if (*curr > task)
		{
			opOrder.emplace(curr, task);
			return curr;
		}
	}

	//cout << "didn't find a better place so put '" << task << "' at the end of the ops" << endl;
	opOrder.push_back(task);

	return opOrder.end();
}

void Parser::FindTask (char task, list<char>::iterator start, list<char>::iterator & pos)
{

	//pos = this->opOrder.end();

	for (auto curr = start; curr != opOrder.end(); curr++)
	{
		if (*curr == task)
		{
			pos = curr;
			return;
		}

	}

	pos = opOrder.end();
}

void Parser::Process(const std::string & curr_line)
{
	char doFirst, doAfter;

	bool ok = false;

	//cout << __LINE__ << endl;
	ok = ParseLine(curr_line, doFirst, doAfter);

	if (!ok)
	{
		//cout << "Failed to parse line::: " << curr_line << endl;
		return;
	}
      //cout << __LINE__ << endl;
  
	if (this->opOrder.size() == 0)
	{
		this->opOrder.push_back(doFirst);
		this->opOrder.push_back(doAfter);
	}
      //cout << __LINE__ << endl;
  
	// find the 'dofirst' item
	list<char>::iterator firstPos;
	FindTask(doFirst, opOrder.begin(), firstPos);
      //cout << __LINE__ << endl;
  	
	// if don't find it
	if (firstPos == opOrder.end())
	{
		firstPos = InsertTask(doFirst, opOrder.begin());
	}
	// find the 'doAfter' item
	list<char>::iterator afterPos;
	FindTask (doAfter, firstPos, afterPos);

      //cout << __LINE__ << endl;
  	// already after the before task
	if (afterPos != opOrder.end())
	{
      //cout << __LINE__ << endl;
  		//PrintResults();	
	// after is already after before, done
		return;
	}

      //cout << __LINE__ << " about to erase " << doAfter << " from the list" << endl;
  
	// if it is before, erase
	opOrder.remove(doAfter);

	//PrintResults();
	// if it is before or not at all, insert after
	auto firstInsertPoint = firstPos;
	firstInsertPoint++;
	InsertTask (doAfter, firstInsertPoint);	

	//cout << " Task to be completed first = " << doFirst << ", task to do after = " << doAfter << endl;
	//PrintResults();
}

void Parser::PrintResults()
{

	cout << "Order of operations:: " << endl;

	// ???
	for (const auto& curr : opOrder)
	{
		cout << curr;
	}
	cout << endl;

}

bool Parser::ParseLine (const std::string& line, char & beforeTask, char& afterTask)
{
	// Step F must be finished before step E can begin.
	//cout << " PARSING::: " << line << endl;
	if (line[4] != ' ' || line[6] != ' ')
		return false;

	int stepIdx = line.find("step ");

	if (stepIdx == string::npos)
		return false;

	beforeTask = line[5];
	afterTask = line[stepIdx+5];

	if (line[stepIdx+6] != ' ')
		return false;
	return true;
}
	

