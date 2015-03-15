# EntityPlus Features #

For an overview of all features in EntityPlus, download the level designer manual here: https://code.google.com/p/entityplus/downloads/list

## Additional info about the 1.1.4 release ##
  * `[`Fixed] notarget console command does nothing.
  * `[`Fixed] Entities with matching targetname2 don't respond to target\_modify.
  * `[`Fixed] target\_unlink won't unlink target\_relay or target\_delay entities.
  * `[`Fixed] Picking up backpack can push ammo count beyond 999.
  * `[`Added] trigger\_target command.
  * `[`Added] target2 key to target\_modify.
  * `[`Added] target\_modify can be used to change value of "damage" or "dmg" keys.
  * `[`Added] Surfaces with a shader with "surfaceparm flesh" will make flesh footstep noises instead of the default sound.
  * `[`Added] GIVE\_PLAYER spawnflag to target\_give.
  * `[`Added] IGNORE\_PLAYER, PATROL\_WALK and ALWAYS\_WALK spawnflags to target\_botspawn.
  * `[`Added] Green glow to BFG bolts.
  * `[`Added] notep key to prevent entities from spawning in EntityPlus.
  * `[`Changed] g\_debugBotSpawns echoes out health for spawned bot.

Most important changes:

**notep key added to all entities**

EntityPlus now supports the "notep" key for all entities. This key works similar to the notq3a and notta keys, meaning that any entities that have the value of this key set to 1 won't be spawned in EntityPlus games. In theory, this allows level designers to create an ordinary deathmatch level and then tag the correct entities with "notep" or "notq3a" keys so that the same map can be played in deathmatch games using baseq3 or as single player adventure using EntityPlus.


**trigger\_target console command**

The trigger\_target console command can be used to trigger entities with specific targetname or targetname2 values. Usage of the command is:

trigger\_target `[`targetname]

where `[`targetname] is replaced with any targetname/targetname2 value that should be triggered. This can be used to test parts of complex entity setups or trigger entities that would normally require a relatively long time to trigger.

**additional target\_botspawn spawnflags**

The target\_botspawn entity received a number of new spawnflags. These are: IGNORE\_PLAYER, PATROL\_WALK and ALWAYS\_WALK. The IGNORE\_PLAYER spawnflag can be used to force bots to always ignore the player (even when attacked). Patrol walk and always walk can be used to force the bot to walk (only when patrolling or always, respectively). These spawnflags can be used to create more believable non-combat or NPC characters.


