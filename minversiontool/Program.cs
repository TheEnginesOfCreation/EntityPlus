using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace mvt
{
	class Program
	{
		static void Main(string[] args)
		{
			string filename= "";
			bool debug = false;

			for (int i = 0; i < args.Length; i++)
			{
				if (args[i] == "-d")
					debug = true;
				else if (filename == "")
					filename = args[i];
			}

			if (filename == "")
			{
				Console.WriteLine("You must supply the path to a .map file");
				Console.ReadKey();
				return;
			}

			if (!File.Exists(filename))
			{
				Console.WriteLine("The specified map file could not be found");
				Console.ReadKey();
				return;
			}

			MinVersionTool mvt = new MinVersionTool(filename, debug);
		}
	}
}
