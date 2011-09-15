using System;
using System.Collections.Generic;
using System.IO;
using System.Text;


namespace mvt
{
	class MinVersionTool
	{
		#region private members
		private List<Entity> entities = new List<Entity>();
		private bool debug = false;
		#endregion

		
		#region enums
		private enum ParserStatus
		{
			Normal = 0,
			EntityTokenFound = 1,
			EntityStartTokenFound = 2,
			EntityEndTokenFound = 3,
			ReadingBrush = 4,
			ReadingPatch = 5
		}
		#endregion


		#region Constructor
		public MinVersionTool(string filename, bool debug)
		{
			this.debug = debug;
			ParseMap(filename);

			Console.WriteLine("===============");
			Console.WriteLine("Finished parsing \"" + filename + "\"");
			Console.WriteLine("\nminversion = 1.0");
			Console.WriteLine("===============");
			Console.ReadKey(true);
		}
		#endregion


		#region private methods
		private void ParseMap(string filename)
		{
			StreamReader sr = File.OpenText(filename);

			ParserStatus parserStatus = ParserStatus.Normal;
			string line = "";
			Entity ent = null;
			while (sr.Peek() > 0)
			{
				line = sr.ReadLine();
				if (line.IndexOf("// entity") >= 0)
				{
					parserStatus = ParserStatus.EntityTokenFound;
					ent = new Entity();
					ent.EntityNum = int.Parse(line.Replace("// entity", ""));
				}
				else if (line.IndexOf("// brush") >= 0)
				{
					parserStatus = ParserStatus.ReadingBrush;
				}
				else if (line.IndexOf("patchDef2") >= 0)
				{
					parserStatus = ParserStatus.ReadingPatch;
				}
				else if (line == "{" && parserStatus == ParserStatus.EntityTokenFound)
				{
					parserStatus = ParserStatus.EntityStartTokenFound;
				}
				else if (line != "}" && parserStatus == ParserStatus.EntityStartTokenFound)
				{
					ParseKeyValue(line, ent);
				}
				else if (line == "}" && parserStatus == ParserStatus.EntityStartTokenFound)
				{
					parserStatus = ParserStatus.Normal;
					Debug(String.Format("Entity {0}: {1}", ent.EntityNum, ent.GetValue("classname")));
					entities.Add(ent);
				}
				else if (line == "}" && parserStatus == ParserStatus.ReadingBrush)
				{
					parserStatus = ParserStatus.EntityStartTokenFound;
				}
				else if (line == "}" && parserStatus == ParserStatus.ReadingPatch)
				{
					parserStatus = ParserStatus.ReadingBrush;
				}
			}

			sr.Close();
		}

		private void ParseKeyValue(string line, Entity ent)
		{
			int startKey = line.IndexOf("\"") + 1;
			int endKey = line.IndexOf("\"", startKey);
			string key = line.Substring(startKey, endKey - startKey);

			int startValue = line.IndexOf("\"", endKey + 1) + 1;
			int endValue = line.IndexOf("\"", startValue);
			string value = line.Substring(startValue, endValue - startValue);

			ent.AddKeyValuePair(key, value);
		}

		private void Debug(string text)
		{
			if (debug)
			{
				Console.WriteLine(text);
			}
		}
		#endregion
	}
}
