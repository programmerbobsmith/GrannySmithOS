#include "update.h"
#include <graphx.h>
#include "gfx/gfx.h"
#include <sys/power.h>
#include <sys/rtc.h>
#include <time.h>

void update_clock(void)
{

	gfx_SetColor(31);
	gfx_FillRectangle(212,1,50,10);
	gfx_SetTextFGColor(254);
	uint8_t clock_minutes = rtc_Minutes;
	uint8_t clock_hours = rtc_Hours;
	if (boot_IsAfterNoon())
	{
		gfx_PrintStringXY("PM",242,2);
		gfx_SetTextXY(206,2);
		if (clock_hours == 12)
		{
			gfx_PrintInt(12,2);
		}else
		{
			gfx_PrintInt(clock_hours-12,2);
		}
	}else if (!boot_IsAfterNoon())
	{
		gfx_PrintStringXY("AM",242,2);
		gfx_SetTextXY(206,2);
		if (clock_hours == 0)
		{
			gfx_PrintInt(12,2);
		}else
		{
			gfx_PrintInt(clock_hours,2);
		}
	}
    gfx_PrintChar(':');
	gfx_PrintInt(clock_minutes,2);
}

void update_battery(void)
{
	uint8_t percentage = boot_GetBatteryStatus();
    switch (percentage)
    {
        //Battery is about to die.
        case 1:
            gfx_SetColor(31);
            gfx_FillRectangle(266,3,16,6);
            gfx_SetColor(224);
            gfx_Line(265,3,265,9);
            gfx_Line(266,2,282,2);
            gfx_Line(266,10,282,10);
            gfx_Line(283,3,283,9);
            gfx_Line(286,5,286,7);
            break;
        //Battery is 33%.
        case 2:
            gfx_SetColor(31);
            gfx_FillRectangle(272,3,10,6);
            break;
        //Battery is 66%.
        case 3:
            gfx_SetColor(31);
            gfx_FillRectangle(277,3,5,6);
            break;
        //Battery is fully charged.
        case 4:
            break;
    }
    if (boot_BatteryCharging() == true)
    {
        gfx_SetColor(6);
        gfx_Line(265,3,265,9);
        gfx_Line(266,2,282,2);
        gfx_Line(266,10,282,10);
        gfx_Line(283,3,283,9);
        gfx_Line(286,5,286,7);
    }
}

void update_all(void)
{
	update_clock();
	update_battery();
}
