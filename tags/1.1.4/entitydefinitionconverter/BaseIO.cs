using System;
using System.Collections.Generic;
using System.Globalization;
using System.Text;

namespace edc
{
	public abstract class BaseIO
	{
		protected CultureInfo ci = (CultureInfo)CultureInfo.CurrentCulture.Clone();

		#region Constructor
		public BaseIO()
		{
			ci.NumberFormat.CurrencyDecimalSeparator = ".";
			ci.NumberFormat.NumberDecimalSeparator = ".";
		}
		#endregion
	}
}
