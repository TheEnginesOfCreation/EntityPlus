#include "ui_local.h"

#define ID_BACK		1
#define ID_NEXT		2
#define ID_PICTURES	3	// 4, 5, 6
#define ID_PREVPAGE 7
#define ID_NEXTPAGE 8

#define ID_SKILL1 9
#define ID_SKILL2 10
#define ID_SKILL3 11
#define ID_SKILL4 12
#define ID_SKILL5 13

#define MAX_MAPSPERPAGE	4
#define MAX_MAPCOLS 2
#define MAX_MAPROWS 2
#define MAX_SERVERMAPS	64
#define MAX_NAMELENGTH	16
#define MAX_DESCRIPTIONLINES 10
#define MAX_DESCRIPTIONLINELENGTH 40
#define MAX_DESCRIPTIONLENGTH	MAX_DESCRIPTIONLINES * MAX_DESCRIPTIONLINELENGTH

#define ART_FRAME					"menu/art/cut_frame"
#define ART_FIGHT0					"menu/art/fight_0"
#define ART_FIGHT1					"menu/art/fight_1"
#define ART_MAP_COMPLETE1			"menu/art/level_complete1"
#define ART_MAP_COMPLETE2			"menu/art/level_complete2"
#define ART_MAP_COMPLETE3			"menu/art/level_complete3"
#define ART_MAP_COMPLETE4			"menu/art/level_complete4"
#define ART_MAP_COMPLETE5			"menu/art/level_complete5"

#define ART_BACK0		"menu/art/back_0"
#define ART_BACK1		"menu/art/back_1"	
#define ART_NEXT0		"menu/art/next_0"
#define ART_NEXT1		"menu/art/next_1"
#define ART_FRAMEL		"menu/art/frame2_l"
#define ART_FRAMER		"menu/art/frame1_r"
#define ART_SELECT		"menu/art/maps_select"
#define ART_SELECTED	"menu/art/maps_selected"
#define ART_UNKNOWNMAP	"menu/art/unknownmap"
#define ART_ARROWS		"menu/art/gs_arrows_0"
#define ART_ARROWSL		"menu/art/gs_arrows_l"
#define ART_ARROWSR		"menu/art/gs_arrows_r"


typedef struct {
	menuframework_s	menu;

	menutext_s		banner;
	menutext_s		mapname;

	menubitmap_s	framel;
	menubitmap_s	framer;
	menubitmap_s	back;
	menubitmap_s	next;
	menubitmap_s	mappics[MAX_MAPSPERPAGE];
	menubitmap_s	mapbuttons[MAX_MAPSPERPAGE];
	menubitmap_s	arrows;
	menubitmap_s	prevpage;
	menubitmap_s	nextpage;

	menutext_s		highScoreCaption;
	menutext_s		highScore;

	menutext_s		versionWarningsRequires[MAX_MAPSPERPAGE];
	menutext_s		versionWarnings[MAX_MAPSPERPAGE];
	menutext_s		versionWarningsVersion[MAX_MAPSPERPAGE];

	menutext_s		mapLongName;
	menutext_s		mapAuthor;
	menutext_s		mapDescriptionLines[MAX_DESCRIPTIONLINES];

	char			maplist[MAX_SERVERMAPS][MAX_NAMELENGTH];
	char			mapversions[MAX_SERVERMAPS][MAX_NAMELENGTH];
	char			mapdescriptions[MAX_SERVERMAPS][MAX_DESCRIPTIONLENGTH];
	char			maplongnames[MAX_SERVERMAPS][MAX_DESCRIPTIONLINELENGTH];
	char			mapauthors[MAX_SERVERMAPS][MAX_DESCRIPTIONLINELENGTH];
	int				page;
	int				currentmap;
	int				nummaps;
	int				maxpages;
	int				mapGamebits[MAX_SERVERMAPS];
} epMenuInfo_t;

char lines[MAX_DESCRIPTIONLINES][MAX_DESCRIPTIONLINELENGTH];

typedef struct {
	menuframework_s	menu;

	menutext_s		banner;
	menutext_s		item_skill1;
	menutext_s		item_skill2;
	menutext_s		item_skill3;
	menutext_s		item_skill4;
	menutext_s		item_skill5;

	menubitmap_s	frame;
	menubitmap_s	back;
	menubitmap_s	next;
	menubitmap_s	art_skillPic;

	qhandle_t		skillpics[5];
	sfxHandle_t		nightmareSound;
	sfxHandle_t		silenceSound;
} epSkillInfo_t;

static epMenuInfo_t		epMenuInfo;
static epSkillInfo_t	epSkillInfo;

/*
===============
EPSkill_StartGame

Starts the game at the selected skill level
===============
*/
void EPSkill_StartGame( void ) {
	trap_Cvar_SetValue( "sv_maxclients", 64 );
	trap_Cvar_SetValue ("timelimit", 0 );
	trap_Cvar_SetValue ("fraglimit", 0 );
	//trap_Cvar_SetValue ("con_notifytime", 0 );
	trap_Cvar_SetValue ("g_gametype", GT_ENTITYPLUS );
	trap_Cmd_ExecuteText( EXEC_APPEND, va( "map %s\n", epMenuInfo.maplist[epMenuInfo.currentmap] ) );
}