## Additional info about the 1.1 release ##

  * `[`Added] "cg\_paintballMode" and "cg\_bigheadMode" cvars
  * `[`Added] Top 5 of scores are saved now instead of just the high score and viewable through scores menu.
  * `[`Added] target\_botremove entity.
  * `[`Added] target\_music entity.
  * `[`Added] "dmg" and "radius" keys to func\_breakable.
  * `[`Added] "breaksound" key to func\_breakable.
  * `[`Added] func\_breakable entities can be targeted and will break upon activation.
  * `[`Added] "startsound" and "endsound" keys to func\_train.
  * `[`Added] "nobots" and "nohumans" keys to func\_door and func\_door\_rotating.
  * `[`Added] "FADE" spawnflag and "startcolor", "endcolor" and "wait" keys for target\_effect.
  * `[`Added] "ONCE" spawnflag to target\_relay.
  * `[`Added] "WP\_GAUNTLET" spawnflag to target\_botspawns. Botspawns without this spawnflag now spawn bots without Gauntlet.
  * `[`Added] "lockedsound" and "unlockedsound" keys to trigger\_lock.
  * `[`Added] "fov" key to info\_camera.
  * `[`Added] "NO\_BOTS" and "NO\_HUMANS" spawnflags to all shooter`_*` entities.
  * `[`Added] "SILENT" spawnflag to all item pickup (item`_*`, weapon`_*`, holdable`_*`, ammo`_*`) entities.
  * `[`Added] "objectivesoverlay" key to worldspawn entity.
  * `[`Added] "enablebreath" and "enabledust" keys to worldspawn entity.
  * `[`Added] "position" console command to get current player position coordinates.
  * `[`Added] "g\_debugVariables", "g\_debugBotspawns" and "g\_debugScore" cvars.
  * `[`Added] "g\_disableCutscenes" cvar.
  * `[`Added] "g\_disableScripts" cvar.
  * `[`Added] "g\_enableBreath" and "g\_enableDust" cvars.
  * `[`Added] Support for longname, author and description through arena files.
  * `[`Added] "Loading..." text and icon is displayed when map is loading.
  * `[`Fixed] target\_unlink does not work on func\_bobbing entities.
  * `[`Fixed] Bots get stuck in each other when they should be telefragged.
  * `[`Fixed] Lightning gun, Railgun and BFG idle sounds continue playing during cutscenes.
  * `[`Fixed] Shooting the machinegun into the void (in a leaked map) crashes the game.
  * `[`Fixed] Music is audible for a short time when s\_musicvolume is set to 0 and death screen or end-game scoreboard is shown.
  * `[`Fixed] Menu item mouseover sound effect is played when mouse is moved over "EntityPlus" title in main menu.
  * `[`Changed] Removed all gametypes from the game. Setting g\_gametype to 8 is no longer necessary.
  * `[`Changed] Scores are calculated differently.
  * `[`Changed] End-game scoreboard specifies accuracy bonus and skill bonus seperately now.
  * `[`Changed] New stylized icon for backpack.
  * `[`Changed] Particles from target\_effect are slightly bigger now so they are better visible.
  * `[`Changed] Bodies of dead bots sink into the floor and no longer pop out of existence.
  * `[`Changed] Increased max ammo amount for all weapons from 200 to 999.
  * `[`Changed] Cameras now take shortest yaw and roll paths.
  * `[`Changed] "setviewpos" console command no longer applies teleporter kick and allows setting of pitch, yaw and roll as well.
  * `[`Changed] Value of "cg\_marks" determines how long wallmarks stay.
  * `[`Changed] "g\_listEntity" is now cheat protected, accepts a value of 2 to only list in-use entity slots and prints out in-use entity count.
  * `[`Changed] Allowed the use of cg\_drawTimer again when cheats are enabled. Timer also displays milliseconds.
  * `[`Changed] Objectives text in objectives overlay automatically wraps to next line without breaking words.
  * `[`Changed] All debris related spawnflags on target\_debrisemitter and func\_breakable are now named `DEBRIS_[type]`.
  * `[`Changed] New main menu artwork.


Most important changes:

**It is no longer necessary to run EntityPlus maps in g\_gametype 8**

The g\_gametype cvar is completely ignored now.

**New scoring system**

The calculation of high scores has changed, so all previous scores are ignored and the scoring starts from scratch. The mod does save a top 5 of scores now.

**Paintball mode and Big Head mode**

Paintball mode makes the gun shoot colorful blobs of paint. In big head mode, all enemies have really, _really_ large heads.

**WP\_GAUNTLET spawnflag for botspawns**

Botspawns without any spawnflags will now spawn bots without any weapons. Use the WP\_GAUNTLET spawnflag to make them spawn with a gauntlet.

**objectives overlay can be changed in worldspawn**

The graphics that should be used for the objectives overlay can be specified individually for each map. If no graphics are specified, the default graphics will be used.



## Additional info about the 1.0 release ##

