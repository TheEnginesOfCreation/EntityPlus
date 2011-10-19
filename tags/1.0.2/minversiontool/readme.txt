ENTITYPLUS MINVERSIONTOOL
-------------------------

MinVersionTool is a tool for level designers who create maps for the EntityPlus mod.
Because each version of the mod adds new features and functionality, it is possible that a player downloads a map that makes use of certain features that are not supported by the version of EntityPlus that the player is running.

To prevent players from unknowingly playing maps that are not fully functional, or indeed impossible to finish, level designers can add a "minversion" setting to the .arena file that accompanies the map. This setting will inform the game what minimum version of EntityPlus is required to run the map correctly. If the user is running an older version, the incompatibility is indicated by a yellow "requires version x.x" text on the picture of the map in the map selection screen.

This minversion tool can analyze a .map file and tell you what the minversion for that map will be.


Usage
-----

Simply type 
mvt.exe "filename"
in a command prompt to analyze a map. Replace filename with the full path to the mapfile. The tool also supports a -d switch. When the -d switch is used, it will output debug information.


Compatibility
-------------

The minversiontool is only able to determine the minversion up to the version that the minversiontool itself is compatible with. It is therefor important to always make sure your minversiontool is up-to-date with the version of EntityPlus you are running yourself.


Contact
-------
Visit the EntityPlus project website at http://code.google.com/p/entityplus