/*
===============
EPSkill_Cache

Caches assets
===============
*/
void EPSkill_Cache( void ) {
	
	trap_R_RegisterShaderNoMip( ART_FRAME );
	trap_R_RegisterShaderNoMip( ART_BACK0 );
	trap_R_RegisterShaderNoMip( ART_BACK1 );
	trap_R_RegisterShaderNoMip( ART_FIGHT0 );
	trap_R_RegisterShaderNoMip( ART_FIGHT1 );

	epSkillInfo.skillpics[0] = trap_R_RegisterShaderNoMip( ART_MAP_COMPLETE1 );
	epSkillInfo.skillpics[1] = trap_R_RegisterShaderNoMip( ART_MAP_COMPLETE2 );
	epSkillInfo.skillpics[2] = trap_R_RegisterShaderNoMip( ART_MAP_COMPLETE3 );
	epSkillInfo.skillpics[3] = trap_R_RegisterShaderNoMip( ART_MAP_COMPLETE4 );
	epSkillInfo.skillpics[4] = trap_R_RegisterShaderNoMip( ART_MAP_COMPLETE5 );

	epSkillInfo.nightmareSound = trap_S_RegisterSound( "sound/misc/nightmare.wav", qfalse );
	epSkillInfo.silenceSound = trap_S_RegisterSound( "sound/misc/silence.wav", qfalse );
}

/*
===============
EPSkill_SetSkillColor
===============
*/
static void EPSkill_SetSkillColor( int skill, vec4_t color ) {
	switch( skill ) {
	case 1:
		epSkillInfo.item_skill1.color = color;
		break;
	case 2:
		epSkillInfo.item_skill2.color = color;
		break;
	case 3:
		epSkillInfo.item_skill3.color = color;
		break;
	case 4:
		epSkillInfo.item_skill4.color = color;
		break;
	case 5:
		epSkillInfo.item_skill5.color = color;
		break;
	default:
		break;
	}
}

/*
===============
EPMenu_MenuEvent
===============
*/
static void EPSkill_MenuEvent( void* ptr, int event ) {
	int		id;
	int		skill;

	if( event != QM_ACTIVATED ) {
		return;
	}

	switch( ((menucommon_s*)ptr)->id ) {
		case ID_BACK:
			UI_PopMenu();
			break;
		
		case ID_NEXT:
			EPSkill_StartGame();
			break;

		case ID_SKILL1:
		case ID_SKILL2:
		case ID_SKILL3:
		case ID_SKILL4:
		case ID_SKILL5:
			EPSkill_SetSkillColor( (int)trap_Cvar_VariableValue( "g_spSkill" ), color_red );

			id = ((menucommon_s*)ptr)->id;
			skill = id - ID_SKILL1 + 1;
			trap_Cvar_SetValue( "g_spSkill", skill );

			EPSkill_SetSkillColor( skill, color_white );
			epSkillInfo.art_skillPic.shader = epSkillInfo.skillpics[skill - 1];

			if( id == ID_SKILL5 ) {
				trap_S_StartLocalSound( epSkillInfo.nightmareSound, CHAN_ANNOUNCER );
			}
			else {
				trap_S_StartLocalSound( epSkillInfo.silenceSound, CHAN_ANNOUNCER );
			}
			break;
	}
}

