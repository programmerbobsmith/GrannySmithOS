#include "error.h"
#include <graphx.h>
#include "gfx/gfx.h"
#include <sys/rtc.h>
#include <string.h>
#include <sys/timers.h>

void error_banner(const char *header, const char *text, unsigned int x, unsigned int y)
{
	gfx_sprite_t *notification_background = gfx_MallocSprite(137,30);
	gfx_GetSprite(notification_background,180,20);
	error_notification(x,y,136,30,0);
	gfx_PrintStringXY(header,x+6,y+3);
	gfx_PrintStringXY(text,x+10,y+12);
	msleep(2000);
	gfx_Sprite(notification_background,180,20);
}

void error_notification(unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned int color)
{
	gfx_SetColor(color);
	gfx_Line(x,y+4,x,y+height-4);
	gfx_Line(x+1,y+2,x+1,y+height-2);
	gfx_Line(x+2,y+1,x+2,y+height-1);
	gfx_Line(x+3,y+1,x+3,y+height-1);
	gfx_FillRectangle(x+4,y,width-6,height);
	gfx_Line(x+width-3,y+1,x+width-3,y+height-1);
	gfx_Line(x+width-2,y+1,x+width-2,y+height-1);
	gfx_Line(x+width-1,y+2,x+width-1,y+height-2);
	gfx_Line(x+width,y+4,x+width,y+height-4);
}