#include "algebra.h"

#include <graphx.h>
#include "gfx/gfx.h"
#include <ti/getcsc.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <sys/rtc.h>
#include "io.h"

#define MAX_ENTRY_PER_PAGE 7

unsigned int algebra_gui()
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

	gfx_PrintStringXY("A L G E B R A      S U I T E",108,56);
	gfx_PrintStringXY("Software Credits:",55,84);
	gfx_PrintStringXY("- Jonathan Khayat 'BobSmith'",65,96);
	gfx_PrintStringXY("App Icon Credits:",55,118);
	gfx_PrintStringXY("- Jonathan Havard 'Mediocre CHUCH'",65,130);
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
	gfx_PrintStringXY("A L G E B R A      S U I T E",108,30);

	algebra_gui_solver_page1();
	unsigned int increment = get_Slider(80,52,3);
	return(increment);

}

void algebra_gui_solver_page1(void)
{
	unsigned int start_x = 80;
	unsigned int start_y = 52;

	gfx_PrintStringXY("1:   Factoring",start_x,start_y);
	gfx_PrintStringXY("2:   Quadratic Solver",start_x,start_y+15);
	gfx_PrintStringXY("3:   Radical Simplifier",start_x,start_y+30);

}
void algebra_factoring(void) // don't mess this is complete
{
	gfx_SetColor(0);
	gfx_FillRectangle(52,52,253,150);

	unsigned int key;
	unsigned int increment = 0;
	char user_input[21];
	char key_pad[] = { [sk_0] = '0', [sk_1] = '1', [sk_2] = '2', [sk_3] = '3', [sk_4] = '4', [sk_5] = '5', [sk_6] = '6', [sk_7] = '7', [sk_8] = '8', [sk_9] = '9'};
	gfx_SetTextFGColor(254);
	gfx_PrintStringXY("Rules:",60,48);
	gfx_PrintStringXY("- 20 Char Limit",70,58);
	gfx_PrintStringXY("- Exclude commas",70,68);
	gfx_PrintStringXY("- Number must be an integer over 0",70,78);
	gfx_PrintStringXY("Enter Number:",60,90);
	unsigned int user_input_converted = get_Integer(180,90);
	gfx_PrintStringXY("Factors are:",60,112);
	unsigned int x = 152;
	unsigned int y = 112;
	for(unsigned int i = 1; i <= user_input_converted; ++i)
	{
		if (user_input_converted % i == 0)
		{
			gfx_SetTextXY(x,y);
			gfx_PrintInt(i,1);
			if (y == 192)
			{
				x += 35;
				y = 112;
			}else
			{
				y += 10;
			}
		}
	}
}

