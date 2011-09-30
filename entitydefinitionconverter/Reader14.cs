using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Text;

namespace edc
{
	class Reader14 : BaseReader
	{
		#region Enums and constants
		private enum ParserStatus
		{
			Reading = 0,				//reading garbage
			DefinitionFound = 1,		//parser encountered /*QUAKED substring
			ReadingKeys = 2,			//parser is reading entity's keys
			ReadingSpawnflags = 3,		//parser is reading entity's spawnflags
			ReadingNotes = 4,			//parser is reading entity's notes
		}

		
		#endregion


		#region Methods - Public
		public override List<Entity> ReadFile(string path)
		{
			List<Entity> entities = new List<Entity>();

			//open file for reading
			StreamReader sr = File.OpenText(path);

			//initialize parser status
			ParserStatus ps = ParserStatus.Reading;

			//read line-by-line
			string line;
			Entity ent = null;
			while (sr.Peek() > 0)
			{
				line = sr.ReadLine();

				if (line.Length >= 2 && line.Substring(0, 2) == "//")
					continue;

				if (line == "*/")
					ps = ParserStatus.Reading;

				if (line.IndexOf("- KEYS -") != -1)
				{
					ps = ParserStatus.ReadingKeys;
					continue;
				}

				if (line.IndexOf("- SPAWNFLAGS -") != -1)
				{
					ps = ParserStatus.ReadingSpawnflags;
					continue;
				}

				if (line.IndexOf("- NOTES -") != -1)
				{
					ps = ParserStatus.ReadingNotes;
					continue;
				}

				if (line.IndexOf("model=\"") != -1 && ent != null)
				{
					ent.Model = line.Replace("model=\"", "").Replace("\"", "").Replace("*/", "");
					if (IsDefinitionEnd(line))
						ps = ParserStatus.Reading;
				}
					

				if (line.IndexOf("/*QUAKED") != -1)
				{
					int idx = 0;
					ps = ParserStatus.DefinitionFound;
					string[] parts = line.Split(' ');

					//create new entity definition
					ent = new Entity(parts[++idx]);

					//get color
					ent.Color[0] = float.Parse(parts[++idx].Replace("(", ""), ci);
					ent.Color[1] = float.Parse(parts[++idx], ci);
					ent.Color[2] = float.Parse(parts[++idx].Replace(")", ""), ci);

					//get dimensions
					if (parts[++idx] == "?")
					{
						//dealing with a brush
						ent.Mins = null;
						ent.Maxs = null;
					}
					else
					{
						ent.Mins[0] = int.Parse(parts[idx].Replace("(", ""));
						ent.Mins[1] = int.Parse(parts[++idx]);
						ent.Mins[2] = int.Parse(parts[++idx].Replace(")", ""));

						ent.Maxs[0] = int.Parse(parts[++idx].Replace("(", ""));
						ent.Maxs[1] = int.Parse(parts[++idx]);
						ent.Maxs[2] = int.Parse(parts[++idx].Replace(")", ""));
					}

					//get spawnflags
					idx++;
					int spawnflagValue = 1;
					while (idx < parts.Length)
					{
						if (!String.IsNullOrEmpty(parts[idx])) {
							if (!(parts[idx] == "-")) 
								ent.AddSpawnflag(parts[idx], spawnflagValue);
							spawnflagValue *= 2;
						}
						idx++;
					}

					entities.Add(ent);
					continue;
				}

				if (ps == ParserStatus.DefinitionFound)
				{
					ps = ParserStatus.Reading;
					ent.Description = line.Replace("*/", "");
					continue;
				}
				

				if (ps == ParserStatus.ReadingKeys) {
					
					string[] parts = line.Split(':');
					if (parts.Length < 2)
						continue;

					string key = parts[0];
					string descr = parts[1];
					if (parts.Length > 2)
					{
						for (int i = 2; i < parts.Length; i++)
							descr += parts[i];
					}

					//there are keys like this: "_cs OR _castshadows". Split them into two keys.
					if (key.Contains(" OR "))
					{
						int orIndex = key.IndexOf("OR");
						string key2 = key.Substring(orIndex + 2);
						ent.AddKey(key2.Trim().Replace("\"", ""), descr.Trim().Replace("*/", ""));
						key = key.Substring(0, orIndex);
					}

					ent.AddKey(key.Trim().Replace("\"", ""), descr.Trim().Replace("*/", ""));

					if (IsDefinitionEnd(line))
						ps = ParserStatus.Reading;
					continue;
				}
				
				
				if (ps == ParserStatus.ReadingSpawnflags)
				{
					string[] parts = line.Split(':');
					if (parts.Length < 2)
						continue;

					string name = parts[0];
					string descr = parts[1];
					if (parts.Length > 2)
					{
						for (int i = 2; i < parts.Length; i++)
							descr += parts[i];
					}

					ent.SetSpawnflagDescription(name.Trim(), descr.Trim().Replace("*/", ""));
					if (IsDefinitionEnd(line))
						ps = ParserStatus.Reading;
					continue;
				}

				if (ps == ParserStatus.ReadingNotes)
				{
					if (ent.Notes == null)
						ent.Notes = "";
					ent.Notes += line.Replace("*/", "");
					if (IsDefinitionEnd(line))
						ps = ParserStatus.Reading;
				}
			}

			sr.Close();
			return entities;
		}
		#endregion


		#region Methods - Private
		private bool IsDefinitionEnd(string line)
		{
			return (line.IndexOf("*/") != -1);
		}
		#endregion
	}
}
