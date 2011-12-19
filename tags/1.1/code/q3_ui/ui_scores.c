#include "ui_local.h"


#define ART_TABLE				"menu/art/table"
#define ART_BACK0				"menu/art/back_0"
#define ART_BACK1				"menu/art/back_1"

#define ID_BACK					99

typedef struct {
	menuframework_s		menu;

	menutext_s			banner;
	menutext_s			levelname;
	
	menutext_s			tableheader;
	menubitmap_s		table;
	menutext_s			scoretexts[SCOREBOARD_LENGTH];
	
	menuradiobutton_s	paintballmode;
	menuradiobutton_s	bigheadmode;
	menuradiobutton_s	machinegunonly;
	menuradiobutton_s	instagib;
	menuradiobutton_s	resetscoreafterdeath;

	menubitmap_s		back;
} scores_t;

static scores_t s_scores;
char	*levelname;

static void Scores_Event( void* ptr, int notification ) {
	if( notification != QM_ACTIVATED ) {
		return;
	}

	switch( ((menucommon_s*)ptr)->id ) {
		case ID_BACK:
			UI_PopMenu();
			break;
	}
}

void Scores_GenerateScoringTable( void ) {
	highscores_t	hs;
	int				i, n, ds;
	char			carnagePad[5][7];
	char			accuracyScorePad[5][5];
	char			accuracyPad[5][3];
	char			secretsScorePad[5][5];
	char			secretsFoundPad[5][3];
	char			secretsCountPad[5][3];
	char			deathsScorePad[5][6];
	char			deathsCountPad[5][2];
	char			skillScorePad[5][5];
	char			totalScorePad[5][6];

	hs = COM_LoadLevelScores( levelname );

	
	for ( i = 0; i < SCOREBOARD_LENGTH; i++ ) {
		//calculate paddings for carnage
		strcpy( carnagePad[i], "") ;
		n = 1000000;
		while ( n > 1 ) {
			if ( hs.highscores[i].carnageScore < n ) {
				strcat( carnagePad[i], " " );
				n = n / 10;
			} else
				break;
		}

		//calculate paddings for accuracy score
		strcpy( accuracyScorePad[i], "") ;
		n = 10000;
		while ( n > 1 ) {
			if ( hs.highscores[i].accuracyScore < n ) {
				strcat( accuracyScorePad[i], " " );
				n = n / 10;
			} else
				break;
		}

		//calculate paddings for accuracy percentage
		strcpy( accuracyPad[i], "") ;
		n = 100;
		while ( n > 1 ) {
			if ( hs.highscores[i].accuracy < n ) {
				strcat( accuracyPad[i], " " );
				n = n / 10;
			} else
				break;
		}

		//calculate paddings for secrets score
		strcpy( secretsScorePad[i], "") ;
		n = 1000;
		while ( n > 1 ) {
			if ( hs.highscores[i].secretsScore < n ) {
				strcat( secretsScorePad[i], " " );
				n = n / 10;
			} else
				break;
		}

		//calculate padding for secrets found
		strcpy( secretsFoundPad[i], "") ;
		n = 10;
		while ( n > 1 ) {
			if ( hs.highscores[i].secretsFound < n ) {
				strcat( secretsFoundPad[i], " " );
				n = n / 10;
			} else
				break;
		}

		//calculate padding for secrets count
		strcpy( secretsCountPad[i], "") ;
		n = 10;
		while ( n > 1 ) {
			if ( hs.highscores[i].secretsCount < n ) {
				strcat( secretsCountPad[i], " " );
				n = n / 10;
			} else
				break;
		}

		//calculate padding for deathsscore
		strcpy( deathsScorePad[i], "");
		n = 10000;
		ds = 0 - hs.highscores[i].deathsScore;
		if (ds == 0)
			strcpy( deathsScorePad[i], "     ");
		else {
			while ( n > 1 ) {
				if ( ds < n ) {
					strcat( deathsScorePad[i], " " );
					n = n / 10;
				} else
					break;
			}
		}
		
		//calculate padding for deaths count
		strcpy( deathsCountPad[i], "") ;
		n = 10;
		while ( n > 1 ) {
			if ( hs.highscores[i].deaths < n ) {
				strcat( deathsCountPad[i], " " );
				n = n / 10;
			} else
				break;
		}

		//calculate padding for skill score
		strcpy( skillScorePad[i], "");
		n = 10000;
		while ( n > 1 ) {
			if ( hs.highscores[i].skillScore < n ) {
				strcat( skillScorePad[i], " " );
				n = n / 10;
			} else
				break;
		}

		//calculate padding for total score
		strcpy( totalScorePad[i], "");
		n = 10000;
		while ( n > 1 ) {
			if ( hs.highscores[i].totalScore < n ) {
				strcat( totalScorePad[i], " " );
				n = n / 10;
			} else
				break;
		}
	}


	for (i = 0; i < SCOREBOARD_LENGTH; i++ ) {
		Com_sprintf(s_scores.scoretexts[i].string, 80, "%i.    %s%i   %s%i %s(%i%%)   %s%i %s%s(%i/%i)   %s%i %s(%ix)   %s%i (%1.0f)   %s%i",
		//sprintf( s_scores.scoretexts[i].string, "%i.    %s%i   %s%i %s(%i%%)   %s%i %s%s(%i/%i)   %s%i %s(%ix)   %s%i (%1.0f)   %s%i", 
			i + 1,
			carnagePad[i], hs.highscores[i].carnageScore,
			accuracyScorePad[i], hs.highscores[i].accuracyScore, accuracyPad[i], hs.highscores[i].accuracy,
			secretsScorePad[i], hs.highscores[i].secretsScore, secretsFoundPad[i], secretsCountPad[i], hs.highscores[i].secretsFound, hs.highscores[i].secretsCount,
			deathsScorePad[i], hs.highscores[i].deathsScore, deathsCountPad[i], hs.highscores[i].deaths,
			skillScorePad[i], hs.highscores[i].skillScore, hs.highscores[i].skill,
			totalScorePad[i], hs.highscores[i].totalScore);
	}
}

