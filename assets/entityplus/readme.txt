ENTITYPLUS 
version 0.3
-----------

EntityPlus is a Quake III Arena mod that is aimed at expanding the toolset for Quake III Arena map makers.
The goal is to build an expansive library of new entities that map makers can use in their maps to create
whole new experiences.

Because a mod is a rather strict prerequisite for any custom map, and Q3A's age and waning popularity don't
exactly help in that aspect either, the aim will be at a completely experimental set of features that will hopefully
expand the possibilities of single player experiences in Q3A. While Q3A will never be a full fledge single player 
campaign-based game, EntityPlus will give map makers a broader palette of features to work with, allowing the
most innovative of mappers to create interesting new experiences that haven't been part of Quake III Arena yet.

The mod is completely open source and anyone is allowed to make their own additions to the code base. I am
even accepting feature requests which I will try to implement in the codebase in a timely fashion. This will allow
mappers for the first time to think way beyond the boundaries of Q3A. Within this mod, a challenge for mappers
is hidden. Try to think of something that sheds the shackles of Q3A's basic multiplayer deathmatch gameplay
and think of new interesting things to do within this new limitless world.



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


VERSION HISTORY
---------------
v0.3 (12 apr 2011)
	- [Added] IMMEDIATELY spawnflag for target_disable.
	- [Added] mapname key for target_mapchange.
	- [Added] SHOW_INTERMISSION spawnflat for target_mapchange.
	- [Added] Health, armor, weapons and ammo are retained through a map change if it was caused by a target_mapchange.
	- [Added] target_death and target_frag entities.
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


CREDITS
-------
Project lead and programming	: Eraesr (eraesr@gmail.com)

Additional programming and
programming support				: ^misantropia^

Additional programming			: Kaz



CONTACT
-------
Contact me at eraesr@gmail.com or visit The Engines of Creation at http://www.theenginesofcreation.com.
To follow the project or get the source code, go to https://code.google.com/p/entityplus
For more info, visit the Level Editing & Modelling forums at http://www.quake3world.com/forums.