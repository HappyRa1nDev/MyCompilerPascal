#pragma once
#include <string>
#include <memory>
#include "PascalDefines.h"
using namespace std;
enum eTokenType {
	eConstant = 1,
	eConstantInt = 1 << 1,
	eConstantReal = 1<<2,
	eConstantChar = 1<<3,
	eConstantBoolean = 1<<4,
	eOperation = 1<<5,
	eOperationLog = 1<<6,
	eOperationA = 1<<7,
	eKeyword = 1<<8,
	eKeywordHelper = 1<<9,
	eKeywordSimple = 1<< 10,
	eKeywordIdent = 1<<11
};
class Token {
public:
	virtual int getTokenType() = 0;
	virtual string toString() = 0; /*{ return lex->toString() + " Token"; }*/
	shared_ptr<lexeme> lex;
};




