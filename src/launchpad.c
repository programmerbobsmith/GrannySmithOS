#include "launchpad.h"
#include <compression.h>
#include <graphx.h>
#include "gfx/gfx.h"
#include <ti/getcsc.h>
#include "io.h"
#include <stdbool.h>
#include <fileioc.h>
#include <string.h>
#include "error.h"

#include <timers.h>
void launchpad_gui(void)
{
	zx0_Decompress(gfx_vram,background_compressed);
	gfx_SetTextFGColor(254);
	gfx_SetTransparentColor(7);
	gfx_TransparentSprite(launchpad_basic,80,80);
	gfx_TransparentSprite(launchpad_cprog,80,150);
	int increment = get_LaunchSlider(80,55);
	switch (increment)
	{
		case 1:
			launchpad_prog_basic();
			break;
		case 2:
			launchpad_prog_c();
			break;
	}
}

void launchpad_prog_basic(void)
{
	zx0_Decompress(gfx_vram,background_compressed);
	gfx_SetTextFGColor(0);
	char *var_name;
	void *vat_ptr = NULL;
	unsigned int x,y;
	x = 30;
	y = 10;
	char name[8];
	while(var_name = ti_DetectVar(&vat_ptr,NULL,TI_PRGM_TYPE))
	{
		strcpy(name,var_name);
		if (name[0] >'A' && name [0] < 'Z' + 1)
		{
			gfx_PrintStringXY(var_name,x,y);
			y+=15;
		}
	}
	if (var_name == NULL && y == 10)
	{
		gfx_PrintStringXY("No TI-Basic Programs!",80,80);
		msleep(2000);
		return;
	}
	unsigned int num_prog = (y-10)/15;
	unsigned int increment = get_ProgSlider(30,10,num_prog);
	vat_ptr = NULL;
	unsigned int i=0;
	while (i < increment)
	{
		var_name = ti_DetectVar(&vat_ptr,NULL,TI_PRGM_TYPE);
		i++;
	}
	int error = os_RunPrgm(var_name,NULL,0,launch_callbacks);
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

int launch_callbacks(void *data, int retval)
{
	return main();
}

void launchpad_prog_c(void)
{
	zx0_Decompress(gfx_vram,background_compressed);
	gfx_SetTextFGColor(0);
	char *var_name;
	void *vat_ptr = NULL;
	unsigned int x,y;
	x = 30;
	y = 10;
	while(var_name = ti_DetectVar(&vat_ptr,NULL,TI_PPRGM_TYPE))
	{
		gfx_PrintStringXY(var_name,x,y);
		y+=15;
	}
	if (var_name == NULL && y == 10)
	{
		gfx_PrintStringXY("No C/ASM Programs!",80,80);
		msleep(2000);
		return;
	}
	unsigned int num_prog = (y-10)/15;
	unsigned int increment = get_ProgSlider(30,10,num_prog);
	vat_ptr = NULL;
	unsigned int i=0;
	while (i < increment)
	{
		var_name = ti_DetectVar(&vat_ptr,NULL,TI_PPRGM_TYPE);
		i++;
	}
	int error = os_RunPrgm(var_name,NULL,0,launch_callbacks);
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

