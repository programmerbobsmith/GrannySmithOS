#include "main.h"
#include <fileioc.h>
#include <fontlibc.h>
#include <graphx.h>
#include <keypadc.h>
#include <tice.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <ti/tokens.h>
#include <ti/vars.h>
#include <compression.h>
#include <sys/rtc.h>
#include <sys/power.h>
#include <ti/info.h>

//monterey files
#include "gfx/gfx.h"
#include "detect.h"
#include "algebra.h"
#include "about.h"
#include "geometry.h"
#include "update.h"
#include "launchpad.h"
#include "io.h"
#include "trig.h"
#include "error.h"
#include "chemistry.h"

#define MAX_FOLDERS 50

//global variables
int xpos = 160;
int ypos = 120;
unsigned int key=0;
int app_number = 0;
struct settings_t
{
	unsigned int color_appbackground;
	unsigned int color_appforeground;
	unsigned int color_appheadertext;
	unsigned int color_appbodytext;
	unsigned int color_menu;
	unsigned int color_dock;
	unsigned int color_launchpadprog;
	unsigned int cursor_interior;
	unsigned int cursor_outline;
	
}settings;

struct montdat_t
{
	unsigned int total;
	unsigned int current_hours,current_minutes,current_seconds;
	unsigned int launchpad;
	unsigned int wordCE;
	unsigned int montcas;
	unsigned int algebra;
	unsigned int geometry;
	unsigned int trigonometry;
	unsigned int chess;
	unsigned int credits;
}data;

uint8_t montset,montdat;

//this is the background sprite for the cursor.
gfx_sprite_t *behind_sprite;

int main(void)
{
	gfx_Begin();
	gfx_SetPalette(global_palette, sizeof_global_palette, 0);
    gfx_SetTransparentColor(7);
	lcd_BacklightLevel = 0;
	startup();
	second_main();
    return 0;
}

int second_main()
{
	montdat = ti_Open("MONTDATA","r+");
	if (montdat == 0)
	{
		ti_Open("MONTDAT","w+");
		data.current_hours = rtc_Hours;
		data.current_minutes = rtc_Minutes;
		data.current_seconds = rtc_Seconds;
		data.total = 1;
		data.launchpad = 0;
		data.montcas = 0;
		data.wordCE = 0;
		data.algebra = 0;
		data.trigonometry = 0;
		data.geometry = 0;
		data.chess = 0;
		data.credits = 0;
		ti_Write(&data,sizeof(struct montdat_t),1,montdat);
		ti_Rewind(montdat);
	}
	ti_Read(&data,sizeof(struct montdat_t),1,montdat);
	gfx_SetPalette(global_palette, sizeof_global_palette, 0);
    gfx_SetTransparentColor(7);
	montset = ti_Open("MONTSET","r+");
	if (montset == 0)
	{
		montset = ti_Open("MONTSET","w+");
		settings.color_appbackground = 0;
		settings.color_appforeground = 8;
		settings.color_appheadertext = 31;
		settings.color_appbodytext = 254;
		settings.color_menu = 31;
		settings.color_dock = 31;
		settings.color_launchpadprog = 254;
		settings.cursor_outline = 254;
		settings.cursor_interior = 0;
		ti_Write(&settings,sizeof(struct settings_t),1,montset);
		ti_Close(montset);
		montset = ti_Open("MONTSET","r+");
	}
	ti_Read(&settings,sizeof(struct settings_t),1,montset);

	unsigned int returned;

    behind_sprite = gfx_MallocSprite(11,16);

    setdesktop();
	update_all();

    gfx_GetSprite(behind_sprite, xpos, ypos);
   	cursor( xpos, ypos);

	while((key=os_GetCSC()) != sk_Clear)
	{
		if (!key) continue;
    	while((key=os_GetCSC()) <= sk_Up)
    	{
        	cursordetect(behind_sprite);
    	}
		update_all();
		switch (key)
			{
				case sk_Clear:
					gfx_End();
					ti_SetArchiveStatus(true,montset);
					ti_SetArchiveStatus(true,montdat);
					ti_Close(montset);
					ti_Close(montdat);
					exit(0);
					break;
				case sk_Enter:
					returned = detect_Enter(xpos,ypos,app_number);
					decode_Enter(returned);
					break;
				case sk_Prgm:
					decode_Enter(8);
					break;
				case sk_Yequ:
					decode_Enter(9);
					break;
				case sk_Window:
					decode_Enter(10);
					break;
				case sk_Zoom:
					decode_Enter(13);
					break;
				case sk_Trace:
					decode_Enter(17);
					break;
				case sk_Graph:
					decode_Enter(18);
					break;
					
			}
		update_all();
	}
    gfx_End();
	free(behind_sprite);
}

