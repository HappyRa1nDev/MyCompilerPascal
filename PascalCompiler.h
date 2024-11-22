#pragma once
#include "IOModule.h"
#include "LEXModule.h"
#include "AreaView.h"
#include "Errors.h"
#include <set>
#include <memory>

using namespace std;
class PascalCompiler
{
public:
	PascalCompiler() = delete;
	PascalCompiler(string program_path);
	~PascalCompiler();
	//! запустить компиляцию
	void compile();
	
private:
	//!+ блок функций синтаксического анализатора
	//! прочитать начало программы Program ...;
	void ReadStartProgram();
	//! прочитьать блок кода
	void ReadCodeBlock();
	//! прочитать блок переменных
	void ReadIdentBlock();
	//! прочитать составной блок
	void ReadBeginEnd();
	//! прочитать оператор
	void ReadOperator();
	//! прочитать выражение
	void ReadExpression();
	//! прочитать операнд
	void readOperand();
	//! прочитать булевское выражение
	void ReadBoolExpression();
	//! Прочитать логический операнд
	bool readBoolOperand();

	//! прочитать if else
	void ReadIfThenELse();
	//! прочитать while do
	void ReadWhileDo();



	//!! функции проверки токна
	bool acceptKeyWord(eKeywordEnum w, int code = -1);
	bool acceptOperation(eKeywordEnum w, int code = -1);
	bool acceptConstant(int code = -1);
	bool acceptIdent(int code = -1);

	//!! функции проверки токена после поулчения токена
	bool acceptKeyWord(eKeywordEnum w, shared_ptr<Token> tok,int code=-1);
	bool acceptOperation(eKeywordEnum w, shared_ptr<Token> tok, int code = -1);
	bool acceptConstant(shared_ptr<Token> tok, int code = -1);
	bool acceptIdent(shared_ptr<Token> tok, int code = -1);

	//вспопомгательные функции
	shared_ptr<Token> checkNext() { lexm->pushToOld(nextT()); return lastTok; }

	//!- блок функций синтаксического анализатора
	//!+ семантический
	void OpenArea();
	void CloseArea();
	//! - семантический
private:
	int lvl_expr = 0;

	shared_ptr<Token> lastTok;
	shared_ptr<Token> nextT() {
		lastTok= lexm->getNext();
		return lastTok;
	}
	//! модуль ввода/вывода
	shared_ptr<IOModule> iom;
	shared_ptr<LEXModule> lexm;

	//вектор областей видимости
	int cur_area = -1;
	vector<shared_ptr<AreaView>> areas;
};
