#include "trig.h"
#include <graphx.h>
#include "gfx/gfx.h"
#include <ti/getcsc.h>
#include <time.h>
#include "io.h"
#include <math.h>

#define MAX_ENTR_PER_PAGE 5
#define pi 3.141592654

int trig_gui(void)
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

	gfx_SetTextFGColor(254);
	gfx_PrintStringXY("T R I G O N O M E T R Y      S U I T E",90,56);
	gfx_PrintStringXY("Software Credits:",55,84);
	gfx_PrintStringXY("- Jonathan Khayat 'BobSmith'",65,96);
	gfx_PrintStringXY("App Icon Credits:",55,118);
	gfx_PrintStringXY("- Jonathan Havard 'Mediocre CHUCH'",65,130);
	gfx_PrintStringXY("Copyright July 2022.",100,192);
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
	gfx_PrintStringXY("T R I G O N O M E T R Y     S U I T E",90,30);

	trig_gui_page1();
	return(get_Slider(80,52,5));

}

void trig_gui_page1(void)
{
	unsigned int start_x = 80;
	unsigned int start_y = 52;

	gfx_PrintStringXY("1:   Argument Solver",start_x,start_y);
	gfx_PrintStringXY("2:   Deg/Rad Convertor",start_x,start_y+15);
	gfx_PrintStringXY("3:   Probability Calculator",start_x,start_y+30);
	gfx_PrintStringXY("4:   Sequence and Series",start_x,start_y+45);
	gfx_PrintStringXY("5:   Triangle Solver",start_x,start_y+60);
}

void trig_arg(void)
{
	gfx_SetColor(0);
	gfx_FillRectangle(52,52,253,100);
	gfx_PrintStringXY("Which solver do you want?",80,52);
	gfx_PrintStringXY("- Half-Argument",90,62);
	gfx_PrintStringXY("- Double-Argument",90,72);
	unsigned int first = get_Slider(90,62,2);

	gfx_SetColor(0);
	gfx_FillRectangle(52,52,253,100);
	gfx_PrintStringXY("- sin()",90,62);
	gfx_PrintStringXY("- cos()",90,72);
	gfx_PrintStringXY("- tan()",90,82);
	unsigned int second = get_Slider(90,62,3);

	gfx_SetColor(0);
	gfx_FillRectangle(52,52,253,100);
	gfx_PrintStringXY("Rules:",80,52);
	gfx_PrintStringXY("- Decimals allowed.",90,62);
	gfx_PrintStringXY("- Argument must be degrees.",90,72);
	gfx_PrintStringXY("Degrees:",80,90);
	double degrees = get_Double(150,90);
	gfx_PrintStringXY("Answer =   ",90,110);
	switch (first)
	{
		case 1:
			if (second==1)
			{
				print_Double(180/pi*sin(1/2*degrees*pi/180),5);
			}else if (second == 2)
			{
				print_Double(180/pi*cos(1/2*degrees*pi/180),5);
			}else if (second == 3)
			{
				print_Double(180/pi*tan(1/2*degrees*pi/180),5);
			}
			break;
		case 2:
			if (second==1)
			{
				print_Double(180/pi*sin(2*degrees*pi/180),5);
			}else if (second == 2)
			{
				print_Double(180/pi*cos(2*degrees*pi/180),5);
			}else if (second == 3)
			{
				print_Double(180/pi*tan(2*degrees*pi/180),5);
			}
			break;
	}
}

void trig_degrad(void)
{
	gfx_SetColor(0);
	gfx_FillRectangle(52,52,253,100);
	gfx_PrintStringXY("What are you given?",80,52);
	gfx_PrintStringXY("- Degrees",90,62);
	gfx_PrintStringXY("- Radians",90,72);
	unsigned int increment = get_Slider(90,62,2);
	switch (increment)
	{
		gfx_SetColor(0);
		gfx_FillRectangle(52,52,253,100);
		gfx_SetTextFGColor(254);
		gfx_PrintStringXY("Rules:",80,52);
		gfx_PrintStringXY("- Decimals allowed.",90,62);
		gfx_PrintStringXY("- NO FRACTIONS!",90,72);
		case 1:
			gfx_PrintStringXY("Degrees:",80,90);
			double degrees = get_Double(150,90);
			gfx_PrintStringXY("Radians(in terms of pi) =   ",70,110);
			print_Double(degrees/180,5);
			break;
		case 2:
			gfx_PrintStringXY("Radians(terms of pi):",80,90);
			double radians = get_Double(270,90);
			gfx_PrintStringXY("Degrees =   ",90,110);
			print_Double(radians*180,5);
			break;
	}
}

