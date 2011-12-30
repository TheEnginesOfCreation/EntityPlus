using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace mvt
{
	class Program
	{
		//version: first three numbers are EntityPlus version it supports, last number is incremental version of the tool itself
		private const string version = "1.1.2.0";

		static void Main(string[] args)
		{
			Console.WriteLine("=== MinVersionTool " + version + " for EntityPlus v1.1 ===");
			string filename= "";
			MinVersionTool.LogModes logMode = MinVersionTool.LogModes.None;

			for (int i = 0; i < args.Length; i++)
			{
				if (args[i] == "-d" && logMode != MinVersionTool.LogModes.Verbose)
					logMode = MinVersionTool.LogModes.Debug;
				else if (args[i] == "-v")
					logMode = MinVersionTool.LogModes.Verbose;
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

			MinVersionTool mvt = new MinVersionTool(filename, logMode);
		}
	}
}
