// Copyright (C) 1999-2000 Id Software, Inc.
//
// cg_scoreboard -- draw the scoreboard on top of the game screen
#include "cg_local.h"


#define	SCOREBOARD_X		(0)

#define SB_HEADER			86
#define SB_TOP				(SB_HEADER+32)

// Where the status bar starts, so we don't overwrite it
#define SB_STATUSBAR		420

#define SB_NORMAL_HEIGHT	40
#define SB_INTER_HEIGHT		16 // interleaved height

#define SB_MAXCLIENTS_NORMAL  ((SB_STATUSBAR - SB_TOP) / SB_NORMAL_HEIGHT)
#define SB_MAXCLIENTS_INTER   ((SB_STATUSBAR - SB_TOP) / SB_INTER_HEIGHT - 1)

// Used when interleaved



#define SB_LEFT_BOTICON_X	(SCOREBOARD_X+0)
#define SB_LEFT_HEAD_X		(SCOREBOARD_X+32)
#define SB_RIGHT_BOTICON_X	(SCOREBOARD_X+64)
#define SB_RIGHT_HEAD_X		(SCOREBOARD_X+96)
// Normal
#define SB_BOTICON_X		(SCOREBOARD_X+32)
#define SB_HEAD_X			(SCOREBOARD_X+64)

#define SB_SCORELINE_X		112

#define SB_RATING_WIDTH	    (6 * BIGCHAR_WIDTH) // width 6
#define SB_SCORE_X			(SB_SCORELINE_X + BIGCHAR_WIDTH) // width 6
#define SB_RATING_X			(SB_SCORELINE_X + 6 * BIGCHAR_WIDTH) // width 6
#define SB_PING_X			(SB_SCORELINE_X + 12 * BIGCHAR_WIDTH + 8) // width 5
#define SB_TIME_X			(SB_SCORELINE_X + 17 * BIGCHAR_WIDTH + 8) // width 5
#define SB_NAME_X			(SB_SCORELINE_X + 22 * BIGCHAR_WIDTH) // width 15

// The new and improved score board
//
// In cases where the number of clients is high, the score board heads are interleaved
// here's the layout

//
//	0   32   80  112  144   240  320  400   <-- pixel position
//  bot head bot head score ping time name
//  
//  wins/losses are drawn on bot icon now

