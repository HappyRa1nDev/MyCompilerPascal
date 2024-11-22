#include "PascalCompiler.h"
#include "TKeyWords.h"
#include "TOperations.h"
#include "TConstants.h"
#include "TIdent.h"
#include "AreaView.h"

//#define use_debug 1;
PascalCompiler::PascalCompiler(string program_path)
{
	iom = make_shared<IOModule>(program_path);
	lexm = make_shared<LEXModule>(iom);
}

PascalCompiler::~PascalCompiler()
{
}

void PascalCompiler::compile()
{
	//прочитать старт программы
	ReadStartProgram();
	//прочитать блок
	ReadCodeBlock();
	for (auto v : t_error.vec_err) {
		cout << v->toString() << endl;
	}
}

void PascalCompiler::ReadStartProgram()
{
	cout << "+StartProgram"<<endl;
	lexm->read_vars = true;
	acceptKeyWord(kwProgram);
	acceptIdent();
	acceptKeyWord(kwhSemicolon);
	lexm->read_vars = false;
	cout << "-StartProgram"<<endl;
}

void PascalCompiler::ReadCodeBlock()
{
	cout << "+CodeBlock" << endl;
	OpenArea();
	//! читаем перменные
	ReadIdentBlock();
	//! читаем операторы
	ReadBeginEnd();
	CloseArea();
	cout << "-CodeBlock" << endl;
}

void PascalCompiler::ReadIdentBlock()
{
	cout << "+IdentBlock" << endl;
	lexm->read_vars = true;
	nextT();
	if (lastTok->lex->value == "var") {
		shared_ptr<TIdent> tok;
		vector<shared_ptr<TIdent>> vec;
		acceptKeyWord(kwVar, lastTok, eSynt);
		do {
			do {
				if (!acceptIdent(eSynt)) { 
					t_error.vec_err.pop_back(); 
					lexm->pushToOld(lastTok); 	
					lexm->read_vars = false;	
					cout << "-IdentBlock" << endl; 
					return; 
				}
				vec.push_back(dynamic_pointer_cast<TIdent>(lastTok));
				acceptKeyWord(kwhComma);
			} while (lastTok->lex->value == ",");
			acceptKeyWord(kwhColon, lastTok, eSynt);
			nextT();
			if (acceptKeyWord(kwInteger, lastTok) || acceptKeyWord(kwBoolean, lastTok)|| acceptKeyWord(kwChar, lastTok) || acceptKeyWord(kwReal, lastTok)) {
				//добавить в таблицу имен
				int type;
				string value = lastTok->lex->value;
				if (value == tableKeyWordByInt[kwBoolean]) {
					type = eBoolean;
				}
				else if (value== tableKeyWordByInt[kwInteger]){
					type = eInteger;
				}
				else if (value == tableKeyWordByInt[kwReal]) {
					type = eReal;
				}
				else if (value == tableKeyWordByInt[kwChar]) {
					type = eChar;
				}

				for (auto v : vec) {
					areas[cur_area]->AddValue(v, (eTypeVar)type);
				}
				vec.clear();
				acceptKeyWord(kwhSemicolon, eSynt);
			}
		} while (lastTok->lex->value == ";");
	}
	else {
		lexm->pushToOld(lastTok);
	}
	lexm->read_vars = false;
	cout << "-IdentBlock" << endl;
}
void PascalCompiler::readOperand() {
	std::cout << "+readOperand" << endl;
	shared_ptr<Token> tok = nextT();
	if (tok->lex->value == "-") {
		readOperand();
	}
	else {
		if (tok->lex->value == ")") {
			if (lvl_expr < 2) {
				t_error.AddError(tok->lex, eSynt);
			}
		}
		else if (tok->lex->value == "(") {
			ReadExpression();
		}
		else if (!(tok->getTokenType() & eConstant) && !(areas[cur_area]->vars.count(tok->lex->value))) {
			t_error.AddError(tok->lex, eSynt);
		}
		else {
			if (areas[cur_area]->vars.count(tok->lex->value) && (areas[cur_area]->init_vars.find(tok->lex->value)==areas[cur_area]->init_vars.end())) {
				t_error.AddError(tok->lex, eSem);
			}
			//читаем константу или берем значение перменной.
		}
	}
	std::cout << "-readOperand" << endl;
}
void PascalCompiler::ReadExpression()
{
	lvl_expr++;
	std::cout << "+readExpression" << endl;
	readOperand();
	shared_ptr<Token> tok = nextT();
	string t = tok->lex->value;
	while (t == "-" || t == "*" || t == "/" || t == "+") {
		readOperand();
		tok = nextT();
		t = tok->lex->value;
	}
	lexm->pushToOld(lastTok);
	if (checkNext()->lex->value == ")") {
		acceptOperation(kwhRightpar,eSynt);
	}
	lvl_expr--;
	std::cout << "-readExpression" << endl;
}
void PascalCompiler::ReadBoolExpression() {
	std::cout << "+ReadBoolExpression" << endl;
	if (!readBoolOperand()) {
		ReadExpression();
		nextT();
		if (acceptOperation(kwoEqual, lastTok) || acceptOperation(kwoLess, lastTok) || acceptOperation(kwoMore, lastTok)) {
			//readBoolOperand();
			ReadExpression();
		}
		else {
			lexm->pushToOld(lastTok);
		}
		
	}
	std::cout << "-ReadBoolExpression" << endl;
}

