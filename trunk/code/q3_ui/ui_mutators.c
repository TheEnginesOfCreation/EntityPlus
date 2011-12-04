#include "ui_local.h"


#define ART_FRAMEL				"menu/art/frame2_l"
#define ART_FRAMER				"menu/art/frame1_r"
#define ART_BACK0				"menu/art/back_0"
#define ART_BACK1				"menu/art/back_1"

#define MUTATORS_X_POS		360


#define ID_MACHINEGUNONLY		1
#define	ID_RESETSCOREAFTERDEATH	2
#define ID_BACK					99

typedef struct {
	menuframework_s		menu;

	menutext_s			banner;
	menubitmap_s		framel;
	menubitmap_s		framer;
	
	menuradiobutton_s	machinegunonly;
	menuradiobutton_s	resetscoreafterdeath;

	menubitmap_s		back;
} mutators_t;

static mutators_t s_mutators;

static void Mutators_SetMenuItems( void ) {
	int value = trap_Cvar_VariableValue("g_mutators");

	s_mutators.machinegunonly.curvalue = (value & ID_MACHINEGUNONLY != 0);
}

static void Mutators_UpdateCvar( int id ) {
	int value = trap_Cvar_VariableValue("g_mutators");

	if ( value & id )
		value -= id;
	else
		value += id;

	trap_Cvar_SetValue("g_mutators", value);
}

static void Mutators_Event( void* ptr, int notification ) {
	if( notification != QM_ACTIVATED ) {
		return;
	}

	switch( ((menucommon_s*)ptr)->id ) {
		case ID_BACK:
			UI_PopMenu();
			break;

		case ID_MACHINEGUNONLY:
			Mutators_UpdateCvar(ID_MACHINEGUNONLY);
			break;

		case ID_RESETSCOREAFTERDEATH:
			Mutators_UpdateCvar(ID_RESETSCOREAFTERDEATH);
			break;
	}
}

static void Mutators_MenuInit( void ) {
	int				y;

	memset( &s_mutators, 0, sizeof(mutators_t) );

	Mutators_Cache();

	s_mutators.menu.wrapAround = qtrue;
	s_mutators.menu.fullscreen = qtrue;

	s_mutators.banner.generic.type	= MTYPE_BTEXT;
	s_mutators.banner.generic.x		= 320;
	s_mutators.banner.generic.y		= 16;
	s_mutators.banner.string		= "MUTATORS";
	s_mutators.banner.color         = color_white;
	s_mutators.banner.style         = UI_CENTER;

	s_mutators.framel.generic.type  = MTYPE_BITMAP;
	s_mutators.framel.generic.name  = ART_FRAMEL;
	s_mutators.framel.generic.flags = QMF_INACTIVE;
	s_mutators.framel.generic.x		= 0;
	s_mutators.framel.generic.y		= 78;
	s_mutators.framel.width  		= 256;
	s_mutators.framel.height  		 = 329;

	s_mutators.framer.generic.type  = MTYPE_BITMAP;
	s_mutators.framer.generic.name  = ART_FRAMER;
	s_mutators.framer.generic.flags = QMF_INACTIVE;
	s_mutators.framer.generic.x		= 376;
	s_mutators.framer.generic.y		= 76;
	s_mutators.framer.width  		= 256;
	s_mutators.framer.height  		= 334;

	//machinegun only
	y = 144;
	s_mutators.machinegunonly.generic.type        = MTYPE_RADIOBUTTON;
	s_mutators.machinegunonly.generic.name	      = "Machinegun only:";
	s_mutators.machinegunonly.generic.flags	      = QMF_PULSEIFFOCUS|QMF_SMALLFONT;
	s_mutators.machinegunonly.generic.callback    = Mutators_Event;
	s_mutators.machinegunonly.generic.id          = ID_MACHINEGUNONLY;
	s_mutators.machinegunonly.generic.x	          = MUTATORS_X_POS;
	s_mutators.machinegunonly.generic.y	          = y;

	//reset score after death
	y += BIGCHAR_HEIGHT;
	s_mutators.resetscoreafterdeath.generic.type		= MTYPE_RADIOBUTTON;
	s_mutators.resetscoreafterdeath.generic.name		= "Reset score after death:";
	s_mutators.resetscoreafterdeath.generic.flags		= QMF_PULSEIFFOCUS|QMF_SMALLFONT;
	s_mutators.resetscoreafterdeath.generic.callback	= Mutators_Event;
	s_mutators.resetscoreafterdeath.generic.id			= ID_RESETSCOREAFTERDEATH;
	s_mutators.resetscoreafterdeath.generic.x			= MUTATORS_X_POS;
	s_mutators.resetscoreafterdeath.generic.y			= y;

	s_mutators.back.generic.type		= MTYPE_BITMAP;
	s_mutators.back.generic.name		= ART_BACK0;
	s_mutators.back.generic.flags		= QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS;
	s_mutators.back.generic.callback	= Mutators_Event;
	s_mutators.back.generic.id			= ID_BACK;
	s_mutators.back.generic.x			= 0;
	s_mutators.back.generic.y			= 480-64;
	s_mutators.back.width				= 128;
	s_mutators.back.height				= 64;
	s_mutators.back.focuspic			= ART_BACK1;

	Menu_AddItem( &s_mutators.menu, &s_mutators.banner );
	Menu_AddItem( &s_mutators.menu, &s_mutators.framel );
	Menu_AddItem( &s_mutators.menu, &s_mutators.framer );
	
	Menu_AddItem( &s_mutators.menu, &s_mutators.machinegunonly );
	Menu_AddItem( &s_mutators.menu, &s_mutators.resetscoreafterdeath );
	Menu_AddItem( &s_mutators.menu, &s_mutators.back );

	Mutators_SetMenuItems();
}


void Mutators_Cache( void ) {
	trap_R_RegisterShaderNoMip( ART_FRAMEL );
	trap_R_RegisterShaderNoMip( ART_FRAMER );
	trap_R_RegisterShaderNoMip( ART_BACK0 );
	trap_R_RegisterShaderNoMip( ART_BACK1 );
}

void UI_MutatorsMenu( void ) {
	Mutators_MenuInit();
	UI_PushMenu( &s_mutators.menu );
}