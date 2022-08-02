#include "io.h"
#include <graphx.h>
#include "gfx/gfx.h"
#include <string.h>
#include <ti/getcsc.h>
#include <math.h>
#include "main.h"

void print_Double(double value, unsigned int number_of_decimal_places)
{
	gfx_SetTextFGColor(254);
	gfx_PrintInt((int)value,1);
	gfx_PrintChar('.');
	gfx_PrintInt((int)((value - (int)value)*(pow(10,number_of_decimal_places))),number_of_decimal_places);
}

int get_Integer(unsigned int x, unsigned int y)
{
	gfx_SetTextFGColor(254);
	unsigned int key;
	unsigned int increment = 0;
	char user_input[21];
	char key_pad[] = { [sk_0] = '0', [sk_1] = '1', [sk_2] = '2', [sk_3] = '3', [sk_4] = '4', [sk_5] = '5', [sk_6] = '6', [sk_7] = '7', [sk_8] = '8', [sk_9] = '9', [sk_Chs] = '-'};
	gfx_SetColor(254);
	gfx_Line(x,y+7,x+8,y+7);
	gfx_Line(x,y+8,x+8,y+8);
	while(key = os_GetCSC(), key != sk_Enter)
	{
		if (key == sk_Del && increment != 0)	// user deletes char
		{
			increment--;
			gfx_SetColor(0);
			gfx_Line(x,y+7,x+8,y+7);
			gfx_Line(x,y+8,x+8,y+8);
			gfx_FillRectangle(x+8*increment,y,8,8);
			x -= 8;
			gfx_SetColor(254);
			gfx_Line(x,y+7,x+8,y+7);
			gfx_Line(x,y+8,x+8,y+8);
		}else if (key == sk_Enter)
		{
			break;
		}else if (key == sk_Clear)
		{
			gfx_End();
			monterey_appvar();
			exit(0);
		}else if (key != 0 && key != sk_Enter && key != sk_Del && key != sk_Clear)
		{
			gfx_SetColor(0);
			gfx_Line(x,y+7,x+8,y+7);
			gfx_Line(x,y+8,x+8,y+8);
			gfx_SetTextFGColor(254);
			gfx_SetTextXY(x,y);
			gfx_PrintChar(key_pad[key]);
			x += 8;
			gfx_SetColor(254);
			gfx_Line(x,y+7,x+8,y+7);
			gfx_Line(x,y+8,x+8,y+8);
			user_input[increment++] = key_pad[key];
		}
	}
	user_input[increment] = '\0';		// terminates string at last position
	long int user_input_converted = strtol(user_input,NULL,0);
	gfx_SetColor(0);
	gfx_Line(x,y+7,x+8,y+7);
	gfx_Line(x,y+8,x+8,y+8);
	return (user_input_converted);
}

double get_Double(unsigned int x, unsigned int y)
{
	gfx_SetTextFGColor(254);
	unsigned int key;
	unsigned int increment = 0;
	char user_input[21];
	char key_pad[] = { [sk_0] = '0', [sk_1] = '1', [sk_2] = '2', [sk_3] = '3', [sk_4] = '4', [sk_5] = '5', [sk_6] = '6', [sk_7] = '7', [sk_8] = '8', [sk_9] = '9', [sk_DecPnt] = '.'};
	gfx_SetColor(254);
	gfx_Line(x,y+7,x+8,y+7);
	gfx_Line(x,y+8,x+8,y+8);
	while(key = os_GetCSC(), key != sk_Enter)
	{
		if (key == sk_Del && increment != 0)	// user deletes char
		{
			increment--;
			gfx_SetColor(0);
			gfx_Line(x,y+7,x+8,y+7);
			gfx_Line(x,y+8,x+8,y+8);
			gfx_FillRectangle(x+8*(increment-1),y,8,8);
			x -= 8;
			gfx_SetColor(254);
			gfx_Line(x,y+7,x+8,y+7);
			gfx_Line(x,y+8,x+8,y+8);
		}else if (key == sk_Enter)
		{
			break;
		}else if (key == sk_Clear)
		{
			gfx_End();
			monterey_appvar();
			exit(0);
		}else if (key < 18 || key > 36 || key == 21 || key == 22 || key == 23 || key == 24 || key == 29 || key == 30 || key == 31 || key == 32)
		{
		}else if (key != 0 && key != sk_Enter && key != sk_Del && key != sk_Clear)
		{
			gfx_SetColor(0);
			gfx_Line(x,y+7,x+8,y+7);
			gfx_Line(x,y+8,x+8,y+8);
			gfx_SetTextFGColor(254);
			gfx_SetTextXY(x,y);
			gfx_PrintChar(key_pad[key]);
			x += 8;
			gfx_SetColor(254);
			gfx_Line(x,y+7,x+8,y+7);
			gfx_Line(x,y+8,x+8,y+8);
			user_input[increment++] = key_pad[key];
		}
	}
	user_input[increment] = '\0';		// terminates string at last position
	double user_input_converted = strtod(user_input,NULL);
	gfx_SetColor(0);
	gfx_Line(x,y+7,x+8,y+7);
	gfx_Line(x,y+8,x+8,y+8);
	return (user_input_converted);
}

