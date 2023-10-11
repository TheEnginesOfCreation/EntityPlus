// Copyright (C) 1999-2000 Id Software, Inc.
//
// g_utils.c -- misc utility functions for game module

#include "g_local.h"

typedef struct {
  char oldShader[MAX_QPATH];
  char newShader[MAX_QPATH];
  float timeOffset;
} shaderRemap_t;

#define MAX_SHADER_REMAPS 128

int remapCount = 0;
shaderRemap_t remappedShaders[MAX_SHADER_REMAPS];

void AddRemap(const char *oldShader, const char *newShader, float timeOffset) {
	int i;

	for (i = 0; i < remapCount; i++) {
		if (Q_stricmp(oldShader, remappedShaders[i].oldShader) == 0) {
			// found it, just update this one
			strcpy(remappedShaders[i].newShader,newShader);
			remappedShaders[i].timeOffset = timeOffset;
			return;
		}
	}
	if (remapCount < MAX_SHADER_REMAPS) {
		strcpy(remappedShaders[remapCount].newShader,newShader);
		strcpy(remappedShaders[remapCount].oldShader,oldShader);
		remappedShaders[remapCount].timeOffset = timeOffset;
		remapCount++;
	}
}

const char *BuildShaderStateConfig() {
	static char	buff[MAX_STRING_CHARS*4];
	char out[(MAX_QPATH * 2) + 5];
	int i;
  
	memset(buff, 0, MAX_STRING_CHARS);
	for (i = 0; i < remapCount; i++) {
		Com_sprintf(out, (MAX_QPATH * 2) + 5, "%s=%s:%5.2f@", remappedShaders[i].oldShader, remappedShaders[i].newShader, remappedShaders[i].timeOffset);
		Q_strcat( buff, sizeof( buff ), out);
	}
	return buff;
}

/*
=========================================================================

model / sound configstring indexes

=========================================================================
*/

/*
================
G_FindConfigstringIndex

================
*/
int G_FindConfigstringIndex( char *name, int start, int max, qboolean create ) {
	int		i;
	char	s[MAX_STRING_CHARS];

	if ( !name || !name[0] ) {
		return 0;
	}

	for ( i=1 ; i<max ; i++ ) {
		trap_GetConfigstring( start + i, s, sizeof( s ) );
		if ( !s[0] ) {
			break;
		}
		if ( !strcmp( s, name ) ) {
			return i;
		}
	}

	if ( !create ) {
		return 0;
	}

	if ( i == max ) {
		G_Error( "G_FindConfigstringIndex: overflow" );
	}

	trap_SetConfigstring( start + i, name );

	return i;
}


int G_ModelIndex( char *name ) {
	return G_FindConfigstringIndex (name, CS_MODELS, MAX_MODELS, qtrue);
}

int G_SoundIndex( char *name ) {
	return G_FindConfigstringIndex (name, CS_SOUNDS, MAX_SOUNDS, qtrue);
}

//=====================================================================


/*
================
G_TeamCommand

Broadcasts a command to only a specific team
================
*/
void G_TeamCommand( team_t team, char *cmd ) {
	int		i;

	for ( i = 0 ; i < level.maxclients ; i++ ) {
		if ( level.clients[i].pers.connected == CON_CONNECTED ) {
			if ( level.clients[i].sess.sessionTeam == team ) {
				trap_SendServerCommand( i, va("%s", cmd ));
			}
		}
	}
}


/*
=============
G_Find

Searches all active entities for the next one that holds
the matching string at fieldofs (use the FOFS() macro) in the structure.

Searches beginning at the entity after from, or the beginning if NULL
NULL will be returned if the end of the list is reached.

=============
*/
gentity_t *G_Find (gentity_t *from, int fieldofs, const char *match)
{
	char	*s;

	if (!from)
		from = g_entities;
	else
		from++;

	for ( ; from < &g_entities[level.num_entities] ; from++)
	{
		if (!from->inuse)
			continue;
		s = *(char **) ((byte *)from + fieldofs);
		if (!s)
			continue;
		if (!Q_stricmp (s, match))
			return from;
	}

	return NULL;
}


/*
=============
G_PickTarget

Selects a random entity from among the targets
=============
*/
#define MAXCHOICES	32

gentity_t *G_PickTarget (char *targetname)
{
	gentity_t	*ent = NULL;
	int		num_choices = 0;
	gentity_t	*choice[MAXCHOICES];

	if (!targetname)
	{
		G_Printf("G_PickTarget called with NULL targetname\n");
		return NULL;
	}

	while(1)
	{
		ent = G_Find (ent, FOFS(targetname), targetname);
		if (!ent)
			break;
		choice[num_choices++] = ent;
		if (num_choices == MAXCHOICES)
			break;
	}

	if (!num_choices)
	{
		G_Printf("G_PickTarget: target %s not found\n", targetname);
		return NULL;
	}

	return choice[rand() % num_choices];
}


