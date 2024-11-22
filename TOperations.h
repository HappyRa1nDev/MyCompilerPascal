#pragma once
#include "Token.h"
//Операции
class TOperation :public Token {
public:
	eKeywordEnum word;
	virtual int getTokenType() override { return eOperation; }
	virtual string toString() override { return lex->toString() + " TOperation"; }
};
//class TOperationLogical : public TOperation {
//public:
//	virtual int getTokenType() override { return eOperation | eOperationLog; }
//};
//class TOperationA :public TOperation {
//public:
//	bool isContains()
//	virtual int getTokenType() override { return eOperation | eOperationA; }
//};