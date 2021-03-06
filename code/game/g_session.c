// Copyright (C) 1999-2000 Id Software, Inc.
//
#include "g_local.h"


/*
=======================================================================

  SESSION DATA

Session data is the only data that stays persistant across level loads
and tournament restarts.
=======================================================================
*/

/*
================
G_WriteClientSessionData

Called on game shutdown
================
*/
void G_WriteClientSessionData( gclient_t *client ) {
	const char	*s;
	const char	*var;
	const char	*var2;

	s = va("%i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i", 
		client->sess.sessionTeam,
		client->sess.spectatorTime,
		client->sess.spectatorState,
		client->sess.spectatorClient,
		client->sess.wins,
		client->sess.losses,
		client->sess.teamLeader,
		client->sess.sessionHealth,
		client->sess.sessionArmor,
		client->sess.sessionWeapons,
		client->sess.sessionWeapon,
		client->sess.sessionAmmoMG,
		client->sess.sessionAmmoSG,
		client->sess.sessionAmmoGL,
		client->sess.sessionAmmoRL,
		client->sess.sessionAmmoLG,
		client->sess.sessionAmmoRG,
		client->sess.sessionAmmoPG,
		client->sess.sessionAmmoBFG,
		client->sess.sessionHoldable,
		client->sess.carnageScore,
		client->sess.deaths,
		client->sess.secrets,
		client->sess.accuracyShots,
		client->sess.accuracyHits
		);

	var = va( "session%i", client - level.clients );
	trap_Cvar_Set( var, s );

	//set score level name
	var2 = va ( "session%i_lvl", client - level.clients );
	trap_Cvar_Set( var2, client->sess.scoreLevelName );
}

/*
================
G_ReadSessionData

Called on a reconnect
================
*/
void G_ReadSessionData( gclient_t *client ) {
	char	s[MAX_STRING_CHARS];
	const char	*var;
	const char	*var2;

	// bk001205 - format
	int teamLeader;
	int spectatorState;
	int sessionTeam;

	var = va( "session%i", client - level.clients );
	trap_Cvar_VariableStringBuffer( var, s, sizeof(s) );

	sscanf( s, "%i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i",
		&sessionTeam,                 // bk010221 - format
		&client->sess.spectatorTime,
		&spectatorState,              // bk010221 - format
		&client->sess.spectatorClient,
		&client->sess.wins,
		&client->sess.losses,
		&teamLeader,                   // bk010221 - format
		&client->sess.sessionHealth,
		&client->sess.sessionArmor,
		&client->sess.sessionWeapons,
		&client->sess.sessionWeapon,
		&client->sess.sessionAmmoMG,
		&client->sess.sessionAmmoSG,
		&client->sess.sessionAmmoGL,
		&client->sess.sessionAmmoRL,
		&client->sess.sessionAmmoLG,
		&client->sess.sessionAmmoRG,
		&client->sess.sessionAmmoPG,
		&client->sess.sessionAmmoBFG,
		&client->sess.sessionHoldable,
		&client->sess.carnageScore,
		&client->sess.deaths,
		&client->sess.secrets,
		&client->sess.accuracyShots,
		&client->sess.accuracyHits
		);

	// bk001205 - format issues
	client->sess.sessionTeam = (team_t)sessionTeam;
	client->sess.spectatorState = (spectatorState_t)spectatorState;
	client->sess.teamLeader = (qboolean)teamLeader;

	// read score level name
	var2 = va ( "session%i_lvl", client - level.clients );
	trap_Cvar_VariableStringBuffer( var2, client->sess.scoreLevelName, sizeof(client->sess.scoreLevelName) );
}


/*
================
G_InitSessionData

Called on a first-time connect
================
*/
void G_InitSessionData( gclient_t *client, char *userinfo ) {
	clientSession_t	*sess;
	const char		*value;

	sess = &client->sess;

	// initial team determination
	if ( G_IsTeamGame() ) {
		if ( g_teamAutoJoin.integer ) {
			sess->sessionTeam = PickTeam( -1 );
		} else {
			// always spawn as spectator in team games
			sess->sessionTeam = TEAM_SPECTATOR;	
		}
	} else {
		value = Info_ValueForKey( userinfo, "team" );
		if ( value[0] == 's' ) {
			// a willing spectator, not a waiting-in-line
			sess->sessionTeam = TEAM_SPECTATOR;
		} else {
			if ( g_maxGameClients.integer > 0 && level.numNonSpectatorClients >= g_maxGameClients.integer ) {
				sess->sessionTeam = TEAM_SPECTATOR;
			} else {
				sess->sessionTeam = TEAM_FREE;
			}
		}
	}

	sess->spectatorState = SPECTATOR_FREE;
	sess->spectatorTime = level.time;

	G_WriteClientSessionData( client );
}