int get_Slider(unsigned int start_x, unsigned int start_y, unsigned int max_entries)
{
	unsigned int increment = 1;
	unsigned int key;
	start_y -= 2;
	gfx_SetColor(254);
	gfx_FillTriangle( start_x-18, start_y+(15*(increment-1)), start_x-10, start_y+4+(15*(increment-1)), start_x-18, start_y+8+(15*(increment-1)));
	while(key = os_GetCSC(), key != sk_Enter)
	{
		if (key == sk_Clear)
		{
			gfx_End();
			monterey_appvar();
			exit(0);
		}else if (key == sk_Up && increment != 1)
		{
			gfx_SetColor(0);
			gfx_FillTriangle( start_x-18, start_y+(15*(increment-1)), start_x-10, start_y+4+(15*(increment-1)), start_x-18, start_y+8+(15*(increment-1)));
			increment--;
			gfx_SetColor(254);
			gfx_FillTriangle( start_x-18, start_y+(15*(increment-1)), start_x-10, start_y+4+(15*(increment-1)), start_x-18, start_y+8+(15*(increment-1)));
		}else if (key == sk_Down && increment != max_entries)
		{
			gfx_SetColor(0);
			gfx_FillTriangle( start_x-18, start_y+(15*(increment-1)), start_x-10, start_y+4+(15*(increment-1)), start_x-18, start_y+8+(15*(increment-1)));
			increment++;
			gfx_SetColor(254);
			gfx_FillTriangle( start_x-18, start_y+(15*(increment-1)), start_x-10, start_y+4+(15*(increment-1)), start_x-18, start_y+8+(15*(increment-1)));
		}
	}
	return (increment);
}

int get_LaunchSlider(unsigned int x, unsigned int y)
{
	gfx_sprite_t *slider_background1 = gfx_MallocSprite(25,30);
	gfx_sprite_t *slider_background2 = gfx_MallocSprite(25,30);
	gfx_GetSprite(slider_background1,50,95);
	gfx_GetSprite(slider_background2,50,165);
	gfx_SetColor(31);
	gfx_FillTriangle(50,95,50,115,70,105);
	unsigned int key;
	unsigned int increment = 1;
	while(key = os_GetCSC(), key != sk_Enter)
	{
		if (key == sk_Clear)
		{
			gfx_End();
			monterey_appvar();
			exit(0);
		}else if(key == sk_Up && increment != 1)
		{
			increment--;
			gfx_FillTriangle(50,95,50,115,70,105);
			gfx_Sprite(slider_background2,50,165);
		}else if (key == sk_Down && increment != 2)
		{
			increment++;
			gfx_FillTriangle(50,165,50,185,70,175);
			gfx_Sprite(slider_background1,50,95);
		}
	}
	free(slider_background1);
	free(slider_background2);
	return(increment);
}

int get_ProgSlider(unsigned int start_x, unsigned int start_y, unsigned int max_entries)
{
	gfx_sprite_t *slider_background = gfx_MallocSprite(15,240);
	gfx_GetSprite(slider_background,10,0);
	unsigned int increment = 1;
	unsigned int key;
	start_y -= 2;
	gfx_SetColor(254);
	gfx_FillTriangle( start_x-18, start_y+(15*(increment-1)), start_x-10, start_y+4+(15*(increment-1)), start_x-18, start_y+8+(15*(increment-1)));
	while(key = os_GetCSC(), key != sk_Enter)
	{
		if (key == sk_Clear)
		{
			gfx_End();
			monterey_appvar();
			exit(0);
		}
		else if (key == sk_Up && increment != 1)
		{
			gfx_Sprite(slider_background,10,0);
			increment--;
			gfx_SetColor(254);
			gfx_FillTriangle( start_x-18, start_y+(15*(increment-1)), start_x-10, start_y+4+(15*(increment-1)), start_x-18, start_y+8+(15*(increment-1)));
		}else if (key == sk_Down && increment != max_entries)
		{
			gfx_Sprite(slider_background,10,0);
			increment++;
			gfx_SetColor(254);
			gfx_FillTriangle( start_x-18, start_y+(15*(increment-1)), start_x-10, start_y+4+(15*(increment-1)), start_x-18, start_y+8+(15*(increment-1)));
		}
	}
	free(slider_background);
	return (increment);	


}