static qboolean localClient; // true if local client has been displayed

							 /*
=================
CG_DrawScoreboard
=================
*/
static void CG_DrawClientScore( int y, score_t *score, float *color, float fade, qboolean largeFormat ) {
	char	string[1024];
	vec3_t	headAngles;
	clientInfo_t	*ci;
	int iconx, headx;

	if ( score->client < 0 || score->client >= cgs.maxclients ) {
		Com_Printf( "Bad score->client: %i\n", score->client );
		return;
	}
	
	ci = &cgs.clientinfo[score->client];

	iconx = SB_BOTICON_X + (SB_RATING_WIDTH / 2);
	headx = SB_HEAD_X + (SB_RATING_WIDTH / 2);

	// draw the handicap or bot skill marker (unless player has flag)
	if ( ci->powerups & ( 1 << PW_NEUTRALFLAG ) ) {
		if( largeFormat ) {
			CG_DrawFlagModel( iconx, y - ( 32 - BIGCHAR_HEIGHT ) / 2, 32, 32, TEAM_FREE, qfalse );
		}
		else {
			CG_DrawFlagModel( iconx, y, 16, 16, TEAM_FREE, qfalse );
		}
	} else if ( ci->powerups & ( 1 << PW_REDFLAG ) ) {
		if( largeFormat ) {
			CG_DrawFlagModel( iconx, y - ( 32 - BIGCHAR_HEIGHT ) / 2, 32, 32, TEAM_RED, qfalse );
		}
		else {
			CG_DrawFlagModel( iconx, y, 16, 16, TEAM_RED, qfalse );
		}
	} else if ( ci->powerups & ( 1 << PW_BLUEFLAG ) ) {
		if( largeFormat ) {
			CG_DrawFlagModel( iconx, y - ( 32 - BIGCHAR_HEIGHT ) / 2, 32, 32, TEAM_BLUE, qfalse );
		}
		else {
			CG_DrawFlagModel( iconx, y, 16, 16, TEAM_BLUE, qfalse );
		}
	} else {
		if ( ci->botSkill > 0 && ci->botSkill <= 5 ) {
			if ( cg_drawIcons.integer ) {
				if( largeFormat ) {
					CG_DrawPic( iconx, y - ( 32 - BIGCHAR_HEIGHT ) / 2, 32, 32, cgs.media.botSkillShaders[ ci->botSkill - 1 ] );
				}
				else {
					CG_DrawPic( iconx, y, 16, 16, cgs.media.botSkillShaders[ ci->botSkill - 1 ] );
				}
			}
		} else if ( ci->handicap < 100 ) {
			Com_sprintf( string, sizeof( string ), "%i", ci->handicap );
			CG_DrawSmallStringColor( iconx, y, string, color );
		}
	}

	// draw the face
	VectorClear( headAngles );
	headAngles[YAW] = 180;
	if( largeFormat ) {
		CG_DrawHead( headx, y - ( ICON_SIZE - BIGCHAR_HEIGHT ) / 2, ICON_SIZE, ICON_SIZE, 
			score->client, headAngles );
	}
	else {
		CG_DrawHead( headx, y, 16, 16, score->client, headAngles );
	}

	// draw the score line
	if ( score->ping == -1 ) {
		Com_sprintf(string, sizeof(string),
			" connecting    %s", ci->name);
	} else if ( ci->team == TEAM_SPECTATOR ) {
		Com_sprintf(string, sizeof(string),
			" SPECT %3i %4i %s", score->ping, score->time, ci->name);
	} else {
		Com_sprintf(string, sizeof(string),
			"%5i %4i %4i %s", score->score, score->ping, score->time, ci->name);
	}

	// highlight your position
	if ( score->client == cg.snap->ps.clientNum ) {
		float	hcolor[4];
		int		rank;

		localClient = qtrue;

		if ( cg.snap->ps.persistant[PERS_TEAM] == TEAM_SPECTATOR 
			|| CG_IsTeamGame() ) {
			rank = -1;
		} else {
			rank = cg.snap->ps.persistant[PERS_RANK] & ~RANK_TIED_FLAG;
		}
		if ( rank == 0 ) {
			hcolor[0] = 0;
			hcolor[1] = 0;
			hcolor[2] = 0.7f;
		} else if ( rank == 1 ) {
			hcolor[0] = 0.7f;
			hcolor[1] = 0;
			hcolor[2] = 0;
		} else if ( rank == 2 ) {
			hcolor[0] = 0.7f;
			hcolor[1] = 0.7f;
			hcolor[2] = 0;
		} else {
			hcolor[0] = 0.7f;
			hcolor[1] = 0.7f;
			hcolor[2] = 0.7f;
		}

		hcolor[3] = fade * 0.7;
		CG_FillRect( SB_SCORELINE_X + BIGCHAR_WIDTH + (SB_RATING_WIDTH / 2), y, 
			640 - SB_SCORELINE_X - BIGCHAR_WIDTH, BIGCHAR_HEIGHT+1, hcolor );
	}

	CG_DrawBigString( SB_SCORELINE_X + (SB_RATING_WIDTH / 2), y, string, fade );

	// add the "ready" marker for intermission exiting
	if ( cg.snap->ps.stats[ STAT_CLIENTS_READY ] & ( 1 << score->client ) ) {
		CG_DrawBigStringColor( iconx, y, "READY", color );
	}
}

/*
=================
CG_TeamScoreboard
=================
*/
static int CG_TeamScoreboard( int y, team_t team, float fade, int maxClients, int lineHeight ) {
	int		i;
	score_t	*score;
	float	color[4];
	int		count;
	clientInfo_t	*ci;

	color[0] = color[1] = color[2] = 1.0;
	color[3] = fade;

	count = 0;
	for ( i = 0 ; i < cg.numScores && count < maxClients ; i++ ) {
		score = &cg.scores[i];
		ci = &cgs.clientinfo[ score->client ];

		if ( team != ci->team ) {
			continue;
		}

		CG_DrawClientScore( y + lineHeight * count, score, color, fade, lineHeight == SB_NORMAL_HEIGHT );

		count++;
	}

	return count;
}