/*
==============================
G_UseTargets

"activator" should be set to the entity that initiated the firing.

Search for (string)targetname in all entities that
match (string)self.target and call their .use function

==============================
*/
void G_UseTargets( gentity_t *ent, gentity_t *activator ) {
	gentity_t		*t;
	
	if ( !ent ) {
		return;
	}

	if (ent->targetShaderName && ent->targetShaderNewName) {
		float f = level.time * 0.001;
		AddRemap(ent->targetShaderName, ent->targetShaderNewName, f);
		trap_SetConfigstring(CS_SHADERSTATE, BuildShaderStateConfig());
	}

	// use ent->target
	if ( ent->target ) {

		//find all entities with matching targetname
		t = NULL;
		while ( (t = G_Find (t, FOFS(targetname), ent->target)) != NULL ) {
			if ( t == ent ) {
				G_Printf ("WARNING: Entity used itself.\n");
			} else {
				if ( t->use ) {
					t->use (t, ent, activator);
				}
			}
			if ( !ent->inuse ) {
				G_Printf("entity was removed while using targets\n");
				return;
			}
		}

		//find all entities with matching targetname2
		t = NULL;
		while ( (t = G_Find (t, FOFS(targetname2), ent->target)) != NULL ) {
			if ( t == ent ) {
				G_Printf ("WARNING: Entity used itself.\n");
			} else {
				if ( t->use ) {
					t->use (t, ent, activator);
				}
			}
			if ( !ent->inuse ) {
				G_Printf("entity was removed while using targets\n");
				return;
			}
		}
	}

	// use ent->target2
	if ( ent->target2 ) {
		
		//find all entities with matching targetname
		t = NULL;
		while ( (t = G_Find (t, FOFS(targetname), ent->target2)) != NULL ) {
			if ( t == ent ) {
				G_Printf ("WARNING: Entity used itself.\n");
			} else {
				if ( t->use ) {
					t->use (t, ent, activator);
				}
			}
			if ( !ent->inuse ) {
				G_Printf("entity was removed while using targets\n");
				return;
			}
		}

		//find all entities with matching targetname2
		t = NULL;
		while ( (t = G_Find (t, FOFS(targetname2), ent->target2)) != NULL ) {
			if ( t == ent ) {
				G_Printf ("WARNING: Entity used itself.\n");
			} else {
				if ( t->use ) {
					t->use (t, ent, activator);
				}
			}
			if ( !ent->inuse ) {
				G_Printf("entity was removed while using targets\n");
				return;
			}
		}
	}
}

/*
==============================
G_UseDeathTargets

"activator" is the BOT client that died.

Search for (string)targetname in all entities that
match (string)self.deathtarget and call their .use function.
Specifically used for target_botspawn entities that have their 
deathtarget key set.

==============================
*/
void G_UseDeathTargets( gentity_t *ent, gentity_t *activator ) {
	gentity_t		*t;
	
	if ( !ent ) {
		return;
	}

	if (ent->targetShaderName && ent->targetShaderNewName) {
		float f = level.time * 0.001;
		AddRemap(ent->targetShaderName, ent->targetShaderNewName, f);
		trap_SetConfigstring(CS_SHADERSTATE, BuildShaderStateConfig());
	}

	if ( !ent->deathTarget ) {
		return;
	}

	//search for entities with matching targetname
	t = NULL;
	while ( (t = G_Find (t, FOFS(targetname), ent->deathTarget)) != NULL ) {
		if ( t == ent ) {
			G_Printf ("WARNING: Entity used itself.\n");
		} else {
			if ( t->use ) {
				t->use (t, ent, activator);
			}
		}
		if ( !ent->inuse ) {
			G_Printf("entity was removed while using targets\n");
			return;
		}
	}

	//search for entities with matching targetname2
	t = NULL;
	while ( (t = G_Find (t, FOFS(targetname2), ent->deathTarget)) != NULL ) {
		if ( t == ent ) {
			G_Printf ("WARNING: Entity used itself.\n");
		} else {
			if ( t->use ) {
				t->use (t, ent, activator);
			}
		}
		if ( !ent->inuse ) {
			G_Printf("entity was removed while using targets\n");
			return;
		}
	}
}

/*
==============================
G_DropLoot

"activator" is the BOT client that died

Search for (string)targetname in all entities that
match (string)self.lootTarget and spawn it.
Specifically used for target_botspawn entities that have their
lootTarget key set.

==============================
*/

