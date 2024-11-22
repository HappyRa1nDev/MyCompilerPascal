#pragma once
#include "Token.h"
//общий класс идентификаторов
class TIdent : public Token {
public:
	virtual int getTokenType() override { return (eKeywordIdent); }
	virtual string toString() override { return lex->toString() + " TIdent"; }
};