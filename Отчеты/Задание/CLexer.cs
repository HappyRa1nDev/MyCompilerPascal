using System;
using System.Collections.Generic;
using System.Text;

namespace expr_eval
{
	enum Oper
	{
		oLeftBracet,
		oRightBracet,
		oPlus,
		oMinus,
		oMul,
		oDiv,
	}

	enum ToketType
	{
		ttValue,
		ttOper
	}

	class CToken
	{
		public ToketType tokenType { get; private set; }
		
		public Oper operation { get; private set; }

		public float value { get; private set; }

		public CToken(float val)
		{
			value = val;
			tokenType = ToketType.ttValue;
		}

		public CToken(Oper op)
		{
			operation = op;
			tokenType = ToketType.ttOper;
		}
	}

	class CLexer
	{
		public string Expr { get; private set; }

		private int pos;
		private string[] parsed;
		public CLexer(string expr)
		{
			Expr = expr;
			parsed = expr.Split(' ');
			pos = 0;
		}

		public CToken getNextToken()
		{
			if (pos >= parsed.Length) return null;
			var curS = parsed[pos++];
			if (char.IsDigit(curS[0])) return new CToken(float.Parse(curS));
			switch (curS[0])
			{
				case '(':
					return new CToken(Oper.oLeftBracet);
				case ')':
					return new CToken(Oper.oRightBracet);
				case '+':
					return new CToken(Oper.oPlus);
				case '-':
					return new CToken(Oper.oMinus);
				case '*':
					return new CToken(Oper.oMul);
				case '/':
					return new CToken(Oper.oDiv);
				default:
					throw new Exception("bad symbol");
			}
		}
	}
}