Here's the full list of changes:

  * `[`Added] g\_debugCameras cvar to log info\_camera debugging info to console.
  * `[`Added] optional minversion key to arena files.
  * `[`Added] playermodel and playerheadmodel keys to worldspawn entity.
  * `[`Added] TARGET\_PLAYER spawnflag to shooter`_` entities
  * `[`Added] dmg key to shooter`_` entities.
  * `[`Added] Support for color and light keys in target\_modify.
  * `[`Added] NO\_PLAYER, NO\_BOTS and NO\_SHOOTER spawnflags to func\_breakable.
  * `[`Fixed] func\_door\_rotating spawnflags are incorrect.
  * `[`Fixed] Using SUBTITLE spawnflag on target\_print displays value of wait key instead of message.
  * `[`Fixed] Subtitles are not visible during cutscenes.
  * `[`Fixed] Lightning gun continues firing during cutscenes.
  * `[`Fixed] Player's viewangles are not locked during a cutscene.
  * `[`Fixed] Crouching becomes useless due to extreme low speeds when being affected by a target\_playerspeed that lowers the player's speed.
  * `[`Fixed] Camera activates triggers, doors and plats when moving through them during cutscenes.
  * `[`Fixed] Camera pitch sometimes makes unintentional complete roll in cutscenes.
  * `[`Fixed] Player spawns with gauntlet and machinegun with 0 ammo when going through a target\_mapchange without having any weapons.
  * `[`Fixed] Deferred models aren't loaded when the objectives overlay is displayed.
  * `[`Fixed] func\_timer's random value defaults to 1 instead of 0.
  * `[`Fixed] Colors of key icons get distorted when health drops below 25.
  * `[`Fixed] When a connection error occurs a blank screen without error message is shown.
  * `[`Fixed] Game crashes when no active spawnpoints are found.
  * `[`Fixed] shooter`_` entities deal full damage instead of damage scaled by skill level.
  * `[`Fixed] shooter`_` and target\_effect entities cannot be unlinked by target\_unlink.
  * `[`Fixed] Game crashes when shooter`_` entity shoots a func\_breakable.
  * `[`Fixed] Replaced info\_player\_deathmatch entitiy in example map with an info\_player\_start entity.
  * `[`Fixed] Credits roll doesn't overrule s\_musicvolume setting anymore.
  * `[`Changed] Objectives notification is drawn on top of letterbox, fades and overlays.
  * `[`Changed] Skill based score modifier runs from 1.0 (easiest skill) to 1.4 (hardest skill) now.
  * `[`Changed] Cutscenes run at a fixed FOV of 90.
  * `[`Changed] It is no longer possible for a second player to connect to the server.
  * `[`Changed] Setting cg\_letterBoxSize to 0 completely removes letterbox effect.
  * `[`Changed] New objectives overlay.

Most important changes:

**Specifying a minversion in the .arena file**

Arena files can be expanded with a "minversion" key that can be used to specify which version of EntityPlus is required to run this map. At this point, only a value of "1.0" is supported. Refer to chapter 4.5 ("Creating an .arena file for your map") of the manual for more information.

**Skill score modifier**

The score modifier for the skill level that is being played at now runs from 1.0 to 1.4. This means that the skill level has less of an impact on the final score. This also means that playing at Nightmare difficulty will most likely result in a lower score than people have been achieving so far. Therefor it is advised to remove the EntityPlus/Games/ep\_example.epgame file if upgrading EntityPlus from an older version.

**func\_timer's default random value**

Quake 3 would assume a default random value for func\_timers of 1. In EntityPlus this has changed to 0. So if you have used any func\_timers in a map that do not explicitly specify a random key, it is advised to specify a random value of 1.

**shooter`_` entities damage level**

Shooter`_` entities would deal the full amount of damage. From 1.0 onward, the skill level that is being played at influences the damage for shooter`_` entities in the same way as it does with the amount of damage bots deal.

**Specifying model/headmodel through worldspawn**

The playermodel and playerheadmodel keys can be added to the worldspawn entity to force the player model that the player will be playing with.

## Additional info about the beta1 release ##

Here's the full list of changes:

  * `[`Added] func\_door\_rotating entity.
  * `[`Added] New credits to exit menu.
  * `[`Added] Background music plays in main menu.
  * `[`Added] info\_backpack entity which can be used with nodrop brushes to teleport a backpack from an unreachable location to a safe location.
  * `[`Added] target\_playerstats entity which can set a player's health and armor.
  * `[`Added] target\_variable entity which can set or read and compare variables that persist across map changes.
  * `[`Added] target\_cutscene and info\_camera for creating cutscenes.
  * `[`Added] START\_UNLINKED spawnflag for func\_static.
  * `[`Added] TOGGLE spawnflag for target\_delay.
  * `[`Added] START\_DELAYED spawnflag and count key for func\_timer.
  * `[`Added] SUBTITLE spawnflag for target\_print.
  * `[`Added] cg\_drawsubtitles cvar to enable/disable subtitles (also available in game options menu).
  * `[`Added] cg\_drawHoldableItems cvar to enable/disable drawing of holdable item icons (teleporter/medkit/keys)
  * `[`Added] deathmusic key to worldspawn entity.
  * `[`Fixed] Spawning a bot with only a Gauntlet results in the bot spawning with a MG and console errors when the bot attacks.
  * `[`Fixed] Picking up a Gauntlet after it has been removed results in the Gauntlet being unusable.
  * `[`Fixed] target\_unlink with IMMEDIATELY spawnflag won't unlink entities that spawn on second frame (such as movers).
  * `[`Fixed] target\_unlink ALWAYS\_UNLINK and ALWAYS\_LINK spawnflags have opposite effect.
  * `[`Fixed] target\_unlink toggles unlinked entities if ALWAYS\_UNLINK is set and linked entities if ALWAYS\_LINK is set.
  * `[`Fixed] target\_score doesn't add any score when triggered.
  * `[`Fixed] deathtarget key on target\_botspawn does not activate entities with matching targetname2.
  * `[`Changed] Shots at a func\_breakable are now counted as hits and thus will positively affect accuracy instead of negatively
  * `[`Changed] Using the skill key on target\_botspawn now actually influences the general AI skill level of that bot.
  * `[`Changed] Picking up a weapon if no weapons are currently held will automatically switch to that weapon.
  * `[`Changed] Setting a speed of -1 for target\_playerspeed will freeze the player in his spot, unable to jump or duck as well.
  * `[`Changed] Countdown is no longer displayed when issueing a map\_restart.
  * `[`Changed] Default health value for target\_botspawn was changed from 125 to 100.
  * `[`Changed] Bot health is higher/lower depending on skill level.
  * `[`Changed] Picking up weapon for which you already have ammo adds normal amount of ammo instead of just 1.
  * `[`Changed] Removed info\_player\_deathmatch from entities.def
  * `[`Changed] Renamed the skill levels.

