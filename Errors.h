#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include "Token.h"

using namespace std;

enum eCodeError {
	eLex = 1000,
	eSynt = 2000,
	eSyntNoname,
	eSem = 3000,
};
class Error {
public:
	Error(textposition p, string t, int c) {
		pos = p;
		text = t;
		code = c;
	}
	string text;
	textposition pos;
	int code;
	string toString() {
		string type;
		switch (code / 1000) {
		case 1:
			type = "ErrorLex";
			break;
		case 2:
			type = "ErrorSynt";
			break;
		case 3:
			type = "ErrorSem";
			break;
		}
		return type + to_string(code) + " line:" + to_string(pos.linenumber) + "col: " + to_string(pos.charnumber) + " " + text;
	}
};
class TableError {
public:
	void AddError(shared_ptr<lexeme> lex, int code, int type_wait = -1);
	vector<shared_ptr<Error>> vec_err;
};
namespace {
	TableError t_error;
}