/*
===============
UI_EPSkillMenu

Builds the EntityPlus skill selection menu
===============
*/
void UI_EPSkillMenu( void ) {
	int skill;

	//initialize menu
	memset( &epSkillInfo, 0, sizeof(epSkillInfo) );
	epSkillInfo.menu.fullscreen = qtrue;
	epSkillInfo.menu.wrapAround = qtrue;

	//cache assets
	EPSkill_Cache();

	//add text banner
	epSkillInfo.banner.generic.type  = MTYPE_BTEXT;
	epSkillInfo.banner.generic.x	   = 320;
	epSkillInfo.banner.generic.y	   = 16;
	epSkillInfo.banner.string        = "DIFFICULTY";
	epSkillInfo.banner.color         = color_white;
	epSkillInfo.banner.style         = UI_CENTER;
	Menu_AddItem( &epSkillInfo.menu, &epSkillInfo.banner );

	//add frame
	epSkillInfo.frame.generic.type		= MTYPE_BITMAP;
	epSkillInfo.frame.generic.name		= ART_FRAME;
	epSkillInfo.frame.generic.flags		= QMF_LEFT_JUSTIFY|QMF_INACTIVE;
	epSkillInfo.frame.generic.x			= 142;
	epSkillInfo.frame.generic.y			= 118;
	epSkillInfo.frame.width				= 359;
	epSkillInfo.frame.height			= 256;
	Menu_AddItem( &epSkillInfo.menu, &epSkillInfo.frame );

	//add skill level texts
	epSkillInfo.item_skill1.generic.type		= MTYPE_PTEXT;
	epSkillInfo.item_skill1.generic.flags		= QMF_CENTER_JUSTIFY|QMF_PULSEIFFOCUS;
	epSkillInfo.item_skill1.generic.x			= 320;
	epSkillInfo.item_skill1.generic.y			= 170;
	epSkillInfo.item_skill1.generic.callback	= EPSkill_MenuEvent;
	epSkillInfo.item_skill1.generic.id			= ID_SKILL1;
	epSkillInfo.item_skill1.string				= "Beginner"; // seems more single player-ish
	epSkillInfo.item_skill1.color				= color_red;
	epSkillInfo.item_skill1.style				= UI_CENTER;
	Menu_AddItem( &epSkillInfo.menu, &epSkillInfo.item_skill1 );

	epSkillInfo.item_skill2.generic.type		= MTYPE_PTEXT;
	epSkillInfo.item_skill2.generic.flags		= QMF_CENTER_JUSTIFY|QMF_PULSEIFFOCUS;
	epSkillInfo.item_skill2.generic.x			= 320;
	epSkillInfo.item_skill2.generic.y			= 198;
	epSkillInfo.item_skill2.generic.callback	= EPSkill_MenuEvent;
	epSkillInfo.item_skill2.generic.id			= ID_SKILL2;
	epSkillInfo.item_skill2.string				= "Easy";
	epSkillInfo.item_skill2.color				= color_red;
	epSkillInfo.item_skill2.style				= UI_CENTER;
	Menu_AddItem( &epSkillInfo.menu, &epSkillInfo.item_skill2 );

	epSkillInfo.item_skill3.generic.type		= MTYPE_PTEXT;
	epSkillInfo.item_skill3.generic.flags		= QMF_CENTER_JUSTIFY|QMF_PULSEIFFOCUS;
	epSkillInfo.item_skill3.generic.x			= 320;
	epSkillInfo.item_skill3.generic.y			= 227;
	epSkillInfo.item_skill3.generic.callback	= EPSkill_MenuEvent;
	epSkillInfo.item_skill3.generic.id			= ID_SKILL3;
	epSkillInfo.item_skill3.string				= "Medium";
	epSkillInfo.item_skill3.color				= color_red;
	epSkillInfo.item_skill3.style				= UI_CENTER;
	Menu_AddItem( &epSkillInfo.menu, &epSkillInfo.item_skill3 );

	epSkillInfo.item_skill4.generic.type		= MTYPE_PTEXT;
	epSkillInfo.item_skill4.generic.flags		= QMF_CENTER_JUSTIFY|QMF_PULSEIFFOCUS;
	epSkillInfo.item_skill4.generic.x			= 320;
	epSkillInfo.item_skill4.generic.y			= 255;
	epSkillInfo.item_skill4.generic.callback	= EPSkill_MenuEvent;
	epSkillInfo.item_skill4.generic.id			= ID_SKILL4;
	epSkillInfo.item_skill4.string				= "Hard";
	epSkillInfo.item_skill4.color				= color_red;
	epSkillInfo.item_skill4.style				= UI_CENTER;
	Menu_AddItem( &epSkillInfo.menu, &epSkillInfo.item_skill4 );

	epSkillInfo.item_skill5.generic.type		= MTYPE_PTEXT;
	epSkillInfo.item_skill5.generic.flags		= QMF_CENTER_JUSTIFY|QMF_PULSEIFFOCUS;
	epSkillInfo.item_skill5.generic.x			= 320;
	epSkillInfo.item_skill5.generic.y			= 283;
	epSkillInfo.item_skill5.generic.callback	= EPSkill_MenuEvent;
	epSkillInfo.item_skill5.generic.id			= ID_SKILL5;
	epSkillInfo.item_skill5.string				= "Nightmare";
	epSkillInfo.item_skill5.color				= color_red;
	epSkillInfo.item_skill5.style				= UI_CENTER;
	Menu_AddItem( &epSkillInfo.menu, &epSkillInfo.item_skill5 );

	//add skillpic
	epSkillInfo.art_skillPic.generic.type		= MTYPE_BITMAP;
	epSkillInfo.art_skillPic.generic.flags	= QMF_LEFT_JUSTIFY|QMF_INACTIVE;
	epSkillInfo.art_skillPic.generic.x		= 320-64;
	epSkillInfo.art_skillPic.generic.y		= 368;
	epSkillInfo.art_skillPic.width			= 128;
	epSkillInfo.art_skillPic.height			= 96;
	Menu_AddItem( &epSkillInfo.menu, &epSkillInfo.art_skillPic );

	//add back button
	epSkillInfo.back.generic.type			= MTYPE_BITMAP;
	epSkillInfo.back.generic.name			= ART_BACK0;
	epSkillInfo.back.generic.flags			= QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS;
	epSkillInfo.back.generic.x				= 0;
	epSkillInfo.back.generic.y				= 480-64;
	epSkillInfo.back.generic.callback		= EPSkill_MenuEvent;
	epSkillInfo.back.generic.id				= ID_BACK;
	epSkillInfo.back.width					= 128;
	epSkillInfo.back.height					= 64;
	epSkillInfo.back.focuspic				= ART_BACK1;
	Menu_AddItem( &epSkillInfo.menu, &epSkillInfo.back );

	//add fight button
	epSkillInfo.next.generic.type			= MTYPE_BITMAP;
	epSkillInfo.next.generic.name			= ART_FIGHT0;
	epSkillInfo.next.generic.flags			= QMF_RIGHT_JUSTIFY|QMF_PULSEIFFOCUS;
	epSkillInfo.next.generic.x				= 640;
	epSkillInfo.next.generic.y				= 480-64;
	epSkillInfo.next.generic.callback		= EPSkill_MenuEvent;
	epSkillInfo.next.generic.id				= ID_NEXT;
	epSkillInfo.next.width					= 128;
	epSkillInfo.next.height					= 64;
	epSkillInfo.next.focuspic				= ART_FIGHT1;
	Menu_AddItem( &epSkillInfo.menu, &epSkillInfo.next );

	//highlight the right skill level
	skill = (int)Com_Clamp( 1, 5, trap_Cvar_VariableValue( "g_spSkill" ) );
	EPSkill_SetSkillColor( skill, color_white );
	epSkillInfo.art_skillPic.shader = epSkillInfo.skillpics[skill - 1];
	if( skill == 5 ) {
		trap_S_StartLocalSound( epSkillInfo.nightmareSound, CHAN_ANNOUNCER );
	}

	//add menu to stack
	UI_PushMenu( &epSkillInfo.menu );
}




/*
=================
EPMenu_MapGametype
=================
*/

