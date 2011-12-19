using System;
using System.Collections.Generic;
using System.Text;

namespace edc
{
	public class Key
	{
		#region Properties
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
		#endregion


		#region Constructor
		public Key(string name, string description)
		{
			Name = name;
			Description = description;
		}
		#endregion
	}
}
