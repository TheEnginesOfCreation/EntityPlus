// INCLUDE FILES
#include "ui_local.h"

// CONSTANT DEFINITIONS

#define SCROLLSPEED	3.00 // The scrolling speed in pixels per second.
						  

//#define BACKGROUND_SHADER
//uncomment this if you want a background
 
// STRUCTURES

typedef struct {
	menuframework_s	menu;
} creditsmenu_t;

static creditsmenu_t	s_credits;

int starttime; 
float mvolume; 
               

// change this to change the background colour on credits
vec4_t color_background	        = {0.00, 0.00, 0.00, 1.00};


qhandle_t	BackgroundShader; 

typedef struct
{
	char *string;
	int style;
	vec4_t *colour;
} cr_line;

cr_line credits[] = { // edit this as necessary for your credits
	
{ "EntityPlus", UI_CENTER|UI_GIANTFONT|UI_PULSE, &color_ochre },
{ "Credits", UI_CENTER|UI_SMALLFONT, &color_white },
{ "", UI_CENTER|UI_SMALLFONT, &color_blue },
{ "Project Lead and Programming", UI_CENTER|UI_BIGFONT, &color_ochre },
{ "Eraser", UI_CENTER|UI_SMALLFONT, &color_white },
{ "", UI_CENTER|UI_SMALLFONT, &color_blue },
{ "Additional Programming", UI_CENTER|UI_BIGFONT, &color_ochre },
{ "^misantropia^", UI_CENTER|UI_SMALLFONT, &color_white },
{ "Kaz", UI_CENTER|UI_SMALLFONT, &color_white },
{ "cyr", UI_CENTER|UI_SMALLFONT, &color_white },
{ "gooball", UI_CENTER|UI_SMALLFONT, &color_white },
{ "", UI_CENTER|UI_SMALLFONT, &color_blue },
{ "Programming Support", UI_CENTER|UI_BIGFONT, &color_ochre },
{ "^misantropia^", UI_CENTER|UI_SMALLFONT, &color_white },
{ "Perle", UI_CENTER|UI_SMALLFONT, &color_white },
{ "", UI_CENTER|UI_SMALLFONT, &color_blue },
{ "Testing & Feedback", UI_CENTER|UI_BIGFONT, &color_ochre },
{ "AEon", UI_CENTER|UI_SMALLFONT, &color_white },
{ "EmeraldTiger", UI_CENTER|UI_SMALLFONT, &color_white },
{ "tigger.on", UI_CENTER|UI_SMALLFONT, &color_white },
{ "deqer", UI_CENTER|UI_SMALLFONT, &color_white },
{ "", UI_CENTER|UI_SMALLFONT, &color_blue },
{ "Keycard Models", UI_CENTER|UI_BIGFONT, &color_ochre },
{ "Obsidian", UI_CENTER|UI_SMALLFONT, &color_white },
{ "", UI_CENTER|UI_SMALLFONT, &color_blue },
{ "Debris and Backpack Models", UI_CENTER|UI_BIGFONT, &color_ochre },
{ "DaEngineer", UI_CENTER|UI_SMALLFONT, &color_white },
{ "", UI_CENTER|UI_SMALLFONT, &color_blue },
{ "Stone Debris Models", UI_CENTER|UI_BIGFONT, &color_ochre },
{ "gooball", UI_CENTER|UI_SMALLFONT, &color_white },
{ "", UI_CENTER|UI_SMALLFONT, &color_blue },
{ "Skeleton Key Models", UI_CENTER|UI_BIGFONT, &color_ochre },
{ "Hipshot", UI_CENTER|UI_SMALLFONT, &color_white },
{ "", UI_CENTER|UI_SMALLFONT, &color_blue },
{ "Custom Sound Effects", UI_CENTER|UI_BIGFONT, &color_ochre },
{ "Patrick 'Scout' Schotte", UI_CENTER|UI_SMALLFONT, &color_white },
{ "", UI_CENTER|UI_SMALLFONT, &color_blue },
{ "", UI_CENTER|UI_SMALLFONT, &color_blue },
{ "Thanks go out to the entire", UI_CENTER|UI_SMALLFONT, &color_white },
{ "Quake3World LEM Community", UI_CENTER|UI_SMALLFONT, &color_white },
{ "", UI_CENTER|UI_SMALLFONT, &color_blue },
{ "", UI_CENTER|UI_SMALLFONT, &color_blue },
{ "Click to Exit", UI_CENTER|UI_SMALLFONT, &color_red },



  {NULL}
};

