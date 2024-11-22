#pragma once
#include "IOModule.h"
#include <algorithm>
#include "AreaView.h"
#include <queue>

using namespace std;
class LEXModule {
public:
	

	LEXModule() = delete;
	LEXModule(shared_ptr<IOModule> iom) { iom_ptr = iom; }

	bool read_vars = false;
	//! �������� ��������� ����� �� IO
	shared_ptr<Token> getNext();
	//! ������������� ����� � �������
	shared_ptr<Token> genToken(shared_ptr<lexeme> lex);

	//! �� ������������� �������� � ������� �����, ��� ��������� getNext
	void pushToOld(shared_ptr<Token> tok);
	//! ��������� �������� �� ������������ ����� � ������.
	bool isReal(string s) const;
	//! ��������� ������� �� ������ � ������
	bool isChar(string s) const {
		return s.size() == 3 && s[0] == '\'' && s[2] == '\'';
	}
	//! ��������� ������� �� ����� ����� � ������
	bool isInt(string s)const{ return !s.empty() && s.find_first_not_of("0123456789") == std::string::npos; }
	//! ��������� �������� �� ��������� ���������� � ������
	bool isBoolean(string s) const { return s == "true" || s == "false"; }

	shared_ptr<AreaView> area_;
private:
	
	queue<shared_ptr<Token>> old_mas;
	shared_ptr<IOModule> iom_ptr;
};