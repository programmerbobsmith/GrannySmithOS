#include "detect.h"

#include <stdbool.h>

static struct enter_code
	{
	    unsigned int xmin;
	    unsigned int ymin;
	    unsigned int xmax;
	    unsigned int ymax;
	    bool valid;
	}button[50];

int detect_Enter(unsigned int x, unsigned int y, unsigned int app_number)
{

//menuapple
    button[0].xmin = 0;
    button[0].ymin = 0;
    button[0].xmax = 12;
    button[0].ymax = 12;

//credits
    button[1].xmin = 16;
    button[1].ymin = 0;
	button[1].xmax = 40;
	button[1].ymax = 12;

//time
	button[3].xmin = 204;
	button[3].ymin = 0;
	button[3].xmax = 256;
	button[3].ymax = 12;

//battery
	button[4].xmin = 260;
	button[4].ymin = 0;
	button[4].xmax = 288;
	button[4].ymax = 12;

//search
	button[5].xmin = 288;
	button[5].ymin = 0;
	button[5].xmax = 300;
	button[5].ymax = 12;

//notification
	button[6].xmin = 304;
	button[6].ymin = 0;
	button[6].xmax = 316;
	button[6].ymax = 12;

//finder_icon
	button[7].xmin = 4;
	button[7].ymin = 212;
	button[7].xmax = 24;
	button[7].ymax = 236;

//launchpad_icon
	button[8].xmin = 32;
	button[8].ymin = 212;
	button[8].xmax = 48;
	button[8].ymax = 236;

//word_icon
	button[9].xmin = 56;
	button[9].ymin = 212;
	button[9].xmax = 76;
	button[9].ymax = 236;

//pineappleCAS
	button[10].xmin = 80;
	button[10].ymin = 212;
	button[10].xmax = 100;
	button[10].ymax = 232;

//orig: algebra_icon, current: chess
	button[15].xmin = 104;
	button[15].ymin = 212;
	button[15].xmax = 124;
	button[15].ymax = 232;

//word_close
	button[11].xmin = 16;
	button[11].ymin = 28;
	button[11].xmax = 16;
	button[11].ymax = 28;

//word_new
	button[12].xmin = 16;
	button[12].ymin = 40;
	button[12].xmax = 48;
	button[12].ymax = 76;

//menu_close
	button[14].xmin = 64;
	button[14].ymin = 48;
	button[14].xmax = 68;
	button[14].ymax = 52;

//chess_app ignore
	//button[15].xmin = 180;
	//button[15].ymin = 212;
	//button[15].xmax = 200;
	//button[15].ymax = 232;

//orig: geometry_app current:settings
	button[20].xmin = 131;
	button[20].ymin = 212;
	button[20].xmax = 151;
	button[20].ymax = 232;

// trigonometry_app
	button[18].xmin = 155;
	button[18].ymin = 212;
	button[18].xmax = 175;
	button[18].ymax = 232;

//settings_app ignore
	//button[20].xmin = 206;
	//button[20].ymin = 212;
	//button[20].xmax = 226;
	//button[20].ymax = 232;
//settings_menu_color
	button[21].xmin = 180;
	button[21].ymin = 80;
	button[21].xmax = 210;
	button[21].ymax = 90;
//settings_dock_color
	button[22].xmin = 180;
	button[22].ymin = 100;
	button[22].xmax = 210;
	button[22].ymax = 110;
//settings_cursor_color
	button[23].xmin = 180;
	button[23].ymin = 120;
	button[23].xmax = 210;
	button[23].ymax = 130;
//settings_cursor_outline
	button[24].xmin = 180;
	button[24].ymin = 140;
	button[24].xmax = 210;
	button[24].ymax = 150;

//initial states of buttons
    button[0].valid = true;
    button[1].valid = true;
	button[2].valid = true;
	button[3].valid = true;
	button[4].valid = true;
	button[5].valid = true;
	button[6].valid = true;
	button[7].valid = true;
	button[8].valid = true;
	button[9].valid = true;
	button[10].valid = true;
	button[11].valid = false;
	button[12].valid = false;
	button[13].valid = true;
	button[14].valid = false;
	button[15].valid = true;
	button[17].valid = true;
	button[18].valid = true;
	// button[19].valid = true; chem
	button[20].valid = true;
	button[21].valid = false;
//sets buttons within an app to be true when the app is opened.
	switch (app_number)
	{
		//word app
		case 1:
			button[11].valid = true;
			button[12].valid = true;
			break;
		//algebra app
		case 3:
			button[11].valid = true;
			break;
		//menu app
		case 4:
			button[14].valid = true;
			break;
		//geometry app
		case 5:
			button[11].valid = true;
			break;
		case 6:
			button[11].valid = true;
			break;
		case 7:
			button[11].valid = true;
			break;
		//settings
		case 8:
			button[11].valid = true;
			break;
	}

//tests where the user pressed
    for (int button_number=0; button_number<=50; button_number++)
    {
		if (button[button_number].valid)
		{
	    	if (x >= button[button_number].xmin && x <= button[button_number].xmax)
	    	{
				if (y >= button[button_number].ymin && y <= button[button_number].ymax)
				{
		    		return(button_number);
				}
	    	}
		}
	}

//returns 100 if nothing is under the position of the cursor
    return(100);
}