void G_DropLoot(gentity_t* ent, gentity_t* activator) {
	gentity_t* t;

	if (!ent || !activator) {
		return;
	}

	if (!ent->lootTarget) {
		return;
	}

	//search for entities with matching targetname
	t = NULL;
	while ((t = G_Find(t, FOFS(targetname), ent->lootTarget)) != NULL) {
		if (t->s.eType != ET_ITEM) {
			G_Printf("WARNING: Target entity is not an item\n");
		} else {
			if (t->count > 0) {
				t->item->quantity = t->count;
			}
			Drop_Item(activator, t->item, 0);
		}
		if (!ent->inuse) {
			G_Printf("entity was removed while using targets\n");
			return;
		}
	}

	//search for entities with matching targetname2
	t = NULL;
	while ((t = G_Find(t, FOFS(targetname2), ent->lootTarget)) != NULL) {
		if (t->s.eType != ET_ITEM) {
			G_Printf("WARNING: Target entity is not an item\n");
		} else {
			t->item->quantity = t->count;
			Drop_Item(activator, t->item, 0);
		}
		if (!ent->inuse) {
			G_Printf("entity was removed while using targets\n");
			return;
		}
	}
}

/*
==============================
G_SetEntityLinked
==============================
*/
void G_SetEntityLinked( gentity_t *t, int spawnflags ) {
	if ( spawnflags & 4 ) {								
		//always_unlink spawnflag is set, so unlink entity from the world
		if ( strcmp(t->classname, "func_bobbing") ) {
			if ( t->r.linked ) { trap_UnlinkEntity( t ); }
		} else {
			if ( t->s.eType == ET_MOVER ) { t->s.eType = ET_INVISIBLE; }
		}
		
	} else if ( spawnflags & 8 ) {						
		//always_link spawnflag is set, so link entity from the world
		if ( strcmp(t->classname, "func_bobbing") ) {
			if ( !t->r.linked ) { trap_LinkEntity( t ); }	
		} else {
			if ( t->s.eType == ET_INVISIBLE ) { t->s.eType = ET_MOVER; }
		}
	} else {											
		//no spawnflag is set, so toggle
		if ( strcmp(t->classname, "func_bobbing") ) {
			if ( t->r.linked )
				trap_UnlinkEntity( t );
			else
				trap_LinkEntity( t );
		} else {
			if ( t->s.eType == ET_MOVER )
				t->s.eType = ET_INVISIBLE;
			else
				t->s.eType = ET_MOVER;
		}
	}
}

/*
==============================
G_ToggleTargetsLinked

Search for targetname(2) in all entities that
match ent.target(2) and link or unlink them from the world

==============================
*/
void G_ToggleTargetsLinked( gentity_t *ent ) {
	gentity_t		*t;
	
	if ( !ent ) {
		return;
	}

	if ( !ent->target && !ent->target2 ) {
		return;
	}

	if (ent->target) {
		t = NULL;
		while ( (t = G_Find (t, FOFS(targetname), ent->target)) != NULL ) {
			if ( t == ent ) {
				G_Printf( "WARNING: Entity %s at %s targets itself.\n", ent->classname, vtos(ent->s.origin) );
			} else {
				G_SetEntityLinked( t, ent->spawnflags );
			}
			if ( !ent->inuse ) {
				G_Printf("entity was removed while using targets\n");
				return;
			}
		}

		t = NULL;
		while ( (t = G_Find (t, FOFS(targetname2), ent->target)) != NULL ) {
			if ( t == ent ) {
				G_Printf( "WARNING: Entity %s at %s targets itself.\n", ent->classname, vtos(ent->s.origin) );
			} else {
				G_SetEntityLinked( t, ent->spawnflags );
			}
			if ( !ent->inuse ) {
				G_Printf("entity was removed while using targets\n");
				return;
			}
		}
	}

	if (ent->target2) {
		t = NULL;
		while ( (t = G_Find (t, FOFS(targetname), ent->target2)) != NULL ) {
			if ( t == ent ) {
				G_Printf( "WARNING: Entity %s at %s targets itself.\n", ent->classname, vtos(ent->s.origin) );
			} else {
				G_SetEntityLinked( t, ent->spawnflags );
			}
			if ( !ent->inuse ) {
				G_Printf("entity was removed while using targets\n");
				return;
			}
		}

		t = NULL;
		while ( (t = G_Find (t, FOFS(targetname2), ent->target2)) != NULL ) {
			if ( t == ent ) {
				G_Printf( "WARNING: Entity %s at %s targets itself.\n", ent->classname, vtos(ent->s.origin) );
			} else {
				G_SetEntityLinked( t, ent->spawnflags );
			}
			if ( !ent->inuse ) {
				G_Printf("entity was removed while using targets\n");
				return;
			}
		}
	}
}

