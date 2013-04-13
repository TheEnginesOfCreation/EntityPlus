using System;
using System.Collections.Generic;
using System.Text;

namespace edc
{
	public abstract class BaseWriter : BaseIO
	{
		#region Abstract methods and variables
		public abstract void WriteFile(List<Entity> entities, string path);
		public abstract string OutputFilename { get; }
		#endregion


		#region Helper methods
		protected string FloatToString(float number)
		{
			string result = number.ToString(ci);

			if (result.Length > 1 && result.Substring(0, 2) == "0.")
				return result.Substring(1, result.Length - 1);
			else
				return result;
		}

		protected string TripletToString(float[] triplet)
		{
			string result = "";
			result += FloatToString(triplet[0]);
			result += " ";
			result += FloatToString(triplet[1]);
			result += " ";
			result += FloatToString(triplet[2]);
			return result;
		}

		protected string TripletToString(int[] triplet)
		{
			string result = "";
			result += triplet[0].ToString();
			result += " ";
			result += triplet[1].ToString();
			result += " ";
			result += triplet[2].ToString();
			return result;
		}
		#endregion
	}
}