static void Scores_MenuInit( void ) {
	int				i;
	int				x, y;
	static			char scorebuffers[SCOREBOARD_LENGTH][4096];

	memset( &s_scores, 0, sizeof(scores_t) );

	Scores_Cache();

	s_scores.menu.wrapAround = qtrue;
	s_scores.menu.fullscreen = qtrue;

	s_scores.banner.generic.type	= MTYPE_BTEXT;
	s_scores.banner.generic.x		= 320;
	s_scores.banner.generic.y		= 16;
	s_scores.banner.string			= "SCORES";
	s_scores.banner.color			= color_white;
	s_scores.banner.style			= UI_CENTER;

	s_scores.levelname.generic.type	= MTYPE_TEXT;
	s_scores.levelname.generic.x	= 320;
	s_scores.levelname.generic.y	= 48;
	s_scores.levelname.string		= levelname;
	s_scores.levelname.color		= text_color_normal;
	s_scores.levelname.style		= UI_CENTER;

	s_scores.back.generic.type		= MTYPE_BITMAP;
	s_scores.back.generic.name		= ART_BACK0;
	s_scores.back.generic.flags		= QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS;
	s_scores.back.generic.callback	= Scores_Event;
	s_scores.back.generic.id		= ID_BACK;
	s_scores.back.generic.x			= 0;
	s_scores.back.generic.y			= 480-64;
	s_scores.back.width				= 128;
	s_scores.back.height			= 64;
	s_scores.back.focuspic			= ART_BACK1;

	y = 96;
	x = 320;
	s_scores.tableheader.generic.type	= MTYPE_TEXT;
	s_scores.tableheader.generic.flags	= QMF_CENTER_JUSTIFY|QMF_INACTIVE;
	s_scores.tableheader.generic.x		= x;
	s_scores.tableheader.generic.y		= y;
	s_scores.tableheader.style			= UI_CENTER|UI_SMALLFONT;
	s_scores.tableheader.color			= color_red;
	s_scores.tableheader.string			= "POS   CARNAGE     ACCURACY       SECRETS         DEATHS        SKILL     TOTAL";

	s_scores.table.generic.type		= MTYPE_BITMAP;
	s_scores.table.generic.name		= ART_TABLE;
	s_scores.table.generic.flags	= QMF_INACTIVE;
	s_scores.table.generic.x		= 0;
	s_scores.table.generic.y		= y;
	s_scores.table.width  			= 640;
	s_scores.table.height  			= 128;

	y += 20;
	for (i = 0; i < SCOREBOARD_LENGTH; i++ ) {
		s_scores.scoretexts[i].generic.type		= MTYPE_TEXT;
		s_scores.scoretexts[i].generic.flags	= QMF_CENTER_JUSTIFY|QMF_INACTIVE;
		s_scores.scoretexts[i].generic.x		= x;
		s_scores.scoretexts[i].generic.y		= y;
		s_scores.scoretexts[i].style			= UI_CENTER|UI_SMALLFONT;
		s_scores.scoretexts[i].color			= color_red;
		s_scores.scoretexts[i].string			= scorebuffers[i];
		y += 16;
	}
	
	Menu_AddItem( &s_scores.menu, &s_scores.banner );
	Menu_AddItem( &s_scores.menu, &s_scores.levelname );
	Menu_AddItem( &s_scores.menu, &s_scores.back );

	Menu_AddItem( &s_scores.menu, &s_scores.tableheader );
	Menu_AddItem( &s_scores.menu, &s_scores.table );
	for (i = 0; i < SCOREBOARD_LENGTH; i++ )
		Menu_AddItem( &s_scores.menu, &s_scores.scoretexts[i] );

	Scores_GenerateScoringTable();
}


void Scores_Cache( void ) {
	trap_R_RegisterShaderNoMip( ART_TABLE );
	trap_R_RegisterShaderNoMip( ART_BACK0 );
	trap_R_RegisterShaderNoMip( ART_BACK1 );
}

void UI_ScoresMenu( char *mapname ) {
	levelname = mapname;
	Scores_MenuInit();
	UI_PushMenu( &s_scores.menu );
}
