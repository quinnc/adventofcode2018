#include "opcodes.h"
#include <string>

#include <cstdio>
#include <iostream>

using namespace std;
void OpCode::PrintInfo ()
{
	cout << __FUNCTION__ << ":" << __LINE__ << " OP= " << name << " - " << opNum << endl;
}
void OpCode::SetOpNum (int op)
{
	if (opNum != -1)
	{
		opNum = op;
	}
	else
	{
		opNum = opNum * 100 + op;
		opNum = -1 * opNum;
	}
}

 
void SplitRegs (const string& line, int &r1, int& r2, int& r3, int& r4)
{
        int start, end;

        start = 9;
        end = line.find(',', start);
//	cout << "start=" << start << ", end=" << end << ", substr=" << line.substr(start,end-start) << endl;
        r1 = stoi (line.substr(start, end-start));

        start = end+2;
        end = line.find (',', start);
  //      cout << "start=" << start << ", end=" << end << ", substr=" << line.substr(start,end-start) << endl;

        r2 =  stoi (line.substr(start, end-start));

        start = end+2;
        end = line.find (',', start);
    //    cout << "start=" << start << ", end=" << end << ", substr=" << line.substr(start,end-start) << endl;
        r3 =  stoi (line.substr(start, end-start));

        start = end+2;
        end = line.find (']', start);
      //  cout << "start=" << start << ", end=" << end << ", substr=" << line.substr(start,end-start) << endl;
        r4 =  stoi (line.substr(start, end-start));
}

void OpCode::Init (const string & line)
{
	SplitRegs(line, regs[0], regs[1], regs[2], regs[3]);
//	cout << __FUNCTION__ << " input line: " << line << endl;
//	cout << "    parsed as -" << regs[0] << "-" << regs[1] << "-" << regs[2] << "-" << regs[3] << endl;
}

bool OpCode::DoResultsMatch (const string& line)
{
	int t[4];
	SplitRegs(line, t[0], t[1], t[2], t[3]);
	cout << __FUNCTION__ << " OP [" << name << "]: results line:::" << line 
		<< ":::   parsed as -" << t[0] << "-" << t[1] << "-" << t[2] << "-" << t[3] 
		<< ", reg as -" << regs[0] << "-" << regs[1] << "-" << regs[2] << "-" << regs[3] << endl;

	bool isMatch = (t[0] == regs[0] && t[1] == regs[1] && t[2] == regs[2] && t[3] == regs[3]);
/*
	if (isMatch)
	{
		if (opNum == -1)
		{
			opNum = parsedOpNum;
		}
		else if (opNum != parsedOpNum)
		{
			opNum = -2;
		}
	}
*/
	return isMatch;
}


void OpCode::SplitLine(const string& line, int& op, int& arg1, int& arg2, int& arg3)
{
	int start, end;

	start = 0;
	end = line.find(' ', start);
    //   cout << "start=" << start << ", end=" << end << ", substr=" << line.substr(start,end-start) << endl;
 	op = stoi (line.substr(start, end-start));
	parsedOpNum = op;

	start = end+1;
	end = line.find (' ', start);
//       cout << "start=" << start << ", end=" << end << ", substr=" << line.substr(start,end-start) << endl;
 	arg1 =  stoi (line.substr(start, end-start));
	//arg1 = line[2] - '0';
	
	start = end+1;
        end = line.find (' ', start);
  //     cout << "start=" << start << ", end=" << end << ", substr=" << line.substr(start,end-start) << endl;
         arg2 =  stoi (line.substr(start, end-start));
	//arg2 = line[4] - '0';
	
	start = end+1;
	end = line.find (' ', start);
    //   cout << "start=" << start << ", end=" << end << ", substr=" << line.substr(start,end-start) << endl;
	arg3 =  stoi (line.substr(start, end-start));
	//arg3 = line[6] - '0';

	//cout << __FUNCTION__ << " input line: " << line << endl;
	//cout << "    parsed as -" << op << "-" << arg1 << "-" << arg2 << "-" << arg3 << endl;
}

/* op X Y Z: add contents of reg X to contents of reg Y and write to reg Z */
void AddR::Exec(const string& line)
{
	int cmdA, cmdB, cmdC, cmdOp;
	SplitLine(line, cmdOp, cmdA, cmdB, cmdC);

	regs[cmdC] = regs[cmdA] + regs[cmdB];
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

void MultI::Exec(const string& line)
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
{
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

        regs[c[3]] = ( (regs[c[1]] > regs[c[2]]) ? 1 : 0);
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

