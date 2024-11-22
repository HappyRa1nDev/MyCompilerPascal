#include "IOModule.h"
#include <fstream>
#include <vector>
#include "BaseTypes.h"
#include <string>
using namespace std;



void IOModule::readNext(char& ch) {
	ch = tolower(file->get());
	if (ch == '\r' || ch == '\n') {
		currRow++;
		currCol = 0;
	}
	else {
		currCol++;
	}
}

IOModule::~IOModule()
{
	file->close();
}

shared_ptr<lexeme> IOModule::ReadNext() {
	//ifstream file(path);
	shared_ptr<lexeme> lex;
	if (file->eof()) {
		return lex;
	}
	string str;


	std::vector<char> tmpLex;
	char ch;
	int row = currRow;
	int col = currCol;

	while (!file->eof()) {
		readNext(ch);
		switch (ch) {
		case '\r':
		case '\n':
		case 9:
		case ' ': {
			if (tmpLex.size() > 0) {
				string str(tmpLex.begin(), tmpLex.end());
				lex = make_shared<lexeme>(row, col, str);
				file->seekg(-1, file->cur); //сместить позицию
				currCol--;
				tmpLex.clear();
				return lex;
			}
			col = currCol;
			row = currRow;
			break;
		}
		case '+':
		case '-':
		case '*':
		case '/':
		case '=':
		case '<':
		case '>':
		case ';':
		case '(':
		case ')':
		case ',':
		{
			if (tmpLex.size() > 0) {
				string str(tmpLex.begin(), tmpLex.end());
				lex = make_shared<lexeme>(row, col, str);
				tmpLex.clear();
				file->seekg(-1, file->cur);
				currCol--;
				return lex;
			}
			string s;
			s.push_back(ch);
			lex = make_shared<lexeme>(row, col, s);
			return lex;
			break;
		}
		case '.':
		{
			if (tmpLex.size() > 0) {
				string str(tmpLex.begin(), tmpLex.end());
				bool flag = true;
				for (int i = 0; i < str.size(); i++) {
					if (str[i] - '0' > 9 || str[i] - '0' < 0)
					{
						flag = false;
						break;
					}
				}
				if (flag) {
					tmpLex.push_back(ch);
					break;
				}
				lex = make_shared<lexeme>(row, col, str);
				tmpLex.clear();
				file->seekg(-1, file->cur);
				currCol--;
				return lex;
			}
			string s;
			s.push_back(ch);
			lex = make_shared<lexeme>(row, col, s);
			return lex;
			break;
		}
		case ':':{
			if (tmpLex.size() > 0) {
				string str(tmpLex.begin(), tmpLex.end());
				file->seekg(-1, file->cur);
				currCol--;
				lex = make_shared<lexeme>(row, col, str);
				tmpLex.clear();
				return lex;
			}
			readNext(ch);
			if (ch != '=') {
				string str = ":";
				file->seekg(-1, file->cur);
				currCol--;
				lex = make_shared<lexeme>(row, col, str);
				return lex;
			}
			else {
				string str = ":=";
				lex = make_shared<lexeme>(row, col, str);
				tmpLex.clear();
				return lex;
			}
			break;
		}
		case'{': {
			if (tmpLex.size() > 0) {
				string str(tmpLex.begin(), tmpLex.end());
				lex = make_shared<lexeme>(row, col, str);
				file->seekg(-1, file->cur); //сместить позицию
				currCol--;
				tmpLex.clear();
				return lex;
			}
			while(ch!='}')
				readNext(ch);
		}
		break;
		default:
		{
			tmpLex.push_back(ch);
		}
		}
	}
	return lex;
	
}
