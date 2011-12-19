using System;
using System.Collections.Generic;
using System.Text;

namespace edc
{
	public class KeyGroup
	{
		#region Properties
		public string Name
		{
			get;
			set;
		}

		public int KeyCount
		{
			get { return m_Keys.Count; }
		}
		#endregion


		#region Private Fields
		private List<Key> m_Keys = new List<Key>();
		#endregion


		#region Constructor
		public KeyGroup(string name)
		{
			Name = name;
		}
		#endregion


		#region Methods - Public
		public void AddKey(Key key)
		{
			m_Keys.Add(key);
		}

		public Key GetKey(int index)
		{
			return m_Keys[index];
		}
		#endregion
	}
}
