#include "chemistry.h"
#include <graphx.h>
#include <gfx/gfx.h>
#include <string.h>
#include <math.h>
#include "io.h"
#include <time.h>

int chemistry_gui(void)
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

	gfx_PrintStringXY("C H E M I S T R Y      S U I T E",108,56);
	gfx_PrintStringXY("Software Credits:",55,84);
	gfx_PrintStringXY("- Jonathan Khayat 'BobSmith'",65,96);
	gfx_PrintStringXY("App Icon Credits:",55,118);
	gfx_PrintStringXY("- Jonathan Khayat 'BobSmith",65,130);
	gfx_PrintStringXY("Copyright June 2022.",100,192);
    while(!os_GetCSC())
    {
        gfx_SetColor(0);
        if((clock() % CLOCKS_PER_SEC < CLOCKS_PER_SEC * 8 / 10))
		{
            gfx_FillRectangle(132,156,100,15);
        }else
		{
			gfx_SetTextFGColor(31);
            gfx_PrintStringXY("Press any Key",132,156);
        }
    }
	gfx_FillRectangle(132,156,100,15);

//display the different solvers
	gfx_FillRectangle(52,52,253,100);
	gfx_PrintStringXY("C H E M I S T R Y      S U I T E",108,30);

	geometry_gui_page1();

	unsigned int increment = get_Slider(80,52,5);
	return (increment);

}

void chemistry_gui_page1(void)
{
	unsigned int start_x = 80;
	unsigned int start_y = 52;

	gfx_PrintStringXY("1:   Electrochemistry Solvers",start_x,start_y);
	gfx_PrintStringXY("2:   Equilibrium Solvers",start_x,start_y+15);
	gfx_PrintStringXY("3:   Gas and Liquid Solvers",start_x,start_y+30);
	gfx_PrintStringXY("4:   Molar Mass Calculator",start_x,start_y+45);
}

void chemistry_electrochem(void)
{
	gfx_SetColor(0);
	gfx_FillRectangle(52,52,253,100);
	gfx_PrintStringXY("Select a Solver:",80,52);
	gfx_PrintStringXY("- Heat (q=mCAT)",90,62);
	gfx_PrintStringXY("- Entropy (S)",90,77);
	gfx_PrintStringXY("- Enthalpy (H)",90,92);
	gfx_PrintStringXY("- Gibbs Energy (G)",90,107);
	gfx_PrintStringXY("- Current (I)",90,122);
	gfx_PrintStringXY("- Reduction Potential (Ecell)",90,137);
	unsigned int increment = get_Slider(80,62,6);
	gfx_SetColor(0);
	gfx_FillRectangle(52,52,253,100);
	gfx_PrintStringXY("Rules:",80,52);
	gfx_PrintStringXY("- Decimals allowed.",90,62);
	gfx_PrintStringXY("- Sci Notation NOT ALLOWED!",90,72);
	gfx_PrintStringXY("- Enter '0' for output variable.",90,82);
	switch(increment)
	{
		case 1:
			gfx_PrintStringXY("q:",80,100);
			double q = get_Double(95,100);
			gfx_PrintStringXY("m (in grams):",90,100);
	}
}