/*
==================
G_UpdateGlobalSessionDataForMapChange

Updates session data prior to a map change that's forced by a target_mapchange entity
==================
*/
void G_UpdateGlobalSessionDataForMapChange() {
	char	buf[MAX_INFO_STRING];

	trap_GetConfigstring(CS_TARGET_VARIABLE, buf, sizeof(buf));

	if ( !buf || strlen(buf) == 0)
		strcpy(buf, "-");

	trap_Cvar_Set( "epsession", va("%s", buf) );
}

/*
==================
G_UpdateClientSessionDataForMapChange

Updates session data for a client prior to a map change that's forced by a target_mapchange entity
==================
*/
void G_UpdateClientSessionDataForMapChange( gclient_t *client ) {
	clientSession_t	*sess;
	char *mapname;
	int secretFound, secretCount;

	sess = &client->sess;

	sess->sessionHealth = client->ps.stats[STAT_HEALTH];
	sess->sessionArmor = client->ps.stats[STAT_ARMOR];
	if ( client->ps.stats[STAT_WEAPONS] )
		sess->sessionWeapons = client->ps.stats[STAT_WEAPONS];
	else
		sess->sessionWeapons = -1;		//-1 means no weapons
	sess->sessionWeapon = client->ps.weapon;
	if ( client->ps.ammo[WP_MACHINEGUN] )
		sess->sessionAmmoMG = client->ps.ammo[WP_MACHINEGUN];
	else
		sess->sessionAmmoMG = -1;		//-1 means no ammo for machinegun, to overrule the spawning with 100 ammo
	sess->sessionAmmoSG = client->ps.ammo[WP_SHOTGUN];
	sess->sessionAmmoGL = client->ps.ammo[WP_GRENADE_LAUNCHER];
	sess->sessionAmmoRL = client->ps.ammo[WP_ROCKET_LAUNCHER];
	sess->sessionAmmoLG = client->ps.ammo[WP_LIGHTNING];
	sess->sessionAmmoRG = client->ps.ammo[WP_RAILGUN];
	sess->sessionAmmoPG = client->ps.ammo[WP_PLASMAGUN];
	sess->sessionAmmoBFG = client->ps.ammo[WP_BFG];
	sess->sessionHoldable = client->ps.stats[STAT_HOLDABLE_ITEM];
	sess->carnageScore = client->ps.persistant[PERS_SCORE];
	sess->deaths = client->ps.persistant[PERS_KILLED];

	secretFound = (client->ps.persistant[PERS_SECRETS] & 0x7F);
	secretCount = ((client->ps.persistant[PERS_SECRETS] >> 7) & 0x7F) + level.secretCount;
	sess->secrets = secretFound + (secretCount << 7);

	sess->accuracyShots = client->accuracy_shots;
	sess->accuracyHits = client->accuracy_hits;

	strcpy(sess->scoreLevelName, G_GetScoringMapName());
}

/*
==================
G_ClearSessionDataForMapChange

Clears session data for map changes so that data does not persist through a hard map change (a map change not caused by target_mapchange) 
==================
*/
void G_ClearSessionDataForMapChange( gclient_t *client ) {
	clientSession_t	*sess;

	sess = &client->sess;

	sess->sessionHealth = 0;
	sess->sessionArmor = 0;
	sess->sessionWeapons = 0;
	sess->sessionWeapon = 0;
	sess->sessionAmmoMG = 0;
	sess->sessionAmmoSG = 0;
	sess->sessionAmmoGL = 0;
	sess->sessionAmmoRL = 0;
	sess->sessionAmmoLG = 0;
	sess->sessionAmmoRG = 0;
	sess->sessionAmmoPG = 0;
	sess->sessionAmmoBFG = 0;
	sess->sessionHoldable = 0;
	sess->carnageScore = 0;
	sess->deaths = 0;
	sess->secrets = 0;
	sess->accuracyShots = 0;
	sess->accuracyHits = 0;
	strcpy(sess->scoreLevelName, "" );
}

