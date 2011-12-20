using System;
using System.Collections.Generic;
using System.IO;
using System.Text;


namespace mvt
{
	class MinVersionTool
	{
		#region private members
		private List<Entity> entities = new List<Entity>();
		private LogModes logMode = LogModes.None;
		#endregion

		
		#region definitions
		public enum LogModes
		{
			None = 0,
			Debug = 1,
			Verbose = 2
		}

		/// <summary>The default minversion. Should always be 1.0</summary>
		private const Versions DEFAULT_MINVERSION = Versions.one_zero;

		/// <summary>Statuses for the map file parser</summary>
		private enum ParserStatus
		{
			Normal = 0,
			EntityTokenFound = 1,
			EntityStartTokenFound = 2,
			EntityEndTokenFound = 3,
			ReadingBrush = 4,
			ReadingPatch = 5
		}

		/// <summary>List of supported EntityPlus versions. Numeric enum values match the indexes in the VersionsStrings array</summary>
		private enum Versions
		{
			UnableToDetect = 0,
			one_zero = 1,
			one_one = 2,
		}

		/// <summary>List of strings for supported EntityPlus versions</summary>
		private string[] VersionsStrings =
		{
			"Unable to determine due to unknown entity classnames.",
			"1.0",
			"1.1"
		};

		/// <summary>A list of all the known entity classnames</summary>
		private string[] KnownEntities = 
		{ 
			//worldspawn and q3map2 entities
			"_decal", "_skybox", "worldspawn", 
			//ammo_
			"ammo_bfg", "ammo_bullets", "ammo_cells", "ammo_grenades", "ammo_lightning", "ammo_rockets", "ammo_shells", "ammo_slugs", 
			//func_
			"func_bobbing", "func_breakable", "func_button", "func_door", "func_door_rotating", "func_group", "func_pendulum", "func_plat", 
			"func_rotating", "func_static", "func_timer", "func_train",
			//holdable_
			"holdable_key_blue", "holdable_key_gold", "holdable_key_green", "holdable_key_iron", "holdable_key_master", "holdable_medkit", 
			"holdable_key_red", "holdable_key_silver", "holdable_teleporter", "holdable_key_yellow",
			//info_
			"info_backpack", "info_camera", "info_camp", "info_notnull", "info_null", "info_player_intermission", "info_player_start",
			"info_waypoint", "info_firstplace", "info_secondplace", "info_thirdplace", "info_player_deathmatch",
			//item_
			"item_armor_body", "item_armor_combat", "item_armor_vest", "item_armor_shard", "item_botroam", "item_enviro", "item_flight",
			"item_haste", "item_health", "item_health_large", "item_health_mega", "item_health_small", "item_invis", "item_quad",
			"item_regen",
			//light
			"light",
			//misc_
			"misc_model", "misc_portal_camera", "misc_portal_surface", "misc_teleporter_dest", 
			//path_
			"path_corner",
			//shooter_
			"shooter_bfg", "shooter_grenade", "shooter_plasma", "shooter_rocket",
			//target_
			"target_botremove", "target_botspawn", "target_cutscene", "target_debrisemitter", "target_delay", "target_earthquake", 
			"target_effect", "target_finish", "target_give", "target_gravity", "target_kill", "target_laser", "target_logic", 
			"target_mapchange", "target_modify", "target_music", "target_objective", "target_playerspeed", "target_playerstats",
			"target_position", "target_print", "target_push", "target_relay", "target_remove_powerups", "target_score", "target_script",
			"target_secret", "target_skill", "target_speaker", "target_teleporter", "target_unlink", "target_variable",
			//trigger_
			"trigger_always", "trigger_death", "trigger_frag", "trigger_lock", "trigger_hurt", "trigger_multiple", "trigger_push",
			"trigger_teleport",
			//weapon_
			"weapon_bfg", "weapon_gauntlet", "weapon_grapplinghook", "weapon_grenadelauncher", "weapon_lightning", "weapon_machinegun",
			"weapon_plasmagun", "weapon_railgun", "weapon_rocketlauncher", "weapon_shotgun", 
		};
		#endregion


		#region Constructor
		public MinVersionTool(string filename, LogModes logMode)
		{
			this.logMode = logMode;

			DateTime start = DateTime.Now;
			
			ParseMap(filename);
			Versions minversion = AnalyseEntities();
			
			DateTime end= DateTime.Now;
			TimeSpan diff = end.Subtract(start);
			string prefix = "";
			if (diff.Milliseconds < 100)
				prefix += "0";
			if (diff.Milliseconds < 10)
				prefix += "0";
			Console.WriteLine("Finished parsing \"" + filename + "\" in " + diff.Seconds + "." + prefix + diff.Milliseconds + "s");
			
			Console.WriteLine("\n================");
			Console.WriteLine("minversion = " + VersionsStrings[(int)minversion]);
			Console.WriteLine("================");
			Console.WriteLine("\n\npress any key to continue...");

			Console.ReadKey(true);
		}
		#endregion