void trig_prob(void)
{
	gfx_SetColor(0);
	gfx_FillRectangle(52,52,253,100);
	gfx_SetTextFGColor(254);
	gfx_PrintStringXY("Which solver do you want?",80,52);
	gfx_PrintStringXY("- Combination Solver",80,62);
	gfx_PrintStringXY("- Permutation Solver",80,72);
	gfx_PrintStringXY("- Help",80,92);
	unsigned int increment = get_Slider(80,62,3);
	gfx_SetColor(0);
	gfx_FillRectangle(52,52,253,100);
	if (increment == 3)
	{
		gfx_PrintStringXY("Permutation is when order",80,52);
		gfx_PrintStringXY("does NOT matter.",90,62);
		gfx_PrintStringXY("Combination is when order",80,72);
		gfx_PrintStringXY("DOES matter.",90,82);
		return;
	}
	gfx_PrintStringXY("Rules:",80,52);
	gfx_PrintStringXY("- Decimals allowed.",80,62);
	gfx_PrintStringXY("Number of Objects:",80,80);
	double num = get_Double(230,80);
	gfx_PrintStringXY("Objects in Group:",80,90);
	double obj = get_Double(230,90);
	gfx_PrintStringXY("Possibilities =   ",90,110);
	switch(increment)
	{
		case 1:
			print_Double(fact(num)/fact(num-obj),5);
			print_Double(fact(5),5);
			break;
		case 2:
			print_Double(fact(num)/(fact(obj)*fact(num-obj)),5);
			break;
	}
}

void trig_seq_series(void)
{
	gfx_SetColor(0);
	gfx_FillRectangle(52,52,253,100);
	gfx_SetTextFGColor(254);
	gfx_PrintStringXY("- Sequence",80,52);
	gfx_PrintStringXY("- Series",80,67);
	unsigned int increment = get_Slider(80,52,2);
	gfx_FillRectangle(52,52,253,100);
	gfx_PrintStringXY("- Arithmetic",80,52);
	gfx_PrintStringXY("- Geometric",80,67);
	unsigned int second = get_Slider(80,52,2);
	gfx_SetColor(0);
	gfx_FillRectangle(52,52,253,100);
	switch(increment)
	{
		gfx_PrintStringXY("Rules:",80,52);
		gfx_PrintStringXY("- Decimals allowed.",90,62);
		case 1:
			gfx_PrintStringXY("First term:",80,80);
			double firstterm = get_Double(165,80);
			gfx_PrintStringXY("Desired term:",80,90);
			double desiredterm = get_Double(175,90);
			if(second == 1)
			{
				gfx_PrintStringXY("Common Difference:",80,100);
				double d = get_Double(220,100);
				print_Double(firstterm + (desiredterm-1)*d,5);
			}else if(second == 2)
			{
				gfx_PrintStringXY("Common Ratio:",80,100);
				double r = get_Double(180,100);
				print_Double(firstterm*pow(r,desiredterm-1),5);
			}
			gfx_SetTextXY(80,120);
			print_Double(desiredterm,0);
			gfx_PrintChar('t');
			gfx_PrintChar('h');
			gfx_PrintChar(' ');
			gfx_PrintChar('T');
			gfx_PrintChar('e');
			gfx_PrintChar('r');
			gfx_PrintChar('m');
			gfx_PrintChar(':');
			break;
		case 2:
			gfx_PrintStringXY("First term:",80,80);
			double term1 = get_Double(165,80);
			gfx_PrintStringXY("Terms in series (N):",80,90);
			double n = get_Double(190,80);
			if(second == 1)
			{
				gfx_PrintStringXY("Common Difference:",80,100);
				double cd = get_Double(220,100);
				print_Double(n/2*(2*term1+cd*(n-1)),5);
			}else if (second == 2)
			{
				gfx_PrintStringXY("Common Ratio:",80,100);
				double cr = get_Double(180,100);
				print_Double(term1*((1-pow(cr,n))/(1-cr)),5);
			}
			gfx_SetTextXY(80,120);
			print_Double(desiredterm,0);
			gfx_PrintChar('t');
			gfx_PrintChar('h');
			gfx_PrintChar(' ');
			gfx_PrintChar('T');
			gfx_PrintChar('e');
			gfx_PrintChar('r');
			gfx_PrintChar('m');
			gfx_PrintChar(':');
			break;
	}
}

