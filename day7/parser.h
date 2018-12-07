#ifndef _Parser_
#define _Parser_ 1

#include <utility>
#include <map>


class Parser
{
public:
	void Process(const std::string & curr_line);
	void PrintResults();

private:
	bool ParseLine (const std::string& line, char & beforeTask, char& afterTask);	
};
	
#endif

