#include "opcodes.h"
#include <string>

#include <cstdio>
#include <iostream>

using namespace std;

void OpCode::Init (const string & line)
{
	reg[0] = line[9] - '0';
	reg[1] = line[12] - '0';;
	reg[2] = line[15] - '0';
	reg[3] = line[18] - '0';
	cout << __FUNCTION__ << " input line: " << line << endl;
	cout << "    parsed as -" << reg[0] << "-" << reg[1] << "-" << reg[2] << "-" << reg[3] << endl;

}

bool OpCode::DoResultsMatch (const string& line)
{
	int t[4];

	
	t[0] = line[9] - '0';
	t[1] = line[12] - '0';
	t[2] = line[15] - '0';
	t[3] = line[18] - '0';

	cout << __FUNCTION__ << " input line: " << line << endl;
	cout << "    parsed as -" << t[0] << "-" << t[1] << "-" << t[2] << "-" << t[3] << endl;

	return (t[0] == reg[0] && t[1] == reg[1] && t[2] == reg[2] && t[3] == reg[3]);
}


void OpCode::SplitLine(const string& line, int& op, int& arg1, int& arg2, int& arg3)
{

	op = line[0] - '0';
	arg1 = line[2] - '0';
	arg2 = line[4] - '0';
	arg3 = line[6] - '0';

	cout << __FUNCTION__ << " input line: " << line << endl;
	cout << "    parsed as -" << op << "-" << arg1 << "-" << arg2 << "-" << arg3 << endl;
}

/* op X Y Z: add contents of reg X to contents of reg Y and write to reg Z */
void AddR::Exec(const string& line)
{
	int cmdA, cmdB, cmdC, cmdOp;
	SplitLine(line, cmdOp, cmdA, cmdB, cmdC);

	regs[cmdC] = regs[cmdA] + regs[cmdB]
}

void AddI::Exec(const string& line) 
{
	int c[4];
	SplitLine(line, c[0],c[1],c[2],c[3]);

	regs[c[3]] = regs[c[1]] + c[2];
}


void MultR::Exec(const string& line)
{
       int c[4];
        SplitLine(line, c[0],c[1],c[2],c[3]);

	regs[c[3]] = regs[c[1]] * regs[c[2]];
}

void Multi::Exec(const string& line)
{
       int c[4];
        SplitLine(line, c[0],c[1],c[2],c[3]);

        regs[c[3]] = regs[c[1]] * c[2];
}

/* bit wise AND of 2 registers */
//class BanR : public OpCode
void BanR::Exec(const string& line)
{
       int c[4];
        SplitLine(line, c[0],c[1],c[2],c[3]);

        regs[c[3]] = regs[c[1]] & regs[c[2]];
}

//class BandI : public OpCode
void BandI::Exec(const string& line)
{
       int c[4];
        SplitLine(line, c[0],c[1],c[2],c[3]);

        regs[c[3]] = regs[c[1]] & c[2];

}

/* bitwise OR */
void BorR::Exec(const string& line)
{
       int c[4];
        SplitLine(line, c[0],c[1],c[2],c[3]);

        regs[c[3]] = regs[c[1]] | regs[c[2]];

}

//class BorI : public OpCode
 void BorI::Exec(const string& line)
{

       int c[4];
        SplitLine(line, c[0],c[1],c[2],c[3]);

        regs[c[3]] = regs[c[1]] | c[2];
}

/* store A in C (B is ignored) */
//class SetR : public OpCode
void SetR::Exec(const string& line) 
{
       int c[4];
        SplitLine(line, c[0],c[1],c[2],c[3]);

        regs[c[3]] = regs[c[1]];

}

//class SetI : public OpCode
 void SetI::Exec(const string& line)
{

       int c[4];
        SplitLine(line, c[0],c[1],c[2],c[3]);

        regs[c[3]] = c[1];

}

/* greater than */
//class GtIR : public OpCode
 void GtIR::Exec(const string& line)

       int c[4];
        SplitLine(line, c[0],c[1],c[2],c[3]);

        regs[c[3]] = ( (c[1] > regs[c[2]])? 1 : 0);
}


//class GtRI : public OpCode
 void GtRI::Exec(const string& line) 
{
       int c[4];
        SplitLine(line, c[0],c[1],c[2],c[3]);

        regs[c[3]] = ( ( regs[c[1]] > c[2]) ? 1 : 0);
}

//class GtRR : public OpCode
 void GtRR::Exec(const string& line) 
{
       int c[4];
        SplitLine(line, c[0],c[1],c[2],c[3]);

        regs[c[3]] = ( (regs[c[1]] > regs[c[2]]) ? 1 : 0;
}


/* equal to */
//class EqIR : public OpCode
 void EqIR::Exec(const string& line) 
{
       int c[4];
        SplitLine(line, c[0],c[1],c[2],c[3]);

        regs[c[3]] = ( (c[1] ==  regs[c[2]]) ? 1 : 0);
}

//class EqRI : public OpCode
void EqRI::Exec(const string& line)
{
	int c[4];
	SplitLine (line, c[0],c[1],c[2],c[3]);
	
	regs[c[3]] = ( (regs[c[1]] == c[2]) ? 1 : 0 );
}

//class EqRR : public OpCode
void EqRR::Exec(const string& line)
{
	int c[4];
	SplitLine (line, c[0],c[1],c[2],c[3]);
	
	regs[c[3]] = ( (regs[c[1]] ==  regs[c[2]]) ? 1 : 0);
}

