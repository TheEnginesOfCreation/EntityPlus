// Copyright (C) 1999-2000 Id Software, Inc.
//
/*
=======================================================================

MAIN MENU

=======================================================================
*/


#include "ui_local.h"


#define ID_SINGLEPLAYER				10
#define ID_MULTIPLAYER				11
#define ID_SETUP					12
#define ID_DEMOS					13
#define ID_CINEMATICS				14
#define ID_TEAMARENA				15
#define ID_MODS						16
#define ID_EXIT						17

#define MAIN_BANNER_MODEL				"models/mapobjects/banner/banner5.md3"
#define MAIN_MENU_MODEL_KEY_MASTER		"models/powerups/keys/key_master.md3"
#define MAIN_MENU_MODEL_KEY_GOLD		"models/powerups/keys/key_gold.md3"
#define MAIN_MENU_MODEL_KEY_SILVER		"models/powerups/keys/key_silver.md3"
#define MAIN_MENU_MODEL_KEY_RED			"models/powerups/keys/keycard-r.md3"
#define MAIN_MENU_MODEL_KEY_BLUE		"models/powerups/keys/keycard-b.md3"
#define MAIN_MENU_MODEL_BACKPACK		"models/powerups/backpack/backpack.md3"
#define MAIN_MENU_MODEL_ROCKET_LAUNCHER	"models/weapons2/rocketl/rocketl.md3"
#define MAIN_MENU_MODEL_ARMOR_RED		"models/powerups/armor/armor_red.md3"
#define MAIN_MENU_MODEL_AMMO_MG			"models/powerups/ammo/machinegunam.md3"
#define MAIN_MENU_MODEL_SKULL			"models/gibs/skull.md3"

#define ART_LOGO						"menu/art/logo"

#define MAIN_MENU_VERTICAL_SPACING	34



typedef struct {
	menuframework_s	menu;

	menutext_s		singleplayer;
	menutext_s		multiplayer;
	menutext_s		setup;
	menutext_s		demos;
	menutext_s		cinematics;
	menutext_s		teamArena;
	menutext_s		mods;
	menutext_s		exit;

	menubitmap_s	logo;

	qhandle_t		bannerModel;
	qhandle_t		menuModel;
	vec3_t			menuModelOrigin;
	vec3_t			menuModelAngles;
} mainmenu_t;


static mainmenu_t s_main;

typedef struct {
	menuframework_s menu;	
	char errorMessage[4096];
} errorMessage_t;

static errorMessage_t s_errorMessage;

/*
=================
MainMenu_ExitAction
=================
*/
static void MainMenu_ExitAction( qboolean result ) {
	if( !result ) {
		return;
	}
	UI_PopMenu();
	UI_CreditMenu();
}



/*
=================
Main_MenuEvent
=================
*/
void Main_MenuEvent (void* ptr, int event) {
	if( event != QM_ACTIVATED ) {
		return;
	}

	switch( ((menucommon_s*)ptr)->id ) {
	case ID_SINGLEPLAYER:
		UI_EPLevelMenu();
		break;

	case ID_MULTIPLAYER:
		UI_ArenaServersMenu();
		break;

	case ID_SETUP:
		UI_SetupMenu();
		break;

	case ID_DEMOS:
		UI_DemosMenu();
		break;

	case ID_CINEMATICS:
		UI_CinematicsMenu();
		break;

	case ID_MODS:
		UI_ModsMenu();
		break;

	case ID_TEAMARENA:
		trap_Cvar_Set( "fs_game", "missionpack");
		trap_Cmd_ExecuteText( EXEC_APPEND, "vid_restart;" );
		break;

	case ID_EXIT:
		UI_ConfirmMenu( "EXIT GAME?", NULL, MainMenu_ExitAction );
		break;
	}
}


