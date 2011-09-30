using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Xml;

namespace edc
{
	class Writer15 : BaseWriter
	{
		#region Properties
		public override string OutputFilename
		{
			get
			{
				return "entities.ent";
			}
		}
		#endregion

		
		#region Members
		private List<XmlDocument> m_KeyTypes = new List<XmlDocument>();
		#endregion


		#region Methods - Public
		public override void WriteFile(List<Entity> entities, string path)
		{
			LoadKeyTypes();

			StringBuilder sb = new StringBuilder();

			sb.AppendLine("<?xml version=\"1.0\"?>");
			sb.AppendLine("<classes>");

			foreach (Entity ent in entities)
			{
				//write opening tag
				string model = "";
				if (!String.IsNullOrEmpty(ent.Model))
					model = " model=\"" + ent.Model + "\"";

				if (ent.Mins == null)
					sb.AppendLine(String.Format("\n<group name=\"{0}\" color=\"{1}\"{2}>", ent.Name, TripletToString(ent.Color), model));
				else
					sb.AppendLine(
						String.Format(
							"\n<point name=\"{0}\" color=\"{1}\" box=\"{2} {3}\"{4}>",
							ent.Name,
							TripletToString(ent.Color),
							TripletToString(ent.Mins),
							TripletToString(ent.Maxs),
							model
						)
					);


				//write keys
				if (ent.KeyGroupCount > 0)
				{
					for (int i = 0; i < ent.KeyGroupCount; i++)
					{
						KeyGroup keyGroup = ent.GetKeyGroup(i);
						sb.AppendLine("-------- " + keyGroup.Name + " --------");

						for (int n = 0; n < keyGroup.KeyCount; n++)
						{
							Key key = keyGroup.GetKey(n);
							string keyType = GetKeyType(key.Name);

							if (!String.IsNullOrEmpty(keyType))
								sb.AppendLine(String.Format("<{0} key=\"{1}\" name=\"{1}\">{2}</{0}>", keyType, key.Name, key.Description));
						}
					}
				}

				//write spawnflags
				if (ent.SpawnflagCount > 0)
				{
					sb.AppendLine("-------- SPAWNFLAGS --------");
					for (int i = 0; i < ent.SpawnflagCount; i++)
					{
						Spawnflag sf = ent.GetSpawnflag(i);
						sb.AppendLine(String.Format("<flag key=\"{0}\" name=\"{0}\" bit=\"{1}\">{2}</flag>", sf.Name, sf.Value, sf.Description));
					}
				}

				if (!String.IsNullOrEmpty(ent.Notes))
				{
					sb.AppendLine("-------- NOTES --------");
					sb.AppendLine(ent.Notes);
				}

				if (ent.Mins == null)
					sb.AppendLine("</group>");
				else
					sb.AppendLine("</point>");
			}

			Console.WriteLine("Writing output to \"" + path + "\"");
			StreamWriter sw = new StreamWriter(path);
			sw.Write(sb.ToString());
			sw.Close();
			Console.WriteLine("Done.");
		}
		#endregion


		#region Methods - Private
		private void LoadKeyTypes()
		{
			string[] filenames = Directory.GetFiles("KeyTypes", "*.xml");

			foreach (string filename in filenames)
			{
				XmlDocument xml = new XmlDocument();
				xml.Load(filename);
				Console.WriteLine("Read " + filename);
				m_KeyTypes.Add(xml);
			}
		}

		private string GetKeyType(string key)
		{
			foreach (XmlDocument xml in m_KeyTypes)
			{
				XmlNodeList nodes = xml.SelectNodes("keytypes/" + key);

				if (nodes.Count > 0)
					return nodes[0].InnerText;
			}

			Console.WriteLine("Cannot find type for key \"" + key + "\"");
			return "";
		}
		#endregion
	}
}