		#region private methods
		/// <summary>Parses a complete .map file</summary>
		/// <param name="filename">Filename of the map to parse</param>
		/// <returns>The minimum version of EntityPlus that's required to run this map</returns>
		private void ParseMap(string filename)
		{
			Debug("Reading map file... ", false);
			StreamReader sr = File.OpenText(filename);

			ParserStatus parserStatus = ParserStatus.Normal;
			string line = "";
			Entity ent = null;
			while (sr.Peek() > 0)
			{
				line = sr.ReadLine();
				if (line.IndexOf("// entity") >= 0)
				{
					parserStatus = ParserStatus.EntityTokenFound;
					ent = new Entity();
					ent.EntityNum = int.Parse(line.Replace("// entity", ""));
				}
				else if (line.IndexOf("// brush") >= 0)
				{
					parserStatus = ParserStatus.ReadingBrush;
				}
				else if (line.IndexOf("patchDef2") >= 0)
				{
					parserStatus = ParserStatus.ReadingPatch;
				}
				else if (line == "{" && parserStatus == ParserStatus.EntityTokenFound)
				{
					parserStatus = ParserStatus.EntityStartTokenFound;
				}
				else if (line != "}" && parserStatus == ParserStatus.EntityStartTokenFound)
				{
					ParseKeyValue(line, ent);
				}
				else if (line == "}" && parserStatus == ParserStatus.EntityStartTokenFound)
				{
					parserStatus = ParserStatus.Normal;
					entities.Add(ent);
				}
				else if (line == "}" && parserStatus == ParserStatus.ReadingBrush)
				{
					parserStatus = ParserStatus.EntityStartTokenFound;
				}
				else if (line == "}" && parserStatus == ParserStatus.ReadingPatch)
				{
					parserStatus = ParserStatus.ReadingBrush;
				}
			}

			sr.Close();

			DateTime end = DateTime.Now;
			
			Debug("Done.");
		}

		/// <summary>
		/// Gets the most recent version of two versions. This is used to determine if an entity should push up 
		/// the map's minversion value. If either of the supplied versions is UnableToDetect, the method will
		/// return UnableToDetect as most recent version
		/// </summary>
		/// <param name="a"></param>
		/// <param name="b"></param>
		/// <returns></returns>
		private Versions GetMostRecentVersion(Versions a, Versions b)
		{
			//if either version is marked as UnableToDetect, return this version value
			if (a == Versions.UnableToDetect || b == Versions.UnableToDetect)
				return Versions.UnableToDetect;

			if ((int)a > (int)b)
				return a;
			else
				return b;
		}

		/// <summary>Parses a single key/value combination for an entity</summary>
		/// <param name="line">The line containing the key/value information</param>
		/// <param name="ent">The entity object to which the key/value pair should be added</param>
		private void ParseKeyValue(string line, Entity ent)
		{
			int startKey = line.IndexOf("\"") + 1;
			int endKey = line.IndexOf("\"", startKey);
			string key = line.Substring(startKey, endKey - startKey);

			int startValue = line.IndexOf("\"", endKey + 1) + 1;
			int endValue = line.IndexOf("\"", startValue);
			string value = line.Substring(startValue, endValue - startValue);

			ent.AddKeyValuePair(key, value);
		}

		private Versions AnalyseEntities()
		{
			Versions minversion = DEFAULT_MINVERSION;
			Versions entversion = DEFAULT_MINVERSION;

			foreach (Entity ent in entities)
			{
				Verbose(String.Format("Entity {0}: {1}", ent.EntityNum, ent.GetValue("classname")));
				entversion = CheckEntity(ent);
				minversion = GetMostRecentVersion(entversion, minversion);
			}

			return minversion;
		}

		/// <summary>Checks the version of EntityPlus that's required to support the entity in this form.</summary>
		/// <param name="ent">The entity to check.</param>
		/// <returns>The minimum EntityPlus version required to support this entity</returns>
		private Versions CheckEntity(Entity ent)
		{
			string classname = ent.GetValue("classname");
			if (!IsKnownEntity(classname))
			{
				Console.WriteLine("WARNING: Unknown classname \"" + ent.GetValue("classname") + "\"");
				return Versions.UnableToDetect;
			}

			//Checking for v1.2 requirements
			//if (IsVersion12(ent))
			//	return Versions.one_two;

			//Checking for v1.1 requirements
			if (HasVersion11Keys(ent) || HasVersion11Targets(ent))
				return Versions.one_one;

			return Versions.one_zero;
		}