/*
===============
MainMenu_Cache
===============
*/
void MainMenu_Cache( void ) {
	int r;
	qtime_t tm;
	int seed;
	
	trap_R_RegisterShaderNoMip( ART_LOGO );

	s_main.bannerModel = trap_R_RegisterModel( MAIN_BANNER_MODEL );

	trap_RealTime(&tm);
	seed = 1;
	seed = seed * 31 + tm.tm_sec;
	seed = seed * 31 + tm.tm_min;
	seed = seed * 31 + tm.tm_hour;
	seed = seed * 31 + tm.tm_mday;
	srand( seed );
	
	r = rand() % MM_NUM_MENUMODELS;

	//set default origin
	s_main.menuModelOrigin[0] = 100;	//depth on the 2D menu plane
	s_main.menuModelOrigin[1] = -5;	//X on the 2D menu plane
	s_main.menuModelOrigin[2] = -10;	//Y on the 2D menu plane

	//set default angles
	VectorSet( s_main.menuModelAngles, 0, 0, 0 );

	//if gibs are disabled and the skull was selected for the menu model, select a different menu model
	if (trap_Cvar_VariableValue( "cg_gibs" ) == 0)
		while (r == MM_SKULL)
			r = rand() % MM_NUM_MENUMODELS;

	switch ( r ) {
		default:
		case MM_KEY_MASTER:
			s_main.menuModel = trap_R_RegisterModel( MAIN_MENU_MODEL_KEY_MASTER );
			break;
		case MM_KEY_GOLD:
			s_main.menuModel = trap_R_RegisterModel( MAIN_MENU_MODEL_KEY_GOLD );
			break;
		case MM_KEY_SILVER:
			s_main.menuModel = trap_R_RegisterModel( MAIN_MENU_MODEL_KEY_SILVER );
			break;
		case MM_KEY_RED:
			s_main.menuModelOrigin[0] = 150;
			VectorSet( s_main.menuModelAngles, 0, 0, 15 );
			s_main.menuModel = trap_R_RegisterModel( MAIN_MENU_MODEL_KEY_RED );
			break;
		case MM_KEY_BLUE:
			s_main.menuModelOrigin[0] = 150;
			VectorSet( s_main.menuModelAngles, 15, 0, -15 );
			s_main.menuModel = trap_R_RegisterModel( MAIN_MENU_MODEL_KEY_BLUE );
			break;
		case MM_BACKPACK:
			s_main.menuModelOrigin[0] = 150;
			VectorSet( s_main.menuModelAngles, 15, 0, -15 );
			s_main.menuModel = trap_R_RegisterModel( MAIN_MENU_MODEL_BACKPACK );
			break;
		case MM_ROCKET_LAUNCHER:
			s_main.menuModelOrigin[0] = 150;
			s_main.menuModelOrigin[2] = 0;
			VectorSet( s_main.menuModelAngles, -15, 0, 15 );
			s_main.menuModel = trap_R_RegisterModel( MAIN_MENU_MODEL_ROCKET_LAUNCHER );
			break;
		case MM_ARMOR_RED:
			s_main.menuModelOrigin[0] = 175;
			s_main.menuModel = trap_R_RegisterModel( MAIN_MENU_MODEL_ARMOR_RED );
			break;
		case MM_AMMO_MG:
			s_main.menuModelOrigin[0] = 200;
			s_main.menuModelOrigin[2] = 0;
			VectorSet( s_main.menuModelAngles, 0, 0, 15 );
			s_main.menuModel = trap_R_RegisterModel( MAIN_MENU_MODEL_AMMO_MG );
			break;
		case MM_SKULL:
			s_main.menuModelOrigin[2] = 0;
			VectorSet( s_main.menuModelAngles, 0, 0, 10 );
			s_main.menuModel = trap_R_RegisterModel( MAIN_MENU_MODEL_SKULL );
			break;
	}
}

sfxHandle_t ErrorMessage_Key(int key)
{
	trap_Cvar_Set( "com_errorMessage", "" );
	UI_MainMenu();
	return (menu_null_sound);
}

/*
===============
Main_MenuDraw
TTimo: this function is common to the main menu and errorMessage menu
===============
*/

