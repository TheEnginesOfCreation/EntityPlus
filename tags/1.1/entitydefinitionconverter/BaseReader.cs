using System;
using System.Collections.Generic;
using System.Text;


namespace edc
{
	public abstract class BaseReader : BaseIO
	{
		#region Abstract methods
		public abstract List<Entity> ReadFile(string path);
		#endregion
	}
}
