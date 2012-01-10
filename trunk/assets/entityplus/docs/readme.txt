ENTITYPLUS 
version 1.1.3
-------------

EntityPlus is a Quake III Arena mod that is aimed at expanding the toolset for Quake III Arena map makers.
The goal is to build an expansive library of new entities that map makers can use in their maps to create
whole new experiences.

Because a mod is a rather strict prerequisite for any custom map, and Q3A's age and waning popularity don't
exactly help in that aspect either, the aim will be to achieve a complete set of features that will
expand the possibilities of single player experiences in Q3A. EntityPlus has reached a state where it allows
level designers to create true single player experiences in Quake III Arena. While Q3A features a single
player mode, this  is nothing more than a multiplayer deathmatch game where the player fights against
computer controlled AI bots to score the most frags. In EntityPlus, the term "single player" is used to 
describe an experience more akin to the SP games of Quake or Quake 2 than Quake 3's own single player bot matches.

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
You can either overwrite the existing entities.def in baseq3 (although this is not recommended) or configure 
GtkRadiant 1.4 or ZeroRadiant 1.6 to use the entityplus folder as working folder.

A seperate entities.ent for use in GtkRadiant 1.5 is available from the EntityPlus project website.

Configuring Radiant to use the entityplus folder as working folder can be done by going to "File" > "Project Settings", 
then under "Select mod" pick the option "Custom Quake III modification" and enter "entityplus" as value for the fs_game 
input field. Click "ok" to apply the settings. A more in-depth explanation for this is included in the manual that
accompanies the mod.

The mod can be started by using the "EntityPlus.bat" file found in your Quake III Arena installation folder. In EntityPlus,
the single player menu will list all the maps that are compatible with entityplus' single player mode.



FEATURES
--------
EntityPlus adds a few new entities that can be used in maps. If you use any of the EntityPlus features in your map, 
it can only be correctly played using the EntityPlus mod. For a list of features added to EntityPlus, download the
manual from:

https://code.google.com/p/entityplus/downloads/list



EXAMPLE MAP
-----------
The release package of EntityPlus contains an example map which demonstrates a number of the features found in EntityPlus.
It is based on an old classic map that everyone that played Quake 3 will instantly recognize. Don't get too comfy though,
because this time you'll be fighting through piles of enemy guards to uncover a secret that you never knew was there and 
escape to safety. The map can be found in the single player menu.



CREDITS
-------
Project lead and programming	: Eraser
								  [http://www.theenginesofcreation.com]

Additional programming and		: ^misantropia^
programming support				  [https://github.com/bnoordhuis]

Additional programming			: Kaz
								  [http://student.cs.appstate.edu/freemancw]
								  
Additional programming			: cyr
								  [http://quake3world.com/forum/memberlist.php?mode=viewprofile&u=32395]
								  
Programming support				: Perle			
								  [http://www.q3rally.com]
								  
Programming support				: themuffinman
								  [http://quake3world.com/forum/memberlist.php?mode=viewprofile&u=28606]

Keycard models,					: Obsidian
main menu artwork and logo		  [http://www.robotrenegade.com]

Skeleton key models				: Hipshot
								  [http://www.zfight.com]

Debris and backpack models		: DaEngineer
								  [http://victorkarp.wordpress.com]

Stone debris models and 		: gooball
additional programming			  [http://quake3world.com/forum/memberlist.php?mode=viewprofile&u=30967]


Custom sound effects			: Patrick "Scout" Schotte


Objectives overlay art			: Noruen
								  [http://quake3world.com/forum/memberlist.php?mode=viewprofile&u=28238]
		
Testing and feedback			: AEon
								  [http://aeons.poweredbylasers.com]			  
								  
Testing and feedback 			: EmeraldTiger
								  [http://emeraldproductions.weebly.com/]

Testing and feedback			: tigger.on
								  [http://tig.onemoremonkey.com]
								  
Testing and feedback			: deqer
								  [http://www.ryanbriscall.com/portfolio/games/level-design/]
								  
Testing and feedback			: Ouija
								  [http://quake3world.com/forum/memberlist.php?mode=viewprofile&u=32714]
								  
Testing and feedback			: nick lol
								  [http://quake3world.com/forum/memberlist.php?mode=viewprofile&u=32102]
								  
Testing and feedback			: ZTurtleMan
								  [http://ztm.x10hosting.com/ta/]
								  
Support and general enthusiasm	: The entire Quake3World LEM community
								  [http://quake3world.com/forum/viewforum.php?f=10]

ADDITIONAL CREDIT
-----------------
- Parts of the earthquake code used in EntityPlus were taken from The Reaction Factory [http://rfactory.org]
- Parts of the particle effect code used in EntityPlus were taken from Juz's Slipgate [http://www.juz.org.uk]

					
CONTACT
-------
Contact Eraser at eraesr@gmail.com or visit The Engines of Creation at http://www.theenginesofcreation.com.
To follow the project or get the source code, go to https://code.google.com/p/entityplus.
If you want to follow discussions surrounding the mod or leave your own input, visit the 
discussion thread in the Quake3World Level Editing & Modeling forums at http://quake3world.com/forum/viewtopic.php?f=10&t=45510,
or report an issue at the Google Code page.


VERSION HISTORY
---------------
For a complete version history, view the "version history.txt" file.