//this code needs to be reviewed
void algebra_gcf_lcm(void)
{
	gfx_SetColor(0);
	gfx_FillRectangle(52,52,253,150);

	gfx_SetTextFGColor(254);
	gfx_PrintStringXY("Rules:",60,48);
	gfx_PrintStringXY("- All numbers must be integers.",70,58);
	gfx_PrintStringXY("How many numbers:",60,70);
	unsigned int quantity = get_Integer(200,70);

	gfx_PrintStringXY("- Separate Numbers with Commas.",70,80);
	gfx_PrintStringXY("- No spaces.",70,90);
	gfx_PrintStringXY("Enter Numbers:",60,112);
	char numbers_input[quantity*6];
	char key_pad_comma[] = { [sk_0] = '0', [sk_1] = '1', [sk_2] = '2', [sk_3] = '3', [sk_4] = '4', [sk_5] = '5', [sk_6] = '6', [sk_7] = '7', [sk_8] = '8', [sk_9] = '9', [sk_Comma] = ','};

	unsigned int x = 188;
	unsigned int y = 112;
	unsigned int key;
	unsigned int increment = 1;
	gfx_SetColor(254);
	gfx_Line(x,y+7,x+8,y+7);
	gfx_Line(x,y+8,x+8,y+8);
	while(key = os_GetCSC(), key != sk_Clear)
	{
		if (key == sk_Del && increment != 0)	// user deletes char
		{
			increment--;
			gfx_SetColor(0);
			gfx_Line(x,y+7,x+8,y+7);
			gfx_Line(x,y+8,x+8,y+8);
			gfx_FillRectangle(188+8*increment,112,8,8);
			x -= 8;
			gfx_SetColor(254);
			gfx_Line(x,y+7,x+8,y+7);
			gfx_Line(x,y+8,x+8,y+8);
		}else if (key == sk_Enter)
		{
			break;
		}else if (key != 0 && key != sk_Enter && key != sk_Del && key != sk_Clear)
		{
			gfx_SetColor(0);
			gfx_Line(x,y+7,x+8,y+7);
			gfx_Line(x,y+8,x+8,y+8);
			gfx_SetTextFGColor(254);
			gfx_SetTextXY(x,y);
			gfx_PrintChar(key_pad_comma[key]);
			x += 8;
			gfx_SetColor(254);
			gfx_Line(x,y+7,x+8,y+7);
			gfx_Line(x,y+8,x+8,y+8);
			numbers_input[increment++] = key_pad_comma[key];
		}
	}
	
	numbers_input[increment] = '\0'; //terminates string at current position

	//now, i need to create code with strtol to separate the numbers out

	long int numbers_input_converted[quantity];
	char rest_of_numbers_input[sizeof(numbers_input_converted)/sizeof(numbers_input_converted[0])];

	for(unsigned int x = 0; x <= quantity; x++)
	{
		numbers_input_converted[x] = strtol(numbers_input,&rest_of_numbers_input,0);
		if (x >= 1)
		{
			rest_of_numbers_input[0] = '0'; //removes the comma that would be left over from the strtol and puts a zero
		}
	}
	
	long int max = numbers_input_converted[0];
	for (x = 0; x <= quantity; x++) // stores the largest integer in numbers_input_converted in max
	{
		if (max < numbers_input_converted[x])
		{
			max = numbers_input_converted[x];
		}
	}
	
	unsigned int LCM;
	while(1) // find LCM of the first two numbers
	{
		if (max % numbers_input_converted[0] == 0 && max % numbers_input_converted[1] == 0)
		{
			LCM = max;
			break;
		}
		++max;
	}
	
	if (quantity > 2) // continues calculation of LCM is more than two numbers are entered
	{
		for (x=2; x<= quantity;)
		{
			if(LCM % numbers_input_converted[x] == 0)
			{
				x++;
				break;
			}
			
			LCM++;
		}
	}

	gfx_PrintStringXY("LCM is",60,128);
	gfx_SetTextXY(105,128);
	gfx_PrintInt(LCM,1);
	gfx_PrintChar('.');
	gfx_PrintInt(max,1);
	gfx_PrintChar('.');
	gfx_PrintInt(quantity,1);
	gfx_PrintChar('.');
	for(x=0;x<=quantity;x++)
	{
		gfx_PrintInt(numbers_input_converted[x],1);
	}

	gfx_SetColor(0);
}
void algebra_prime(void) //still needs work, keeps resetting calc.
{
	gfx_SetColor(0);
	gfx_FillRectangle(52,52,253,100);
	gfx_PrintStringXY("Rules:",80,52);
	gfx_PrintStringXY("- Only integers.",90,62);
	gfx_PrintStringXY("Enter starting point:",80,80);
	unsigned int start = get_Integer(230,80);
	gfx_SetTextXY(80,70);
	gfx_PrintInt(1,1);
	unsigned int c;
	unsigned int key;
	while(key = os_GetCSC(), key != sk_Clear)
	{
		if (key == sk_Enter)
		{
			c = 1;
			while(c != 0)
			{
				c++;
				if(c == start/2)
				{
					start++;
				}else if (start%c == 0)
				{
					break;
				}
			}
			gfx_FillRectangle(52,52,253,100);
			gfx_SetTextXY(80,70);
			gfx_PrintInt(start,1);
		}
	}
}

void algebra_quadratic(void)
{
	gfx_SetColor(0);
	gfx_FillRectangle(52,52,253,100);
	gfx_SetTextFGColor(254);
	gfx_PrintStringXY("Rules:",80,52);
	gfx_PrintStringXY("- Decimals allowed.",80,62);
	gfx_PrintStringXY("A*X^2 + BX + C",80,80);
	gfx_PrintStringXY("A:",80,90);
	double a = get_Double(95,90);
	gfx_PrintStringXY("B:",80,100);
	double b = get_Double(95,100);
	gfx_PrintStringXY("C:",80,110);
	double c = get_Double(95,110);
	if (b*b - 4*a*c < 0)
	{
		gfx_PrintStringXY("No real roots.",80,140);
	}else if (b*b-4*a*c >= 0)
	{
		gfx_PrintStringXY("X =    ",80,140);
		print_Double((-b+sqrt(b*b-4*a*c))/(2*a),7);
	}
	if (b*b-4*a*c > 0)
	{
		gfx_SetTextXY(108,150);
		print_Double((-b-sqrt(b*b-4*a*c))/(2*a),7);
	}
}