		/// <summary>
		/// Checks if MinVersionTool is aware of this entity type. It could be that someone uses an older MinVersionTool that's not aware of
		/// newer entities. MinVersionTool reports any unknown classnames because such classnames prevent it from accurately detecting the
		/// minimum version required to run this map.
		/// </summary>
		/// <param name="classname">The classname to check</param>
		/// <returns>True if MinVersionTool recognizes the classname, false if not.</returns>
		private bool IsKnownEntity(string classname)
		{
			foreach (string cn in KnownEntities)
			{
				if (cn == classname)
					return true;
			}
			return false;
		}

		/// <summary>checks if potentialTarget is targeted by ent</summary>
		/// <param name="ent">The entity doing the targeting</param>
		/// <param name="potentialTarget">The entity potentially being targeted</param>
		/// <returns>true if ent targets potentialTarget, false if not</returns>
		private bool IsTarget(Entity ent, Entity potentialTarget)
		{
			string target = ent.GetValue("target");
			string target2 = ent.GetValue("target2");
			string targetname = potentialTarget.GetValue("targetname");
			string targetname2 = potentialTarget.GetValue("targetname2");

			if (!String.IsNullOrEmpty(target))
			{
				if (target == targetname || target == targetname2)
					return true;
			}

			if (!String.IsNullOrEmpty(target2))
			{
				if (target2 == targetname || target2 == targetname2)
					return true;
			}

			return false;
		}

		/// <summary>Prints a debug message (only if the -d or -v commandline switch was supplied)</summary>
		/// <param name="text">Debug text to print</param>
		private void Debug(string text)
		{
			Debug(text, true);
		}

		/// <summary>Prints a debug message (only if the -d or -v commandline switch was supplied)</summary>
		/// <param name="text">Debug text to print</param>
		/// <param name="newline">When true, WriteLine is used. When false, Write is used</param>
		private void Debug(string text, bool newline)
		{
			if (logMode == LogModes.Debug || logMode == LogModes.Verbose)
			{
				if (newline)
					Console.WriteLine(text);
				else
					Console.Write(text);
			}
		}

		/// <summary>Prints a verbose message (only if the -v commandline switch was supplied)</summary>
		/// <param name="text">Verbose text to print</param>
		private void Verbose(string text)
		{
			Verbose(text, true);
		}

		/// <summary>Prints a verbose message (only if the -v commandline switch was supplied)</summary>
		/// <param name="text">Verbose text to print</param>
		/// <param name="newline">When true, WriteLine is used. When false, Write is used</param>
		private void Verbose(string text, bool newline)
		{
			if (logMode == LogModes.Verbose)
			{
				if (newline)
					Console.WriteLine(text);
				else
					Console.Write(text);
			}
		}
		#endregion


