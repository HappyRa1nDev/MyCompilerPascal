#include "Errors.h"
#include <string>
using namespace std;
void TableError::AddError(shared_ptr<lexeme> lex, int code, int type_wait)
{
	string txt;
	switch (code) {
	case 1000:
	case 2000:
	case 3000:
		if (type_wait != -1) {
			txt = "expected " + tableKeyWordByInt[type_wait] + " got " + lex->value;
		}
		else {
			txt = "unexpected token " + lex->value;
		}
		break;
	case 2001:
		txt = "noname token " + lex->value;
		break;
	}

	vec_err.push_back(make_shared<Error>(lex->position, txt, code));
}

