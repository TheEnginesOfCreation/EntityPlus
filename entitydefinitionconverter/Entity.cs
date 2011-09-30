using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Text;

namespace edc
{
	public class Entity
	{
		private List<string> m_Keys = new List<string>();
		private List<string> m_KeyDescriptions = new List<string>();
		private List<Spawnflag> m_Spawnflags = new List<Spawnflag>();

		public string Name
		{
			get;
			set;
		}

		public string Description
		{
			get;
			set;
		}

		public string Notes
		{
			get;
			set;
		}

		public string Model
		{
			get;
			set;
		}

		public float[] Color		//3 float values
		{
			get;
			set;
		}

		public int[] Mins			//3 int values
		{
			get;
			set;
		}

		public int[] Maxs			//3 int values
		{
			get;
			set;
		}

		public int KeyCount
		{
			get { return m_Keys.Count; }
		}

		public int SpawnflagCount
		{
			get { return m_Spawnflags.Count; }
		}

		#region Constructor
		public Entity(string name)
		{
			Name = name;
			Color = new float[3];
			Mins = new int[3];
			Maxs = new int[3];
		}
		#endregion


		#region Methods - Public
		public void AddKey(string key, string description)
		{
			m_Keys.Add(key);
			m_KeyDescriptions.Add(description);
		}

		public string GetKeyName(int index)
		{
			return m_Keys[index];	
		}

		public string GetKeyDescription(int index)
		{
			return m_KeyDescriptions[index];
		}

		public void AddSpawnflag(string name, int value)
		{
			m_Spawnflags.Add(new Spawnflag(name, value));
		}

		public Spawnflag GetSpawnflag(int index)
		{
			return m_Spawnflags[index];
		}

		public void SetSpawnflagDescription(string name, string description)
		{
			foreach (Spawnflag sf in m_Spawnflags)
			{
				if (sf.Name == name)
				{
					sf.Description = description;
				}
			}
		}
		#endregion
	}
}