int all_callbacks(void *data, int retval)
{
	gfx_Begin();
	return second_main();
}

int cas_callbacks(void *data, int retval)
{
	int error = os_RunPrgm("PCAS",NULL,0,all_callbacks);
	switch (error)
	{
		case -1:
			error_banner("Invalid","Program not found",180,20);
			break;
		case -2:
			error_banner("Memory","Not enough MEM",180,20);
			break;
	}
}

// startup() is the loading screen with the loading bar.
void startup (void)
{
    gfx_ZeroScreen();
    gfx_SetTransparentColor(7);
    gfx_TransparentSprite(applelogo,140,50);
    gfx_SetColor(254);
    gfx_HorizLine(55,115,210);
    gfx_HorizLine(55,120,210);
    gfx_VertLine(54,116,4);
    gfx_VertLine(265,116,4);
    for(int barinc=0;barinc<210;barinc++)
    {
        gfx_SetColor(254);
        if ((clock()%100)==0) 
		{
            gfx_VertLine(55+barinc,116,4);
        }else 
		{
            barinc--;
        }
    }
}

//setdesktop() sets the background and menu bar.
void setdesktop()
{
    zx0_Decompress(gfx_vram,background_compressed);
    dock_draw();
	app_number = 0;
    gfx_SetColor(31);
    gfx_FillRectangle(0,0,320,13);
    gfx_SetTransparentColor(7);
    gfx_TransparentSprite(menuapple,1,0);
    gfx_SetTextFGColor(254);
    gfx_PrintStringXY("Credits",16,3);
    gfx_TransparentSprite(notification,305,0);
    gfx_TransparentSprite(search,290,0);
    gfx_TransparentSprite(battery,265,2);
}

//cursordetect() is the drawing and movement of the cursor.
void cursordetect()
{
    // clear out the old sprite
    gfx_Sprite(behind_sprite, xpos, ypos);
    switch (key)
    {
        case sk_Left:
            xpos-=4;
            if (xpos<0)
            {
                xpos=0;
            }
            break;
        case sk_Right:
            xpos+=4;
            if (xpos>316)
            {
                xpos=316;
            }
            break;
        case sk_Up:
            ypos-=4;
            if (ypos<0)
            {
                ypos=0;
            }
            break;
        case sk_Down:
            ypos+=4;
            if (ypos>236)
            {
                ypos=236;
            }
            break;
    }
    // get the new background and draw the moved sprite
    gfx_GetSprite(behind_sprite, xpos, ypos);
    cursor( xpos, ypos);
    //gfx_FillRectangle(278,13,35,35); //for debugging
    //gfx_SetTextXY(280,15);
    //gfx_PrintInt(xpos,3);
    //gfx_SetTextXY(280,30);
    //gfx_PrintInt(ypos,3);
}