/*
==============================
G_RemoveBotsForBotspawn

Called by G_RemoveBotsForTarget. Removes all 
bots that were spawned by the specified target_botspawn

==============================
*/
void G_RemoveBotsForBotspawn( gentity_t *self, qboolean kill, qboolean gib ) {
	gentity_t *ent;
	int i;
	
	if ( strcmp(self->classname, "target_botspawn") )
		return;

	//iterate through clients
	for (i = 0; i < MAX_CLIENTS; i++) {
		ent = &g_entities[i];
		if ( ent->client && ent->parent == self )
		{
			vec3_t dir;
			dir[0] = 0;
			dir[1] = 0;
			dir[2] = 0;
			if ( gib ) {
				Cmd_Kill_f( ent );
			}
			else if ( kill ) {
				ent->client->ps.stats[STAT_HEALTH] = ent->health = 0;
				player_die (ent, ent, ent, ent->client->ps.stats[STAT_HEALTH], MOD_FALLING);
			}
			else 
				DropClientSilently( ent->client->ps.clientNum );
		}
	}
}

/*
==============================
G_RemoveBotsForTarget

Search for targetname(2) in all target_botspawn entities that
match ent.target(2) and remove bots spawned by that botspawn.

ent: a target_botremove entity
kill: when true, bot will receive damage equal to its health, effectively killing it.
gib: when true, bot will receive 999 damage, effectively gibbing it. Will overrule 'kill'.
==============================
*/

void G_RemoveBotsForTarget( gentity_t *ent, qboolean kill, qboolean gib ) {
	gentity_t		*t;
	
	if ( !ent ) {
		return;
	}

	// ent->target
	if ( ent->target ) {

		//find all entities with matching targetname
		t = NULL;
		while ( (t = G_Find (t, FOFS(targetname), ent->target)) != NULL ) {
			if ( !strcmp(t->classname, "target_botspawn") ) {
				G_RemoveBotsForBotspawn( t, kill, gib );
			}
			if ( !ent->inuse ) {
				G_Printf("entity was removed while finding targets\n");
				return;
			}
		}

		//find all entities with matching targetname2
		t = NULL;
		while ( (t = G_Find (t, FOFS(targetname2), ent->target)) != NULL ) {
			if ( !strcmp(t->classname, "target_botspawn") ) {
				G_RemoveBotsForBotspawn( t, kill, gib );
			}
			if ( !ent->inuse ) {
				G_Printf("entity was removed while finding targets\n");
				return;
			}
		}
	}

	// use ent->target2
	if ( ent->target2 ) {
		
		//find all entities with matching targetname
		t = NULL;
		while ( (t = G_Find (t, FOFS(targetname), ent->target2)) != NULL ) {
			if ( !strcmp(t->classname, "target_botspawn") ) {
				G_RemoveBotsForBotspawn( t, kill, gib );
			}
			if ( !ent->inuse ) {
				G_Printf("entity was removed while finding targets\n");
				return;
			}
		}

		//find all entities with matching targetname2
		t = NULL;
		while ( (t = G_Find (t, FOFS(targetname2), ent->target2)) != NULL ) {
			if ( !strcmp(t->classname, "target_botspawn") ) {
				G_RemoveBotsForBotspawn( t, kill, gib );
			}
			if ( !ent->inuse ) {
				G_Printf("entity was removed while finding targets\n");
				return;
			}
		}
	}
}

/*
==============================
G_UseTriggerDeathEntities

"died" should be set to the entity that died.
"attacker" is the entity that is responsible for the death.

Search for all trigger_death entities and fire them
==============================
*/
void G_UseTriggerFragAndDeathEntities ( gentity_t *died, gentity_t *attacker ) {
	gentity_t		*t;

	//fire trigger_frag entities if the attacker was a human player
	if ( attacker->client ) {
		t = NULL;
		while ( ( t = G_Find( t, FOFS(classname), "trigger_frag" ) ) != NULL ) {
			if ( t->use )
				t->use( t, died, attacker );
		}
	}

	//fire trigger_death entities
	t = NULL;
	while ( ( t = G_Find( t, FOFS(classname), "trigger_death" ) ) != NULL ) {
		if ( t->use )
			t->use( t, attacker, died );
	}
}

/*
=============
TempVector

This is just a convenience function
for making temporary vectors for function calls
=============
*/
float	*tv( float x, float y, float z ) {
	static	int		index;
	static	vec3_t	vecs[8];
	float	*v;

	// use an array so that multiple tempvectors won't collide
	// for a while
	v = vecs[index];
	index = (index + 1)&7;

	v[0] = x;
	v[1] = y;
	v[2] = z;

	return v;
}


/*
=============
VectorToString

This is just a convenience function
for printing vectors
=============
*/
char	*vtos( const vec3_t v ) {
	static	int		index;
	static	char	str[8][32];
	char	*s;

	// use an array so that multiple vtos won't collide
	s = str[index];
	index = (index + 1)&7;

	Com_sprintf (s, 32, "(%i %i %i)", (int)v[0], (int)v[1], (int)v[2]);

	return s;
}