static qboolean EPMenu_MapGametype( char *string ) {
	char	*p;
	char	*token;

	p = string;
	while( 1 ) {
		token = COM_ParseExt( &p, qfalse );
		if( token[0] == 0 ) {
			break;
		}

		if( Q_stricmp( token, "entityplus" ) == 0 ) {
			return qtrue;
		}
	}

	return qfalse;
}

/*
===============
EPMenu_VersionAccepted

Returns true if the mod version supports the features used in the map
===============
*/
qboolean EPMenu_VersionAccepted( char *version ) {
	if ( strlen( version ) > 0 )
		if 
		(	
			Q_stricmp( version, "1.0" ) != 0 && 
			Q_stricmp( version, "1.0.1" ) != 0 &&
			Q_stricmp( version, "1.0.2" ) != 0 &&
			Q_stricmp( version, "1.1" ) != 0
		)
		{
			return qfalse;
		}

	return qtrue;
}

/*
=================
EPMenu_Update
=================
*/
static void EPMenu_Update( void ) {
	int				i;
	int				top;
	static	char	picname[MAX_MAPSPERPAGE][64];

	top = epMenuInfo.page*MAX_MAPSPERPAGE;

	// clear version warnings
	for (i=0; i<MAX_MAPSPERPAGE; i++) {
		epMenuInfo.versionWarningsRequires[i].string = "";
		epMenuInfo.versionWarningsVersion[i].string = "";
		epMenuInfo.versionWarnings[i].string = "";
	}

	// clear description
	for ( i = 0; i < MAX_DESCRIPTIONLINES; i++ ) {
		strcpy(lines[i], "");
		epMenuInfo.mapDescriptionLines[i].string = "";
	}


	for (i=0; i<MAX_MAPSPERPAGE; i++)
	{
		if (top+i >= epMenuInfo.nummaps)
			break;

		Com_sprintf( picname[i], sizeof(picname[i]), "levelshots/%s", epMenuInfo.maplist[top+i] );

		epMenuInfo.mappics[i].generic.flags &= ~QMF_HIGHLIGHT;
		epMenuInfo.mappics[i].generic.name   = picname[i];
		epMenuInfo.mappics[i].shader         = 0;

		// reset
		epMenuInfo.mapbuttons[i].generic.flags |= QMF_PULSEIFFOCUS;
		epMenuInfo.mapbuttons[i].generic.flags &= ~QMF_INACTIVE;

		// update version warning
		if ( !EPMenu_VersionAccepted( epMenuInfo.mapversions[top+i] ) ) {
			epMenuInfo.versionWarningsRequires[i].string = "Requires";
			epMenuInfo.versionWarningsVersion[i].string = "version";
			epMenuInfo.versionWarnings[i].string = epMenuInfo.mapversions[top+i];
		}
	}

	for (; i<MAX_MAPSPERPAGE; i++)
	{
		epMenuInfo.mappics[i].generic.flags &= ~QMF_HIGHLIGHT;
		epMenuInfo.mappics[i].generic.name   = NULL;
		epMenuInfo.mappics[i].shader         = 0;

		// disable
		epMenuInfo.mapbuttons[i].generic.flags &= ~QMF_PULSEIFFOCUS;
		epMenuInfo.mapbuttons[i].generic.flags |= QMF_INACTIVE;
	}


	// no servers to start
	if( !epMenuInfo.nummaps ) {
		epMenuInfo.next.generic.flags |= QMF_INACTIVE;

		// set the map name
		strcpy( epMenuInfo.mapname.string, "NO MAPS FOUND" );
	}
	else {
		// set the highlight
		epMenuInfo.next.generic.flags &= ~QMF_INACTIVE;
		i = epMenuInfo.currentmap - top;
		if ( i >=0 && i < MAX_MAPSPERPAGE ) 
		{
			epMenuInfo.mappics[i].generic.flags    |= QMF_HIGHLIGHT;
			epMenuInfo.mapbuttons[i].generic.flags &= ~QMF_PULSEIFFOCUS;
		}

		// set the map name
		strcpy( epMenuInfo.mapname.string, epMenuInfo.maplist[epMenuInfo.currentmap] );

		// set the high score
		strcpy( epMenuInfo.highScore.string, va("%i", COM_LoadLevelScore( epMenuInfo.maplist[epMenuInfo.currentmap] ) ) );

		// set the longname
		if ( strlen(epMenuInfo.maplongnames[epMenuInfo.currentmap]) == 0 )
			strcpy( epMenuInfo.mapLongName.string, epMenuInfo.maplist[epMenuInfo.currentmap] );	//display mapname if no longname is specified
		else
			strcpy( epMenuInfo.mapLongName.string, epMenuInfo.maplongnames[epMenuInfo.currentmap] );
			Q_strupr( epMenuInfo.mapLongName.string );


		// set the author
		if ( strlen( epMenuInfo.mapauthors[epMenuInfo.currentmap] ) > 0 ) {
			strcpy( epMenuInfo.mapAuthor.string, "by: ");
			strcat( epMenuInfo.mapAuthor.string, epMenuInfo.mapauthors[epMenuInfo.currentmap] );
		} else {
			strcpy( epMenuInfo.mapAuthor.string, "");
		}

		// set the description
		if ( strlen( epMenuInfo.mapdescriptions[epMenuInfo.currentmap] ) ) {
			char desc[MAX_DESCRIPTIONLENGTH];
			int spaceIndex, prevSpaceIndex = 0;
			int currentLine = 0;
			int lineIndex = 0;
			char c[2];

			Q_strncpyz(desc, epMenuInfo.mapdescriptions[epMenuInfo.currentmap], sizeof(desc));

			for ( i = 0; i < MAX_DESCRIPTIONLENGTH; i++ ) {
				c[0] = desc[i];
				c[1] = '\0';

				if ( c[0] == ' ' && lineIndex < MAX_DESCRIPTIONLINELENGTH ) {
					spaceIndex = i;
				}

				if (lineIndex == MAX_DESCRIPTIONLINELENGTH) {
					if (spaceIndex - prevSpaceIndex <= 0) {
						strcat(lines[currentLine-1], &desc[prevSpaceIndex-1]);
						break;
					} else {
						Q_strncpyz(lines[currentLine], &desc[prevSpaceIndex], (spaceIndex - prevSpaceIndex) + 1);
					}
					prevSpaceIndex = spaceIndex;
					prevSpaceIndex++;
					i = spaceIndex;
					lineIndex = -1;
					currentLine++;
				}
				lineIndex++;
			}

			for ( i = 0; i < MAX_DESCRIPTIONLINES; i++ ) {
				epMenuInfo.mapDescriptionLines[i].string = lines[i];
			}
		} else {
			epMenuInfo.mapDescriptionLines[0].string = "no description available...";
		}
		
	}
	
	Q_strupr( epMenuInfo.mapname.string );
}