bool PascalCompiler::readBoolOperand()
{
	nextT();
	if (lastTok->getTokenType() & eConstantBoolean || (areas[cur_area]->vars[lastTok->lex->value] && areas[cur_area]->vars[lastTok->lex->value]->getTokenType() & eConstantBoolean)) {
		//применить операнд
		if (areas[cur_area]->vars[lastTok->lex->value]) {
			if (areas[cur_area]->init_vars.find(lastTok->lex->value) == areas[cur_area]->init_vars.end()) {
				t_error.AddError(lastTok->lex, eSem);
			}
		}
		return true;
	}
	else {
		lexm->pushToOld(lastTok);
		return false;
	}
}

void PascalCompiler::ReadIfThenELse()
{
	cout << "+ReadIfThenELse" << endl;
	acceptKeyWord(kwIf, eSynt);
	ReadBoolExpression();
	acceptKeyWord(kwThen, eSynt);
	ReadOperator();
	if (checkNext()->lex->value == "else") {
		acceptKeyWord(kwElse, eSynt);
		ReadOperator();
	}
	cout << "-ReadIfThenELse" << endl;
}
void PascalCompiler::ReadWhileDo() {
	cout << "+ReadWhileDo" << endl;
	acceptKeyWord(kwWhile, eSynt);
	ReadBoolExpression();
	acceptKeyWord(kwDo, eSynt);
	ReadOperator();
	cout << "-ReadWhileDo" << endl;
}

void PascalCompiler::ReadOperator() {
	std::cout << "+readOperator" << endl;
	shared_ptr<Token> tok=nextT();
	string v = tok->lex->value;
	int kek = areas[cur_area]->vars.count(tok->lex->value);
	if (v == tableKeyWordByInt[kwIf]) {
		//условный оператор
		lexm->pushToOld(lastTok);
		ReadIfThenELse();
	}
	else if (v == tableKeyWordByInt[kwWhile]) {
		//цикл while
		lexm->pushToOld(lastTok);
		ReadWhileDo();
	}
	else if (v == tableKeyWordByInt[kwBegin]) {
		lexm->pushToOld(lastTok);
		ReadBeginEnd();

	}
	else if (areas[cur_area]->vars.count(tok->lex->value)) {
		acceptKeyWord(kwAssign, eSynt);
		
		if (tok->getTokenType() & eConstantBoolean || (areas[cur_area]->vars[tok->lex->value] && areas[cur_area]->vars[tok->lex->value]->getTokenType() & eConstantBoolean))//
		{
			//прочитать булевское выражение
			ReadBoolExpression();
			acceptKeyWord(kwhSemicolon, eSynt);
		}
		else {
			//прочитать выражение
			ReadExpression();
			acceptKeyWord(kwhSemicolon, eSynt);
		}
		areas[cur_area]->init_vars.insert(tok->lex->value);
	}
	else if (v != tableKeyWordByInt[kwEnd]) {
		t_error.AddError(tok->lex, eSyntNoname);
	}

	std::cout << "-readOperator" << endl;
}

