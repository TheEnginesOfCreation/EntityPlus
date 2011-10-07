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

			string outputPath = null;
			if (args.Length > 1)
				outputPath = args[1];
			EntityDefinitionsConverter prog = new EntityDefinitionsConverter(args[0], outputPath);
			Console.ReadKey(true);
		}
	}
}