/*
=================
CG_GetSkill

Gets the current g_spskill value
=================
*/
int CG_GetSkill( void ) {
	char skill[64];
	
	trap_Cvar_VariableStringBuffer( "g_spskill", skill, sizeof(skill) );
	return atoi(skill);
}

/*
=================
CG_GetAccuracy

Gets the current g_spskill value
=================
*/
int CG_GetAccuracy( void ) {
	int i;
	for ( i = 0 ; i < cg.numScores ; i++ ) {
		if ( cg.scores[i].client == cg.snap->ps.clientNum ) {
			return cg.scores[i].accuracy;
		}
	}

	return 0;
}

/*
=================
CG_DrawSinglePlayerIntermission

Draw the single player intermission screen
=================
*/
void CG_DrawSinglePlayerIntermission( void ) {
	vec4_t color;
	int i, y;
	int index;
	playerscore_t *scores;
	/*
	int carnageScore, accuracyScore, deathsScore, secretsScore, subtotalScore, skillScore, totalScore;
	int accuracy, deaths, secrets, secretsCount, skill;
	*/
	
	COM_CalculatePlayerScore( scores, cg.snap->ps.persistant, CG_GetAccuracy(), CG_GetSkill() );

	/*
	carnageScore = cg.snap->ps.persistant[PERS_SCORE];
	accuracy = CG_GetAccuracy();
	accuracyScore = COM_AccuracyToScore(accuracy, carnageScore);
	deaths = cg.snap->ps.persistant[PERS_KILLED];
	deathsScore = deaths * SCORE_DEATH;
	secrets = (cg.snap->ps.persistant[PERS_SECRETS] & 0x7F);
	secretsCount = ((cg.snap->ps.persistant[PERS_SECRETS] >> 7) & 0x7F);
	secretsScore = secrets * SCORE_SECRET;
	subtotalScore = carnageScore + deathsScore + secretsScore;
	skill = CG_GetSkill();
	skillScore = subtotalScore * (((skill - 1) * SCORE_SKILL));
	totalScore = COM_CalculateLevelScore( cg.snap->ps.persistant, accuracy, skill );
	*/
	
return;

	color[0] = 1;
	color[1] = 1;
	color[2] = 1;
	color[3] = 1;

	//carnage score
	y = 64;
	index = 1;
	if (cg.time < cg.intermissionTime + (SCOREB_TIME * index))
		CG_DrawStringExt( 64, y, "       Carnage :", color, qtrue, qtrue, BIGCHAR_WIDTH, BIGCHAR_HEIGHT, 0 );
	else {
		if (cg.scoreSoundsPlayed == index - 1) {
			trap_S_StartLocalSound( cgs.media.scoreShow, CHAN_LOCAL_SOUND );
			cg.scoreSoundsPlayed++;
		}
		CG_DrawStringExt( 64, y, va("       Carnage : %i", scores->carnageScore), color, qtrue, qtrue, BIGCHAR_WIDTH, BIGCHAR_HEIGHT, 0 );
	}
	
	//deaths score
	y += BIGCHAR_HEIGHT;
	index++;
	if (cg.time < cg.intermissionTime + (SCOREB_TIME * index))
		CG_DrawStringExt( 64, y, "        Deaths :", color, qtrue, qtrue, BIGCHAR_WIDTH, BIGCHAR_HEIGHT, 0 );
	else {
		if (cg.scoreSoundsPlayed == index - 1) {
			trap_S_StartLocalSound( cgs.media.scoreShow, CHAN_LOCAL_SOUND );
			cg.scoreSoundsPlayed++;
		}
		CG_DrawStringExt( 64, y, va("        Deaths : %i (%ix)", scores->deathsScore, scores->deaths), color, qtrue, qtrue, BIGCHAR_WIDTH, BIGCHAR_HEIGHT, 0 );
	}

	//secrets score
	y += BIGCHAR_HEIGHT;
	index++;
	if (cg.time < cg.intermissionTime + (SCOREB_TIME * index))
		CG_DrawStringExt( 64, y, "       Secrets :", color, qtrue, qtrue, BIGCHAR_WIDTH, BIGCHAR_HEIGHT, 0 );
	else {
		if (cg.scoreSoundsPlayed == index - 1) {
			trap_S_StartLocalSound( cgs.media.scoreShow, CHAN_LOCAL_SOUND );
			cg.scoreSoundsPlayed++;
		}
		CG_DrawStringExt( 64, y, va("       Secrets : %i (%i/%i)", scores->secretsScore, scores->secretsFound, scores->secretsCount), color, qtrue, qtrue, BIGCHAR_WIDTH, BIGCHAR_HEIGHT, 0 );		
	}

	//skill modifier
	y += BIGCHAR_HEIGHT;
	index++;
	if (cg.time < cg.intermissionTime + (SCOREB_TIME * index))
		CG_DrawStringExt( 64, y, "Skill modifier :", color, qtrue, qtrue, BIGCHAR_WIDTH, BIGCHAR_HEIGHT, 0 );
	else {
		if (cg.scoreSoundsPlayed == index - 1) {
			trap_S_StartLocalSound( cgs.media.scoreShow, CHAN_LOCAL_SOUND );
			cg.scoreSoundsPlayed++;
		}

		//CG_DrawStringExt( 64, y, va("Skill modifier : %1.1f", 1 + scores->skillModifier), color, qtrue, qtrue, BIGCHAR_WIDTH, BIGCHAR_HEIGHT, 0 );
	}

	//total score
	y += BIGCHAR_HEIGHT;
	index++;
	if (cg.time < cg.intermissionTime + (SCOREB_TIME * index) + SCOREB_TIME_LAST)	//wait slightly longer before showing final score
		CG_DrawStringExt( 64, y, "         TOTAL :", color, qtrue, qtrue, BIGCHAR_WIDTH, BIGCHAR_HEIGHT, 0 );
	else {
		if (cg.scoreSoundsPlayed == index - 1) {
			trap_S_StartLocalSound( cgs.media.finalScoreShow, CHAN_LOCAL_SOUND );
			cg.scoreSoundsPlayed++;
		}

		CG_DrawStringExt( 64, y, va("         TOTAL : %i", scores->totalScore), color, qtrue, qtrue, BIGCHAR_WIDTH, BIGCHAR_HEIGHT, 0 );
	}
}