/*
===============
G_SetMovedir

The editor only specifies a single value for angles (yaw),
but we have special constants to generate an up or down direction.
Angles will be cleared, because it is being used to represent a direction
instead of an orientation.
===============
*/
void G_SetMovedir( vec3_t angles, vec3_t movedir ) {
	static vec3_t VEC_UP		= {0, -1, 0};
	static vec3_t MOVEDIR_UP	= {0, 0, 1};
	static vec3_t VEC_DOWN		= {0, -2, 0};
	static vec3_t MOVEDIR_DOWN	= {0, 0, -1};

	if ( VectorCompare (angles, VEC_UP) ) {
		VectorCopy (MOVEDIR_UP, movedir);
	} else if ( VectorCompare (angles, VEC_DOWN) ) {
		VectorCopy (MOVEDIR_DOWN, movedir);
	} else {
		AngleVectors (angles, movedir, NULL, NULL);
	}
	VectorClear( angles );
}


float vectoyaw( const vec3_t vec ) {
	float	yaw;
	
	if (vec[YAW] == 0 && vec[PITCH] == 0) {
		yaw = 0;
	} else {
		if (vec[PITCH]) {
			yaw = ( atan2( vec[YAW], vec[PITCH]) * 180 / M_PI );
		} else if (vec[YAW] > 0) {
			yaw = 90;
		} else {
			yaw = 270;
		}
		if (yaw < 0) {
			yaw += 360;
		}
	}

	return yaw;
}


void G_InitGentity( gentity_t *e ) {
	e->inuse = qtrue;
	e->classname = "noclass";
	e->s.number = e - g_entities;
	e->r.ownerNum = ENTITYNUM_NONE;
}

/*
=================
G_Spawn

Either finds a free entity, or allocates a new one.

  The slots from 0 to MAX_CLIENTS-1 are always reserved for clients, and will
never be used by anything else.

Try to avoid reusing an entity that was recently freed, because it
can cause the client to think the entity morphed into something else
instead of being removed and recreated, which can cause interpolated
angles and bad trails.
=================
*/
gentity_t *G_Spawn( void ) {
	int			i, force;
	gentity_t	*e;

	e = NULL;	// shut up warning
	i = 0;		// shut up warning
	for ( force = 0 ; force < 2 ; force++ ) {
		// if we go through all entities and can't find one to free,
		// override the normal minimum times before use
		e = &g_entities[MAX_CLIENTS];
		for ( i = MAX_CLIENTS ; i<level.num_entities ; i++, e++) {
			if ( e->inuse ) {
				continue;
			}

			// the first couple seconds of server time can involve a lot of
			// freeing and allocating, so relax the replacement policy
			if ( !force && e->freetime > level.startTime + 2000 && level.time - e->freetime < 1000 ) {
				continue;
			}

			// reuse this slot
			G_InitGentity( e );
			return e;
		}
		if ( i != MAX_GENTITIES ) {
			break;
		}
	}
	if ( i == ENTITYNUM_MAX_NORMAL ) {
		for (i = 0; i < MAX_GENTITIES; i++) {
			G_Printf("%4i: %s\n", i, g_entities[i].classname);
		}
		G_Error( "G_Spawn: no free entities" );
	}
	
	// open up a new slot
	level.num_entities++;

	// let the server system know that there are more entities
	trap_LocateGameData( level.gentities, level.num_entities, sizeof( gentity_t ), 
		&level.clients[0].ps, sizeof( level.clients[0] ) );

	G_InitGentity( e );
	return e;
}

/*
=================
G_EntitiesFree
=================
*/
qboolean G_EntitiesFree( void ) {
	int			i;
	gentity_t	*e;

	e = &g_entities[MAX_CLIENTS];
	for ( i = MAX_CLIENTS; i < level.num_entities; i++, e++) {
		if ( e->inuse ) {
			continue;
		}
		// slot available
		return qtrue;
	}
	return qfalse;
}


/*
=================
G_FreeEntity

Marks the entity as free
=================
*/
void G_FreeEntity( gentity_t *ed ) {
	trap_UnlinkEntity (ed);		// unlink from world

	if ( ed->neverFree ) {
		return;
	}

	memset (ed, 0, sizeof(*ed));
	ed->classname = "freed";
	ed->freetime = level.time;
	ed->inuse = qfalse;
}

/*
=================
G_TempEntity

Spawns an event entity that will be auto-removed
The origin will be snapped to save net bandwidth, so care
must be taken if the origin is right on a surface (snap towards start vector first)
=================
*/
gentity_t *G_TempEntity( vec3_t origin, int event ) {
	gentity_t		*e;
	vec3_t		snapped;

	e = G_Spawn();
	e->s.eType = ET_EVENTS + event;

	e->classname = "tempEntity";
	e->eventTime = level.time;
	e->freeAfterEvent = qtrue;

	VectorCopy( origin, snapped );
	SnapVector( snapped );		// save network bandwidth
	G_SetOrigin( e, snapped );

	// find cluster for PVS
	trap_LinkEntity( e );

	return e;
}



/*
==============================================================================

Kill box

==============================================================================
*/

