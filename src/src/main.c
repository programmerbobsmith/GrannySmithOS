#include <fileioc.h>
#include <fontlibc.h>
#include <graphx.h>
#include <keypadc.h>
#include <tice.h>
#include <string.h>
#include <stdint.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <ti/tokens.h>
#include <ti/vars.h>
#include <compression.h>

//header files
#include "gfx/gfx.h"
//#include "delete.h"
//#include "file.h"
//#include "create.h"
//#include "dialog.h"

#define MAX_FOLDERS 50

//initializes the file to be used as the appvar.
uint8_t dat;

//global variables
unsigned int xpos = 160;
unsigned int ypos = 120;
unsigned int key=0;
int first_valid;

struct foldersave
    {
	char name[10];
	int xpos;
	int ypos;
	int files;
	bool valid;
    }folders[MAX_FOLDERS];

//function prototypes
void startup();
void setdesktop();
void batterystatus();
void cursordetect();
void readfolder();
void dock_up();
void dock_down();
void dock_draw();

//this is the background sprite for the cursor.
gfx_sprite_t *behind_sprite;

int main(void)
{
    //Tests if this is the first time the program is executed, if invalid, and creates file.
    dat = ti_Open("MONTDAT","r+");
    if (dat == 0)
    {
        dat = ti_Open("MONTDAT","w+");

	/* sets all valid variables in struct foldersave to false.*/
        for(uint8_t x = 0; x < MAX_FOLDERS; x++)
        {
            folders[x].valid = false;
        }

        ti_Write(&folders[0], sizeof(struct foldersave), MAX_FOLDERS, dat);
        ti_Rewind(dat);
    }

    //Begins program
    ti_Read(&folders[0],sizeof(struct foldersave),MAX_FOLDERS,dat);
    ti_Rewind(dat);

    gfx_Begin();
    gfx_SetPalette(global_palette, sizeof_global_palette, 0);
    gfx_SetTransparentColor(6);

    startup();
    readfolder();
    batterystatus();

    behind_sprite = gfx_MallocSprite(cursor_width, cursor_height);

    setdesktop();

    gfx_GetSprite(behind_sprite, xpos, ypos);

    gfx_TransparentSprite(cursor, xpos, ypos);

    while((key=os_GetCSC()) <= sk_Up)
    {
        if (!key) continue;
        cursordetect(behind_sprite);

	// this pulls the dock up if the cursor moves close to the bottom
	if (ypos>LCD_WIDTH-30)
	{
	    dock_up();

	    //this pushes the dock down if the cursor moves away from the bottom
	    if (ypos<LCD_WIDTH-30)
	    {
		dock_down();
	    }
	}
    }
//maps different keys with commands
    while (!os_GetCSC());

    //writes all the variables to the AppVar.
    ti_Rewind(dat);
    ti_Write(&folders[0], sizeof(struct foldersave), MAX_FOLDERS, dat);
    ti_Close(dat);
    free(behind_sprite);
    gfx_End();

    return 0;


}

// startup() is the loading screen with the loading bar.
void startup (void)
{
    gfx_ZeroScreen();
    gfx_TransparentSprite(applelogo,140,50);
    gfx_SetColor(254);
    gfx_HorizLine(55,115,210);
    gfx_HorizLine(55,120,210);
    gfx_VertLine(54,116,4);
    gfx_VertLine(265,116,4);
    for(int barinc=0;barinc<210;barinc++)
    {
        gfx_SetColor(254);
        if ((clock()%100)==0) {
            gfx_VertLine(55+barinc,116,4);
        }else {
            barinc--;
        }
    }
}

//setdesktop() sets the background and menu bar.
void setdesktop()
{

    zx0_Decompress(gfx_vram,background_compressed);
    gfx_SetColor(0);
    gfx_FillRectangle(0,0,320,13);
    gfx_Sprite(menuapple,0,0);
    gfx_Sprite(notification,305,0);
    gfx_Sprite(search,290,0);
    gfx_Sprite(battery,265,0);
    gfx_SetPixel(283,0);
    gfx_SetPixel(283,8);
}

