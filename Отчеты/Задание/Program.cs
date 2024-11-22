using System;

namespace expr_eval
{
	class Program
	{
		static void Main(string[] args)
		{
			Console.WriteLine(CExpr.evaluate("1 + 2 - ( 1 + 2 ) * 3"));
		}
	}
}