		#region Version checking methods
		private bool HasVersion11Keys(Entity ent)
		{
			bool result = false;
			string versionString = VersionsStrings[(int)Versions.one_one];
			string classname = ent.GetValue("classname");
			switch (classname)
			{
				case "target_relay":
					if ((ent.Spawnflags & 8) != 0)
					{
						Debug(" > use of \"ONCE\" spawnflag requires " + versionString);
						result = true;
					}
					break;

				case "func_breakable":
					if (!String.IsNullOrEmpty(ent.GetValue("dmg")) && ent.GetValue("dmg") != "0")
					{
						Debug(" > use of \"dmg\" key requires " + versionString);
						result = true;
					}
					if (!String.IsNullOrEmpty(ent.GetValue("radius")))
					{
						Debug(" > use of \"radius\" key requires " + versionString);
						result = true;
					}
					if (!String.IsNullOrEmpty(ent.GetValue("targetname")))
					{
						Debug(" > use of \"targetname\" key requires " + versionString);
						result = true;
					}
					if (!String.IsNullOrEmpty(ent.GetValue("targetname2")))
					{
						Debug(" > use of \"targetname2\" key requires " + versionString);
						result = true;
					}
					if (!String.IsNullOrEmpty(ent.GetValue("breaksound")))
					{
						Debug(" > use of \"breaksound\" key requires " + versionString);
						result = true;
					}
					break;

				case "info_camera":
					if (!String.IsNullOrEmpty(ent.GetValue("fov")) && ent.GetValue("fov") != "90")
					{
						Debug(" > use of \"fov\" key requires " + versionString);
						result = true;
					}
					break;

				case "trigger_lock":
					if (!String.IsNullOrEmpty(ent.GetValue("lockedsound")))
					{
						Debug(" > use of \"lockedsound\" key requires " + versionString);
						result = true;
					}
					if (!String.IsNullOrEmpty(ent.GetValue("unlockedsound")))
					{
						Debug(" > use of \"unlockedsound\" key requires " + versionString);
						result = true;
					}
					break;
				
				case "target_botspawn":
					if ((ent.Spawnflags & 1) != 0)
					{
						Debug(" > use of \"WP_GAUNTLET\" spawnflag requires " + versionString);
						result = true;
					}
					break;

				case "target_botremove":
					Debug(" > use of \"target_botremove\" entity requires " + versionString);
					result = true;
					break;

				case "target_music":
					Debug(" > use of \"target_music\" entity requires " + versionString);
					result = true;
					break;

				case "func_door":
				case "func_door_rotating":
					if (!String.IsNullOrEmpty(ent.GetValue("nohumans")) && ent.GetValue("nohumans") != "0")
					{
						Debug(" > use of \"nohumans\" requires " + versionString);
						result = true;
					}
					if (!String.IsNullOrEmpty(ent.GetValue("nobots")) && ent.GetValue("nobots") != "0")
					{
						Debug(" > use of \"nobots\" requires " + versionString);
						result = true;
					}
					break;

				case "func_train":
					if (!String.IsNullOrEmpty(ent.GetValue("startsound")))
					{
						Debug(" > use of \"startsound\" requires " + versionString);
						result = true;
					}
					if (!String.IsNullOrEmpty(ent.GetValue("endsound")))
					{
						Debug(" > use of \"endsound\" requires " + versionString);
						result = true;
					}
					break;

				case "shooter_rocket":
				case "shooter_plasma":
				case "shooter_bfg":
				case "shooter_grenade":
					if ((ent.Spawnflags & 2) != 0)
					{
						Debug(" > use of \"NO_BOTS\" spawnflag requires " + versionString);
						result = true;
					}
					if ((ent.Spawnflags & 4) != 0)
					{
						Debug(" > use of \"NO_HUMANS\" spawnflag requires " + versionString);
						result = true;
					}
					break;

				case "target_effect":
					if ((ent.Spawnflags & 64) != 0)
					{
						Debug(" > use of \"FADE\" spawnflag requires " + versionString);
						result = true;
					}
					break;

				case "worldspawn":
					if (!String.IsNullOrEmpty(ent.GetValue("objectivesoverlay")) && ent.GetValue("objectivesoverlay") != "menu/objectives/overlay.tga")
					{
						Debug(" > use of \"objectivesoverlay\" key requires " + versionString);
						result = true;
					}

					if (!String.IsNullOrEmpty(ent.GetValue("enabledust")) && ent.GetValue("enabledust") != "0")
					{
						Debug(" > use of \"enabledust\" key requires " + versionString);
						result = true;
					}

					if (!String.IsNullOrEmpty(ent.GetValue("enablebreath")) && ent.GetValue("enablebreath") != "0")
					{
						Debug(" > use of \"enablebreath\" key requires " + versionString);
						result = true;
					}
					break;
			}

			if (
				classname.IndexOf("item_") == 0 ||
				classname.IndexOf("ammo_") == 0 ||
				classname.IndexOf("weapon_") == 0 ||
				classname.IndexOf("holdable_") == 0
			)
			{
				if ((ent.Spawnflags & 2) != 0)
				{
					Debug(" > use of \"SILENT\" spawnflag requires " + versionString);
					result = true;
				}
			}

			return result;
		}

		private bool HasVersion11Targets(Entity ent)
		{
			string versionString = VersionsStrings[(int)Versions.one_one];
			string target = ent.GetValue("target");
			string target2 = ent.GetValue("target2");
			string classname = ent.GetValue("classname");

			if (String.IsNullOrEmpty(target) && String.IsNullOrEmpty(target2))
				return false;

			if (classname != "target_unlink")
				return false;

			bool result = false;
			foreach (Entity t in entities)
			{
				if (!IsTarget(ent, t))
					continue;

				if (classname == "target_unlink" && t.GetValue("classname") == "func_bobbing")
				{
					Debug(" > targeting \"func_bobbing\" requires " + versionString);
					result = true;
				}
			}
			
			return result;
		}
		#endregion
	}
}
