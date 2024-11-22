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
	//! ��������� ����������
	void compile();
	
private:
	//!+ ���� ������� ��������������� �����������
	//! ��������� ������ ��������� Program ...;
	void ReadStartProgram();
	//! ���������� ���� ����
	void ReadCodeBlock();
	//! ��������� ���� ����������
	void ReadIdentBlock();
	//! ��������� ��������� ����
	void ReadBeginEnd();
	//! ��������� ��������
	void ReadOperator();
	//! ��������� ���������
	void ReadExpression();
	//! ��������� �������
	void readOperand();
	//! ��������� ��������� ���������
	void ReadBoolExpression();
	//! ��������� ���������� �������
	bool readBoolOperand();

	//! ��������� if else
	void ReadIfThenELse();
	//! ��������� while do
	void ReadWhileDo();



	//!! ������� �������� �����
	bool acceptKeyWord(eKeywordEnum w, int code = -1);
	bool acceptOperation(eKeywordEnum w, int code = -1);
	bool acceptConstant(int code = -1);
	bool acceptIdent(int code = -1);

	//!! ������� �������� ������ ����� ��������� ������
	bool acceptKeyWord(eKeywordEnum w, shared_ptr<Token> tok,int code=-1);
	bool acceptOperation(eKeywordEnum w, shared_ptr<Token> tok, int code = -1);
	bool acceptConstant(shared_ptr<Token> tok, int code = -1);
	bool acceptIdent(shared_ptr<Token> tok, int code = -1);

	//���������������� �������
	shared_ptr<Token> checkNext() { lexm->pushToOld(nextT()); return lastTok; }

	//!- ���� ������� ��������������� �����������
	//!+ �������������
	void OpenArea();
	void CloseArea();
	//! - �������������
private:
	int lvl_expr = 0;

	shared_ptr<Token> lastTok;
	shared_ptr<Token> nextT() {
		lastTok= lexm->getNext();
		return lastTok;
	}
	//! ������ �����/������
	shared_ptr<IOModule> iom;
	shared_ptr<LEXModule> lexm;

	//������ �������� ���������
	int cur_area = -1;
	vector<shared_ptr<AreaView>> areas;
};
