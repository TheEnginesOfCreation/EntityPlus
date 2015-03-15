# Tutorial 2: Adding enemies #

This tutorial is a followup for [Tutorial 1](Tutorial1.md). Make sure you have followed the instructions in that tutorial before continuing with this tutorial.

An EntityPlus map is no fun without enemies, so this tutorial will explain the steps to follow to add an enemy to your map. Note that this tutorial only explains the basics. For more extensive details about the entities involved, refer to the EntityPlus manual.

## Creating the map ##

The starting point for this tutorial is where tutorial 1 left off. Load that map file again and perform the following steps:

  1. Add a second trigger\_multiple entity to the map. Make sure it doesn't overlap the existing trigger\_multiple entity. It's wise to mark the locations of the two trigger\_multiple entities with a brush so you know where they are in-game.
  1. Give the new trigger\_multiple a _wait_ key of -1 to make sure we'll only spawn one enemy into the game.
  1. Add a _nobots_ key to the old trigger\_multiple (the one targeting the target\_finish entity) and give it a value of 1. This is done so that the enemy we are going to spawn won't accidentally run into this trigger\_multiple and activate it.
  1. Add a target\_botspawn entity and place it in the position where you want the enemy to spawn.
  1. Give the target\_botspawn entity a _health_ key with a value of 25. This will give the bot 25 health which means he's relatively easy to kill. Also add a _clientname_ key to the target\_botspawn and give it a value like "sarge" or "visor" or some other bot's name. You can omit this key as well. The game will default to "sarge" then.
  1. Check the WP\_SHOTGUN spawnflag for the target\_botspawn entity to make sure the enemy spawns with a shotgun. You can check other WP`_` spawnflags as well to spawn the enemy with those weapons.
  1. Have the new trigger\_multiple target the target\_botspawn entity.

If you compile the map and load it in the game, you'll be able to run into the new trigger\_multiple and you'll see that a bot spawns into the map. It's possible that he doesn't move after spawning, most likely when he spawns with his back to you. Shooting the bot will eventually kill it. Run into the trigger\_multiple that targets the target\_finish and you'll see that you've actually accumulated some points this time around.

A more realistic behavior is to have enemies patrol along certain paths. EntityPlus allows you to define bot patrol routes using info\_waypoint entities. Follow these steps to define a route for our bot to patrol:

  1. Add an info\_waypoint entity and put it in a location where you want your bot to run to after spawning.
  1. Check the IGNORE\_PLAYER spawnflag on the target\_botspawn entity. This will make sure that the bot will always ignore the player. This allows us to view the bot running along it's patrol route without having it attack us and break free from it's patrolling routine. Note that if no IGNORE\_PLAYER spawnflag is present, you're probably runnning an older version of the mod that does not support this yet. [Download the most recent version](https://code.google.com/p/entityplus/downloads/list) before continuing this tutorial.
  1. Have the target\_botspawn target the info\_waypoint entity.
  1. Add another info\_waypoint entity and put it in a second location where you want your bot to run to after reaching the first waypoint. It's no problem to put an info\_waypoint entity in the same location as your target\_botspawn, but it's something I wouldn't recommend due to one entity obscuring the other in the editor.
  1. Have the first info\_waypoint target the second info\_waypoint.
  1. Add a third info\_waypoint entity and have the second info\_waypoint target the third info\_waypoint.

Compile the map and load it in the game. After triggering the target\_botspawn by running into the appropriate trigger, you'll notice that the bot starts running towards the first waypoint, then to the second and then to the third. Once the third waypoint is reached, the bot will run back to the second and then to the first again. The bot will continue running up and down the patrol route until it's killed.

It's also possible to set up circular patrol routes. You can do this by making one simple adjustment to the map: have the third info\_waypoint target the first info\_waypoint. After compiling and loading the map, you'll notice that the bot will now run directly back to the first waypoint after reaching the third waypoint rather than backtracking along the waypoints.


A tip: Because it's an odd sight to see a bot appear out of nowhere in a map, it's good practice to have bots spawn into the game in a location where the player can't see them (yet). For example, place a trigger\_multiple before a corner of a corridor and put the target\_botspawn entity (or entities) after the corner. The player can't see the bots spawn into the game now which gives the impression like they always were there.