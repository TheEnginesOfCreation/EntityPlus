ENTITYPLUS 
version 0.4
-----------

EntityPlus is a Quake III Arena mod that is aimed at expanding the toolset for Quake III Arena map makers.
The goal is to build an expansive library of new entities that map makers can use in their maps to create
whole new experiences.

Because a mod is a rather strict prerequisite for any custom map, and Q3A's age and waning popularity don't
exactly help in that aspect either, the aim will be at a completely experimental set of features that will hopefully
expand the possibilities of single player experiences in Q3A. While Q3A will never be a full fledge single player 
campaign-based game, EntityPlus will give map makers a broader palette of features to work with, allowing the
most innovative of mappers to create interesting new experiences that haven't been part of Quake III Arena yet.

The mod is completely open source and anyone is allowed to make their own additions to the codebase. I am
even accepting feature requests which I will try to implement in the codebase in a timely fashion. This will, for 
the first time, allow mappers to think way beyond the boundaries of Q3A. Within this mod, a challenge for mappers
is hidden. Try to think of something that sheds the shackles of Q3A's basic multiplayer deathmatch gameplay
and think of new interesting things to do within this new limitless world.


SINGLE PLAYER
-------------
Through the course of developing this mod it quickly became apparent that the Quake 3 mapping community is really
excited about the possibility of making Quake 3 maps that are meant to be single player experiences. The term
"single player" here is used to describe an experience more akin to the SP games of Quake or Quake 2 than Quake 3's
own single player bot matches.
To facilitate this, EntityPlus implements a lot of features that are strictly aimed at single player gameplay. These
features and changes are only applied when running the game in single player mode (g_gametype 2). To force the game
into single player mode, a map must be loaded with the "spmap" command rather than the "map" command.


INSTALLATION
------------
Simply extract the files within the downloaded ZIP package to your Quake 3 Arena folder, retaining the folder
structure inside the package. Execute the entityplus.bat file to start EntityPlus or use the game's MODS menu
to load the mod.

The entityplus package contains an entities.def file which is an expanded version of the entities.def file you'll
find in your baseq3\scripts folder. This new .def file contains entity definitions for the new entities in EntityPlus.
You can either overwrite the existing entities.def or configure GtkRadiant 1.4 or ZeroRadiant 1.6 to use the 
entityplus folder as working folder. There is no entity definition file for use with GtkRadiant 1.5 yet.



FEATURES
--------
EntityPlus adds a few new entities that can be used in maps. If you use any of the EntityPlus features in your map, 
it can only be correctly played using the EntityPlus mod. For a list of features added to EntityPlus, go to the
mod's Wiki:

https://code.google.com/p/entityplus/wiki/EntityPlus



EXAMPLE MAP
-----------
The release package of EntityPlus contains an example map which demonstrates a number of the features found in EntityPlus. 
This map can be loaded by entering the following commands in the console:

	\fraglimit 0
	\timelimit 0
    \spmap entityplus 

The map can also be started by double clicking the entityplus.bat file that comes with the release package. This batch file 
is located next to the quake.exe executable.


KEY EXAMPLE
-----------
A seperate map to demonstrate the use of the key and lock entities is included with the name "keytest".


CREDITS
-------
Project lead and programming	: Eraesr

Additional programming and
programming support				: ^misantropia^

Additional programming			: Kaz

Keycard models and skins		: Obsidian

Skeleton key models and skins	: Hipshot

Debris models					: DaEngineer


CONTACT
-------
Contact me at eraesr@gmail.com or visit The Engines of Creation at http://www.theenginesofcreation.com.
To follow the project or get the source code, go to https://code.google.com/p/entityplus.
If you want to follow discussions surrounding the mod or leave your own input, visit the 
discussion thread in the Quake3World Level Editing & Modelling forums at http://quake3world.com/forum/viewtopic.php?f=10&t=45510.


