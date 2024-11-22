#include "LEXModule.h"
#include "TKeyWords.h"
#include "TConstants.h"
#include "TOperations.h"
#include "TIdent.h"
#include "Errors.h"
shared_ptr<Token> LEXModule::getNext()
{
	if (!old_mas.empty()) {
		shared_ptr<Token> tok;
		tok = old_mas.front();
		old_mas.pop();
		return tok;
	}
	return genToken(iom_ptr->ReadNext());
}
shared_ptr<Token> LEXModule::genToken(shared_ptr<lexeme> lex)
{
	shared_ptr<Token> tok;

	
	//char ch = lex->value[0];
	int keyword_number = tableKeyWord[lex->value];
	if (keyword_number) {
		//ключевое слово
		int type = keyword_number /1000;
		switch (type)
		{
		case 1: // ключевые слова
		case 2: //вспомогательные ключевые слова 
		{
			shared_ptr<TKeyWord> tmp = make_shared<TKeyWord>();
			tmp->word = (eKeywordEnum)keyword_number;
			tok = tmp;
		}
		break;
		case 3: //Операции
			shared_ptr<TOperation> tmp = make_shared<TOperation>();
			tmp->word = (eKeywordEnum)keyword_number;
			tok = tmp;
			break;
		}

	}
	else {
		//константа
		if (isReal(lex->value)) {
			shared_ptr<TConstantReal> tmp = make_shared<TConstantReal>();
			tmp->value = std::stod(lex->value);
			tok = tmp;
		}
		else
		if (isChar(lex->value)) {
			shared_ptr<TConstantChar> tmp = make_shared<TConstantChar>();
			tmp->value = lex->value[1];
			tok = tmp;
		}
		else
		if (isBoolean(lex->value)) {
			shared_ptr<TConstantBoolean> tmp = make_shared<TConstantBoolean>();
			if (lex->value == "true") {
				tmp->value = true;
			}
			else {
				tmp->value = false;
			}
			tok = tmp;
		}
		else
		if (isInt(lex->value)) {
			shared_ptr<TConstantReal> tmp = make_shared<TConstantReal>();
			tmp->value = std::stoi(lex->value);
			tok = tmp;
		}
		else {
			if (read_vars) {
				shared_ptr<TIdent> tmp = make_shared<TIdent>();
				tok = tmp;
			}
			else {
				if (!area_->vars.count(lex->value)) {
					t_error.AddError(lex, eLex);
					for (auto v : t_error.vec_err) {
						std::cout << v->toString() << std::endl;
					}
					exit(3);
				}
				else {
					shared_ptr<TIdent> tmp = make_shared<TIdent>();
					tok = tmp;
				}
			}
			//пока что просто идентификатор, без проверки тбалицы, так как таблица формируется на следующих этапах
		}
	}
	if (tok != nullptr) {
		tok->lex = lex;
	}
	return tok;
}

void LEXModule::pushToOld(shared_ptr<Token> tok)
{
	old_mas.push(tok);
}

bool LEXModule::isReal(string s) const
{
	char dot = '.';
	bool isDot = false;
	for (int i = 0; i < s.size(); i++) {
		if (s[i]==dot && isDot)
			return false;
		if (s[i] == dot) {
			isDot = true;
			continue;
		}
		if (s[i] < '0' || s[i]>'9')
			return false;
	}
	return true;
}