void trig_triangle_solver(void)
{
	gfx_SetColor(0);
	gfx_FillRectangle(52,52,253,150);
	gfx_SetTextFGColor(254);
	gfx_PrintStringXY("- Side, Angle, Side (SAS)",80,52);
	gfx_PrintStringXY("- Side, Side, Side (SSS)",80,67);
	gfx_PrintStringXY("- Angle, Side, Angle (ASA)",80,82);
	gfx_PrintStringXY("- Angle, Angle, Side (AAS)",80,97);
	unsigned int increment = get_Slider(80,52,4);
	gfx_SetColor(0);
	gfx_FillRectangle(52,52,253,100);
	gfx_PrintStringXY("Rules:",80,52);
	gfx_PrintStringXY("- Decimals allowed.",90,62);
	gfx_SetColor(8);
	unsigned int points[] = {84,200,184,200,112,156};
	gfx_Polygon(points,3);
	gfx_SetTextXY(112,161);
	gfx_PrintChar('A');
	gfx_SetTextXY(94,190);
	gfx_PrintChar('B');
	gfx_SetTextXY(174,190);
	gfx_PrintChar('C');
	gfx_SetTextXY(134,190);
	gfx_PrintChar('a');
	gfx_SetTextXY(153,173);
	gfx_PrintChar('b');
	gfx_SetTextXY(93,173);
	gfx_PrintChar('c');
	double side_a,side_b,side_c,angle_A,angle_B,angle_C,semip,area;
	switch (increment)
	{
		case 1:
			gfx_PrintStringXY("Side c = ",80,80);
			side_c = get_Double(160,80);
			gfx_PrintStringXY("Angle A = ",80,90);
			angle_A = get_Double(170,90);
			gfx_PrintStringXY("Side b = ",80,100);
			side_b = get_Double(160,100);
			gfx_PrintStringXY("Side a =    ",80,110);
			side_a = sqrt(side_b*side_b+side_c*side_c-cos(pi/180*angle_A)*2*side_b*side_c);
			print_Double(side_a,5);
			gfx_PrintStringXY("Angle B =   ",80,120);
			angle_B = 180/pi*acos((side_a*side_a+side_c*side_c-side_b*side_b)/(2*side_a*side_c));
			print_Double(angle_B,5);
			gfx_PrintStringXY("Angle C =   ",80,130);
			angle_C = 180/pi*acos((side_a*side_a+side_b*side_b-side_c*side_c)/(2*side_a*side_b));
			print_Double(angle_C,5);
			gfx_PrintStringXY("Area =   ",80,140);
			semip = (side_a+side_b+side_c)/2;
			area = sqrt(semip*(semip-side_a)*(semip-side_b)*(semip-side_c));
			print_Double(area,5);
			break;
		case 2:
			gfx_PrintStringXY("Side a = ",80,80);
			side_a = get_Double(160,80);
			gfx_PrintStringXY("Side b = ",80,90);
			side_b = get_Double(160,90);
			gfx_PrintStringXY("Side c = ",80,100);
			side_c = get_Double(160,100);
			angle_A = 180/pi*acos((side_b*side_b+side_c*side_c-side_a*side_a)/(2*side_b*side_c));
			gfx_PrintStringXY("Angle A =   ",80,110);
			print_Double(angle_A,5);
    		angle_B = 180/pi*acos((side_a*side_a+side_c*side_c-side_b*side_b)/(2*side_a*side_c));
			gfx_PrintStringXY("Angle B =   ",80,120);
			print_Double(angle_B,5);
			gfx_PrintStringXY("Angle C =   ",80,130);
			angle_C = 180/pi*acos((side_a*side_a+side_b*side_b-side_c*side_c)/(2*side_a*side_b));
			print_Double(angle_C,5);
			gfx_PrintStringXY("Area =   ",80,140);
    		semip = (side_a+side_b+side_c)/2;
    		area = sqrt(semip*(semip-side_a)*(semip-side_b)*(semip-side_c));
			print_Double(area,5);
			break;
		case 3:
			gfx_PrintStringXY("Angle A =",80,80);
			angle_A = get_Double(170,80);
			gfx_PrintStringXY("Side c = ",80,90);
			side_c = get_Double(170,90);
			gfx_PrintStringXY("Angle B =",80,100);
			angle_B = get_Double(170,100);
			angle_C = 180 - angle_A - angle_B;
			gfx_PrintStringXY("Angle C =   ",80,110);
			print_Double(angle_C,5);
    		side_a = (side_c*sin(pi/180*angle_A))/sin(pi/180*angle_C);
			gfx_PrintStringXY("Side a =   ",80,120);
			print_Double(side_a,5);
    		side_b = (side_a*sin(pi/180*angle_B))/sin(pi/180*angle_A);
			gfx_PrintStringXY("Side b =   ",80,130);
			print_Double(side_b,5);
    		semip = (side_a+side_b+side_c)/2;
    		area = sqrt(semip*(semip-side_a)*(semip-side_b)*(semip-side_c));
			gfx_PrintStringXY("Area =   ",80,140);
			print_Double(area,5);
			break;
		case 4:
			gfx_PrintStringXY("Angle A =",80,80);
			angle_A = get_Double(170,80);
			gfx_PrintStringXY("Angle B =",80,90);
			angle_B = get_Double(170,90);
			gfx_PrintStringXY("Side a =",80,100);
			side_c = get_Double(160,100);
			angle_C = 180 - angle_B - angle_A;
			gfx_PrintStringXY("Angle C =   ",80,110);
			print_Double(angle_C,5);
    		side_b = (side_a*sin(pi/180*angle_B))/sin(pi/180*angle_A);
			gfx_PrintStringXY("Side b =   ",80,120);
			print_Double(side_b,5);
    		side_c = (side_b*sin(pi/180*angle_C))/sin(pi/180*angle_B);
			gfx_PrintStringXY("Side c =   ",80,130);
			print_Double(side_c,5);
    		semip = (side_a+side_b+side_c)/2;
    		area = sqrt(semip*(semip-side_a)*(semip-side_b)*(semip-side_c));
			gfx_PrintStringXY("Area =   ",80,140);
			print_Double(area,5);
			break;
	}
}
unsigned long long fact(unsigned int num)
{
	unsigned int i;
	unsigned long long int fact = 1;
	for(i = 1; i<=num; ++i)
	{
		fact*=i;
	}
	return (fact);
}