/*
=================
CG_DrawSinglePlayerObjectives

Draw the single player objectives overlay
=================
*/
qboolean CG_DrawSinglePlayerObjectives( void ) {
	const char *p;
	const char *s;
	vec4_t color;
	vec4_t color_black;
	int i;
	int objlen;
	char lines[5][60];
	int spaceIndex, prevSpaceIndex = 0;
	int currentLine = 0;
	int lineIndex = 0;
	char c[2];
	qboolean tooLong = qfalse;	
	playerscore_t *scores;


	if ( !cg.showScores )
		return qfalse;


	cg.objectivesTime = 0;	//stop objectives notification from showing
	
	color[0] = 1;
	color[1] = 1;
	color[2] = 1;
	color[3] = 0.75;

	color_black[0] = 0;
	color_black[1] = 0;
	color_black[2] = 0;
	color_black[3] = 0.6;

	p = CG_ConfigString( CS_PRIMARYOBJECTIVE );
	s = CG_ConfigString( CS_SECONDARYOBJECTIVE );

	//draw objectives overlay
	CG_DrawPic( (SCREEN_WIDTH - 512) / 2, (SCREEN_HEIGHT - 256) / 2, 512, 256, cgs.media.objectivesOverlay );
	
	//draw primary objective
	objlen = strlen(p);

	
	for ( i = 0; i < objlen; i++) {
		
		c[0] = p[i];
		c[1] = '\0';

		if ( c[0] == ' ' ) {
			spaceIndex = i;
		}

		if (lineIndex == 60) {
			if (spaceIndex - prevSpaceIndex <= 0) {
				strcat(lines[currentLine-1], &p[prevSpaceIndex-1]);
				break;
			} else {
				Q_strncpyz(lines[currentLine], &p[prevSpaceIndex], (spaceIndex - prevSpaceIndex) + 1);
				CG_DrawSmallStringColor( 82, 146 + (SMALLCHAR_HEIGHT * currentLine), lines[currentLine], color_black);
				CG_DrawSmallStringColor( 80, 144 + (SMALLCHAR_HEIGHT * currentLine), lines[currentLine], color);
			}
			
			prevSpaceIndex = spaceIndex;
			prevSpaceIndex++;
			i = spaceIndex;
			lineIndex = -1;
			currentLine++;
			if (currentLine == 5)
			{
				tooLong = qtrue;
				break;
			}
			
		}
		lineIndex++;
		
	}

	if ( !tooLong ) {
		CG_DrawSmallStringColor( 82, 146 + (SMALLCHAR_HEIGHT * currentLine), va("%s", &p[prevSpaceIndex]), color_black);
		CG_DrawSmallStringColor( 80, 144 + (SMALLCHAR_HEIGHT * currentLine), va("%s", &p[prevSpaceIndex]), color);
	}


	//draw secondary objective
	spaceIndex = 0;
	prevSpaceIndex = 0;
	lineIndex = 0;
	currentLine = 0;
	tooLong = qfalse;

	objlen = strlen(s);

	for ( i = 0; i < objlen; i++) {
		c[0] = s[i];
		c[1] = '\0';

		if ( c[0] == ' ' ) {
			spaceIndex = i;
		}

		if (lineIndex == 60) {
			if (spaceIndex - prevSpaceIndex <= 0) {
				strcat(lines[currentLine-1], &s[prevSpaceIndex-1]);
				break;
			} else {
				Q_strncpyz(lines[currentLine], &s[prevSpaceIndex], (spaceIndex - prevSpaceIndex) + 1);
				CG_DrawSmallStringColor( 82, 266 + (SMALLCHAR_HEIGHT * currentLine), lines[currentLine], color_black);
				CG_DrawSmallStringColor( 80, 264 + (SMALLCHAR_HEIGHT * currentLine), lines[currentLine], color);
			}
			prevSpaceIndex = spaceIndex;
			prevSpaceIndex++;
			i = spaceIndex;
			lineIndex = -1;
			currentLine++;
			if (currentLine == 4) {
				tooLong = qtrue;
				break;
			}
		}
		lineIndex++;
	}

	if ( !tooLong ) {
		CG_DrawSmallStringColor( 82, 266 + (SMALLCHAR_HEIGHT * currentLine), va("%s", &s[prevSpaceIndex]), color_black);
		CG_DrawSmallStringColor( 80, 264 + (SMALLCHAR_HEIGHT * currentLine), va("%s", &s[prevSpaceIndex]), color);
	}

	//draw deaths counter
	color[0] = 1;
	color[1] = 0;
	color[2] = 0;

	i = strlen(va("%i", cg.snap->ps.persistant[PERS_KILLED]));
	CG_DrawBigStringColor( 208 - (i * BIGCHAR_WIDTH), 343, va("%i", cg.snap->ps.persistant[PERS_KILLED]), color );

	//draw level score
	COM_CalculatePlayerScore( scores, cg.snap->ps.persistant, CG_GetAccuracy(), CG_GetSkill() );
	i = strlen(va("%i", scores->totalScore));
	CG_DrawBigStringColor( 496 - (i * BIGCHAR_WIDTH), 343, va("%i", scores->totalScore), color);	

	if ( ++cg.deferredPlayerLoading > 10 ) {
		CG_LoadDeferredPlayers();
	}

	return qtrue;
}

