# Tutorial 1: A basic map #

Before you can create a map for EntityPlus, you'll need a few things:
  * A legal copy of [Quake III Arena](http://store.steampowered.com/app/2200/), updated to version 1.32 or 1.32c.
  * [GtkRadiant](http://icculus.org/gtkradiant/) version 1.4, 1.5 or 1.6.
  * The [EntityPlus mod](https://code.google.com/p/entityplus/downloads/list).
  * The mod download package contains the manual, but it is available as stand alone download in the [downloads section](https://code.google.com/p/entityplus/downloads/list) as well.
  * If you are using GtkRadiant 1.5, then you will need to download the entities.ent file for GtkRadiant 1.5 as well.

If you want to know how to configure GtkRadiant to use EntityPlus, then refer to the EntityPlus manual.

## Creating the map ##

Simply follow these basic steps to create your first map:

  * Create an empty box room.
  * Place an info\_player\_start entity somewhere in the room.
  * Create a trigger\_multiple entity.
  * Create a target\_finish entity and have the trigger\_multiple entity target the target\_finish entity.
  * Compile the map

Congratulations! You've just created your first EntityPlus map! It's just an empty map that does nothing, but you can walk into the trigger\_multiple entity and the game will switch to the final scoreboard view.