#pragma once
#include "Token.h"
//����� ����� �������� ����
class TKeyWord: public Token {
public:
	eKeywordEnum word;
	virtual int getTokenType() override { return eKeyword; }

	virtual string toString() override { return lex->toString() + " TKeyWord"; }

};
////����� ����� ���������������
//class TKeyWordIdent : public TKeyWord {
//public:
//	virtual int getTokenType() override { return (eKeyword | eKeywordIdent); }
//	virtual string toString() override { return lex->toString() + " TKeyWordIdent"; }
//};
////����� ������������ ����� . ; ,
//class TKeyWordHelper : public TKeyWord {
//public:
//	virtual int getTokenType() override { return (eKeyword | eKeywordHelper); }
//};