#pragma once
#include "Token.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
class IOModule {
public:
	IOModule() = delete;
	IOModule(string p) { p_path = p; 	file = make_unique<ifstream>(p_path);  }
	~IOModule();

public:
	//! ������� ��� ������ ��������� �������
	shared_ptr<lexeme> ReadNext();
	//! �����  �������
	void printLex(lexeme* lex) {
		cout << lex->toString() << endl;
	};
	void printToken(Token* tok) {
		if (tok == nullptr) {
			cout << "nullptr Token"<<endl;
			return;
		}
		cout << tok->toString() << endl;
	};
private:
	int currRow = 0;
	int currCol = 0;
	//! ������ ���������� �������
	void readNext(char& c);

	unique_ptr<ifstream> file;
	string p_path;
};