//draws the whole dock
void dock_draw(void)
{
    unsigned int dock_x=0;
    unsigned int dock_y=209;
    gfx_SetTransparentColor(7);
    gfx_SetColor(31);
    gfx_FillRectangle(7,dock_y,306,31);
    gfx_Line(0,219,0,229);
    gfx_Line(1,216,1,232);
    gfx_Line(2,214,2,234);
    gfx_Line(3,212,3,236);
    gfx_Line(4,212,4,236);
    gfx_Line(5,210,5,238);
    gfx_Line(6,210,6,238);
    gfx_Line(7,209,7,239);
    gfx_Line(319,219,319,229);
    gfx_Line(318,216,318,232);
    gfx_Line(317,214,317,234);
    gfx_Line(316,212,316,236);
    gfx_Line(315,212,315,236);
    gfx_Line(314,210,314,238);
    gfx_Line(313,210,313,238);
    gfx_Line(312,209,312,239);
    gfx_TransparentSprite(finder_icon,dock_x+6,dock_y+5);
    gfx_TransparentSprite(launchpad_icon,dock_x+31,dock_y+5);
    gfx_TransparentSprite(word_icon,dock_x+56,dock_y+5);
    gfx_TransparentSprite(pcas,dock_x+81,dock_y+5);
	gfx_TransparentSprite(algebra_icon,dock_x+106,dock_y+5);
	gfx_TransparentSprite(geometry_icon,dock_x+131,dock_y+5);
	gfx_TransparentSprite(trig_icon,dock_x+156,dock_y+5);
	//gfx_TransparentSprite(chem_icon,dock_x+181,dock_y+5);
	gfx_TransparentSprite(chess_icon,dock_x+181,dock_y+5); // once chem is implemented this should be 206
	gfx_TransparentSprite(settings_icon,dock_x+206,dock_y+5);
}

