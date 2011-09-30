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

		public int Bit
		{
			get;
			set;
		}

		public string Description
		{
			get;
			set;
		}

		public Spawnflag(string name, int bit)
		{
			Name = name;
			Bit = bit;
		}
	}
}