static void Main_MenuDraw( void ) {
	refdef_t		refdef;
	refEntity_t		ent;
	vec3_t			origin;	
	vec3_t			angles;
	float			adjust;
	float			x, y, w, h;
	vec4_t			color = {0, 0, 0.5, 1};
	refdef_t		refdef2;
	refEntity_t		ent2;
	vec3_t			angles2;

	/*
	// setup the refdef for banner model

	memset( &refdef, 0, sizeof( refdef ) );

	refdef.rdflags = RDF_NOWORLDMODEL;

	AxisClear( refdef.viewaxis );

	x = 0;
	y = 0;
	w = 640;
	h = 120;
	UI_AdjustFrom640( &x, &y, &w, &h );
	refdef.x = x;
	refdef.y = y;
	refdef.width = w;
	refdef.height = h;

	adjust = 0; // JDC: Kenneth asked me to stop this 1.0 * sin( (float)uis.realtime / 1000 );
	refdef.fov_x = 60 + adjust;
	refdef.fov_y = 19.6875 + adjust;

	refdef.time = uis.realtime;

	origin[0] = 300;
	origin[1] = 0;
	origin[2] = -32;

	trap_R_ClearScene();

	// add the banner model

	memset( &ent, 0, sizeof(ent) );

	adjust = 5.0 * sin( (float)uis.realtime / 5000 );
	VectorSet( angles, 0, 180 + adjust, 0 );
	AnglesToAxis( angles, ent.axis );
	ent.hModel = s_main.bannerModel;
	VectorCopy( origin, ent.origin );
	VectorCopy( origin, ent.lightingOrigin );
	ent.renderfx = RF_LIGHTING_ORIGIN | RF_NOSHADOW;
	VectorCopy( ent.origin, ent.oldorigin );

	trap_R_AddRefEntityToScene( &ent );

	trap_R_RenderScene( &refdef );
*/



	// setup the refdef for menu model

	memset( &refdef2, 0, sizeof( refdef2 ) );

	refdef2.rdflags = RDF_NOWORLDMODEL;

	AxisClear( refdef2.viewaxis );

	x = 200;
	y = 135;
	w = 440;
	h = 345;
	UI_AdjustFrom640( &x, &y, &w, &h );
	refdef2.x = x;
	refdef2.y = y;
	refdef2.width = w;
	refdef2.height = h;

	refdef2.fov_x = 30;
	refdef2.fov_y = 19.6875;

	refdef2.time = uis.realtime;

	// add the menu model

	memset( &ent2, 0, sizeof(ent2) );

	adjust = uis.realtime / 20;		//makes it rotate
	VectorCopy(s_main.menuModelAngles, angles2);
	angles2[1] += adjust;
	AnglesToAxis( angles2, ent2.axis );
	ent2.hModel = s_main.menuModel;
	VectorCopy( s_main.menuModelOrigin, ent2.origin );
	VectorCopy( s_main.menuModelOrigin, ent2.lightingOrigin );
	ent2.renderfx = RF_LIGHTING_ORIGIN | RF_NOSHADOW;
	VectorCopy( ent2.origin, ent2.oldorigin );

	trap_R_AddRefEntityToScene( &ent2 );

	trap_R_RenderScene( &refdef2 );
	
	if (strlen(s_errorMessage.errorMessage))
	{
		UI_DrawProportionalString_AutoWrapped( 320, 192, 600, 20, s_errorMessage.errorMessage, UI_CENTER|UI_SMALLFONT|UI_DROPSHADOW, menu_text_color );
	}
	else
	{
		// standard menu drawing
		Menu_Draw( &s_main.menu );		
	}

	if (uis.demoversion) {
		UI_DrawProportionalString( 320, 372, "DEMO      FOR MATURE AUDIENCES      DEMO", UI_CENTER|UI_SMALLFONT, color );
		UI_DrawString( 320, 400, "Quake III Arena(c) 1999-2000, Id Software, Inc.  All Rights Reserved", UI_CENTER|UI_SMALLFONT, color );
	} else {
		UI_DrawString( 320, 430, "Get more EntityPlus info at http://code.google.com/p/entityplus", UI_CENTER|UI_SMALLFONT, color );
		UI_DrawString( 320, 450, "Quake III Arena(c) 1999-2000, Id Software, Inc.  All Rights Reserved", UI_CENTER|UI_SMALLFONT, color );
	}
}


/*
===============
UI_TeamArenaExists
===============
*/
static qboolean UI_TeamArenaExists( void ) {
	int		numdirs;
	char	dirlist[2048];
	char	*dirptr;
  char  *descptr;
	int		i;
	int		dirlen;

	numdirs = trap_FS_GetFileList( "$modlist", "", dirlist, sizeof(dirlist) );
	dirptr  = dirlist;
	for( i = 0; i < numdirs; i++ ) {
		dirlen = strlen( dirptr ) + 1;
    descptr = dirptr + dirlen;
		if (Q_stricmp(dirptr, "missionpack") == 0) {
			return qtrue;
		}
    dirptr += dirlen + strlen(descptr) + 1;
	}
	return qfalse;
}