Most important changes:

**Cutscenes**

Cutscenes can be made using the target\_cutscene and info\_camera entities. Refer to the related sections in the manual for additional info on the subject.

**Subtitles**

Subtitles can be enabled/disabled through the games option menu. Level designers can enable the "SUBTITLE" spawnflag on target\_print entities, so that the text of the entity will be displayed as subtitle. This is useful when supplying subtitles for spoken dialogue.

**info\_backpack entity**

A known problem for level designers was players dying in lava, slime, the void or other similar hazards. The backpack that is spawned upon the player's death would become irretrievable. Info\_backpack entities can be placed in the map so that the backpack teleports to the nearest info\_backpack entity whenever it hits a brush that is textured with the common/nodrop texture.

**target\_variable entity**

The target\_variable entity can be used to create variables and assign values to them. The target\_variable entity can read these variables as well and activate other entities depending on the value of the variable. Any variables that are written to memory will persist across mapchanges (when the mapchange is initialized by a target\_mapchange entity). This allows level designers to open a door in one map while the switch to open it is in another map!

**deathmusic key for worldspawn entity**

From beta 1 onward, whenever the player dies the screen will fade to black and a "You died" message will be displayed. Music can be played while the player is dead. By default, no music is played, but by setting the deathmusic key the level designer can specify the music file that should be played while the player is dead.

**info\_player\_deathmatch entity removed**

The info\_player\_deathmatch entity was removed from the entities.def file. This means that it is no longer available in Radiant. Any maps that are already using such entities will still function correctly but will show up incorrectly in Radiant. It is preferable to replace all info\_player\_deathmatch entities with info\_player\_start entities.

**Changes to spawning bots**

Before the beta 1 release, target\_botspawn entities that have no health key defined would spawn bots with 125 health. From this release onwards, bots are spawned with 100 health by default.
Also, the amount of health bots are spawned with is not directly influenced by the skill level the player is playing at. When playing at the medium difficulty setting, bots will spawn with the specified amount of health. At higher difficulty levels, bots spawn with more health (20% extra for skill 4 or 40% extra for skill 5). At lower skill levels, bots spawn with less health (20% less for skill 2 or 40% less for skill 1).
Finally, using the skill key on target\_botspawn does not only influence the amount of damage a bot deals, it also influence the health it will spawn with and the actual AI level of the bot (though for AI level 5 is the maximum).

**Ammo pickup**

EntityPlus now uses the Team Deathmatch ammo pickup system which means that if a player picks up a weapon after picking up an ammo box, the weapon will add the full complement of ammo to the player's inventory (similar to picking up an ammo box). Before the beta 1 release, players would receive only 1 ammo for the picked up weapon if they already had ammo for the weapon.


## Additional info about the v0.8.1 release ##

Here's the full list of changes:

  * `[`Fixed] Looping target\_speakers do not stop playing their sound when triggered.
  * `[`Fixed] Center print messages (such as target\_print message) are not displayed.

Most important changes:

**target\_speaker changes**

