
#ifndef _OPCODES_H_
#define _OPCODES_H_ 1

#include <string>

class OpCode
{
public:
	std::string name;

	OpCode (std::string& _name):name(_name)
	{}

	void SetInitial (int a, int b, int c, int d)
	{
		regA = a;
		regB = b;
		regC = c;
		regD = d;
	}

	virtual void Exec() = 0;

	void GetResult (int& a int& b, int& c, int& d)
	{
		a = regA; b = regB; c = regC; d = regD;
	}

	bool DoResultsMatch (int a, int b, int c, int d)
	{
		return (regA == a && regB == b && regC == c && regD == d);
	}


private:
	int regA, regB, regC, regD;
}

/* op X Y Z: add contents of reg X to contents of reg Y and write to reg Z */
class AddR : public OpCode
{
public:
	AddR():OpCode("addr") {}

	virtual void Exec() override;
}

/* op X Y Z : add Y to contents of reg X and put into reg Z */
class AddI : public OpCode
{
public:
	AddI(): OpCode("addi") {}
	virtual void Exec() override;
}

/* multr X Y Z : multi reg X by reg Y and write to Z */
class MultR : public OpCode
{
public:
	MultR() : OpCode("mulr") {}
	virtual void Exec() override;
}

class MultI : public OpCode
{
public:
	MultI() : OpCode ("muli") {}
	virtual void Exec() override;
}

/* bit wise AND of 2 registers */
class BanR : public OpCode
{
public:
	BandR () : OpCode("banr") {}

	virtual void Exec() override;
}

class BandI : public OpCode
{
public:
	BandI() : OpCode("bani") {}
	virtual void Exec() override;
}

/* bitwise OR */
class BorR : public OpCode
{
public:
	BorR () : OpCode ("borr") {}
	virtual void Exec() override;
}

class BorI : public OpCode
{
public:
	BorI () : OpCode ("bori") {}
	virtual void Exec() override;
}

/* store A in C (B is ignored) */
class SetR : public OpCode
{
public:
	SetR() : OpCode("setr") {}
	virtual void Exec() override;
}

class SetI : public OpCode
{
public:
	SetI() : OpCode("seti") {}
	virtual void Exec() override;
}

/* greater than */
class GtIR : public OpCode
{
public:
	GtIR() : OpCode ("gtir") {}
	virtual void Exec() override;
}


class GtRI : public OpCode
{
public:
	GtRI() : OpCode ("gtri") {}
	virtual void Exec() override;
}

class GtRR : public OpCode
{
public:
	GtRR() : OpCode ("gtrr") {}
	virtual void Exec() override;
}


/* equal to */
class EqIR : public OpCode
{
public:
	EqIR() : OpCode ("eqir") {}
	virtual void Exec() override;
}

class EqRI : public OpCode
{
public:
	EqRI() : OpCode ("eqri") {}
	virtual void Exec() override;
}

class EqRR : public OpCode
{
public:
	EqRR() : OpCode ("eqrr") {}
	virtual void Exec() override;
}


#endif


