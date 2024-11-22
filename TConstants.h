#pragma once
#include "Token.h"

class TConstant : public Token {
public:
	virtual int getTokenType() override { return eConstant; }
	virtual string toString() override { return lex->toString() + " TConstant"; }
};
class TConstantInt : public TConstant {
public:
	int value;
	virtual int getTokenType() override { return eConstant | eConstantInt; }
	virtual string toString() override { return lex->toString() + " TConstantInt"; }
};
class TConstantReal : public TConstant {
public:
	double value;
	virtual int getTokenType() override { return eConstant | eConstantReal ; }
	virtual string toString() override { return lex->toString() + " TConstantReal"; }
};
class TConstantChar : public TConstant {
public:
	char value;
	virtual int getTokenType() override { return eConstant | eConstantChar; }
	virtual string toString() override { return lex->toString() + " TConstantChar"; }
};
class TConstantBoolean : public TConstant {
public:
	bool value;
	virtual int getTokenType() override { return eConstant | eConstantBoolean; }
	virtual string toString() override { return lex->toString() + " TConstantBoolean"; }

};