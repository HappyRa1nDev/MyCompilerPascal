using System;
using System.Collections.Generic;
using System.Text;

namespace expr_eval
{
	class CExpr
	{
		private CLexer lexer;
		private CToken curToken;
		private void getNext()
		{
			curToken = lexer.getNextToken();
		}

		private void accept(Oper op)
		{
			if (curToken == null || curToken.tokenType != ToketType.ttOper || curToken.operation != op)
			{
				throw new Exception("expected another op");
			}
			getNext();
		}

		private bool isOper(List<Oper> ops)
		{
			if (curToken == null || curToken.tokenType != ToketType.ttOper) return false;
			foreach (var op in ops)
			{
				if (curToken.operation == op) return true;
			}
			return false;
		}

		private float factor() // mnozitel
		{
			if (curToken != null && curToken.tokenType == ToketType.ttOper)
			{
				accept(Oper.oLeftBracet);
				var left = simpleExpr();
				accept(Oper.oRightBracet);
				return left;
			}
			if (curToken == null) throw new Exception("Token excpected");
			var res = curToken.value;
			getNext();
			return res;
		}

		private float term() //slagaemoe
		{
			var left = factor();
			while (isOper(new List<Oper>() { Oper.oMul, Oper.oDiv }))
			{
				var oper = curToken.operation;
				getNext();
				var right = factor();
				switch (oper)
				{
					case Oper.oMul:
						left = left * right;
						break;
					case Oper.oDiv:
						left = left / right;
						break;
					default:
						throw new Exception("bad multipl oper");
				}
			}
			return left;
		}

		private float simpleExpr()
		{
			var left = term();
			while (isOper(new List<Oper>() { Oper.oPlus, Oper.oMinus }))
			{
				var oper = curToken.operation;
				getNext();
				var right = term();
				switch (oper)
				{
					case Oper.oPlus:
						left = left + right;
						break;
					case Oper.oMinus:
						left = left - right;
						break;
					default:
						throw new Exception("bad addit oper");
				}
			}
			return left;
		}

		private CExpr(string expr)
		{
			lexer = new CLexer(expr);
			getNext();
		}

		public static float evaluate(string expr)
		{
			var exp = new CExpr(expr);
			return exp.simpleExpr();
		}
	}
}
