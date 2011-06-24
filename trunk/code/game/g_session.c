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

	s = va("%i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %s %i", 
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
		client->sess.scoreLevelName,
		client->sess.secrets
		);

	var = va( "session%i", client - level.clients );

	trap_Cvar_Set( var, s );
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

	// bk001205 - format
	int teamLeader;
	int spectatorState;
	int sessionTeam;

	var = va( "session%i", client - level.clients );
	trap_Cvar_VariableStringBuffer( var, s, sizeof(s) );

	sscanf( s, "%i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %s %i",
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
		&client->sess.scoreLevelName,
		&client->sess.secrets
		);

	// bk001205 - format issues
	client->sess.sessionTeam = (team_t)sessionTeam;
	client->sess.spectatorState = (spectatorState_t)spectatorState;
	client->sess.teamLeader = (qboolean)teamLeader;
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
			BroadcastTeamChange( client, -1 );
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
			switch ( g_gametype.integer ) {
			default:
			case GT_FFA:
			case GT_ENTITYPLUS:
				if ( g_maxGameClients.integer > 0 && 
					level.numNonSpectatorClients >= g_maxGameClients.integer ) {
					sess->sessionTeam = TEAM_SPECTATOR;
				} else {
					sess->sessionTeam = TEAM_FREE;
				}
				break;
			case GT_TOURNAMENT:
				// if the game is full, go into a waiting mode
				if ( level.numNonSpectatorClients >= 2 ) {
					sess->sessionTeam = TEAM_SPECTATOR;
				} else {
					sess->sessionTeam = TEAM_FREE;
				}
				break;
			}
		}
	}

	sess->spectatorState = SPECTATOR_FREE;
	sess->spectatorTime = level.time;

	G_WriteClientSessionData( client );
}

/*
==================
G_UpdateSessionDataForMapChange

Updates session data prior to a map change that's forced by a target_mapchange entity
==================
*/
void G_UpdateSessionDataForMapChange( gclient_t *client ) {
	clientSession_t	*sess;
	char *mapname;

	sess = &client->sess;

	sess->sessionHealth = client->ps.stats[STAT_HEALTH];
	sess->sessionArmor = client->ps.stats[STAT_ARMOR];
	sess->sessionWeapons = client->ps.stats[STAT_WEAPONS];
	sess->sessionWeapon = client->ps.weapon;
	sess->sessionAmmoMG = client->ps.ammo[WP_MACHINEGUN];
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
	sess->secrets = client->ps.persistant[PERS_SECRETS];

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
	strcpy(sess->scoreLevelName, "" );
}

/*
==================
G_InitWorldSession

==================
*/
void G_InitWorldSession( void ) {
	char	s[MAX_STRING_CHARS];
	int			gt;

	trap_Cvar_VariableStringBuffer( "session", s, sizeof(s) );
	gt = atoi( s );
	
	// if the gametype changed since the last session, don't use any
	// client sessions
	if ( g_gametype.integer != gt ) {
		level.newSession = qtrue;
		G_Printf( "Gametype changed, clearing session data.\n" );
	}
}

/*
==================
G_WriteSessionData

==================
*/
void G_WriteSessionData( void ) {
	int		i;

	trap_Cvar_Set( "session", va("%i", g_gametype.integer) );

	for ( i = 0 ; i < level.maxclients ; i++ ) {
		if ( level.clients[i].pers.connected == CON_CONNECTED ) {
			G_WriteClientSessionData( &level.clients[i] );
		}
	}
}
