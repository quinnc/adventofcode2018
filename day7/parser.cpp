

#include <cstdio>
#include <iostream>
#include <map>

#include <list>

#include "parser.h"

using namespace std;

#if 0

list<char>::iterator  Parser::InsertTask (char task, list<char>::iterator startPos)
{
                // as long as the letters more, move to next
                // insert before the first letter you find that is higher

	if (startPos == opOrder.end())
	{
		cout << "   weird, sent in the end iterator " << endl;
	        opOrder.push_back(task);

        	//return opOrder.end()--;
		list<char>::iterator newpos;
		FindTask(task, opOrder.begin(), newpos);
		return newpos;
	}
	else
	{
	//	cout << "   starting looking for insert point at letter " << *startPos << endl;
	}
	for (auto curr = startPos; curr != opOrder.end(); curr++)
	{
		//cout << __LINE__ << ": curr=" << *curr << " new task=" << task << endl;
		if (*curr > task)
		{
	//		cout << "inserting --- " << task << " --- BEFORE === " << *curr << " ===" << endl;
			return opOrder.emplace(curr, task);
		}
		else
		{
	//		cout << "      searching... (curr= " << *curr << "  <  new= " << task << " ) " << endl;
		} 
	}

	cout << "didn't find a better place so put '" << task << "' at the end of the ops" << endl;
	opOrder.push_back(task);

	return opOrder.end()--;
}

void Parser::FindTask (char task, list<char>::iterator start, list<char>::iterator & pos)
{
	for (auto curr = start; curr != opOrder.end(); curr++)
	{
		if (*curr == task)
		{
	//		cout << "   found task " << task << endl;
			pos = curr;
			return;
		}

	}
	
	//cout << "   > didn't find " << task << "  between " << *start << " and the end" << endl;
	pos = opOrder.end();
}
#endif

#if 0
void Parser::Process(const std::string & curr_line)
{
	char doFirst, doAfter;

	bool ok = false;

	//cout << __LINE__ << endl;
	ok = ParseLine(curr_line, doFirst, doAfter);

	if (!ok)
	{
		cout << "Failed to parse line::: " << curr_line << endl;
		return;
	}
      //cout << __LINE__ << endl;
  
	if (this->opOrder.size() == 0)
	{
		this->opOrder.push_back(doFirst);
		this->opOrder.push_back(doAfter);
	//	cout << "   list was empty, added " << doFirst << " then " << doAfter << endl;
		PrintResults();
		return;
	}
      //cout << __LINE__ << endl;
  
	// find the 'dofirst' item
	list<char>::iterator firstPos;
	FindTask(doFirst, opOrder.begin(), firstPos);
      //cout << __LINE__ << endl;
  	
	// if don't find it
	if (firstPos == opOrder.end())
	{
		cout << "   first task wasn't found in the list, inserting from the beginning... " << doFirst << endl;
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
  		PrintResults();	
//	      cout << "  task " << doAfter << " is already after is already after before " << doFirst << " ... done " << endl;
		return;
	}

      //cout << __LINE__ << " about to erase " << doAfter << " from the list" << endl;
  
//	cout << "     Before ERaSE task=" << doAfter << endl;
//	PrintResults();
	// if it is before, erase
	opOrder.remove(doAfter);
//	cout << "     After ERASE task=" << doAfter << endl;
//	PrintResults();

	//PrintResults();
	// if it is before or not at all, insert after
	auto firstInsertPoint = firstPos;
//	cout << "   first task= " << doFirst << ", but at firstPos=" << *firstPos << endl;
	firstInsertPoint++;
	InsertTask (doAfter, firstInsertPoint);	

//	cout << " Task to be completed first = " << doFirst << ", task to do after = " << doAfter << endl;
	PrintResults();
}

#endif

void Parser::Process (const string& line)
{
	char before, after;
	bool parsed;

	parsed = ParseLine (line, before, after);

	if (!parsed)
	{
		cout << "ERROR: unable to parse line [" << line << "]" << endl;
		return;
	}

	UpdateNoBefore(before, after);

	UpdateQueues(before, after);
	
}

list<char>::iterator FindInList (char id, list<char>& listToSearch)
{
	return std::find (listToSeach.begin(), listToSearch.end(), id);
}

void Parser::UpdateNoBefore (char currBefore, char currAfter)
{

	// if currAfter is in the NoBefores list, then remove
	noBefores.erase(currAfter);

	// if currBefore is not in EvenSeen, add to NoBefores
	if (FindInList(currBefore, everSeen) == everSeen.end())
	{
		InsertIntoList(currBefore, noBefores);
		InsertIntoList(currBefore, everSeen);
	}

	// add CurrBefore and CurrAfter no EvenSeen
	InsertInfoList(currAfter, everSeen);
	
}

void Parser::UpdateQueues (char currBefore, char currAfter)
{

	// insert currAfter to currBefore's queuek

	auto currBeforeQueue = queueMap[currBefore];

	InsertIntoList(currAfter, currBeforeQueue);
}

void Parser::PrintResults()
{

	cout << "Order of operations:: ";

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
	cout << "   " << beforeTask << "   BEFORE  " << afterTask << endl;
	return true;
}
	

