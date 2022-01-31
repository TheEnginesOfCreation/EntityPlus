﻿using System;
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
			one_one_two = 3,
			one_one_four = 4,
            one_one_six = 5,
            one_one_seven = 6,
            one_one_eight = 7,
			one_one_nine = 8,
			one_one_ten = 9
		}

		/// <summary>List of strings for supported EntityPlus versions</summary>
		private string[] VersionsStrings =
		{
			"Unable to determine due to unknown entity classnames.",
			"1.0",
			"1.1",
			"1.1.2",
			"1.1.4",
            "1.1.6",
            "1.1.7",
            "1.1.8",
			"1.1.9",
			"1.1.10"
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
			"target_position", "target_print", "target_push", "target_relay", "target_remove_powerups", "target_score",
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
			
			Console.WriteLine("\n==================");
			Console.WriteLine("minversion = " + VersionsStrings[(int)minversion]);
			Console.WriteLine("==================");
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

			//Checking for v1.1.10 requirements
			if (HasVersion1110Keys(ent))
				return Versions.one_one_ten;

			//Checking for v1.1.9 requirements
			if (HasVersion119Keys(ent))
				return Versions.one_one_nine;

            //Checking for v1.1.8 requirements
            if (HasVersion118Keys(ent))
                return Versions.one_one_eight;

            //Checking for v1.1.7 requirements
            if (HasVersion117Keys(ent))
                return Versions.one_one_seven;

            //Checking for v1.1.6 requirements
            if (HasVersion116Keys(ent))
                return Versions.one_one_six;

			//Checking for v1.1.4 requirements
			if (HasVersion114Keys(ent))
				return Versions.one_one_four;

			//Checking for v1.1.2 requirements
			if (HasVersion112Keys(ent))
				return Versions.one_one_two;

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
		private bool HasVersion1110Keys(Entity ent)
		{
			switch (ent.Classname)
			{
				case "target_botspawn":
					if (ent.GetValue("loottarget") != null) {
						Debug(" > use of \"loottarget\" key requires " + VersionsStrings[(int)Versions.one_one_ten]);
						return true;
					}
					break;
			}
			return false;
		}

		private bool HasVersion119Keys(Entity ent)
		{
			switch (ent.Classname)
			{
				case "target_botspawn":
					if (ent.GetIntValue("spawnflags") != null && ((ent.GetIntValue("spawnflags").Value & 16384) > 0)) {
						Debug(" > use of \"SPAWN_EFFECT\" spawnflag requires " + VersionsStrings[(int)Versions.one_one_nine]);
						return true;
					}
					break;

				case "func_door":
					if (ent.GetIntValue("health") != null && ent.GetIntValue("health").Value < 0)
					{
						Debug(" > use of a \"health\" value less than 0 requires " + VersionsStrings[(int)Versions.one_one_nine]);
						return true;
					}
					break;
				case "shooter_rocket":
					if (ent.GetIntValue("speed") != null && ent.GetIntValue("speed").Value != 900)
					{
						Debug(" > use of a \"speed\" value other than 900 requires " + VersionsStrings[(int)Versions.one_one_nine]);
						return true;
					}
					break;
				case "shooter_grenade":
					if (ent.GetIntValue("speed") != null && ent.GetIntValue("speed").Value != 700)
					{
						Debug(" > use of a \"speed\" value other than 700 requires " + VersionsStrings[(int)Versions.one_one_nine]);
						return true;
					}
					break;
				case "shooter_plasma":
				case "shooter_bfg":
					if (ent.GetIntValue("speed") != null && ent.GetIntValue("speed").Value != 2000)
					{
						Debug(" > use of a \"speed\" value other than 2000 requires " + VersionsStrings[(int)Versions.one_one_nine]);
						return true;
					}
					break;
				case "target_effect":
					if (ent.GetIntValue("spawnflags") != null && ((ent.GetIntValue("spawnflags").Value & 128) > 0)) {
						Debug(" > use of \"SMOKEPUFF\" spawnflag requires " + VersionsStrings[(int)Versions.one_one_nine]);
						return true;
					}
					break;
				case "target_cutscene":
					if (ent.GetIntValue("spawnflags") != null && ((ent.GetIntValue("spawnflags").Value & 2) > 0))
					{
						Debug(" > use of \"START_AT_PLAYER\" spawnflag requires " + VersionsStrings[(int)Versions.one_one_nine]);
						return true;
					}
					break;
				case "target_push":
					if (ent.GetIntValue("spawnflags") != null && ((ent.GetIntValue("spawnflags").Value & 2) > 0))
					{
						Debug(" > use of \"JUMP\" spawnflag requires " + VersionsStrings[(int)Versions.one_one_nine]);
						return true;
					}
					break;
			}
			return false;
		}

		private bool HasVersion118Keys(Entity ent)
        {
            switch (ent.Classname)
            {
                case "target_laser":
                    Debug(" > use of \"target_laser\" requires " + VersionsStrings[(int)Versions.one_one_eight]);
                    return true;

                case "trigger_teleport":
                    if (ent.GetIntValue("spawnflags") != null && ((ent.GetIntValue("spawnflags").Value & 1) > 0)) {
                        Debug(" > use of \"PORTAL\" spawnflag requires " + VersionsStrings[(int)Versions.one_one_eight]);
                        return true;
                    }
                    break;

                case "trigger_lock":
                    if (ent.GetIntValue("spawnflags") != null && ((ent.GetIntValue("spawnflags").Value & 1024) > 0))
                    {
                        Debug(" > use of \"KEEP_KEYS\" spawnflag requires " + VersionsStrings[(int)Versions.one_one_eight]);
                        return true;
                    }
                    break;

                case "target_modify":
                    if (ent.GetValue("key") == "wait")
                    {
                        Debug(" > use of \"wait\" as key requires " + VersionsStrings[(int)Versions.one_one_eight]);
                        return true;
                    }
                    break;
            }
            return false;
        }

        private bool HasVersion117Keys(Entity ent)
        {
            bool result = false;
            switch (ent.Classname)
            {
                case "func_train":
                    string val = ent.GetValue("health");
                    int health;
                    if (int.TryParse(val, out health))
                    {
                        if (health > 0)
                        {
                            Debug(" > use of \"health\" key requires " + VersionsStrings[(int)Versions.one_one_seven]);
                            result = true;
                        }
                    }
                    break;

                case "func_rotating":
                    string sfVal = ent.GetValue("spawnflags");
                    int spawnflags;
                    if (int.TryParse(sfVal, out spawnflags))
                    {
                        if ((spawnflags & 32) > 0)
                        {
                            Debug(" > use of \"TOGGLABLE\" spawnflag requires " + VersionsStrings[(int)Versions.one_one_seven]);
                            result = true;
                        }
                        if ((spawnflags & 64) > 0)
                        {
                            Debug(" > use of \"START_OFF\" spawnflag requires " + VersionsStrings[(int)Versions.one_one_seven]);
                            result = true;
                        }
                    }
                    break;
            }
            return result;
        }

        private bool HasVersion116Keys(Entity ent)
        {
            switch (ent.Classname)
            {
                case "trigger_push":
                    string val = ent.GetValue("spawnflags");
                    int spawnflags = 0;
                    if (!String.IsNullOrEmpty(val))
                        int.TryParse(val, out spawnflags);

                    if ((spawnflags & 1) > 0)
                    {
                        Debug(" > use of \"SILENT\" spawnflag requires " + VersionsStrings[(int)Versions.one_one_six]);
                        return true;
                    }
                    break;
            }

            return false;
        }

		private bool HasVersion114Keys(Entity ent)
		{
			bool result = false;
			string versionString = VersionsStrings[(int)Versions.one_one_four];

			string val = ent.GetValue("spawnflags");
			int spawnflags = 0;
			if (!String.IsNullOrEmpty(val))
				int.TryParse(val, out spawnflags);


			if (ent.GetValue("notep") == "1")
			{
				Debug(" > use of \"notep\" key requires " + versionString);
				result = true;
			}

			switch (ent.Classname)
			{
				case "target_modify":
					string value = ent.GetValue("key");
					if (!String.IsNullOrEmpty(value)) { 
						if (value == "damage") {
							Debug(" > use of the value \"damage\" for the \"key\" key requires " + versionString);
							result = true;
						}

						if (value == "dmg")
						{
							Debug(" > use of the value \"dmg\" for the \"key\" key requires " + versionString);
							result = true;
						}
					}

					if (!String.IsNullOrEmpty("target2"))
					{
						Debug(" > use of \"target2\" key requires " + versionString);
						result = true;
					}
					break;

				case "target_give":
					if ((spawnflags & 1) > 0)
					{
						Debug(" > use of \"GIVE_PLAYER\" spawnflag requires " + versionString);
						result = true;
					}
					break;

				case "target_botspawn":
					if ((spawnflags & 2048) > 0)
					{
						Debug(" > use of \"IGNORE_PLAYER\" spawnflag requires " + versionString);
						result = true;
					}
					if ((spawnflags & 4096) > 0)
					{
						Debug(" > use of \"PATROL_WALK\" spawnflag requires " + versionString);
						result = true;
					}
					if ((spawnflags & 8192) > 0)
					{
						Debug(" > use of \"ALWAYS_WALK\" spawnflag requires " + versionString);
						result = true;
					}
					break;
			}

			return result;
		}

		private bool HasVersion112Keys(Entity ent)
		{
			bool result = false;
			string versionString = VersionsStrings[(int)Versions.one_one_two];

			switch (ent.Classname)
			{
				case "info_waypoint":
					if (!String.IsNullOrEmpty(ent.GetValue("wait")) && ent.GetValue("wait") != "0")
					{
						Debug(" > use of \"wait\" key requires " + versionString);
						result = true;
					}
					break;
			}

			return result;
		}

		private bool HasVersion11Keys(Entity ent)
		{
			bool result = false;
			string versionString = VersionsStrings[(int)Versions.one_one];
			switch (ent.Classname)
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
				ent.Classname.IndexOf("item_") == 0 ||
				ent.Classname.IndexOf("ammo_") == 0 ||
				ent.Classname.IndexOf("weapon_") == 0 ||
				ent.Classname.IndexOf("holdable_") == 0
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