VERSION HISTORY
---------------
v0.4 (25 apr 2011)
	- [Added] Dying in single player causes the player to drop a backpack which can be picked up to restore the player's weapons/ammo/holdables.
	- [Added] Ladderclip texture to create ladders.
	- [Added] DARK_DEBRIS key for target_debrisemitter to toggle between lighter and darker bits of debris.
	- [Added] Red, Green, Blue and Yellow keycards.
	- [Added] Master, Gold, Silver and Iron skeleton keys.
	- [Added] nobots and nohumans keys to trigger_multiple.
	- [Added] KEY_RED, KEY_GREEN, KEY_BLUE, KEY_YELLOW, KEY_MASTER, KEY_GOLD, KEY_SILVER and KEY_IRON spawnflags for trigger_lock.
	- [Added] Targeting an info_player_deathmatch with a trigger will enable or disable the spawnpoint.
	- [Added] DISABLED spawnflag to info_player_deathmatch.
	- [Added] SCRIPT spawnflag to target_mapchange.
	- [Fixed] Game crashes when joining the spectators.
	- [Fixed] target_mapchange incorrectly reads specified mapname.
	- [Fixed] IMMEDIATELY spawnflag on target_disable doesn't work in some cases.
	- [Fixed] The RANDOM spawnflag on target_logic causes an entity to always be triggered.
	- [Changed] target_botspawn now spawns bots at it's own location and allows customization of the bot to spawn.
	- [Changed] target_logic can now be targetted by up to 10 entities instead of just 2.
	- [Changed] target_debrisemitter spews out actual debris models.
	- [Changed] Smoke trails for target_debrisemitter are slightly less opaque now.
	- [Changed] target_mapchange now only retains player stats when game is in single player mode.
	- [Changed] Holdable item is also persisted across map changes caused by target_mapchange.
	- [Changed] setting the wait key for a func_door to -2 will prevent it from closing until it is triggered again.
	- [Changed] Player is respawned at the nearest active spawnpoint instead of the furthest in single player mode.
	- [Changed] Damage from bots to players is scaled back depending on skill level (ranging from 0.3 to 0.7 times damage)
	- [Changed] Bots no longer attack each other in single player mode.
	- [Changed] Bots can no longer damage each other in single player mode.
	- [Changed] Bots are no longer able to pick up items in single player mode.
	- [Changed] Bots no longer chat in single player mode.
	- [Changed] "You fragged ... " messages no longer shown in single player mode.
	- [Changed] Obituaries ("... was fragged by ...") messages are no longer shown in single player mode.
	- [Changed] "... conneced" messages no longer shown in SP mode when connecting player is a bot.
	- [Changed] join and team change messages no longer shown in SP mode when joining/changing player is a bot.
	- [Changed] Fraglimit and timelimit are forced to 0 in single player mode.
	- [Changed] Removed non-essential information from HUD in single player mode.
	- [Changed] Hit beep sounds are no longer played in single player.
	- [Changed] Crosshair names are no longer displayed in single player.
	- [Changed] The announcer voice no longer announced fraglimit or timelimit warnings and lead changes in single player.
	
	

v0.3 (12 apr 2011)
	- [Added] IMMEDIATELY spawnflag for target_disable.
	- [Added] mapname key for target_mapchange.
	- [Added] SHOW_INTERMISSION spawnflag for target_mapchange.
	- [Added] Health, armor, weapons and ammo are retained through a map change if it was caused by a target_mapchange.
	- [Added] trigger_death and trigger_frag entities.
	- [Added] count key for spawnpoint entities to limit the number of times a player can spawn there.
	- [Added] startsound and endsound keys to func_door
	- [Added] sound key to func_button
	- [Added] trigger_lock and holdable_key entities
	- [Added] Example map for trigger_lock and holdable_key entities called "keytest"
	- [Added] teleporttarget key to holdable_teleporter
	- [Added] target_debrisemitter entity
	- [Added] target key for func_breakable
	- [Fixed] target_mapchange leaving single player mode when current level is loaded with spmap.
	- [Fixed] Bots are left in the game when a map_restart is issued or the map is changed (note: bots are only kicked when in single player mode)
	- [Fixed] target_mapchange doesn't properly end a map_restart command with a newline character, messing up the next command.
	- [Fixed] Green armor texture is too bright and too saturated
	- [Changed] trigger_disable now links and unlinks entities from the world instead of tagging them with a FL_DISABLED flag.
	- [Changed] Removed START_OFF spawnflag from trigger_hurt.
	- [Changed] Renamed target_intermission to target_mapchange.
	- [Changed] Example map uses target_mapchange instead of target_intermission.
	- [Changed] Bots no longer drop items when in single player mode (g_gametype 2)
	- [Changed] Bots are removed from the game when fragged when in single player mode (g_gametype 2)
	- [Changed] "FIGHT!" message is no longer shown when in single player mode (g_gametype 2)
	- [Changed] Bots defined in arena files are no longer announced when in single player mode (g_gametype 2)
	- [Changed] EntityPlus startup batch file now loads entityplus example map in single player mode
	

v0.2 (25 mar 2011)
	- [Added] shooter_bfg
	- [Added] target_botspawn
	- [Added] target_disable
	- [Added] item_armor_vest
	- [Added] target_playerspeed
	- [Fixed] Two triggers sharing the same origin both targetting the same target_logic won't work.
	- [Changed] func_rotating can rotate along multiple axes.
	- [Changed] func_bobbing can move along multiple axes.
	- [Changed] Removed RED_ONLY/BLUE_ONLY spawnflags from target_intermission and target_gravity.
	- [Changed] Added target_disable, target_botspawn and item_armor_vest example to entityplus example map.

v0.1 (11 mar 2011)
	- [Added] func_breakable
	- [Added] target_gravity
	- [Added] target_intermission
	- [Added] target_logic