/*
=================
G_KillBox

Kills all entities that would touch the proposed new positioning
of ent.  Ent should be unlinked before calling this!
=================
*/
void G_KillBox (gentity_t *ent) {
	int			i, num;
	int			touch[MAX_GENTITIES];
	gentity_t	*hit;
	vec3_t		mins, maxs;

	VectorAdd( ent->client->ps.origin, ent->r.mins, mins );
	VectorAdd( ent->client->ps.origin, ent->r.maxs, maxs );
	num = trap_EntitiesInBox( mins, maxs, touch, MAX_GENTITIES );

	for (i=0 ; i<num ; i++) {
		hit = &g_entities[touch[i]];
		if ( !hit->client ) {
			continue;
		}

		// nail it
		G_Damage ( hit, ent, ent, NULL, NULL,
			100000, DAMAGE_NO_PROTECTION, MOD_TELEFRAG);
	}

}

//==============================================================================

/*
===============
G_AddPredictableEvent

Use for non-pmove events that would also be predicted on the
client side: jumppads and item pickups
Adds an event+parm and twiddles the event counter
===============
*/
void G_AddPredictableEvent( gentity_t *ent, int event, int eventParm ) {
	if ( !ent->client ) {
		return;
	}
	BG_AddPredictableEventToPlayerstate( event, eventParm, &ent->client->ps );
}


/*
===============
G_AddEvent

Adds an event+parm and twiddles the event counter
===============
*/
void G_AddEvent( gentity_t *ent, int event, int eventParm ) {
	int		bits;

	if ( !event ) {
		G_Printf( "G_AddEvent: zero event added for entity %i\n", ent->s.number );
		return;
	}

	// clients need to add the event in playerState_t instead of entityState_t
	if ( ent->client ) {
		bits = ent->client->ps.externalEvent & EV_EVENT_BITS;
		bits = ( bits + EV_EVENT_BIT1 ) & EV_EVENT_BITS;
		ent->client->ps.externalEvent = event | bits;
		ent->client->ps.externalEventParm = eventParm;
		ent->client->ps.externalEventTime = level.time;
	} else {
		bits = ent->s.event & EV_EVENT_BITS;
		bits = ( bits + EV_EVENT_BIT1 ) & EV_EVENT_BITS;
		ent->s.event = event | bits;
		ent->s.eventParm = eventParm;
	}
	ent->eventTime = level.time;
}


/*
=============
G_Sound
=============
*/
void G_Sound( gentity_t *ent, int channel, int soundIndex ) {
	gentity_t	*te;

	te = G_TempEntity( ent->r.currentOrigin, EV_GENERAL_SOUND );
	te->s.eventParm = soundIndex;
}


//==============================================================================


/*
================
G_SetOrigin

Sets the pos trajectory for a fixed position
================
*/
void G_SetOrigin( gentity_t *ent, vec3_t origin ) {
	VectorCopy( origin, ent->s.pos.trBase );
	ent->s.pos.trType = TR_STATIONARY;
	ent->s.pos.trTime = 0;
	ent->s.pos.trDuration = 0;
	VectorClear( ent->s.pos.trDelta );

	VectorCopy( origin, ent->r.currentOrigin );
}

/*
================
DebugLine

  debug polygons only work when running a local game
  with r_debugSurface set to 2
================
*/
int DebugLine(vec3_t start, vec3_t end, int color) {
	vec3_t points[4], dir, cross, up = {0, 0, 1};
	float dot;

	VectorCopy(start, points[0]);
	VectorCopy(start, points[1]);
	//points[1][2] -= 2;
	VectorCopy(end, points[2]);
	//points[2][2] -= 2;
	VectorCopy(end, points[3]);


	VectorSubtract(end, start, dir);
	VectorNormalize(dir);
	dot = DotProduct(dir, up);
	if (dot > 0.99 || dot < -0.99) VectorSet(cross, 1, 0, 0);
	else CrossProduct(dir, up, cross);

	VectorNormalize(cross);

	VectorMA(points[0], 2, cross, points[0]);
	VectorMA(points[1], -2, cross, points[1]);
	VectorMA(points[2], -2, cross, points[2]);
	VectorMA(points[3], 2, cross, points[3]);

	return trap_DebugPolygonCreate(color, 4, points);
}

/*
==================
IsBot
==================
*/
qboolean IsBot( gentity_t *self ) {
	//return qtrue if client is a bot
	return (self->r.svFlags & SVF_BOT);
}

qboolean IsClientBot( gclient_t *client ) {
	gentity_t *ent;
	int i;

	for (i = 0; i < MAX_CLIENTS; i++) {
		ent = &g_entities[i];
		if ( ent->client->ps.clientNum == client->ps.clientNum )
			return IsBot( ent );
	}

	return qfalse;
}

