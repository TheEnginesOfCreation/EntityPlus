using System;
using System.Collections.Generic;
using System.Text;

namespace mvt
{
	class Entity
	{
		public int EntityNum;
		private Dictionary<string, string> KeyValuePairs = new Dictionary<string, string>();


		public Entity()
		{
		}

		public void AddKeyValuePair(string key, string value)
		{
			KeyValuePairs.Add(key, value);
		}

		public string GetValue(string key)
		{
			if (KeyValuePairs.ContainsKey(key))
				return KeyValuePairs[key];
			else
				return null;
		}
	}
}