/*
=================
EPMenu_GametypeEvent
=================
*/
static void EPMenu_GametypeFilter( void ) {
	int			i;
	int			count;
	int			gamebits;
	const char	*info;
	qboolean	show;

	show = qfalse;
	count = UI_GetNumArenas();
	epMenuInfo.nummaps = 0;
	for( i = 0; i < count; i++ ) {
		info = UI_GetArenaInfoByNumber( i );

		show = EPMenu_MapGametype( Info_ValueForKey( info, "type") );
		if ( !show )
			continue;

		Q_strncpyz( epMenuInfo.maplist[epMenuInfo.nummaps], Info_ValueForKey( info, "map" ), MAX_NAMELENGTH );
		Q_strupr( epMenuInfo.maplist[epMenuInfo.nummaps] );
		Q_strncpyz( epMenuInfo.mapversions[epMenuInfo.nummaps], Info_ValueForKey( info, "minversion" ), MAX_NAMELENGTH);
		Q_strncpyz( epMenuInfo.mapdescriptions[epMenuInfo.nummaps], Info_ValueForKey( info, "description" ), MAX_DESCRIPTIONLENGTH);
		Q_strncpyz( epMenuInfo.maplongnames[epMenuInfo.nummaps], Info_ValueForKey( info, "longname" ), MAX_DESCRIPTIONLINELENGTH);
		Q_strncpyz( epMenuInfo.mapauthors[epMenuInfo.nummaps], Info_ValueForKey( info, "author" ), MAX_DESCRIPTIONLINELENGTH);
		epMenuInfo.mapGamebits[epMenuInfo.nummaps] = GT_ENTITYPLUS;
		epMenuInfo.nummaps++;
	}
	epMenuInfo.maxpages = (epMenuInfo.nummaps + MAX_MAPSPERPAGE-1)/MAX_MAPSPERPAGE;
	epMenuInfo.page = 0;
	epMenuInfo.currentmap = 0;

	EPMenu_Update();
}


/*
===============
EPMenu_MenuEvent
===============
*/
static void EPMenu_MenuEvent( void* ptr, int event ) {
	if( event != QM_ACTIVATED ) {
		return;
	}

	switch( ((menucommon_s*)ptr)->id ) {
		case ID_BACK:
			UI_PopMenu();
			break;
		
		case ID_NEXT:
			UI_EPSkillMenu();
			break;

		case ID_PREVPAGE:
			if( epMenuInfo.page > 0 ) {
				epMenuInfo.page--;
				EPMenu_Update();
			}
			break;

		case ID_NEXTPAGE:
			if( epMenuInfo.page < epMenuInfo.maxpages - 1 ) {
				epMenuInfo.page++;
				EPMenu_Update();
			}
			break;
	}
}

/*
===============
EPMenu_LevelshotDraw
===============
*/
static void EPMenu_LevelshotDraw( void *self ) {
	menubitmap_s	*b;
	int				x;
	int				y;
	int				w;
	int				h;
	int				n;

	b = (menubitmap_s *)self;

	if( !b->generic.name ) {
		return;
	}

	if( b->generic.name && !b->shader ) {
		b->shader = trap_R_RegisterShaderNoMip( b->generic.name );
		if( !b->shader && b->errorpic ) {
			b->shader = trap_R_RegisterShaderNoMip( b->errorpic );
		}
	}

	if( b->focuspic && !b->focusshader ) {
		b->focusshader = trap_R_RegisterShaderNoMip( b->focuspic );
	}

	x = b->generic.x;
	y = b->generic.y;
	w = b->width;
	h =	b->height;
	if( b->shader ) {
		UI_DrawHandlePic( x, y, w, h, b->shader );
	}

	x = b->generic.x;
	y = b->generic.y + b->height;
	UI_FillRect( x, y, b->width, 28, colorBlack );

	x += b->width / 2;
	y += 4;
	n = epMenuInfo.page * MAX_MAPSPERPAGE + b->generic.id - ID_PICTURES;
	UI_DrawString( x, y, epMenuInfo.maplist[n], UI_CENTER|UI_SMALLFONT, color_orange );

	x = b->generic.x;
	y = b->generic.y;
	w = b->width;
	h =	b->height + 28;
	if( b->generic.flags & QMF_HIGHLIGHT ) {	
		UI_DrawHandlePic( x, y, w, h, b->focusshader );
	}
}

