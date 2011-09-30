using System;
using System.Collections.Generic;
using System.Text;

namespace edc
{
	public class Spawnflag
	{
		public string Name
		{
			get;
			set;
		}

		public int Value
		{
			get;
			set;
		}

		public string Description
		{
			get;
			set;
		}

		public Spawnflag(string name, int value)
		{
			Name = name;
			Value = value;
		}
	}
}
