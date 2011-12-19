using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace edc
{
	class EntityDefinitionsConverter
	{

		#region Constructor
		public EntityDefinitionsConverter(string path, string outputPath)
		{
			Console.WriteLine("EntityDefinitionsConverter v1.1");
			if (!File.Exists(path))
			{
				Console.WriteLine(String.Format("File \"{0}\" does not exist", path));
				return;
			}

			if (outputPath != null && !Directory.Exists(Path.GetDirectoryName(outputPath)))
			{
				Console.WriteLine(String.Format("Output folder \"{0}\" does not exist", Path.GetDirectoryName(outputPath)));
				return;
			}

			BaseReader reader = new Reader14();
			List<Entity> entities = reader.ReadFile(path);
			Console.WriteLine("Read " + entities.Count + " entities from source file");

			BaseWriter writer = new Writer15();
			if (outputPath == null)
			{
				outputPath = Path.GetDirectoryName(path);
				outputPath += "\\" + writer.OutputFilename;
			}
			writer.WriteFile(entities, outputPath);
		}
		#endregion
	}
}