/*
=================
EPMenu_MapEvent
=================
*/
static void EPMenu_MapEvent( void* ptr, int event ) {
	if( event != QM_ACTIVATED) {
		return;
	}

	epMenuInfo.currentmap = (epMenuInfo.page*MAX_MAPSPERPAGE) + (((menucommon_s*)ptr)->id - ID_PICTURES);
	EPMenu_Update();
}

/*
===============
EPMenu_Cache

Caches assets
===============
*/
void EPMenu_Cache( void ) {
	int			i;
	qboolean	precache;
	char		picname[64];
	const char	*info;

	//register artwork shaders
	trap_R_RegisterShaderNoMip( ART_FRAMEL );
	trap_R_RegisterShaderNoMip( ART_FRAMER );
	trap_R_RegisterShaderNoMip( ART_BACK0 );
	trap_R_RegisterShaderNoMip( ART_BACK1 );
	trap_R_RegisterShaderNoMip( ART_NEXT0 );
	trap_R_RegisterShaderNoMip( ART_NEXT1 );
	trap_R_RegisterShaderNoMip( ART_SELECT );
	trap_R_RegisterShaderNoMip( ART_SELECTED );
	trap_R_RegisterShaderNoMip( ART_UNKNOWNMAP );
	trap_R_RegisterShaderNoMip( ART_ARROWS );
	trap_R_RegisterShaderNoMip( ART_ARROWSL );
	trap_R_RegisterShaderNoMip( ART_ARROWSR );

	//cache maps
	precache = trap_Cvar_VariableValue("com_buildscript");

	epMenuInfo.nummaps = UI_GetNumArenas();

	for( i = 0; i < epMenuInfo.nummaps; i++ ) {
		info = UI_GetArenaInfoByNumber( i );

		Q_strncpyz( epMenuInfo.maplist[i], Info_ValueForKey( info, "map"), MAX_NAMELENGTH );
		Q_strupr( epMenuInfo.maplist[i] );
		epMenuInfo.mapGamebits[i] = GT_ENTITYPLUS;

		if( precache ) {
			Com_sprintf( picname, sizeof(picname), "levelshots/%s", epMenuInfo.maplist[i] );
			trap_R_RegisterShaderNoMip(picname);
		}
	}

	epMenuInfo.maxpages = (epMenuInfo.nummaps + MAX_MAPSPERPAGE-1)/MAX_MAPSPERPAGE;
}

