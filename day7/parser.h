#ifndef _Parser_
#define _Parser_ 1

#include <utility>
#include <list>


class Parser
{
public:
	void Process(const std::string & curr_line);
	void PrintResults();

private:
	bool ParseLine (const std::string& line, char & beforeTask, char& afterTask);	

	std::list<char>::iterator InsertTask (char task, std::list<char>::iterator startPos);

	void FindTask (char task,std::list<char>::iterator start, std::list<char>::iterator & pos);

	std::list<char> opOrder;
};
	
#endif

