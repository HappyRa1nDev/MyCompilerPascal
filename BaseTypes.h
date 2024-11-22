#pragma once
//#include "PascalDefines.h"
#include <map>
#include <vector>
#include <string>
using namespace std;

class textposition {
public:
	textposition() {};
	textposition(int line, int col) {
		linenumber = line;
		charnumber = col;
	}
	int linenumber;
	int charnumber;
};



class lexeme {
public:
	lexeme(int line, int col, string s) {
		position = textposition(line, col);
		value = s;
	}
	textposition position;
	string value;
	
	string toString() const{
		string s = to_string(position.linenumber) + " " + to_string(position.charnumber) + " " + value;
		return s;
	}
};

//std::vector<lexeme> listLexeme;
//struct symbolData {
//	unsigned symbol; //< код символа
//	textposition token;// позиция символа
//	char* addrname;// адрес в таблице имен
//
//	int nmb_int;//значение целой константы
//
//	float nmb_float;//значение вещественной константы
//
//	char one_symbol;//значение символьной константы
//};
//
//std::map<int, std::string> tableKeyWord{
//	{ ident , " "},
//	{ ifsy, "if"},
//	{ dosy, "do"},
//	{ ofsy, "of"},
//	{ orsy, "or"},
//	{ insy, "in"},
//	{ tosy, "to"},
//	{ endsy, "end"},
//	{ varsy, "var"},
//	{ divsy, "div"},
//	{ andsy, "and"},
//	{ notsy, "mot"},
//	{ forsy, "for"},
//	{ modsy, "mod"},
//	{ nilsy, "nil"},
//	{ setsy, "set"},
//	{ thensy, "then"},
//	{ elsesy, "else"},
//	{ casesy, "case"},
//	{ filesy, "file"},
//	{ gotosy, "goto"},
//	{ typesy, "type"},
//	{ withsy, "with"},
//	{ beginsy, "begin"},
//	{ whilesy, "while"},
//	{ arraysy, "array"},
//	{ constsy, "const"},
//	{ labelsy, "label"},
//	{ untilsy, "until"},
//	{ downtosy, "downto"},
//	{ packedsy, "packed"},
//	{ recordsy, "record"},
//	{ repeatsy, "repeat"},
//	{ programsy, "program"},
//	{ functionsy, "function"},
//	{ proceduresy, "precedure"},
//};

//std::vector<symbolData> PascalProgram;