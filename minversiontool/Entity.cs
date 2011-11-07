using System;
using System.Collections.Generic;
using System.Text;

namespace mvt
{
	class Entity
	{
		#region Private fields
		private Dictionary<string, string> KeyValuePairs = new Dictionary<string, string>();
		#endregion

		
		#region Properties
		public int EntityNum
		{
			get;
			set;
		}

		public int Spawnflags
		{
			get
			{
				string sf = GetValue("spawnflags");
				if (String.IsNullOrEmpty(sf))
					return 0;
				else
				{
					try
					{
						int sfi = int.Parse(sf);
						return sfi;
					}
					catch (FormatException)
					{
						Console.WriteLine("ERROR: spawnflags for this entity is set to \"" + sf + "\", which is not a valid numeric value");
						return 0;
					}
				}
			}
		}
		#endregion


		public Entity()
		{
		}

		public void AddKeyValuePair(string key, string value)
		{
			key = key.ToLower();
			if (KeyValuePairs.ContainsKey(key))
			{
				Console.WriteLine(String.Format("Error: entity {0} contains multiple entries for \"{1}\" key", EntityNum, key));
				return;
			}
			KeyValuePairs.Add(key, value);
		}

		public string GetValue(string key)
		{
			key = key.ToLower();
			if (KeyValuePairs.ContainsKey(key))
				return KeyValuePairs[key];
			else
				return null;
		}
	}
}
