#include "ui_local.h"

#define ID_BACK		1
#define ID_NEXT		2
#define ID_PICTURES	3	// 4, 5, 6

#define MAX_MAPSPERPAGE	4
#define MAX_MAPCOLS 2
#define MAX_MAPROWS 2
#define MAX_SERVERMAPS	64
#define MAX_NAMELENGTH	16

#define ART_BACK0		"menu/art/back_0"
#define ART_BACK1		"menu/art/back_1"	
#define ART_FIGHT0		"menu/art/fight_0"
#define ART_FIGHT1		"menu/art/fight_1"
#define ART_FRAMEL		"menu/art/frame2_l"
#define ART_FRAMER		"menu/art/frame1_r"
#define ART_SELECTED	"menu/art/maps_selected"
#define ART_UNKNOWNMAP	"menu/art/unknownmap"

typedef struct {
	menuframework_s	menu;

	menutext_s		banner;

	menubitmap_s	framel;
	menubitmap_s	framer;
	menubitmap_s	item_back;
	menubitmap_s	item_next;
	menubitmap_s	mappics[MAX_MAPSPERPAGE];

	char			maplist[MAX_SERVERMAPS][MAX_NAMELENGTH];
	int				page;
} epMenuInfo_t;

static epMenuInfo_t	epMenuInfo;

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
	n = 0;
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
===============
UI_EPMenu_BackEvent

Callback for "back" button
===============
*/
static void UI_EPMenu_BackEvent( void* ptr, int notification ) {
	if (notification != QM_ACTIVATED) {
		return;
	}

	UI_PopMenu();
}



void UI_EPLevelMenu( void ) {
	int i;
	int x, y;

	//initialize menu
	memset( &epMenuInfo, 0, sizeof(epMenuInfo) );
	epMenuInfo.menu.fullscreen = qtrue;
	epMenuInfo.menu.wrapAround = qtrue;

	//register artwork shaders
	trap_R_RegisterShaderNoMip( ART_FRAMEL );
	trap_R_RegisterShaderNoMip( ART_FRAMER );
	trap_R_RegisterShaderNoMip( ART_BACK0 );
	trap_R_RegisterShaderNoMip( ART_BACK1 );
	trap_R_RegisterShaderNoMip( ART_FIGHT0 );
	trap_R_RegisterShaderNoMip( ART_FIGHT1 );
	trap_R_RegisterShaderNoMip( ART_SELECTED );
	trap_R_RegisterShaderNoMip( ART_UNKNOWNMAP );

	//add text banner
	epMenuInfo.banner.generic.type  = MTYPE_BTEXT;
	epMenuInfo.banner.generic.x	   = 320;
	epMenuInfo.banner.generic.y	   = 16;
	epMenuInfo.banner.string        = "SINGLE PLAYER";
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
	Menu_AddItem( &epMenuInfo.menu, &epMenuInfo.framel );

	//add right frame
	epMenuInfo.framer.generic.type  = MTYPE_BITMAP;
	epMenuInfo.framer.generic.name  = ART_FRAMER;
	epMenuInfo.framer.generic.flags = QMF_INACTIVE;
	epMenuInfo.framer.generic.x	   = 376;
	epMenuInfo.framer.generic.y	   = 76;
	epMenuInfo.framer.width  	   = 256;
	epMenuInfo.framer.height  	   = 334;
	Menu_AddItem( &epMenuInfo.menu, &epMenuInfo.framer );

	//add back button
	epMenuInfo.item_back.generic.type			= MTYPE_BITMAP;
	epMenuInfo.item_back.generic.name			= ART_BACK0;
	epMenuInfo.item_back.generic.flags			= QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS;
	epMenuInfo.item_back.generic.x				= 0;
	epMenuInfo.item_back.generic.y				= 480-64;
	epMenuInfo.item_back.generic.callback		= UI_EPMenu_BackEvent;
	epMenuInfo.item_back.generic.id				= ID_BACK;
	epMenuInfo.item_back.width					= 128;
	epMenuInfo.item_back.height					= 64;
	epMenuInfo.item_back.focuspic				= ART_BACK1;
	Menu_AddItem( &epMenuInfo.menu, &epMenuInfo.item_back );

	//add fight button
	epMenuInfo.item_next.generic.type			= MTYPE_BITMAP;
	epMenuInfo.item_next.generic.name			= ART_FIGHT0;
	epMenuInfo.item_next.generic.flags			= QMF_RIGHT_JUSTIFY|QMF_PULSEIFFOCUS;
	epMenuInfo.item_next.generic.x				= 640;
	epMenuInfo.item_next.generic.y				= 480-64;
	//epMenuInfo.item_next.generic.callback		= UI_SPLevelMenu_NextEvent;
	epMenuInfo.item_next.generic.id				= ID_NEXT;
	epMenuInfo.item_next.width					= 128;
	epMenuInfo.item_next.height					= 64;
	epMenuInfo.item_next.focuspic				= ART_FIGHT1;
	Menu_AddItem( &epMenuInfo.menu, &epMenuInfo.item_next );


	//add map selectors
	for ( i = 0; i < MAX_MAPSPERPAGE; i++)
	{
		x =	(i % MAX_MAPCOLS) * (128+8) + 188;
		y = (i / MAX_MAPROWS) * (128+8) + 96;

		epMenuInfo.mappics[i].generic.type   = MTYPE_BITMAP;
		epMenuInfo.mappics[i].generic.flags  = QMF_LEFT_JUSTIFY|QMF_INACTIVE;
		epMenuInfo.mappics[i].generic.x	    = x;
		epMenuInfo.mappics[i].generic.y	    = y;
		epMenuInfo.mappics[i].generic.id		= ID_PICTURES+i;
		epMenuInfo.mappics[i].width  		= 128;
		epMenuInfo.mappics[i].height  	    = 96;
		epMenuInfo.mappics[i].focuspic       = ART_SELECTED;
		epMenuInfo.mappics[i].errorpic       = ART_UNKNOWNMAP;
		epMenuInfo.mappics[i].generic.ownerdraw = EPMenu_LevelshotDraw;
		Menu_AddItem( &epMenuInfo.menu, &epMenuInfo.mappics[i] );
		
	}
	UI_PushMenu( &epMenuInfo.menu );
}