/*
==================
G_UpdateClientWithSessionData

Updates a client entity with the data that's stored in that client's session data
==================
*/
void G_UpdateClientWithSessionData( gentity_t *ent) {

	//give weapons
	if ( ent->client->sess.sessionWeapons > 0 )
		ent->client->ps.stats[STAT_WEAPONS] = ent->client->sess.sessionWeapons;
	else if ( ent->client->sess.sessionWeapons < 0 )
	{
		ent->client->ps.stats[STAT_WEAPONS] = 0;
		ent->client->ps.weapon = 0;
	}

	//give ammo
	if ( ent->client->sess.sessionAmmoMG == -1 ) 
		ent->client->ps.ammo[WP_MACHINEGUN] = 0;
	else if ( ent->client->sess.sessionAmmoMG )	//if MG ammo is 0, do nothing because player spawns with 100 ammo
		ent->client->ps.ammo[WP_MACHINEGUN] = ent->client->sess.sessionAmmoMG;
	if ( ent->client->sess.sessionAmmoSG ) ent->client->ps.ammo[WP_SHOTGUN] = ent->client->sess.sessionAmmoSG;
	if ( ent->client->sess.sessionAmmoGL ) ent->client->ps.ammo[WP_GRENADE_LAUNCHER] = ent->client->sess.sessionAmmoGL;
	if ( ent->client->sess.sessionAmmoRL ) ent->client->ps.ammo[WP_ROCKET_LAUNCHER] = ent->client->sess.sessionAmmoRL;
	if ( ent->client->sess.sessionAmmoLG ) ent->client->ps.ammo[WP_LIGHTNING] = ent->client->sess.sessionAmmoLG;
	if ( ent->client->sess.sessionAmmoRG ) ent->client->ps.ammo[WP_RAILGUN] = ent->client->sess.sessionAmmoRG;
	if ( ent->client->sess.sessionAmmoPG ) ent->client->ps.ammo[WP_PLASMAGUN] = ent->client->sess.sessionAmmoPG;
	if ( ent->client->sess.sessionAmmoBFG ) ent->client->ps.ammo[WP_BFG] = ent->client->sess.sessionAmmoBFG;

	//select weapon
	if ( ent->client->sess.sessionWeapon )
		ent->client->ps.weapon = ent->client->sess.sessionWeapon;

	//give holdables
	if ( ent->client->sess.sessionHoldable ) 
		ent->client->ps.stats[STAT_HOLDABLE_ITEM] = ent->client->sess.sessionHoldable;

	//give health
	if ( ent->client->sess.sessionHealth ) 
		ent->health = ent->client->ps.stats[STAT_HEALTH] = ent->client->sess.sessionHealth;

	//give armor
	if ( ent->client->sess.sessionArmor )
		ent->client->ps.stats[STAT_ARMOR] = ent->client->sess.sessionArmor;

	//set carnage score info
	if ( ent->client->sess.carnageScore )
		ent->client->ps.persistant[PERS_SCORE] = ent->client->sess.carnageScore;

	//set number of deaths
	if ( ent->client->sess.deaths )
		ent->client->ps.persistant[PERS_KILLED] = ent->client->sess.deaths;

	//set name of level to which scores should be attributed
	if ( strcmp( va("%s", ent->client->sess.scoreLevelName ), "0" ) ) {
		strcpy(level.scoreLevelName, ent->client->sess.scoreLevelName);
	}

	//set secrets
	if ( ent->client->sess.secrets )
		ent->client->ps.persistant[PERS_SECRETS] = ent->client->sess.secrets;

	//set accuracy
	if ( ent->client->sess.accuracyShots )
		ent->client->accuracy_shots = ent->client->sess.accuracyShots;
	
	if ( ent->client->sess.accuracyHits )
		ent->client->accuracy_hits = ent->client->sess.accuracyHits;

	
	// clear map change session data
	G_ClearSessionDataForMapChange( ent->client );
}

/*
==================
G_InitWorldSession

==================
*/
void G_InitWorldSession( void ) {
	char	s[MAX_STRING_CHARS];
	int		gt;
	char	buf[MAX_INFO_STRING];

	//restore session from vQ3 session data
	trap_Cvar_VariableStringBuffer( "session", s, sizeof(s) );
	gt = atoi( s );

	// if the gametype changed since the last session, don't use any client sessions
    if ( g_gametype.integer != gt ) {
            level.newSession = qtrue;
            G_Printf( "Gametype changed, clearing session data.\n" );
    }

	//restore session from additional ep session data
	trap_Cvar_VariableStringBuffer( "epsession", s, sizeof(s) );
	sscanf( s, "%s", &buf );

	//G_Printf("epsession: %s\n", s);

	trap_SetConfigstring( CS_TARGET_VARIABLE, buf );

	//clear epsession data so it only persists when it's set by target_mapchange
	trap_Cvar_Set( "epsession", "" );
}

/*
==================
G_WriteSessionData

==================
*/
void G_WriteSessionData( void ) {
        int             i;

        trap_Cvar_Set( "session", va("%i", g_gametype.integer) );

        for ( i = 0 ; i < level.maxclients ; i++ ) {
                if ( level.clients[i].pers.connected == CON_CONNECTED ) {
                        G_WriteClientSessionData( &level.clients[i] );
                }
        }
}
