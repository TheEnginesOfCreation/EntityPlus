using System;
using System.Collections.Generic;
using System.Text;

namespace edc
{
	class Program
	{
		static void Main(string[] args)
		{
			if (args.Length == 0)
			{
				Console.WriteLine("Need to specify input file");
				Console.ReadKey(true);
				return;
			}

			EntityDefinitionsConverter prog = new EntityDefinitionsConverter(args[0]);
			Console.ReadKey(true);
		}
	}
}