/*
===============
UI_EPLevelMenu

Builds the EntityPlus Single Player menu
===============
*/
void UI_EPLevelMenu( void ) {
	int i;
	int top;
	int x, y;
	static char mapnamebuffer[64];
	static char mapscorebuffer[MAX_HIGHSCORE_TEXT];
	static char maplongnamebuffer[MAX_DESCRIPTIONLINELENGTH];
	static char mapauthorbuffer[MAX_DESCRIPTIONLINELENGTH];

	//initialize menu
	memset( &epMenuInfo, 0, sizeof(epMenuInfo) );
	epMenuInfo.menu.fullscreen = qtrue;
	epMenuInfo.menu.wrapAround = qtrue;

	//cache assets
	EPMenu_Cache();

	//add text banner
	epMenuInfo.banner.generic.type  = MTYPE_BTEXT;
	epMenuInfo.banner.generic.x	   = 320;
	epMenuInfo.banner.generic.y	   = 16;
	epMenuInfo.banner.string        = "NEW GAME";
	epMenuInfo.banner.color         = color_white;
	epMenuInfo.banner.style         = UI_CENTER;
	Menu_AddItem( &epMenuInfo.menu, &epMenuInfo.banner );

	//add left frame
	epMenuInfo.framel.generic.type  = MTYPE_BITMAP;
	epMenuInfo.framel.generic.name  = ART_FRAMEL;
	epMenuInfo.framel.generic.flags = QMF_INACTIVE;
	epMenuInfo.framel.generic.x	   = 0;  
	epMenuInfo.framel.generic.y	   = 78;
	epMenuInfo.framel.width  	   = 256;
	epMenuInfo.framel.height  	   = 329;
	//Menu_AddItem( &epMenuInfo.menu, &epMenuInfo.framel );

	//add right frame
	epMenuInfo.framer.generic.type  = MTYPE_BITMAP;
	epMenuInfo.framer.generic.name  = ART_FRAMER;
	epMenuInfo.framer.generic.flags = QMF_INACTIVE;
	epMenuInfo.framer.generic.x	   = 376;
	epMenuInfo.framer.generic.y	   = 76;
	epMenuInfo.framer.width  	   = 256;
	epMenuInfo.framer.height  	   = 334;
	//Menu_AddItem( &epMenuInfo.menu, &epMenuInfo.framer );

	//add back button
	epMenuInfo.back.generic.type			= MTYPE_BITMAP;
	epMenuInfo.back.generic.name			= ART_BACK0;
	epMenuInfo.back.generic.flags			= QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS;
	epMenuInfo.back.generic.x				= 0;
	epMenuInfo.back.generic.y				= 480-64;
	epMenuInfo.back.generic.callback		= EPMenu_MenuEvent;
	epMenuInfo.back.generic.id				= ID_BACK;
	epMenuInfo.back.width					= 128;
	epMenuInfo.back.height					= 64;
	epMenuInfo.back.focuspic				= ART_BACK1;
	Menu_AddItem( &epMenuInfo.menu, &epMenuInfo.back );

	//add next button
	epMenuInfo.next.generic.type			= MTYPE_BITMAP;
	epMenuInfo.next.generic.name			= ART_NEXT0;
	epMenuInfo.next.generic.flags			= QMF_RIGHT_JUSTIFY|QMF_PULSEIFFOCUS;
	epMenuInfo.next.generic.x				= 640;
	epMenuInfo.next.generic.y				= 480-64;
	epMenuInfo.next.generic.callback		= EPMenu_MenuEvent;
	epMenuInfo.next.generic.id				= ID_NEXT;
	epMenuInfo.next.width					= 128;
	epMenuInfo.next.height					= 64;
	epMenuInfo.next.focuspic				= ART_NEXT1;
	Menu_AddItem( &epMenuInfo.menu, &epMenuInfo.next );

	//add map selectors
	for ( i = 0; i < MAX_MAPSPERPAGE; i++)
	{
		x =	(i % MAX_MAPCOLS) * (128+8) + 16;
		y = (i / MAX_MAPROWS) * (128+8) + 96;

		epMenuInfo.mappics[i].generic.type		= MTYPE_BITMAP;
		epMenuInfo.mappics[i].generic.flags		= QMF_LEFT_JUSTIFY|QMF_INACTIVE;
		epMenuInfo.mappics[i].generic.x			= x;
		epMenuInfo.mappics[i].generic.y			= y;
		epMenuInfo.mappics[i].generic.id		= ID_PICTURES+i;
		epMenuInfo.mappics[i].width				= 128;
		epMenuInfo.mappics[i].height			= 96;
		epMenuInfo.mappics[i].focuspic			= ART_SELECTED;
		epMenuInfo.mappics[i].errorpic			= ART_UNKNOWNMAP;
		epMenuInfo.mappics[i].generic.ownerdraw	= EPMenu_LevelshotDraw;
		Menu_AddItem( &epMenuInfo.menu, &epMenuInfo.mappics[i] );
		
		epMenuInfo.mapbuttons[i].generic.type		= MTYPE_BITMAP;
		epMenuInfo.mapbuttons[i].generic.flags		= QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS|QMF_NODEFAULTINIT;
		epMenuInfo.mapbuttons[i].generic.id			= ID_PICTURES+i;
		epMenuInfo.mapbuttons[i].generic.callback	= EPMenu_MapEvent;
		epMenuInfo.mapbuttons[i].generic.x			= x - 30;
		epMenuInfo.mapbuttons[i].generic.y			= y - 32;
		epMenuInfo.mapbuttons[i].width				= 256;
		epMenuInfo.mapbuttons[i].height				= 248;
		epMenuInfo.mapbuttons[i].generic.left		= x;
		epMenuInfo.mapbuttons[i].generic.top		= y;
		epMenuInfo.mapbuttons[i].generic.right		= x + 128;
		epMenuInfo.mapbuttons[i].generic.bottom		= y + 128;
		epMenuInfo.mapbuttons[i].focuspic			= ART_SELECT;
		Menu_AddItem( &epMenuInfo.menu, &epMenuInfo.mapbuttons[i] );

		epMenuInfo.versionWarningsRequires[i].generic.type = MTYPE_TEXT;
		epMenuInfo.versionWarningsRequires[i].generic.flags = QMF_CENTER_JUSTIFY|QMF_INACTIVE;
		epMenuInfo.versionWarningsRequires[i].generic.x = x;
		epMenuInfo.versionWarningsRequires[i].generic.y = y;
		epMenuInfo.versionWarningsRequires[i].style = UI_LEFT;
		epMenuInfo.versionWarningsRequires[i].color = color_yellow;
		Menu_AddItem( &epMenuInfo.menu, &epMenuInfo.versionWarningsRequires[i] );

		epMenuInfo.versionWarningsVersion[i].generic.type = MTYPE_TEXT;
		epMenuInfo.versionWarningsVersion[i].generic.flags = QMF_CENTER_JUSTIFY|QMF_INACTIVE;
		epMenuInfo.versionWarningsVersion[i].generic.x = x;
		epMenuInfo.versionWarningsVersion[i].generic.y = y + 16;
		epMenuInfo.versionWarningsVersion[i].style = UI_LEFT;
		epMenuInfo.versionWarningsVersion[i].color = color_yellow;
		Menu_AddItem( &epMenuInfo.menu, &epMenuInfo.versionWarningsVersion[i] );

		epMenuInfo.versionWarnings[i].generic.type = MTYPE_TEXT;
		epMenuInfo.versionWarnings[i].generic.flags = QMF_CENTER_JUSTIFY|QMF_INACTIVE;
		epMenuInfo.versionWarnings[i].generic.x = x;
		epMenuInfo.versionWarnings[i].generic.y = y + 32;
		epMenuInfo.versionWarnings[i].style = UI_LEFT;
		epMenuInfo.versionWarnings[i].color = color_yellow;
		Menu_AddItem( &epMenuInfo.menu, &epMenuInfo.versionWarnings[i] );
	}
	
	//add longname
	epMenuInfo.mapLongName.generic.type = MTYPE_TEXT;
	epMenuInfo.mapLongName.generic.flags = QMF_CENTER_JUSTIFY|QMF_INACTIVE;
	epMenuInfo.mapLongName.generic.x = 298;
	epMenuInfo.mapLongName.generic.y = 96;
	epMenuInfo.mapLongName.style = UI_LEFT|UI_SMALLFONT;
	epMenuInfo.mapLongName.color = color_red;
	epMenuInfo.mapLongName.string = maplongnamebuffer;
	Menu_AddItem( &epMenuInfo.menu, &epMenuInfo.mapLongName );

	//add author
	epMenuInfo.mapAuthor.generic.type = MTYPE_TEXT;
	epMenuInfo.mapAuthor.generic.flags = QMF_CENTER_JUSTIFY|QMF_INACTIVE;
	epMenuInfo.mapAuthor.generic.x = 298;
	epMenuInfo.mapAuthor.generic.y = 112;
	epMenuInfo.mapAuthor.style = UI_LEFT|UI_SMALLFONT;
	epMenuInfo.mapAuthor.color = color_red;
	epMenuInfo.mapAuthor.string = mapauthorbuffer;
	Menu_AddItem( &epMenuInfo.menu, &epMenuInfo.mapAuthor );

	//add description
	for (i = 0; i < MAX_DESCRIPTIONLINES; i++ ) {
		epMenuInfo.mapDescriptionLines[i].generic.type = MTYPE_TEXT;
		epMenuInfo.mapDescriptionLines[i].generic.flags = QMF_CENTER_JUSTIFY|QMF_INACTIVE;
		epMenuInfo.mapDescriptionLines[i].generic.x = 298;
		epMenuInfo.mapDescriptionLines[i].generic.y = 128 + (i * 16);
		epMenuInfo.mapDescriptionLines[i].style = UI_LEFT|UI_SMALLFONT;
		epMenuInfo.mapDescriptionLines[i].color = color_red;
		Menu_AddItem( &epMenuInfo.menu, &epMenuInfo.mapDescriptionLines[i] );
	}

	//add next/prev page buttons
	epMenuInfo.arrows.generic.type  = MTYPE_BITMAP;
	epMenuInfo.arrows.generic.name  = ART_ARROWS;
	epMenuInfo.arrows.generic.flags = QMF_INACTIVE;
	epMenuInfo.arrows.generic.x	   = 260;
	epMenuInfo.arrows.generic.y	   = 400;
	epMenuInfo.arrows.width  	   = 128;
	epMenuInfo.arrows.height  	   = 32;
	Menu_AddItem( &epMenuInfo.menu, &epMenuInfo.arrows );

	//add prev page button overlay
	epMenuInfo.prevpage.generic.type	 = MTYPE_BITMAP;
	epMenuInfo.prevpage.generic.flags    = QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS;
	epMenuInfo.prevpage.generic.callback = EPMenu_MenuEvent;
	epMenuInfo.prevpage.generic.id	    = ID_PREVPAGE;
	epMenuInfo.prevpage.generic.x		= 260;
	epMenuInfo.prevpage.generic.y		= 400;
	epMenuInfo.prevpage.width  		    = 64;
	epMenuInfo.prevpage.height			= 32;
	epMenuInfo.prevpage.focuspic        = ART_ARROWSL;
	Menu_AddItem( &epMenuInfo.menu, &epMenuInfo.prevpage );

	//add next page button overlay
	epMenuInfo.nextpage.generic.type	    = MTYPE_BITMAP;
	epMenuInfo.nextpage.generic.flags    = QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS;
	epMenuInfo.nextpage.generic.callback = EPMenu_MenuEvent;
	epMenuInfo.nextpage.generic.id	    = ID_NEXTPAGE;
	epMenuInfo.nextpage.generic.x		= 321;
	epMenuInfo.nextpage.generic.y		= 400;
	epMenuInfo.nextpage.width  		    = 64;
	epMenuInfo.nextpage.height  		    = 32;
	epMenuInfo.nextpage.focuspic         = ART_ARROWSR;
	Menu_AddItem( &epMenuInfo.menu, &epMenuInfo.nextpage );

	//add selected map name
	epMenuInfo.mapname.generic.type  = MTYPE_PTEXT;
	epMenuInfo.mapname.generic.flags = QMF_CENTER_JUSTIFY|QMF_INACTIVE;
	epMenuInfo.mapname.generic.x	    = 320;
	epMenuInfo.mapname.generic.y	    = 440;
	epMenuInfo.mapname.string        = mapnamebuffer;
	epMenuInfo.mapname.style         = UI_CENTER|UI_BIGFONT;
	epMenuInfo.mapname.color         = text_color_normal;
	Menu_AddItem( &epMenuInfo.menu, &epMenuInfo.mapname );

	//add high score caption
	epMenuInfo.highScoreCaption.generic.type = MTYPE_TEXT;
	epMenuInfo.highScoreCaption.generic.flags = QMF_CENTER_JUSTIFY|QMF_INACTIVE;
	epMenuInfo.highScoreCaption.generic.x = 320;
	epMenuInfo.highScoreCaption.generic.y = 360;
	epMenuInfo.highScoreCaption.string = "HIGH SCORE:";
	epMenuInfo.highScoreCaption.style = UI_CENTER;
	epMenuInfo.highScoreCaption.color = text_color_normal;
	Menu_AddItem( &epMenuInfo.menu, &epMenuInfo.highScoreCaption );

	//add high score
	epMenuInfo.highScore.generic.type = MTYPE_TEXT;
	epMenuInfo.highScore.generic.flags = QMF_CENTER_JUSTIFY|QMF_INACTIVE;
	epMenuInfo.highScore.generic.x = 320;
	epMenuInfo.highScore.generic.y = 378;
	epMenuInfo.highScore.string = mapscorebuffer;
	epMenuInfo.highScore.style = UI_CENTER;
	epMenuInfo.mapname.color = text_color_normal;
	Menu_AddItem( &epMenuInfo.menu, &epMenuInfo.highScore );

	//add menu to stack
	UI_PushMenu( &epMenuInfo.menu );

	//filter the levels to show
	EPMenu_GametypeFilter();
}
