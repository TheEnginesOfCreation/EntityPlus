ENTITYPLUS 
version 0.5.1
-------------

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
	\sv_maxclients 32
	\con_notifytime 0
	\spmap ep_example 

The map can also be started by double clicking the entityplus.bat file that comes with the release package. This batch file 
is located next to the quake.exe executable.


CREDITS
-------
Project lead and programming	: Eraesr
								  [http://www.theenginesofcreation.com]

Additional programming and
programming support				: ^misantropia^
								  [https://github.com/bnoordhuis]
	

Additional programming			: Kaz
								  [http://student.cs.appstate.edu/freemancw]

Programming support				: Perle			
								  [http://www.q3rally.com]

Keycard models and skins		: Obsidian
								  [http://www.robotrenegade.com]

Skeleton key models and skins	: Hipshot
								  [http://www.zfight.com]

Debris and backpack models		: DaEngineer
								  [http://victorkarp.wordpress.com]




CONTACT
-------
Contact me at eraesr@gmail.com or visit The Engines of Creation at http://www.theenginesofcreation.com.
To follow the project or get the source code, go to https://code.google.com/p/entityplus.
If you want to follow discussions surrounding the mod or leave your own input, visit the 
discussion thread in the Quake3World Level Editing & Modelling forums at http://quake3world.com/forum/viewtopic.php?f=10&t=45510.


VERSION HISTORY
---------------
For a complete version history, view the "version history.txt" file.