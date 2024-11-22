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
	//! получить следующий токен от IO
	shared_ptr<Token> getNext();
	//! преобразовать токен в лексему
	shared_ptr<Token> genToken(shared_ptr<lexeme> lex);

	//! По необходимости добавить в очередь токен, для получение getNext
	void pushToOld(shared_ptr<Token> tok);
	//! проверить записано ли вещественное число в строке.
	bool isReal(string s) const;
	//! проверить записан ли символ в строке
	bool isChar(string s) const {
		return s.size() == 3 && s[0] == '\'' && s[2] == '\'';
	}
	//! проверить записно ли целое число в строке
	bool isInt(string s)const{ return !s.empty() && s.find_first_not_of("0123456789") == std::string::npos; }
	//! проверить записана ли булевская переменная в строке
	bool isBoolean(string s) const { return s == "true" || s == "false"; }

	shared_ptr<AreaView> area_;
private:
	
	queue<shared_ptr<Token>> old_mas;
	shared_ptr<IOModule> iom_ptr;
};