//batterystatus() determines the charge in the calculator and updates the battery.
void batterystatus()
{
    uint8_t percentage=boot_GetBatteryStatus();
    switch (percentage)
    {
        //Battery is about to die.
        case 1:
            gfx_SetColor(0);
            gfx_FillRectangle(266,2,16,6);
            gfx_SetColor(224);
            gfx_Line(265,1,265,7);
            gfx_Line(266,0,282,0);
            gfx_Line(266,8,282,8);
            gfx_Line(283,1,283,7);
            gfx_Line(286,3,286,5);
            break;
        //Battery is 33%.
        case 2:
            gfx_SetColor(0);
            gfx_FillRectangle(272,2,10,6);
            break;
        //Battery is 66%.
        case 3:
            gfx_SetColor(0);
            gfx_FillRectangle(277,2,5,6);
            break;
        //Battery is fully charged.
        case 4:
            break;
    }
    if (boot_BatteryCharging() == 1)
    {
        gfx_SetColor(7);
        gfx_Line(265,1,265,7);
        gfx_Line(266,0,282,0);
        gfx_Line(266,8,282,8);
        gfx_Line(283,1,283,7);
        gfx_Line(286,3,286,5);
    }
}

//cursordetect() is the drawing and movement of the cursor.
void cursordetect()
{
    // clear out the old sprite
    gfx_Sprite(behind_sprite, xpos, ypos);
    switch (key)
    {
        case sk_Left:
            xpos-=3;
            if (xpos<0)
            {
                xpos=0;
            }
            break;
        case sk_Right:
            xpos+=3;
            if (xpos>LCD_WIDTH)
            {
                xpos=LCD_WIDTH;
            }
            break;
        case sk_Up:
            ypos-=3;
            if (ypos<0)
            {
                ypos=0;
            }
            break;
        case sk_Down:
            ypos+=3;
            if (ypos>LCD_HEIGHT)
            {
                ypos=LCD_HEIGHT;
            }
            break;
    }
    // get the new background and draw the moved sprite
    gfx_GetSprite(behind_sprite, xpos, ypos);
    gfx_TransparentSprite(cursor, xpos, ypos);
}

//readfolder() checks the MONTDAT file and copys all folders and files to desktop.
void readfolder()
{
    for(int x=0;x<MAX_FOLDERS;x++)
    {
        if (folders[x].valid==true)
        {
            gfx_TransparentSprite(folder_icon,folders[x].xpos,folders[x].ypos);
            gfx_PrintStringXY(folders[x].name,folders[x].xpos,folders[x].ypos+17);
        }
    }
}

//dock_up() draws the dock with animation and some basic macOS Monterey Apps.
void dock_up()
{
    int dock_x=0;
    int dock_y=GFX_LCD_HEIGHT;
    for (dock_y;dock_y>209;dock_y++)
    {
    	dock_draw(dock_x,dock_y);
    }
}

//dock_down() draws the dock with animation and some basic macOS Monterey Apps.
void dock_down()
{
    unsigned int dock_x=0;
    unsigned int dock_y=209;
    for (dock_y;dock_y<239;dock_y--)
    {
	dock_draw(dock_x,dock_y);
    }
}

//draws the whole dock
void dock_draw(unsigned int dock_x,unsigned int dock_y)
{
    gfx_SetTransparentColor(6);
    gfx_TransparentSprite(dock_corner1,dock_x,dock_y);
    gfx_TransparentSprite(dock_corner2,dock_x,dock_y+30);
    gfx_TransparentSprite(dock_corner3,dock_x+314,dock_y+25);
    gfx_TransparentSprite(dock_corner4,dock_x+314,dock_y);
    gfx_SetColor(31);
    gfx_FillRectangle(dock_x+4,dock_y,309,30);
    gfx_TransparentSprite(finder_icon,dock_x+6,dock_y+5);
    gfx_TransparentSprite(launchpad_icon,dock_x+31,dock_y+5);
    gfx_TransparentSprite(word_icon,dock_x+56,dock_y+5);
    gfx_TransparentSprite(pcas,dock_x+73,dock_y+5);

}
