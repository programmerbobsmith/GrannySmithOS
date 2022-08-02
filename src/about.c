#include "about.h"

#include <graphx.h>
#include <ti/info.h>
#include "gfx/gfx.h"

void about_gui(void)
{
	gfx_TransparentSprite(dialog_corner1,60,44);
	gfx_TransparentSprite(dialog_corner2,60,156);
	gfx_TransparentSprite(dialog_corner3,268,156);
	gfx_TransparentSprite(dialog_corner4,268,44);

	gfx_SetColor(0);
	gfx_FillRectangle(60,52,10,104);
	gfx_FillRectangle(64,156,204,4);
	gfx_FillRectangle(268,48,4,108);
	gfx_FillRectangle(70,44,198,8);
	gfx_FillRectangle(70,52,198,104);

	//put info and credits
	gfx_PrintStringXY("G r a n n y S m i t h     O S", 88,56);
	gfx_PrintStringXY("Software by Jonathan Khayat",70,72);
	gfx_PrintStringXY("TI-OS Version:",70,82);
	gfx_SetTextXY(100,92);
	gfx_PrintInt(os_GetSystemInfo() -> osMajorVersion,1);
	gfx_PrintChar('.');
	gfx_PrintInt(os_GetSystemInfo() -> osMinorVersion,1);
	gfx_PrintChar('.');
	gfx_PrintInt(os_GetSystemInfo() -> osRevisionVersion,1);
	gfx_PrintChar('.');
	gfx_PrintInt(os_GetSystemInfo() -> osBuildVersion,4);

	gfx_PrintStringXY("GrannySmith OS Version:",70,105);
	gfx_PrintStringXY("v 12.2.0",100,115);
	gfx_PrintStringXY("Copyright July 2022.",90,148);
}

void about_credits(void)
{
	gfx_SetColor(0);
	gfx_TransparentSprite(dialog_corner1,60,44);
	gfx_TransparentSprite(dialog_corner2,60,156);
	gfx_TransparentSprite(dialog_corner3,268,156);
	gfx_TransparentSprite(dialog_corner4,268,44);

	gfx_FillRectangle(60,52,10,104);
	gfx_FillRectangle(64,156,204,4);
	gfx_FillRectangle(268,48,4,108);
	gfx_FillRectangle(70,44,198,8);
	gfx_FillRectangle(70,52,198,104);

	gfx_PrintStringXY("GrannySmith OS",108,48);
	gfx_PrintStringXY("Software Credits:",70,60);
	gfx_PrintStringXY("- Jonathan Khayat (99%)",80,68);
	gfx_PrintStringXY("- Luke Olander (1%)",80,76);
	gfx_PrintStringXY("Sprite Credits:",70,90);
	gfx_PrintStringXY("- Jonathan Khayat (92%)",80,98);
	gfx_PrintStringXY("- Jonathan Havard (8%)",80,106);

	gfx_PrintStringXY("Pineapple CAS created by",70,112);
	gfx_PrintStringXY("Nathan Farlow. Source code",70,120);
	gfx_PrintStringXY("www.github.com/nathanfarlow",70,128);
	gfx_PrintStringXY("/PineappleCAS",70,136);

}