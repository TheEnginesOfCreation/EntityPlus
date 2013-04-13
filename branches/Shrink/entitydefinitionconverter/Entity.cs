using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Text;

namespace edc
{
	public class Entity
	{
		private List<KeyGroup> m_KeyGroups = new List<KeyGroup>();
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

		public int KeyGroupCount
		{
			get { return m_KeyGroups.Count; }
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
		public void AddKeyGroup(KeyGroup keyGroup)
		{
			m_KeyGroups.Add(keyGroup);
		}

		public KeyGroup GetKeyGroup(int index)
		{
			return m_KeyGroups[index];
		}

		public Key GetKey(int groupIndex, int index)
		{
			return m_KeyGroups[groupIndex].GetKey(index);
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