void PascalCompiler::ReadBeginEnd()
{
	cout << "+BeginEnd" << endl;
	acceptKeyWord(kwBegin, eSynt);
	do
	{
		ReadOperator();
		
	} while (checkNext()->lex->value != "end");
	
	cout << "-BeginEnd" << endl;
}

bool PascalCompiler::acceptKeyWord(eKeywordEnum w, int code)
{
	shared_ptr<Token> tok = nextT();
	shared_ptr<TKeyWord> key_w = dynamic_pointer_cast<TKeyWord>(tok);
	if (!key_w || key_w->word != w) {
		if (code > 0) { t_error.AddError(tok->lex, code, (int)w); };
		return false;
	}
	return true;
}
bool PascalCompiler::acceptKeyWord(eKeywordEnum w, shared_ptr<Token> tok, int code)
{
	shared_ptr<TKeyWord> key_w = dynamic_pointer_cast<TKeyWord>(tok);
	if (!key_w || key_w->word != w) {
		if (code > 0) {
			t_error.AddError(tok->lex, code, (int)w);
		};
		return false;
	}
	return true;
}

bool PascalCompiler::acceptOperation(eKeywordEnum w, shared_ptr<Token> tok, int code)
{
	shared_ptr<TOperation> op = dynamic_pointer_cast<TOperation>(tok);
	if (!op || op->word != w) {
		if (code > 0) { t_error.AddError(tok->lex, code, (int)w); };
		return false;
	}
	return true;
}

bool PascalCompiler::acceptConstant(shared_ptr<Token> tok, int code)
{
	shared_ptr<TConstant> con = dynamic_pointer_cast<TConstant>(tok);
	if (!con) {
		if (code > 0) { t_error.AddError(tok->lex, code); };
		return false;
	}
	return true;
}

bool PascalCompiler::acceptIdent(shared_ptr<Token> tok, int code)
{
	shared_ptr<TIdent> ident = dynamic_pointer_cast<TIdent>(tok);
	if (!ident) {
		if (code > 0) { t_error.AddError(tok->lex, code); };
		return false;
	}
	return true;
}

void PascalCompiler::OpenArea()
{
	areas.push_back(make_shared<AreaView>());
	cur_area++;
	lexm->area_ = areas[cur_area];
}

void PascalCompiler::CloseArea()
{
	areas.pop_back();
	cur_area--;
	if(cur_area>=0)
		lexm->area_ = areas[cur_area];
}

bool PascalCompiler::acceptOperation(eKeywordEnum w, int code)
{
	shared_ptr<Token> tok = nextT();
	shared_ptr<TOperation> op = dynamic_pointer_cast<TOperation>(tok);
	if (!op || op->word != w) {
		if (code > 0) { t_error.AddError(tok->lex, code); };
		return false;
	}
	return true;
}

bool PascalCompiler::acceptConstant(int code)
{
	shared_ptr<Token> tok = nextT();
	shared_ptr<TConstant> con = dynamic_pointer_cast<TConstant>(tok);
	if (!con) {
		if (code > 0) { t_error.AddError(tok->lex, code); };
		return false;
	}
	return true;
}

bool PascalCompiler::acceptIdent(int code)
{
	shared_ptr<Token> tok = nextT();
	shared_ptr<TIdent> ident = dynamic_pointer_cast<TIdent>(tok);
	if (!ident) {
		if (code > 0) { t_error.AddError(tok->lex, code); };
		return false;
	}
	return true;
}