/*
=================
UI_CreditMenu_Key
=================
*/
static sfxHandle_t UI_CreditMenu_Key( int key ) {
	if( key & K_CHAR_FLAG ) {
		return 0;
	}

	trap_Cmd_ExecuteText( EXEC_APPEND, 
                         va("s_musicvolume %f; quit\n", mvolume));
	return 0;
}

/*
=================
ScrollingCredits_Draw
This is the main drawing function for the credits.
Most of the code is self-explanatory.
=================
*/
static void ScrollingCredits_Draw(void)
{
  int x = 320, y, n, ysize = 0, fadetime = 0;
  vec4_t fadecolour = { 0.00, 0.00, 0.00, 0.00 };

  
  
  
  if(!ysize) 
  {
    
    for(n = 0; n <= sizeof(credits) - 1; n++) 
    {
      
      if(credits[n].style & UI_SMALLFONT) 
      {
        
        ysize += PROP_HEIGHT * PROP_SMALL_SIZE_SCALE;
        
      
      }else if(credits[n].style & UI_BIGFONT) 
      {
        
        ysize += PROP_HEIGHT;
        
      
      }else if(credits[n].style & UI_GIANTFONT) 
      {
       
        ysize += PROP_HEIGHT * (1 / PROP_SMALL_SIZE_SCALE); 
      }
    }
  }

  
  
#ifdef BACKGROUND_SHADER
  UI_DrawHandlePic(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BackgroundShader);

#else
  
  UI_FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, color_background);
#endif


  
  
  y = 480 - SCROLLSPEED * (float)(uis.realtime - starttime) / 100;
  
  
  for(n = 0; n <= sizeof(credits) - 1; n++)
  {
    
    if(credits[n].string == NULL) 
    {
      if(y < -16) 
      {
        trap_Cmd_ExecuteText( EXEC_APPEND, 
                         va("s_musicvolume %f; quit\n", mvolume));
        break; 
      }
      break;
    }
		
    if( strlen(credits[n].string) == 1) 
      continue;

    if( y > -(PROP_HEIGHT * (1 / PROP_SMALL_SIZE_SCALE))) 
      
      UI_DrawProportionalString(x, y, credits[n].string, 
                                credits[n].style, *credits[n].colour );
		
    
    if(credits[n].style & UI_SMALLFONT)
    {
      y += PROP_HEIGHT * PROP_SMALL_SIZE_SCALE;
    }else if(credits[n].style & UI_BIGFONT)
    {
      y += PROP_HEIGHT;
    }else if(credits[n].style & UI_GIANTFONT)
    {
      y += PROP_HEIGHT * (1 / PROP_SMALL_SIZE_SCALE);
    }

	
    if (y > 480)
    break;
  }
}

/*
===============
UI_CreditMenu
===============
*/
void UI_CreditMenu( void ) {
	memset( &s_credits, 0 ,sizeof(s_credits) );

	s_credits.menu.draw = ScrollingCredits_Draw;
	s_credits.menu.key = UI_CreditMenu_Key;
	s_credits.menu.fullscreen = qtrue;
	UI_PushMenu ( &s_credits.menu );

	starttime = uis.realtime; 
	mvolume = trap_Cvar_VariableValue( "s_musicvolume" );
	if(mvolume < 0.5)
		trap_Cmd_ExecuteText( EXEC_APPEND, "s_musicvolume 0.5\n" );
	trap_Cmd_ExecuteText( EXEC_APPEND, "music music/fla22k_02\n" );

	// load the background shader
#ifdef BACKGROUND_SHADER
	BackgroundShader =
		trap_R_RegisterShaderNoMip("**"); //uncomment line 9 if you want a background
#endif
}