/*
==================
PickDebrisType
returns a type of debris based on the passed spawnflags value
==================
*/
int PickDebrisType( int spawnflags ) {

	if ( spawnflags & SF_DEBRIS_LIGHT )
		return EV_EMIT_DEBRIS_LIGHT;
	
	if ( spawnflags & SF_DEBRIS_DARK )
		return EV_EMIT_DEBRIS_DARK;
	
	if ( spawnflags & SF_DEBRIS_LIGHT_LARGE )
		return EV_EMIT_DEBRIS_LIGHT_LARGE;

	if ( spawnflags & SF_DEBRIS_DARK_LARGE )
		return EV_EMIT_DEBRIS_DARK_LARGE;
	
	if ( spawnflags & SF_DEBRIS_WOOD )
		return EV_EMIT_DEBRIS_WOOD;

	if ( spawnflags & SF_DEBRIS_FLESH )
		return EV_EMIT_DEBRIS_FLESH;
	
	if ( spawnflags & SF_DEBRIS_GLASS )
		return EV_EMIT_DEBRIS_GLASS;
		
	if ( spawnflags & SF_DEBRIS_STONE )
		return EV_EMIT_DEBRIS_STONE;	

	//if no compatible spawnflags supplied, return EV_EMIT_DEBRIS_LIGHT
	return EV_EMIT_DEBRIS_LIGHT;
}

/*
==================
G_IsTeamGame
returns true if we're currently in a team gametype
==================
*/
qboolean G_IsTeamGame() {
	return qfalse;
}

/*
==================
G_GetScoringMapName
returns the bsp name of the map to which high scores should be written
==================
*/
char *G_GetScoringMapName() {
	char info[1024];
	char *result;
	int i;

	if ( strcmp( va("%s", level.scoreLevelName ), "" ) ) {
		return level.scoreLevelName;
	}

	trap_GetServerinfo(info, sizeof(info));
	result = Info_ValueForKey( info, "mapname" );

	for (i = 0; i < strlen(result); i++)
		result[i] = toupper(result[i]);

	return result;
}