In the original Quake 3 Arena, it was impossible to toggle target\_speaker entities off when they had either the LOOPING\_ON or LOOPING\_OFF spawnflags set. Once a looping target\_speaker was playing its sound, it couldn't stop anymore. In EntityPlus, a target\_speaker can be toggled off again by triggering it with another entity.


## Additional info about the v0.8 release ##

Here's the full list of changes:

  * `[`Added] target\_modify entity.
  * `[`Added] target\_secret entity.
  * `[`Added] func\_rotating can be started/stopped by targeting it with a trigger.
  * `[`Added] START\_OFF spawnflag to func\_rotating.
  * `[`Added] Added target2 key to a number of entities.
  * `[`Added] Added targetname2 key to a number of entities.
  * `[`Added] scoreboardmusic key to worldspawn entity.
  * `[`Added] path\_corner entities can have a wait key of -1 which will halt the train until the train is triggered again.
  * `[`Added] STONE\_DEBRIS spawnflag to target\_debrisemitter and func\_breakable.
  * `[`Added] Explosion sound when score is being added up in scoreboard.
  * `[`Added] Lightning effect to main menu background.
  * `[`Fixed] Accuracy does not persist across map changes.
  * `[`Fixed] Players respawning at a spawnpoint targeting a target\_remove\_powerups that removes all weapons end up holding a Gauntlet.
  * `[`Fixed] Objective texts of more than 60 characters run outside of the objectives overlay.
  * `[`Fixed] Objectives updated notification sound does not play if cg\_draw2d is set to 0.
  * `[`Fixed] Highscores are saved to incorrect file when target\_mapchange was used.
  * `[`Fixed] Added missing spawnflags to info\_player\_start in entities.def.
  * `[`Changed] From this release forward, multiplayer modes are officially no longer supported.
  * `[`Changed] target\_disable is renamed to target\_unlink.
  * `[`Changed] Shortened fade-in at start of level if no message key was set for the map's worldspawn entity.
  * `[`Changed] Accuracy is no longer a seperate item in scoreboard and only applies to carnage score.
  * `[`Removed team related entities and spawnflags from entities.def.
  * `[`Changed] Removed FLAGS spawnflag from target\_remove\_powerups.
  * `[`Changed] Removed multiplayer option from main menu.
  * `[`Changed] Removed some multiplayer related settings to the setup menu.


The most important changes:


**Multiplayer is no longer supported**

Multiplayer game modes are no longer supported. Technically they're still there, in full working order, but a number of the new entityplus entities simply don't work well in multiplayer scenarios. To remove all responsibility of having to support that as well, multiplayer is officially out. It also frees up the possibility of re-using multiplayer related structs in the code which are hardcoded into the engine as well, so in the future, the technical functionality of multiplayer may be gone or degraded as well.


**Saving highscores**

It appears saving high scores got broken somewhere between the 0.6 and 0.7.1 releases but I should have it fixed for good now. The game would always save the high score to a file named "0.epgame" which is obviously incorrect.


**target\_modify**

The new target\_modify entity can be used to change key/value pairs (properties) of entities run-time. This makes it possible, for instance, to have a func\_train target a path\_corner sequence but, after pressing a button that triggers the target\_modify, have the path\_corners target a different sequence of path\_corners so the train will move through a different path. Another example is to change the target of a trigger or button.


**target\_secret**

There's also the target\_secret entity now, which allows you to put secrets into your map. Finding a secret earns the player bonus points which will be displayed on the scoreboard.


**target2 and targetname2**

All entities that can trigger a different entity or be triggered by another entity can use the target2 and targetname2 keys as well. These's are similar to the target and targetname keys. It allows you to set up a trigger that activates two other entities with different targetnames, or have an entity that can be triggered by two triggers with different targetnames. target/targetname2 and target2/targetname combinations are possible, so an entity with target2 "t1" will activate an entity with a matching targetname, just like an entity with targetname2 "t2" will be activated by an entity with a matching target.


**toggling func\_trains and func\_rotatings**

path\_corner entities can now have a wait key of -1, so that the train stops moving when it reaches that path\_corner. The train starts moving again when it's triggered. A func\_rotating can also be triggered to make it stop or resume moving.


**target\_disable** _important for mappers!_

target\_disable has been renamed to target\_unlink, so change the value for the classname key on any target\_disable entities you have in your map.