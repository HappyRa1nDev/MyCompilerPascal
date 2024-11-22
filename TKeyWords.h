#pragma once
#include "Token.h"
//обший класс ключевых слов
class TKeyWord: public Token {
public:
	eKeywordEnum word;
	virtual int getTokenType() override { return eKeyword; }

	virtual string toString() override { return lex->toString() + " TKeyWord"; }

};
////общий класс идентификаторов
//class TKeyWordIdent : public TKeyWord {
//public:
//	virtual int getTokenType() override { return (eKeyword | eKeywordIdent); }
//	virtual string toString() override { return lex->toString() + " TKeyWordIdent"; }
//};
////Класс разделителей вроде . ; ,
//class TKeyWordHelper : public TKeyWord {
//public:
//	virtual int getTokenType() override { return (eKeyword | eKeywordHelper); }
//};