# EntityPlus
EntityPlus is a mod that offers a true single player experience in the Quake III Arena videogame. The term "single player" here is used to describe an experience more akin to the single player games of Quake or Quake 2 than Quake 3's own single player bot matches. To facilitate this, EntityPlus implements a lot of features that are strictly aimed at single player gameplay.

News and information about new features will be reported to our [Twitter feed](https://twitter.com/#!/EntityPlus) as they are implemented. This offers a sneak peek into new features the next release of the mod will have.


## Downloads

If you're going to play EntityPlus, you have to download the EntityPlus mod:
* [EntityPlus v1.1.11](https://github.com/TheEnginesOfCreation/EntityPlus/releases/tag/1.1.11)

To add a little variety to the mix, download these custom maps:
* [Carmack Fortress map by deqer](https://storage.googleapis.com/google-code-archive-downloads/v2/code.google.com/entityplus/krep1.zip) (29.1MB)
* [Testing Procedures map by Eraser](http://www.theenginesofcreation.com/content.php?id=addons/ep_procedures) (33.6MB)
* [Survival map by Eraser](http://www.theenginesofcreation.com/content.php?id=addons/ep_survival) (12.1MB) 
* [Duckhunt mappack by Eraser](http://www.theenginesofcreation.com/content.php?id=addons/ep_duckhunt) (696KB)
* [Shipyard 17 map by Martinus](http://www.quake3world.com/forum/viewtopic.php?f=10&t=51412) (56.9MB)
* [Dissent Breach map by Eraser](http://www.theenginesofcreation.com/content.php?id=addons/ep_dissent) (29MB)
* [Castle Wolfenstein map by Eraser](http://www.theenginesofcreation.com/content.php?id=addons/ep_wolf3d) (3MB)
* [The Dimension of Evil map by Eraser](http://www.theenginesofcreation.com/content.php?id=addons/ep_evil) (39MB)

If you're a level designer, you might be interested in the following downloads:
* [The manual for v1.1.11](https://github.com/TheEnginesOfCreation/EntityPlus/releases/download/1.1.11/manual-1.1.11.pdf) (note: the manual is also included with the mod itself)
* [MinversionTool 1.1.11.0](https://github.com/TheEnginesOfCreation/EntityPlus/releases/download/1.1.11/minversiontool-1.1.11.0.zip) to help you determine what the minimum requirements for your map are (note: requires the .NET Framework 3.5 or newer)

## GtkRadiant 1.5 users
If you're a level designer who is using GtkRadiant 1.5, then you may want to download the EntityPlus entities.ent file (the entities.def file for GtkRadiant 1.4/1.6 is included with the mod).
* [entities.ent for v1.1.11](https://github.com/TheEnginesOfCreation/EntityPlus/releases/download/1.1.11/entities.ent)

When using GtkRadiant 1.5/NetRadiant, perform the following steps to make GtkRadiant usable for EntityPlus:
* Add an "entityplus" folder to the q3.game folder
* Copy "default_shaderlist.txt" from the q3.game/baseq3 folder to the q3.game/entityplus folder
* Open the copied "default_shaderlist.txt" with a text editor and add "entityplus" on a new line at the end of the file and save it.
* Make a backup copy of the "entities.ent" in the q3.game/baseq3 folder.
* Put the downloaded entities.ent for EntityPlus in the q3.game/baseq3 folder.
* Configure GtkRadiant to use a custom modification folder named "entityplus". 

## Features

To view a complete list of features added to EntityPlus, download [the manual](https://github.com/TheEnginesOfCreation/EntityPlus/releases/download/1.1.11/manual-1.1.11.pdf). Additional information about each release can be found on the [EntityPlus wiki page](https://github.com/TheEnginesOfCreation/EntityPlus/blob/wiki/Index.md). 

## Example map
The release package of EntityPlus contains an example map which demonstrates a number of the features found in EntityPlus. It is based on an old classic map that everyone that played Quake 3 will instantly recognize. Don't get too comfy though, because this time you'll be fighting through piles of enemy guards to uncover a secret that you never knew was there and escape to safety. The map can be found in the single player menu. 