/*
===============
UI_MainMenu

The main menu only comes up when not in a game,
so make sure that the attract loop server is down
and that local cinematics are killed
===============
*/
void UI_MainMenu( void ) {
	int		y;
	qboolean teamArena = qfalse;
	int		style = UI_CENTER | UI_DROPSHADOW;

	trap_Cvar_Set( "sv_killserver", "1" );

	if( !uis.demoversion && !ui_cdkeychecked.integer ) {
		char	key[17];

		trap_GetCDKey( key, sizeof(key) );
		if( trap_VerifyCDKey( key, NULL ) == qfalse ) {
			UI_CDKeyMenu();
			return;
		}
	}
	
	memset( &s_main, 0 ,sizeof(mainmenu_t) );
	memset( &s_errorMessage, 0 ,sizeof(errorMessage_t) );

	// com_errorMessage would need that too
	MainMenu_Cache();
	
	trap_Cvar_VariableStringBuffer( "com_errorMessage", s_errorMessage.errorMessage, sizeof(s_errorMessage.errorMessage) );
	if (strlen(s_errorMessage.errorMessage))
	{	
		s_errorMessage.menu.draw = Main_MenuDraw;
		s_errorMessage.menu.key = ErrorMessage_Key;
		s_errorMessage.menu.fullscreen = qtrue;
		s_errorMessage.menu.wrapAround = qtrue;
		s_errorMessage.menu.showlogo = qtrue;		

		trap_Key_SetCatcher( KEYCATCH_UI );
		uis.menusp = 0;
		UI_PushMenu ( &s_errorMessage.menu );
		
		return;
	}
	
	s_main.menu.draw = Main_MenuDraw;
	s_main.menu.fullscreen = qtrue;
	s_main.menu.wrapAround = qtrue;
	s_main.menu.showlogo = qfalse;

	//add logo
	s_main.logo.generic.type  = MTYPE_BITMAP;
	s_main.logo.generic.name  = ART_LOGO;
	s_main.logo.generic.flags = QMF_INACTIVE|QMF_CENTER_JUSTIFY;
	s_main.logo.generic.x	   = 320;
	s_main.logo.generic.y	   = 0;
	s_main.logo.width  			= 512;
	s_main.logo.height  	   = 128;

	//add menu buttons
	y = 134;
	s_main.singleplayer.generic.type		= MTYPE_PTEXT;
	s_main.singleplayer.generic.flags		= QMF_PULSEIFFOCUS;
	s_main.singleplayer.generic.x			= 64;
	s_main.singleplayer.generic.y			= y;
	s_main.singleplayer.generic.id			= ID_SINGLEPLAYER;
	s_main.singleplayer.generic.callback	= Main_MenuEvent; 
	s_main.singleplayer.string				= "SINGLE PLAYER";
	s_main.singleplayer.color				= color_lightBlue;
	s_main.singleplayer.style				= UI_DROPSHADOW;

	y += MAIN_MENU_VERTICAL_SPACING;
	s_main.multiplayer.generic.type			= MTYPE_PTEXT;
	s_main.multiplayer.generic.flags		= QMF_PULSEIFFOCUS;
	s_main.multiplayer.generic.x			= 64;
	s_main.multiplayer.generic.y			= y;
	s_main.multiplayer.generic.id			= ID_MULTIPLAYER;
	s_main.multiplayer.generic.callback		= Main_MenuEvent; 
	s_main.multiplayer.string				= "MULTIPLAYER";
	s_main.multiplayer.color				= color_lightBlue;
	s_main.multiplayer.style				= UI_DROPSHADOW;

	y += MAIN_MENU_VERTICAL_SPACING;
	s_main.setup.generic.type				= MTYPE_PTEXT;
	s_main.setup.generic.flags				= QMF_PULSEIFFOCUS;
	s_main.setup.generic.x					= 64;
	s_main.setup.generic.y					= y;
	s_main.setup.generic.id					= ID_SETUP;
	s_main.setup.generic.callback			= Main_MenuEvent; 
	s_main.setup.string						= "SETUP";
	s_main.setup.color						= color_lightBlue;
	s_main.setup.style						= UI_DROPSHADOW;

	y += MAIN_MENU_VERTICAL_SPACING;
	s_main.demos.generic.type				= MTYPE_PTEXT;
	s_main.demos.generic.flags				= QMF_PULSEIFFOCUS;
	s_main.demos.generic.x					= 64;
	s_main.demos.generic.y					= y;
	s_main.demos.generic.id					= ID_DEMOS;
	s_main.demos.generic.callback			= Main_MenuEvent; 
	s_main.demos.string						= "DEMOS";
	s_main.demos.color						= color_lightBlue;
	s_main.demos.style						= UI_DROPSHADOW;

	y += MAIN_MENU_VERTICAL_SPACING;
	s_main.cinematics.generic.type			= MTYPE_PTEXT;
	s_main.cinematics.generic.flags			= QMF_PULSEIFFOCUS;
	s_main.cinematics.generic.x				= 64;
	s_main.cinematics.generic.y				= y;
	s_main.cinematics.generic.id			= ID_CINEMATICS;
	s_main.cinematics.generic.callback		= Main_MenuEvent; 
	s_main.cinematics.string				= "CINEMATICS";
	s_main.cinematics.color					= color_lightBlue;
	s_main.cinematics.style					= UI_DROPSHADOW;

	if (UI_TeamArenaExists()) {
		teamArena = qtrue;
		y += MAIN_MENU_VERTICAL_SPACING;
		s_main.teamArena.generic.type			= MTYPE_PTEXT;
		s_main.teamArena.generic.flags			= QMF_PULSEIFFOCUS;
		s_main.teamArena.generic.x				= 64;
		s_main.teamArena.generic.y				= y;
		s_main.teamArena.generic.id				= ID_TEAMARENA;
		s_main.teamArena.generic.callback		= Main_MenuEvent; 
		s_main.teamArena.string					= "TEAM ARENA";
		s_main.teamArena.color					= color_lightBlue;
		s_main.teamArena.style					= UI_DROPSHADOW;
	}

	y += MAIN_MENU_VERTICAL_SPACING;
	s_main.mods.generic.type			= MTYPE_PTEXT;
	s_main.mods.generic.flags			= QMF_PULSEIFFOCUS;
	s_main.mods.generic.x				= 64;
	s_main.mods.generic.y				= y;
	s_main.mods.generic.id				= ID_MODS;
	s_main.mods.generic.callback		= Main_MenuEvent; 
	s_main.mods.string					= "MODS";
	s_main.mods.color					= color_lightBlue;
	s_main.mods.style					= UI_DROPSHADOW;

	y += MAIN_MENU_VERTICAL_SPACING;
	s_main.exit.generic.type				= MTYPE_PTEXT;
	s_main.exit.generic.flags				= QMF_PULSEIFFOCUS;
	s_main.exit.generic.x					= 64;
	s_main.exit.generic.y					= y;
	s_main.exit.generic.id					= ID_EXIT;
	s_main.exit.generic.callback			= Main_MenuEvent; 
	s_main.exit.string						= "EXIT";
	s_main.exit.color						= color_lightBlue;
	s_main.exit.style						= UI_DROPSHADOW;

	Menu_AddItem( &s_main.menu, &s_main.logo );
	Menu_AddItem( &s_main.menu,	&s_main.singleplayer );
	Menu_AddItem( &s_main.menu,	&s_main.multiplayer );
	Menu_AddItem( &s_main.menu,	&s_main.setup );
	Menu_AddItem( &s_main.menu,	&s_main.demos );
	Menu_AddItem( &s_main.menu,	&s_main.cinematics );
	if (teamArena) {
		Menu_AddItem( &s_main.menu,	&s_main.teamArena );
	}
	Menu_AddItem( &s_main.menu,	&s_main.mods );
	Menu_AddItem( &s_main.menu,	&s_main.exit );             

	trap_Key_SetCatcher( KEYCATCH_UI );
	uis.menusp = 0;
	UI_PushMenu ( &s_main.menu );
		
}
