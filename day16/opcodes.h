
#ifndef _OPCODES_H_
#define _OPCODES_H_ 1

#include <string>

class OpCode
{
public:

	OpCode (const std::string& _name):name(_name)
	{}

	void SetInitial (int a, int b, int c, int d)
	{
		regs[0] = a;
		regs[1] = b;
		regs[2] = c;
		regs[3] = d;
	}

	virtual void Exec(const std::string& line) = 0;

	void GetResult (int& a, int& b, int& c, int& d)
	{
		a = regs[0]; b = regs[1]; c = regs[2]; d = regs[3];
	}

	bool DoResultsMatch (int a, int b, int c, int d)
	{
		return (regs[0] == a && regs[1] == b && regs[2] == c && regs[3] == d);
	}

	int ParsedOpNum () {return parsedOpNum;}
	bool DoResultsMatch (const std::string& resultsLine);
	void PrintInfo ();
	void Init (const std::string& line);
	void SetOpNum (int num);
private:
	std::string name;
	int opNum = -1;
	int parsedOpNum = -1;
	
protected:
	int regs[4];
	void SplitLine (const std::string& opLine, int& op, int& arg1, int& arg2, int& arg3);
};

/* op X Y Z: add contents of reg X to contents of reg Y and write to reg Z */
class AddR : public OpCode
{
public:
	AddR():OpCode("addr") {}

	virtual void Exec(const std::string& line) override;
};

/* op X Y Z : add Y to contents of reg X and put into reg Z */
class AddI : public OpCode
{
public:
	AddI(): OpCode("addi") {}
	virtual void Exec(const std::string& line) override;
};

/* multr X Y Z : multi reg X by reg Y and write to Z */
class MultR : public OpCode
{
public:
	MultR() : OpCode("mulr") {}
	virtual void Exec(const std::string& line) override;
};

class MultI : public OpCode
{
public:
	MultI() : OpCode ("muli") {}
	virtual void Exec(const std::string& line) override;
};

/* bit wise AND of 2 registers */
class BanR : public OpCode
{
public:
	BanR () : OpCode("banr") {}

	virtual void Exec(const std::string& line) override;
};

class BandI : public OpCode
{
public:
	BandI() : OpCode("bani") {}
	virtual void Exec(const std::string& line) override;
};

/* bitwise OR */
class BorR : public OpCode
{
public:
	BorR () : OpCode ("borr") {}
	virtual void Exec(const std::string& line) override;
};

class BorI : public OpCode
{
public:
	BorI () : OpCode ("bori") {}
	virtual void Exec(const std::string& line) override;
};

/* store A in C (B is ignored) */
class SetR : public OpCode
{
public:
	SetR() : OpCode("setr") {}
	virtual void Exec(const std::string& line) override;
};

class SetI : public OpCode
{
public:
	SetI() : OpCode("seti") {}
	virtual void Exec(const std::string& line) override;
};

/* greater than */
class GtIR : public OpCode
{
public:
	GtIR() : OpCode ("gtir") {}
	virtual void Exec(const std::string& line) override;
};


class GtRI : public OpCode
{
public:
	GtRI() : OpCode ("gtri") {}
	virtual void Exec(const std::string& line) override;
};

class GtRR : public OpCode
{
public:
	GtRR() : OpCode ("gtrr") {}
	virtual void Exec(const std::string& line) override;
};


/* equal to */
class EqIR : public OpCode
{
public:
	EqIR() : OpCode ("eqir") {}
	virtual void Exec(const std::string& line) override;
};

class EqRI : public OpCode
{
public:
	EqRI() : OpCode ("eqri") {}
	virtual void Exec(const std::string& line) override;
};

class EqRR : public OpCode
{
public:
	EqRR() : OpCode ("eqrr") {}
	virtual void Exec(const std::string& line) override;
};


#endif