/*
=================
CG_DrawScoreboard

Draw the normal in-game scoreboard
=================
*/
qboolean CG_DrawOldScoreboard( void ) {
	int		x, y, w, i, n1, n2;
	float	fade;
	float	*fadeColor;
	char	*s;
	int maxClients;
	int lineHeight;
	int topBorderSize, bottomBorderSize;

	// don't draw amuthing if the menu or console is up
	if ( cg_paused.integer ) {
		cg.deferredPlayerLoading = 0;
		return qfalse;
	}

	if ( cg.predictedPlayerState.pm_type == PM_INTERMISSION )
	{
		CG_DrawSinglePlayerIntermission();
		cg.deferredPlayerLoading = 0;
		return qfalse;
	}
	else 
	{
		return CG_DrawSinglePlayerObjectives();	//draw objectives screen instead of scores in SP.
	}
}

//================================================================================

/*
================
CG_CenterGiantLine
================
*/
static void CG_CenterGiantLine( float y, const char *string ) {
	float		x;
	vec4_t		color;

	color[0] = 1;
	color[1] = 1;
	color[2] = 1;
	color[3] = 1;

	x = 0.5 * ( 640 - GIANT_WIDTH * CG_DrawStrlen( string ) );

	CG_DrawStringExt( x, y, string, color, qtrue, qtrue, GIANT_WIDTH, GIANT_HEIGHT, 0 );
}

