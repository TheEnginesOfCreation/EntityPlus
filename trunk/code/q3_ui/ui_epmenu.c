#include "ui_local.h"

#define ID_BACK		1
#define ID_NEXT		2
#define ID_PICTURES	3	// 4, 5, 6
#define ID_PREVPAGE 7
#define ID_NEXTPAGE 8

#define MAX_MAPSPERPAGE	4
#define MAX_MAPCOLS 2
#define MAX_MAPROWS 2
#define MAX_SERVERMAPS	64
#define MAX_NAMELENGTH	16

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

	char			maplist[MAX_SERVERMAPS][MAX_NAMELENGTH];
	int				page;
	int				currentmap;
	int				nummaps;
	int				maxpages;
} epMenuInfo_t;

static epMenuInfo_t	epMenuInfo;


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
	}
	
	Q_strupr( epMenuInfo.mapname.string );
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
UI_EPMenu_NextEvent

Callback for "next" button
===============
*/
static void UI_EPMenu_NextEvent( void* ptr, int notification ) {
	//TODO: implement
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
UI_EPLevelMenu

Builds the EntityPlus Single Player menu
===============
*/
void UI_EPLevelMenu( void ) {
	int i;
	int x, y;
	static char mapnamebuffer[64];

	//initialize menu
	memset( &epMenuInfo, 0, sizeof(epMenuInfo) );
	epMenuInfo.menu.fullscreen = qtrue;
	epMenuInfo.menu.wrapAround = qtrue;

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
	epMenuInfo.back.generic.type			= MTYPE_BITMAP;
	epMenuInfo.back.generic.name			= ART_BACK0;
	epMenuInfo.back.generic.flags			= QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS;
	epMenuInfo.back.generic.x				= 0;
	epMenuInfo.back.generic.y				= 480-64;
	//epMenuInfo.back.generic.callback		= UI_EPMenu_BackEvent;
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
	epMenuInfo.next.generic.callback		= UI_EPMenu_NextEvent;
	epMenuInfo.next.generic.id				= ID_NEXT;
	epMenuInfo.next.width					= 128;
	epMenuInfo.next.height					= 64;
	epMenuInfo.next.focuspic				= ART_NEXT1;
	Menu_AddItem( &epMenuInfo.menu, &epMenuInfo.next );


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
		
		epMenuInfo.mapbuttons[i].generic.type     = MTYPE_BITMAP;
		epMenuInfo.mapbuttons[i].generic.flags    = QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS|QMF_NODEFAULTINIT;
		epMenuInfo.mapbuttons[i].generic.id       = ID_PICTURES+i;
		epMenuInfo.mapbuttons[i].generic.callback = EPMenu_MapEvent;
		epMenuInfo.mapbuttons[i].generic.x	     = x - 30;
		epMenuInfo.mapbuttons[i].generic.y	     = y - 32;
		epMenuInfo.mapbuttons[i].width  		     = 256;
		epMenuInfo.mapbuttons[i].height  	     = 248;
		epMenuInfo.mapbuttons[i].generic.left     = x;
		epMenuInfo.mapbuttons[i].generic.top  	 = y;
		epMenuInfo.mapbuttons[i].generic.right    = x + 128;
		epMenuInfo.mapbuttons[i].generic.bottom   = y + 128;
		epMenuInfo.mapbuttons[i].focuspic         = ART_SELECT;
		Menu_AddItem( &epMenuInfo.menu, &epMenuInfo.mapbuttons[i] );
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

	//add menu to stack
	UI_PushMenu( &epMenuInfo.menu );
}