void decode_Enter(unsigned int returned)
{
	int selection = 0;
	int error;
	struct current_settings
	{
		unsigned int menu;
		unsigned int dock;
		unsigned int app_background;
		unsigned int app_header;
		unsigned int app_body;
		unsigned int app_slidercolor;
		unsigned int cursor_color;
		unsigned int cursor_outline;
	}current;

	switch (returned)
	{
		case 0:
			app_number = 4; //menu is app number 4
			data.credits++;
			ti_Write(&data,sizeof(struct montdat_t),1,montdat);
			ti_Rewind(montdat);
			about_gui();
			break;
		case 1:
			app_number = 4;
			data.credits++;
			ti_Write(&data,sizeof(struct montdat_t),1,montdat);
			ti_Rewind(montdat);
			about_credits();
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
		case 8:
			data.launchpad++;
			ti_Write(&data,sizeof(struct montdat_t),1,montdat);
			ti_Rewind(montdat);
			launchpad_gui();
			setdesktop();
			gfx_GetSprite(behind_sprite,xpos,ypos);
			cursor(xpos,ypos);
			break;
		case 9:
			data.wordCE++;
			ti_Write(&data,sizeof (struct montdat_t),1,montdat);
			ti_Rewind(montdat);
			error = os_RunPrgm("NOTES",NULL,0,all_callbacks); //word app is number 1
			switch (error)
			{
				case -1:
					error_banner("Invalid","NOTES not found",180,20);
					break;
				case -2:
					error_banner("Memory","Not enough MEM",180,20);
					break;
			}
			break;
		case 10:
			gfx_End();
			error = os_RunPrgm("MONTINPT",NULL,0,cas_callbacks);
			gfx_Begin();
			switch (error)
			{
				case -1:
					error_banner("Invalid","MONTINPT not found",180,20);
					break;
				case -2:
					error_banner("Memory","Not enough MEM",180,20);
					break;
			}
			break;
		case 11:
			setdesktop();
			gfx_GetSprite(behind_sprite,xpos,ypos);
			cursor(xpos,ypos);
			break;
		case 12:
			break;
		case 13:
			app_number = 3; //algebra app number is 3
			data.algebra++;
			ti_Write(&data,sizeof (struct montdat_t),1,montdat);
			ti_Rewind(montdat);
			selection = algebra_gui();
			switch(selection)
			{
				case 0:
					gfx_End();
					exit(0);
					break;
				case 1:
					algebra_factoring();
					break;
				case 2:
					algebra_quadratic();
					break;
				case 3:
					gfx_End();
					error = os_RunPrgm("RADSIMP",NULL,0,all_callbacks);
					gfx_Begin();
					switch(error)
					{
						case -1:
							error_banner("Invalid","RADSIMP not found",180,20);
							break;
						case -2:
							error_banner("Memory","Not enough MEM",180,20);
							break;
					}
					break;
			}
			break;
		case 14:
			setdesktop();
			gfx_GetSprite(behind_sprite,xpos,ypos);
			cursor(xpos,ypos);
			break;
		case 15:
			data.chess++;
			ti_Write(&data,sizeof(struct montdat_t),1,montdat);
			ti_Rewind(montdat);
			error = os_RunPrgm("CHESS",NULL,0,all_callbacks);
			switch (error)
			{
				case -1:
					error_banner("Invalid","Chess not found",180,20);
					break;
				case -2:
					error_banner("Memory","Not enough MEM",180,20);
					break;
			}
			break;
		case 17:
			app_number = 5; //geometry app number is 5
			data.geometry++;
			ti_Write(&data,sizeof(struct montdat_t),1,montdat);
			ti_Rewind(montdat);
			selection = geometry_gui();
			switch (selection)
			{
				case 0:
					gfx_End();
					exit(0);
					break;
				case 1:
					geometry_area_perimeter();
					break;
				case 2:
					geometry_distance();
					break;
				case 3:
					geometry_mid_slope();
					break;
				case 4:
					geometry_pythag();
					break;
				case 5:
					geometry_slope_forms();
					break;
				case 6:
					geometry_surface_area();
					break;
			}
			break;
		case 18:
			app_number = 6;
			data.trigonometry++;
			ti_Write(&data,sizeof(struct montdat_t),1,montdat);
			ti_Rewind(montdat);
			selection = trig_gui();
			switch (selection)
			{
				case 1:
					trig_arg();
					break;
				case 2:
					trig_degrad(); //this is complete
					break;
				case 3:
					trig_prob();
					break;
				case 4:
					trig_seq_series();
					break;
				case 5:
					trig_triangle_solver(); // this is complete
					break;
			}
			break;
//these are all settings stuff
		case 20:
			app_number = 8;
			settings_gui();
			break;
		case 21: // menu changes
			current.menu = get_current_settings('g','m');
			if (current.menu == 31)
			{
				current.menu = settings_general(0,1);
			}else if (current.menu == 0)
			{
				current.menu = settings_general(31,1);
			}
			break;
		case 22: //dock changes
			current.dock = get_current_settings('g','d');
			if (current.dock == 31)
			{
				current.dock = settings_general(0,2);
			}else if (current.dock == 0)
			{
				current.dock = settings_general(31,2);
			}
			break;
		case 23: //cursor color changes
			current.cursor_color = get_current_settings('g','i');
			if (current.cursor_color == 0)
			{
				current.cursor_color = settings_general(31,3);
			}else if (current.cursor_color == 31)
			{
				current.cursor_color = settings_general(7,3);
			}else if (current.cursor_color == 7)
			{
				current.cursor_color = settings_general(95,3);
			}else if (current.cursor_color == 95)
			{
				current.cursor_color = settings_general(0,3);
			}
			break;
		case 24: //cursor outline changes
			current.cursor_outline = get_current_settings('g','o');
			if (current.cursor_outline == 0)
			{
				current.cursor_outline = settings_general(31,3);
			}else if (current.cursor_outline == 31)
			{
				current.cursor_outline = settings_general(7,3);
			}else if (current.cursor_outline == 7)
			{
				current.cursor_outline = settings_general(95,3);
			}else if (current.cursor_outline == 95)
			{
				current.cursor_outline = settings_general(0,3);
			}
			break;
	}
}