/*
==================
G_LinkCameras
Links all cutscene cameras for a cutscene together (with the target_cutscene entity being the first entity in the chain)
Note that if a camera accidently targets two cameras, it links the first camera it finds.
==================
*/
void G_LinkCameras( gentity_t *ent ) {
	gentity_t	*t;
	gentity_t	*parent;
	qboolean	viewTargetFound;
	gentity_t	*viewTarget;
	gentity_t	*tmp;
	vec3_t		dir;
	int			usePlayerOriginAndViewangles = 0;
	
	// if no entity was passed or the passed entity is not a target_cutscene and not an info_camera, do not link
	if ( !ent || (strcmp(ent->classname, "target_cutscene") && strcmp(ent->classname, "info_camera")) )
		return;

	if (!strcmp(ent->classname, "target_cutscene")) {
		parent = ent;			//if entity is a target_cutscene, the nextTrain target should set the target_cutscene as its parent
		if (ent->spawnflags & 2) {
			usePlayerOriginAndViewangles = 1;	//only allow first camera in cutscene to start at player's origin/viewangles
		}
	}
	else
	{
		parent = ent->parent;	//if entity is an info_camera, the nextTrain target should set the info_camera's parent as parent

		
		//find the viewtarget for this camera (a target_position or info_notnull)
		viewTargetFound = qfalse;

		//note: if 'target' refers to a target_position and an info_camera and G_PickTarget picks the info_camera, 
		//the code assumes that 'target' is not used for viewangle targeting
		if ( ent->target ) {
			tmp = G_PickTarget( ent->target );	
			if ( strcmp( tmp->classname, "info_camera" ) ) {
				viewTarget = tmp;
				viewTargetFound = qtrue;
			}
		}
		
		//note: if 'target2' refers to a target_position and an info_camera and G_PickTarget picks the info_camera, 
		//the code assumes that 'target2' is not used for viewangle targeting
		if ( ent->target2 ) {
			tmp = G_PickTarget( ent->target2 );
			if ( strcmp( tmp->classname, "info_camera" ) ) {
				viewTarget = tmp;
				viewTargetFound = qtrue;
			}
		}

		if ( viewTargetFound ) {
			VectorSubtract( viewTarget->s.origin, ent->s.origin, dir );
			vectoangles( dir, ent->s.angles );
		}

		//camera debugging
		if ( g_debugCameras.integer ) {
			G_Printf("----g_debugCameras----\n cutscene: %i\n origin (XYZ): %s\n angles (PYR): %s\n wait: %f\n pan: %i\n target: %s\n target2: %s\n targetname: %s\n targetname2: %s\n", 
				parent->s.number, vtos(ent->s.origin), vtos(ent->s.angles), ent->wait, (ent->spawnflags & 1), ent->target, ent->target2, ent->targetname, ent->targetname2);
		}
	}

	// ent->target
	if ( ent->target ) {

		//find all entities with matching targetname
		t = NULL;
		while ( (t = G_Find (t, FOFS(targetname), ent->target)) != NULL ) {
			if ( t == ent ) {
				G_Printf( "WARNING: Entity %s at %s targets itself.\n", ent->classname, vtos(ent->s.origin) );
			} else if ( !strcmp(t->classname, "info_camera") ) {
				ent->nextTrain = t;
				t->parent = parent;
				if (usePlayerOriginAndViewangles) {
					t->armor = 1;	//abuse the "armor" property to tell this camera it needs to use the player's origin and viewangles
				}
				G_LinkCameras( t );
				return;
			}
			if ( !ent->inuse ) {
				G_Printf("entity was removed while finding targets\n");
				return;
			}
		}

		//find all entities with matching targetname2
		t = NULL;
		while ( (t = G_Find (t, FOFS(targetname2), ent->target)) != NULL ) {
			if ( t == ent ) {
				G_Printf( "WARNING: Entity %s at %s targets itself.\n", ent->classname, vtos(ent->s.origin) );
			} else if ( !strcmp(t->classname, "info_camera") ) {
				ent->nextTrain = t;
				t->parent = parent;
				if (usePlayerOriginAndViewangles) {
					t->armor = 1;	//abuse the "armor" property to tell this camera it needs to use the player's origin and viewangles
				}
				G_LinkCameras( t );
				return;
			}
			if ( !ent->inuse ) {
				G_Printf("entity was removed while finding targets\n");
				return;
			}
		}
	}

	// ent->target2
	if ( ent->target2 ) {
		
		//find all entities with matching targetname
		t = NULL;
		while ( (t = G_Find (t, FOFS(targetname), ent->target2)) != NULL ) {
			if ( t == ent ) {
				G_Printf( "WARNING: Entity %s at %s targets itself.\n", ent->classname, vtos(ent->s.origin) );
			} else if ( !strcmp(t->classname, "info_camera") ) {
				ent->nextTrain = t;
				t->parent = parent;
				if (usePlayerOriginAndViewangles) {
					t->armor = 1;	//abuse the "armor" property to tell this camera it needs to use the player's origin and viewangles
				}
				G_LinkCameras( t );
				return;
			}
			if ( !ent->inuse ) {
				G_Printf("entity was removed while finding targets\n");
				return;
			}
		}

		//find all entities with matching targetname2
		t = NULL;
		while ( (t = G_Find (t, FOFS(targetname2), ent->target2)) != NULL ) {
			if ( t == ent ) {
				G_Printf( "WARNING: Entity %s at %s targets itself.\n", ent->classname, vtos(ent->s.origin) );
			} else if ( !strcmp(t->classname, "info_camera") ) {
				ent->nextTrain = t;
				t->parent = parent;
				if (usePlayerOriginAndViewangles) {
					t->armor = 1;	//abuse the "armor" property to tell this camera it needs to use the player's origin and viewangles
				}
				G_LinkCameras( t );
				return;
			}
			if ( !ent->inuse ) {
				G_Printf("entity was removed while targeting targets\n");
				return;
			}
		}
	}
}


/*
==================
G_Fade
Tells clients to initiate a fade effect
==================
*/
void G_Fade( float duration, vec4_t startColor, vec4_t endColor ) {
	trap_SendServerCommand( -1, 
		va(
			"fade \"%f\" \"%f\" \"%f\" \"%f\" \"%f\" \"%f\" \"%f\" \"%f\" \"%f\"", 
			duration, startColor[0], startColor[1], startColor[2], startColor[3], endColor[0], endColor[1], endColor[2], endColor[3]
		)
	);
}

/*
==================
G_FadeOut
Fades out to black
==================
*/
void G_FadeOut( float duration ) {
	trap_SendServerCommand( -1, va("fade \"%f\" \"0\" \"0\" \"0\" \"0\" \"0\" \"0\" \"0\" \"1\"", duration) );
}

/*
==================
G_FadeIn
Fades in from black
==================
*/
void G_FadeIn( float duration ) {
	trap_SendServerCommand( -1, va("fade \"%f\" \"0\" \"0\" \"0\" \"1\" \"0\" \"0\" \"0\" \"0\"", duration) );
}


/*
==================
G_CalculatePlayerScore
Wrapper around COM_CalculatePlayerScore. This method calculates data that is required by COM_CalculatePlayerScore and returns
the result of the COM_CalculatePlayerScore function.
==================
*/
playerscore_t G_CalculatePlayerScore( gentity_t *ent ) {
	float skill;
	int accuracy;

	//determine accuracy
	if ( ent->client->accuracy_shots > 0 )
		accuracy = ((float)ent->client->accuracy_hits / (float)ent->client->accuracy_shots) * 100;
	else
		accuracy = 0;

	// get skill
	skill = trap_Cvar_VariableValue( "g_spskill" );

	return COM_CalculatePlayerScore( ent->client->ps.persistant, accuracy, (int)skill);
}
