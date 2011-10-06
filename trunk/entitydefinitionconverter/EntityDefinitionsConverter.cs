using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace edc
{
	class EntityDefinitionsConverter
	{

		#region Constructor
		public EntityDefinitionsConverter(string path)
		{
			Console.WriteLine("EntityDefinitionsConverter v1.0");
			if (!File.Exists(path))
			{
				Console.WriteLine(String.Format("File \"{0}\" does not exist", path));
				return;
			}

			BaseReader reader = new Reader14();
			List<Entity> entities = reader.ReadFile(path);
			Console.WriteLine("Read " + entities.Count + " entities from source file");

			BaseWriter writer = new Writer15();
			string outputPath = Path.GetDirectoryName(path);
			outputPath += "\\" + writer.OutputFilename;
			writer.WriteFile(entities, outputPath);
		}
		#endregion
	}
}
