// Copyright (C) 1999-2000 Id Software, Inc.
//
/*
=======================================================================

MAIN MENU

=======================================================================
*/


#include "ui_local.h"


#define ID_SINGLEPLAYER				10
#define ID_SETUP					12
#define ID_MUTATORS					14
#define ID_EXIT						17

#define ART_OVERLAY					"menu/art/mainoverlay"
#define ART_LOGOMODEL				"models/entplus/logo/entpluslogo.md3"

#define MAIN_MENU_OVERLAY_WIDTH		256
#define MAIN_MENU_VERTICAL_SPACING	34
#define MAIN_MENU_MARGIN_RIGHT		32
#define MAIN_MENU_MARGIN_TOP		294



typedef struct {
	menuframework_s	menu;

	menutext_s		singleplayer;
	menutext_s		setup;
	menutext_s		mutators;
	menutext_s		exit;

	menutext_s		header;
	menubitmap_s	logo;
	menubitmap_s	overlay;

	qhandle_t		menuBackground1;
	qhandle_t		logoModel;

	//int			backgroundDelay;
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

	case ID_SETUP:
		UI_SetupMenu();
		break;

	case ID_MUTATORS:
		UI_MutatorsMenu();
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
	s_main.menuBackground1 = trap_R_RegisterShaderNoMip( "menu/backgrounds/01" );
	s_main.logoModel = trap_R_RegisterModel( ART_LOGOMODEL );
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
	float			x, y, w, h;
	//qtime_t tm;
	//int seed;

	if (strlen(s_errorMessage.errorMessage))
	{
		UI_DrawProportionalString_AutoWrapped( 320, 192, 600, 20, s_errorMessage.errorMessage, UI_CENTER|UI_SMALLFONT|UI_DROPSHADOW, menu_text_color );
	}
	else
	{
		UI_DrawHandlePic(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, s_main.menuBackground1 ); //background shader

		//logo model
		memset( &refdef, 0, sizeof( refdef ) );

		refdef.rdflags = RDF_NOWORLDMODEL;

		AxisClear( refdef.viewaxis );

		x = 0;
		y = 0;
		w = 640;
		h = 240;

		UI_AdjustFrom640( &x, &y, &w, &h );
		refdef.x = x;
		refdef.y = y;
		refdef.width = w;
		refdef.height = h;

		refdef.fov_x = 90;
		refdef.fov_y = 40;

		refdef.time = uis.realtime;

		origin[0] = 250;	//screen space z (lower value is closer to camera)
		origin[1] = 140;	//screen space x (lower value moves to the right)
		origin[2] = 15;		//screen space y (lower value moves downwards)

		trap_R_ClearScene();

		memset( &ent, 0, sizeof(ent) );

		VectorSet( angles, 15, 210, 5 );
		AnglesToAxis( angles, ent.axis );
		ent.hModel = s_main.logoModel;
		VectorCopy( origin, ent.origin );
		VectorCopy( origin, ent.lightingOrigin );
		ent.renderfx = RF_LIGHTING_ORIGIN | RF_NOSHADOW;
		VectorCopy( ent.origin, ent.oldorigin );

		trap_R_AddRefEntityToScene( &ent );

		trap_R_RenderScene( &refdef );

		/*
		//determine delay until next lighting strike
		if ( t == 270 ) {
			trap_RealTime(&tm);
			seed = 1;
			seed = seed * 31 + tm.tm_sec;
			seed = seed * 31 + tm.tm_min;
			seed = seed * 31 + tm.tm_hour;
			seed = seed * 31 + tm.tm_mday;
			srand( seed );
			
			s_main.backgroundDelay = 5000 + (1500 - (rand() % 3000));	//delay somewhere between 3500 and 6500 ms
		}
		*/

		Menu_Draw( &s_main.menu );		
	}

	if (uis.startTitleMusic) {
		trap_S_StartBackgroundTrack("music/fla22k_03.wav", "");
		uis.startTitleMusic = qfalse;
	}
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
	int		overlayX;

	trap_Cvar_Set( "sv_killserver", "1" );
	
	memset( &s_main, 0, sizeof(mainmenu_t) );
	memset( &s_errorMessage, 0, sizeof(errorMessage_t) );

	// com_errorMessage would need that too
	MainMenu_Cache();
	
	trap_Cvar_VariableStringBuffer( "com_errorMessage", s_errorMessage.errorMessage, sizeof(s_errorMessage.errorMessage) );
	if (strlen(s_errorMessage.errorMessage))
	{	
		s_errorMessage.menu.draw = Main_MenuDraw;
		s_errorMessage.menu.key = ErrorMessage_Key;
		s_errorMessage.menu.fullscreen = qtrue;
		s_errorMessage.menu.wrapAround = qtrue;
		s_errorMessage.menu.showlogo = qfalse;		

		trap_Key_SetCatcher( KEYCATCH_UI );
		uis.menusp = 0;
		UI_PushMenu ( &s_errorMessage.menu );
		return;
	}
	
	s_main.menu.draw = Main_MenuDraw;
	s_main.menu.fullscreen = qtrue;
	s_main.menu.wrapAround = qtrue;
	s_main.menu.showlogo = qfalse;

	y = MAIN_MENU_MARGIN_TOP;
	overlayX = SCREEN_WIDTH - (MAIN_MENU_OVERLAY_WIDTH + MAIN_MENU_MARGIN_RIGHT);

	//add overlay
	s_main.overlay.generic.type		= MTYPE_BITMAP;
	s_main.overlay.generic.name		= ART_OVERLAY;
	s_main.overlay.generic.flags	= QMF_INACTIVE;
	s_main.overlay.generic.x		= overlayX;
	s_main.overlay.generic.y		= y - 64;//y - 48;
	s_main.overlay.width  			= MAIN_MENU_OVERLAY_WIDTH;
	s_main.overlay.height			= MAIN_MENU_OVERLAY_WIDTH;

	//add header
	s_main.header.generic.type		= MTYPE_PTEXT;
	s_main.header.generic.flags		= QMF_INACTIVE;
	s_main.header.generic.x			= ((MAIN_MENU_OVERLAY_WIDTH - UI_ProportionalStringWidth("=ENTITYPLUS=")) / 2) + overlayX;
	s_main.header.generic.y			= y;
	s_main.header.string			= "=ENTITYPLUS=";
	s_main.header.color				= color_white;

	//add menu buttons
	y += MAIN_MENU_VERTICAL_SPACING;
	s_main.singleplayer.generic.type		= MTYPE_PTEXT;
	s_main.singleplayer.generic.flags		= QMF_PULSEIFFOCUS;
	s_main.singleplayer.generic.x			= ((MAIN_MENU_OVERLAY_WIDTH - UI_ProportionalStringWidth("NEW GAME")) / 2) + overlayX;
	s_main.singleplayer.generic.y			= y;
	s_main.singleplayer.generic.id			= ID_SINGLEPLAYER;
	s_main.singleplayer.generic.callback	= Main_MenuEvent; 
	s_main.singleplayer.string				= "NEW GAME";
	s_main.singleplayer.color				= color_black;

	/*
	y += MAIN_MENU_VERTICAL_SPACING;
	s_main.mutators.generic.type			= MTYPE_PTEXT;
	s_main.mutators.generic.flags			= QMF_PULSEIFFOCUS;
	s_main.mutators.generic.x				= ((MAIN_MENU_OVERLAY_WIDTH - UI_ProportionalStringWidth("MUTATORS")) / 2) + overlayX;
	s_main.mutators.generic.y				= y;
	s_main.mutators.generic.id				= ID_MUTATORS;
	s_main.mutators.generic.callback		= Main_MenuEvent; 
	s_main.mutators.string					= "MUTATORS";
	s_main.mutators.color					= color_black;
*/
	y += MAIN_MENU_VERTICAL_SPACING;
	s_main.setup.generic.type				= MTYPE_PTEXT;
	s_main.setup.generic.flags				= QMF_PULSEIFFOCUS;
	s_main.setup.generic.x					= ((MAIN_MENU_OVERLAY_WIDTH - UI_ProportionalStringWidth("SETUP")) / 2) + overlayX;
	s_main.setup.generic.y					= y;
	s_main.setup.generic.id					= ID_SETUP;
	s_main.setup.generic.callback			= Main_MenuEvent; 
	s_main.setup.string						= "SETUP";
	s_main.setup.color						= color_black;	

	y += MAIN_MENU_VERTICAL_SPACING;
	s_main.exit.generic.type				= MTYPE_PTEXT;
	s_main.exit.generic.flags				= QMF_PULSEIFFOCUS;
	s_main.exit.generic.x					= ((MAIN_MENU_OVERLAY_WIDTH - UI_ProportionalStringWidth("EXIT")) / 2) + overlayX;
	s_main.exit.generic.y					= y;
	s_main.exit.generic.id					= ID_EXIT;
	s_main.exit.generic.callback			= Main_MenuEvent; 
	s_main.exit.string						= "EXIT";
	s_main.exit.color						= color_black;

	Menu_AddItem( &s_main.menu,	&s_main.overlay );
	Menu_AddItem( &s_main.menu,	&s_main.header );
	Menu_AddItem( &s_main.menu,	&s_main.singleplayer );
	//Menu_AddItem( &s_main.menu,	&s_main.mutators );
	Menu_AddItem( &s_main.menu,	&s_main.setup );
	Menu_AddItem( &s_main.menu,	&s_main.exit );             

	trap_Key_SetCatcher( KEYCATCH_UI );
	uis.menusp = 0;
	UI_PushMenu ( &s_main.menu );

	uis.startTitleMusic = qtrue;	
}