void cursor(unsigned int x, unsigned int y)
{
	gfx_SetColor(settings.cursor_outline);
	gfx_Line(x,y,x,y+13);
	gfx_Line(x+1,y,x+10,y+9);
	gfx_Line(x+1,y+12,x+3,y+10);
	gfx_SetPixel(x+4,y+11);
	gfx_SetPixel(x+4,y+12);
	gfx_SetPixel(x+5,y+13);
	gfx_SetPixel(x+5,y+14);
	gfx_Line(x+6,y+15,x+8,y+15);
	gfx_Line(x+8,y+15,x+8,y+13);
	gfx_SetPixel(x+7,y+12);
	gfx_SetPixel(x+7,y+11);
	gfx_SetPixel(x+6,y+10);
	gfx_Line(x+6,y+9,x+9,y+9);
	gfx_SetColor(settings.cursor_interior);
	gfx_Line(x+1,y+1,x+1,y+11);
	gfx_Line(x+2,y+2,x+2,y+10);
	gfx_Line(x+3,y+3,x+3,y+9);
	gfx_Line(x+4,y+4,x+4,y+10);
	gfx_Line(x+5,y+5,x+5,y+12);
	gfx_Line(x+6,y+6,x+6,y+8);
	gfx_Line(x+7,y+7,x+7,y+8);
	gfx_SetPixel(x+8,y+8);
	gfx_Line(x+6,y+11,x+6,y+14);
	gfx_Line(x+7,y+13,x+7,y+14);

}

void settings_gui(void)
{
	gfx_SetTransparentColor(7);
	gfx_TransparentSprite(finder_corner1,8,20);
	gfx_TransparentSprite(finder_corner2,8,200);
	gfx_TransparentSprite(finder_corner3,312,200);
	gfx_TransparentSprite(finder_corner4,312,20);
	gfx_SetColor(8);
	gfx_FillRectangle(8,31,20,169);
	gfx_FillRectangle(27,20,25,187);
	gfx_FillRectangle(16,200,12,7);
	gfx_SetColor(0);
	gfx_FillRectangle(52,20,260,187);
	gfx_FillRectangle(312,28,7,172);
	gfx_SetColor(254);
	gfx_Line(60,54,130,54);
	gfx_Line(60,64,300,64);
	gfx_Line(130,54,130,64);
	gfx_Line(150,54,220,54);
	gfx_Line(220,54,220,64);
	gfx_Line(250,54,300,54);
	gfx_Line(300,54,300,64);
	gfx_PrintStringXY("General",70,54);

	gfx_PrintStringXY("Menu Bar Color:",60,80);
	gfx_PrintStringXY("Dock Color:",60,100);
	gfx_PrintStringXY("Cursor Color:",60,120);
	gfx_PrintStringXY("Cursor Outline:",60,140);

	gfx_SetColor(settings.color_menu);
	gfx_FillRectangle(180,80,30,10);
	gfx_SetColor(settings.color_dock);
	gfx_FillRectangle(180,100,30,10);
	gfx_SetColor(settings.cursor_interior);
	gfx_FillRectangle(180,120,30,10);
	gfx_SetColor(settings.cursor_outline);
	gfx_FillRectangle(180,140,30,10);
}

unsigned int settings_general(unsigned int color, unsigned int type)
{
	switch(type)
	{
		case 1:
			gfx_SetColor(color);
			gfx_FillRectangle(180,80,30,10);
			settings.color_menu = color;
			break;
		case 2:
			gfx_SetColor(color);
			gfx_FillRectangle(180,100,30,10);
			settings.color_dock = color;
			break;
		case 3:
			gfx_SetColor(color);
			gfx_FillRectangle(180,120,30,10);
			settings.cursor_outline = color;
			break;
		case 4:
			gfx_SetColor(color);
			gfx_FillRectangle(180,140,30,10);
			settings.cursor_interior = color;
			break;
	}
	ti_Write(&settings,sizeof(struct settings_t),1,montset);
	return(color);
}

unsigned int get_current_settings(char sector, char type)
{
		switch (sector)
		{
			case 'g':
				if (type == 'm')
				{
					return (settings.color_menu);
				}else if (type == 'd')
				{
					return (settings.color_dock);
				}else if (type == 'i')
				{
					return (settings.cursor_interior);
				}else if (type == 'o')
				{
					return (settings.cursor_outline);
				}
				break;
		}
}

void monterey_appvar(void)
{
	ti_SetArchiveStatus(true,montset);
	ti_SetArchiveStatus(true,montdat);
	ti_Close(montdat);
	ti_Close(montset);
}