/*
=================
CG_DrawTourneyScoreboard

Draw the oversize scoreboard for tournements
=================
*/
void CG_DrawOldTourneyScoreboard( void ) {
	const char		*s;
	vec4_t			color;
	int				min, tens, ones;
	clientInfo_t	*ci;
	int				y;
	int				i;

	// request more scores regularly
	if ( cg.scoresRequestTime + 2000 < cg.time ) {
		cg.scoresRequestTime = cg.time;
		trap_SendClientCommand( "score" );
	}

	color[0] = 1;
	color[1] = 1;
	color[2] = 1;
	color[3] = 1;

	// draw the dialog background
	color[0] = color[1] = color[2] = 0;
	color[3] = 1;
	CG_FillRect( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, color );

	// print the mesage of the day
	s = CG_ConfigString( CS_MOTD );
	if ( !s[0] ) {
		s = "Scoreboard";
	}

	// print optional title
	CG_CenterGiantLine( 8, s );

	// print server time
	ones = cg.time / 1000;
	min = ones / 60;
	ones %= 60;
	tens = ones / 10;
	ones %= 10;
	s = va("%i:%i%i", min, tens, ones );

	CG_CenterGiantLine( 64, s );


	// print the two scores

	y = 160;
	if ( CG_IsTeamGame() ) {
		//
		// teamplay scoreboard
		//
		CG_DrawStringExt( 8, y, "Red Team", color, qtrue, qtrue, GIANT_WIDTH, GIANT_HEIGHT, 0 );
		s = va("%i", cg.teamScores[0] );
		CG_DrawStringExt( 632 - GIANT_WIDTH * strlen(s), y, s, color, qtrue, qtrue, GIANT_WIDTH, GIANT_HEIGHT, 0 );
		
		y += 64;

		CG_DrawStringExt( 8, y, "Blue Team", color, qtrue, qtrue, GIANT_WIDTH, GIANT_HEIGHT, 0 );
		s = va("%i", cg.teamScores[1] );
		CG_DrawStringExt( 632 - GIANT_WIDTH * strlen(s), y, s, color, qtrue, qtrue, GIANT_WIDTH, GIANT_HEIGHT, 0 );
	} else {
		//
		// free for all scoreboard
		//
		for ( i = 0 ; i < MAX_CLIENTS ; i++ ) {
			ci = &cgs.clientinfo[i];
			if ( !ci->infoValid ) {
				continue;
			}
			if ( ci->team != TEAM_FREE ) {
				continue;
			}

			CG_DrawStringExt( 8, y, ci->name, color, qtrue, qtrue, GIANT_WIDTH, GIANT_HEIGHT, 0 );
			s = va("%i", ci->score );
			CG_DrawStringExt( 632 - GIANT_WIDTH * strlen(s), y, s, color, qtrue, qtrue, GIANT_WIDTH, GIANT_HEIGHT, 0 );
			y += 64;
		}
	}


}
