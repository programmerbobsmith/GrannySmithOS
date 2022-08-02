#include "geometry.h"
#include <graphx.h>
#include "gfx/gfx.h"
#include <time.h>
#include <ti/getcsc.h>
#include <math.h>
#include <stdint.h>
#include "io.h"

#define pi 3.141592654

int geometry_gui(void)
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

	gfx_PrintStringXY("G E O M E T R Y      S U I T E",108,56);
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
	gfx_FillRectangle(52,52,266,100);
	gfx_PrintStringXY("G E O M E T R Y      S U I T E",108,30);
	geometry_gui_page1();
	unsigned int increment = get_Slider(80,52,6);
	return(increment);

}

void geometry_gui_page1(void)
{
	unsigned int start_x = 80;
	unsigned int start_y = 52;

	gfx_PrintStringXY("1:   Area and Perimeter Calculator",start_x,start_y);
	gfx_PrintStringXY("2:   Distance Calculator",start_x,start_y+15);
	gfx_PrintStringXY("3:   Midpoint and Slope Calculator",start_x,start_y+30);
	gfx_PrintStringXY("4:   Pythagorean Calculator",start_x,start_y+45);
	gfx_PrintStringXY("5:   Slope-Int/Pnt-Slope Form",start_x,start_y+60);
	gfx_PrintStringXY("6:   Surface Area/Volume Calculator",start_x,start_y+75);
}

void geometry_distance(void)
{
	gfx_SetColor(0);
	gfx_FillRectangle(52,52,266,100);
	gfx_PrintStringXY("Rules:",80,52);
	gfx_PrintStringXY("- Decimals allowed.",90,62);
	gfx_PrintStringXY("First X:",80,80);
	double x1 = get_Double(144,80);
	gfx_PrintStringXY("First Y:",80,90);
	double y1 = get_Double(144,90);
	gfx_PrintStringXY("Second X:",80,100);
	double x2 = get_Double(150,100);
	gfx_PrintStringXY("Second Y:",80,110);
	double y2 = get_Double(150,110);
	gfx_PrintStringXY("Distance =   ",90,140);
	print_Double(sqrt((x2-x1)*(x2-x1)-(y2-y1)*(y2-y1)),5);
}

void geometry_mid_slope(void)
{
	gfx_SetColor(0);
	gfx_FillRectangle(52,52,266,100);
	gfx_SetTextFGColor(254);
	gfx_PrintStringXY("Rules:",80,52);
	gfx_PrintStringXY("- Decimals allowed.",90,62);
	gfx_PrintStringXY("First X:",80,80);
	double x1 = get_Double(144,80);
	gfx_PrintStringXY("First Y:",80,90);
	double y1 = get_Double(144,90);
	gfx_PrintStringXY("Second X:",80,100);
	double x2 = get_Double(150,100);
	gfx_PrintStringXY("Second Y:",80,110);
	double y2 = get_Double(150,110);
	gfx_PrintStringXY("Slope =   ",90,140);
	print_Double((y2-y1)/(x2-x1),5);
	gfx_PrintStringXY("Midpoint =   (",90,150);
	print_Double((x2+x1)/2,5);
	gfx_PrintChar(',');
	print_Double((y2+y1)/2,5);
	gfx_PrintChar(')');
}

void geometry_pythag(void)
{
	gfx_SetColor(0);
	gfx_FillRectangle(52,52,266,100);
	gfx_SetTextFGColor(254);
	gfx_PrintStringXY("Are you looking for:",80,52);
	gfx_PrintStringXY("- Hypotenuse",90,62);
	gfx_PrintStringXY("- Leg",90,77);
	unsigned int increment = get_Slider(90,62,2);
	
	gfx_SetColor(0);
	gfx_FillRectangle(52,52,253,100);
	gfx_SetTextFGColor(254);
	gfx_PrintStringXY("Rules:",80,52);
	gfx_PrintStringXY("- Decimals allowed.",80,62);
	gfx_PrintStringXY("- Must be right triangle.",80,72);
	switch (increment)
	{
		case 1:
			gfx_PrintStringXY("Larger Leg:",80,90);
			double larger = get_Double(175,90);
			gfx_PrintStringXY("Smaller Leg:",80,100);
			double smaller = get_Double(160,100);
			gfx_PrintStringXY("Hypotenuse =   ",90,120);
			print_Double(sqrt(larger*larger+smaller*smaller),5);
			break;
		case 2:
			gfx_PrintStringXY("Hypotenuse:",80,90);
			double hyp = get_Double(160,90);
			gfx_PrintStringXY("Leg:",80,100);
			double leg = get_Double(110,100);
			gfx_PrintStringXY("Other leg =   ",90,120);
			print_Double(sqrt(hyp*hyp - leg*leg),5);
			break;
	}
}	

void geometry_slope_forms(void)
{
	gfx_SetColor(0);
	gfx_FillRectangle(52,52,266,100);
	gfx_SetTextFGColor(254);
	gfx_PrintStringXY("What form do you want?",80,52);
	gfx_PrintStringXY("- Slope/Intercept",90,62);
	gfx_PrintStringXY("- Point/Slope",90,77);
	unsigned int early_descision = get_Slider(90,62,2);	
	gfx_SetColor(0);
	gfx_FillRectangle(52,52,253,100);
	gfx_SetTextFGColor(254);
	gfx_PrintStringXY("What are you given?",80,52);
	gfx_PrintStringXY("- 2 Points",90,62);
	gfx_PrintStringXY("- Slope and Point",90,77);
	unsigned int increment = get_Slider(90,62,2);
	switch (increment)
	{
		case 1:
			gfx_SetColor(0);
			gfx_FillRectangle(52,52,253,100);
			gfx_PrintStringXY("Rules:",80,52);
			gfx_PrintStringXY("- Decimals allowed.",90,62);
			gfx_PrintStringXY("First X:",80,80);
			double x1 = get_Double(150,80);
			gfx_PrintStringXY("First Y:",80,90);
			double y1 = get_Double(150,90);
			gfx_PrintStringXY("Second X:",80,100);
			double x2 = get_Double(155,100);
			gfx_PrintStringXY("Second Y:",80,110);
			double y2 = get_Double(155,110);
			if (early_descision == 1)
			{
				gfx_PrintStringXY("y = ",75,130);
				print_Double((y2-y1)/(x2-x1),3);
				gfx_PrintChar(' ');
				gfx_PrintChar('x');
				gfx_PrintChar(' ');
				gfx_PrintChar('+');
				gfx_PrintChar(' ');
				print_Double(y1 - ((y2-y1)/(x2-x1)*x1),3);
			}else if(early_descision == 2)
			{
				gfx_PrintStringXY("y -",75,130);
				print_Double(y1,2);
				gfx_PrintChar('=');
				gfx_PrintChar(' ');
				print_Double((y2-y1)/(x2-x1),2);
				gfx_PrintChar('(');
				gfx_PrintChar('x');
				gfx_PrintChar('-');
				print_Double(x1,2);
				gfx_PrintChar(')');
			}
			break;
		case 2:
			gfx_SetColor(0);
			gfx_FillRectangle(52,52,253,100);
			gfx_SetTextFGColor(254);
			if (early_descision == 2)
			{
				gfx_PrintStringXY("Seriously! You're lazy!",80,52);
			}else
			{
				gfx_SetColor(0);
				gfx_FillRectangle(52,52,253,100);
				gfx_PrintStringXY("Rules:",80,52);
				gfx_PrintStringXY("- Decimals allowed.",90,62);
				gfx_PrintStringXY("Slope:",80,80);
				double slope = get_Double(130,80);
				gfx_PrintStringXY("X:",80,90);
				double x = get_Double(92,90);
				gfx_PrintStringXY("Y:",80,100);
				double y = get_Double(92,100);
				gfx_PrintStringXY("y = ",75,130);
				print_Double(slope,3);
				gfx_PrintChar('x');
				gfx_PrintChar('+');
				print_Double(y-slope*x,4);
			}
			break;
	}
}

void geometry_surface_area(void)
{
	gfx_SetColor(0);
	gfx_FillRectangle(52,52,266,100);
	gfx_PrintStringXY("- Pyramid",80,62);
	gfx_PrintStringXY("- Prism",80,77);
	gfx_PrintStringXY("- Sphere",80,92);
	unsigned int increment = get_Slider(80,62,3);

	switch (increment)
	{
		case 1:
			geometry_sa_pyramid();
			break;
		case 2:
			geometry_sa_prism();
			break;
		case 3:
			geometry_sa_sphere();
			break;
	}
}

void geometry_sa_pyramid(void)
{
	gfx_SetColor(0);
	gfx_FillRectangle(52,52,266,100);
	gfx_PrintStringXY("- Rectangular",80,62);
	gfx_PrintStringXY("- Triangular",80,77);
	gfx_PrintStringXY("- Cone",80,92);
	gfx_PrintStringXY("- Other",80,107);
	unsigned int increment = get_Slider(80,62,4);
	gfx_SetColor(0);
	gfx_FillRectangle(52,52,253,100);
	gfx_PrintStringXY("Rules:",80,52);
	gfx_PrintStringXY("- Decimals allowed.",80,62);
	double height,slant,length,radius;
	switch (increment)
	{
		case 1: //rectangular pyramid
			gfx_PrintStringXY("Length:",80,80);
			length = get_Double(140,80);
			gfx_PrintStringXY("Width:",80,90);
			double width = get_Double(135,90);
			gfx_PrintStringXY("Height:",80,100);
			height = get_Double(140,100);
			gfx_PrintStringXY("Surface Area =   ",90,130);
			print_Double(length*width + .5*width*sqrt(4*height*height+length*length)+.5*length*sqrt(4*height*height+width*width),5);
			gfx_PrintStringXY("Volume =   ",90,140);
			print_Double(length*width*height/3,5);
			break;
		case 2: //triangular pyramid
			gfx_PrintStringXY("Side:",80,80);
			double side = get_Double(110,80);
			gfx_PrintStringXY("Apothem:",80,90);
			double apothem = get_Double(150,90);
			gfx_PrintStringXY("Slant Height:",80,100);
			gfx_PrintStringXY("If not given, put 0 and ignore SA.",70,110);
			slant = get_Double(180,100);
			gfx_PrintStringXY("Height:",80,120);
			gfx_PrintStringXY("If not given, put 0 and ignore V.",70,130);
			height = get_Double(150,120);
			gfx_PrintStringXY("Surface Area =    ",90,160);
			print_Double(side*apothem/2+3*side*slant/2,5);
			gfx_PrintStringXY("Volume =    ",90,170);
			print_Double(side*apothem*height/6,5);
			break;
		case 3: //cone
			gfx_PrintStringXY("Radius:",80,80);
			radius = get_Double(140,80);
			gfx_PrintStringXY("Height:",80,90);
			height = get_Double(140,90);
			gfx_PrintStringXY("Surface Area =   ",90,120);
			print_Double(radius*radius+radius*sqrt(height*height+radius*radius),5);
			gfx_PrintStringXY("Volume =   ",90,130);
			print_Double(height/3*radius*radius,5);
			gfx_PrintStringXY("Answers are in terms of pi.",80,150);
			break;
		case 4: //other pyramids
			gfx_PrintStringXY("Number of Base Edges:",70,80);
			double edges = get_Double(240,80);
			gfx_PrintStringXY("Length of Edges:",70,90);
			length = get_Double(200,90);
			gfx_PrintStringXY("Slant Height:",70,100);
			gfx_PrintStringXY("If not given, put 0 and ignore SA.",70,110);
			slant = get_Double(180,100);
			gfx_PrintStringXY("Height:",70,120);
			gfx_PrintStringXY("If not given, put 0 and ignore V.",70,130);
			height = get_Double(140,120);
			gfx_PrintStringXY("Surface Area =   ",80,150);
			print_Double(edges*length*length/(4*tan(pi/edges))+2*edges*slant,5);
			gfx_PrintStringXY("Volume =   ",80,160);
			print_Double(edges*length*length/(4*tan(pi/edges))*height/3,5);
			break;
	}
}

void geometry_sa_prism(void)
{
	gfx_SetColor(0);
	gfx_FillRectangle(52,52,266,100);
	gfx_SetTextFGColor(254);
	gfx_PrintStringXY("- Rectangular",80,62);
	gfx_PrintStringXY("- Triangular",80,77);
	gfx_PrintStringXY("- Cylinder",80,92);
	gfx_PrintStringXY("- Other",80,107);
	unsigned int increment = get_Slider(80,62,4);
	gfx_SetColor(0);
	gfx_SetTextFGColor(254);
	gfx_FillRectangle(52,52,253,100);
	gfx_PrintStringXY("Rules:",80,52);
	gfx_PrintStringXY("- Decimals allowed.",80,62);
	double height,slant,length;
	switch(increment)
	{
		case 1: //rectangular prism
			gfx_PrintStringXY("Length:",80,80);
			length = get_Double(140,80);
			gfx_PrintStringXY("Width:",80,90);
			double width = get_Double(130,90);
			gfx_PrintStringXY("Height:",80,100);
			height = get_Double(140,100);
			gfx_PrintStringXY("Surface Area =   ",90,120);
			print_Double(2*(length*width+width*height+length*height),5);
			gfx_PrintStringXY("Volume =   ",90,140);
			print_Double(length*width*height,5);
			break;
		case 2: //triangular prism
			gfx_PrintStringXY("First Side:",80,80);
			double side1 = get_Double(170,80);
			gfx_PrintStringXY("Second Side:",80,90);
			double side2 = get_Double(180,90);
			gfx_PrintStringXY("Third Side:",80,100);
			double side3 = get_Double(170,100);
			gfx_PrintStringXY("Height:",80,110);
			double height = get_Double(155,110);
			gfx_PrintStringXY("Surface Area =   ",90,140);
			double semi = (side1+side2+side3)/2;
			print_Double(height*side1+height*side2+height*side3+2*sqrt(semi*(semi-side1)*(semi-side2)*(semi-side3)),5);
			gfx_PrintStringXY("Volume =   ",90,150);
			print_Double(height*sqrt(semi*(semi-side1)*(semi-side2)*(semi-side3)),5);
			break;
		case 3: //cylinder
			gfx_PrintStringXY("Radius:",80,80);
			double radius = get_Double(140,80);
			gfx_PrintStringXY("Height:",80,90);
			height = get_Double(140,90);
			gfx_PrintStringXY("Surface Area =   ",90,110);
			print_Double(2*radius*radius+2*radius*height,5);
			gfx_PrintStringXY("Volume =   ",90,120);
			print_Double(radius*radius*height,5);
			gfx_PrintStringXY("Answers are in terms of pi.",80,130);
			break;
		case 4: //other prisms
			gfx_PrintStringXY("Number of Base Edges:",80,80);
			double edges = get_Double(250,80);
			gfx_PrintStringXY("Length of Edge:",80,90);
			length = get_Double(200,90);
			gfx_PrintStringXY("Height:",80,100);
			height = get_Double(140,100);
			gfx_PrintStringXY("Surface Area =   ",90,120);
			print_Double(edges*length*length/(4*tan(pi/edges))*2+edges*length*height,5);
			gfx_PrintStringXY("Volume =   ",90,130);
			print_Double(edges*length*length/(4*tan(pi/edges))*height,5);
			break;
	}
}

void geometry_sa_sphere(void)
{
	gfx_SetColor(0);
	gfx_FillRectangle(52,52,266,100);
	gfx_SetTextFGColor(254);
	gfx_PrintStringXY("Rules:",80,52);
	gfx_PrintStringXY("- Decimals allowed.",90,62);
	gfx_PrintStringXY("- Radius = 1/2 Diameter",90,72);
	gfx_PrintStringXY("Radius:",80,90);
	double radius = get_Double(140,90);
	gfx_PrintStringXY("Surface Area =   ",90,100);
	print_Double(4*radius*radius,5);
	gfx_PrintStringXY("Volume =   ",90,110);
	print_Double(4*radius*radius*radius/3,5);
	gfx_PrintStringXY("Answers are in terms of pi.",80,120);
}

int geometry_area_perimeter(void)
{
	gfx_SetColor(0);
	gfx_FillRectangle(52,52,266,150);
	gfx_PrintStringXY("1:  Rectangle",80,52);
	gfx_PrintStringXY("2:  Triangle",80,67);
	gfx_PrintStringXY("3:  Circle",80,82);
	gfx_PrintStringXY("4:  Trapezoid",80,97);
	gfx_PrintStringXY("5:  Others",80,112);
	unsigned int increment = get_Slider(80,52,5);
	
	switch (increment)
	{
		case 1:
			geometry_ap_rectangle();
			break;
		case 2:
			geometry_ap_triangle();
			break;
		case 3:
			geometry_ap_circle();
			break;
		case 4:
			geometry_ap_trapezoid();
			break;
		case 5:
			geometry_ap_others();
			break;
	}

}
void geometry_ap_rectangle(void)
{
	gfx_SetColor(0);
	gfx_FillRectangle(52,52,253,150);
	gfx_SetTextFGColor(254);
	gfx_PrintStringXY("Rules:",80,52);
	gfx_PrintStringXY("- Decimals allowed.",90,62);
	gfx_PrintStringXY("Length:",80,80);
	double length = get_Double(155,80);
	gfx_PrintStringXY("Width:",80,90);
	double width = get_Double(155,90);
	gfx_PrintStringXY("Area:   ",90,100);
	print_Double(length*width,5);
	gfx_PrintStringXY("Perimeter:   ",90,110);
	print_Double(2*length+2*width,5);
}

void geometry_ap_triangle(void)
{
	gfx_SetColor(0);
	gfx_FillRectangle(52,52,253,150);
	gfx_SetColor(0);
	gfx_FillRectangle(52,52,253,150);
	gfx_PrintStringXY("What are you given?",70,52);
	gfx_PrintStringXY("-  Base and Height",80,67);
	gfx_PrintStringXY("-  SSS",80,82);
	gfx_PrintStringXY("-  SAS",80,97);
	gfx_PrintStringXY("-  Other",80,112);
	unsigned int increment = get_Slider(80,67,4);
	
	double side_1,side_2;
	switch (increment)
	{
		case 1: // base height
			gfx_SetColor(0);
			gfx_FillRectangle(52,52,253,100);
			gfx_PrintStringXY("Rules:",80,52);
			gfx_PrintStringXY("- Decimals allowed.",90,62);
			gfx_PrintStringXY("Base:",80,80);
			double base = get_Double(105,80);
			gfx_PrintStringXY("Height:",80,95);
			double height = get_Double(115,95);
			gfx_PrintStringXY("Area:   ",90,115);
			print_Double(base * height/2, 4);
			gfx_PrintStringXY("Perimeter cannot be determined.",90,130);
			gfx_PrintStringXY("If Equilateral, Perimeter =   ",60,140);
			print_Double(base*3,4);
			gfx_PrintStringXY("If Isosceles, Perimeter =   ", 60, 150);
			print_Double(base + 2*sqrt((base*base+height*height)*(base*base+height*height)),5);
			gfx_PrintStringXY("If Right, Perimeter =   ",60,160);
			print_Double(base + height + sqrt((base*base+height*height)*(base*base+height*height)),5);
			break;
		case 2: // sss
			gfx_SetColor(0);
			gfx_FillRectangle(52,52,253,100);
			gfx_PrintStringXY("Rules:",80,52);
			gfx_PrintStringXY("- Decimals allowed.",90,62);
			gfx_PrintStringXY("First Side:",80,80);
			side_1 = get_Double(140,80);
			gfx_PrintStringXY("Second Side:",80,90);
			side_2 = get_Double(150,90);
			gfx_PrintStringXY("Third Side:",80,100);
			double side_3 = get_Double(140,100);
			gfx_PrintStringXY("Area =   ",90,120);
			double sp = .5*(side_1+side_2+side_3);
			print_Double(sqrt(sp*(sp - side_1)*(sp - side_2)*(sp - side_3)) ,5);
			gfx_PrintStringXY("Perimeter =   ",90,130);
			print_Double(side_1+side_2+side_3,4);
			break;
		case 3: // sas
			gfx_SetColor(0);
			gfx_FillRectangle(52,52,253,100);
			gfx_PrintStringXY("Rules:",80,52);
			gfx_PrintStringXY("- Decimals allowed.",90,62);
			gfx_PrintStringXY("First Side:",80,80);
			side_1 = get_Double(130,80);
			gfx_PrintStringXY("Angle:",80,90);
			double angle = get_Double(120,90);
			gfx_PrintStringXY("Second Side:",80,100);
			side_2 = get_Double(135,100);
			gfx_PrintStringXY("Area =   ",90,120);
			print_Double(.5*side_1*side_2*(sin(angle*pi/180)),5);
			gfx_PrintStringXY("Perimeter =   ",90,130);
			print_Double(side_1+side_2+sqrt(side_1*side_1 + side_2*side_2 - 2*side_1*side_2*(cos(angle*pi/180))),5);
			break;
		case 4:
			gfx_SetColor(0);
			gfx_FillRectangle(52,52,253,100);
			gfx_PrintStringXY("Calculation is not possible!",80,80);
			break;
	}
}

void geometry_ap_circle(void)
{
	gfx_SetColor(0);
	gfx_FillRectangle(52,52,253,150);
	gfx_PrintStringXY("Rules:",80,52);
	gfx_PrintStringXY("- Decimals allowed.",90,62);
	gfx_PrintStringXY("- Radius = 1/2 Diameter",90,72);
	gfx_PrintStringXY("Radius:",80,90);
	double radius = get_Integer(155,90);
	gfx_PrintStringXY("Area:   ",90,110);
	print_Double(2*pi*radius,3);
	gfx_PrintStringXY("Circumference:   ",90,120);
	print_Double(2*pi*radius,3);
}

void geometry_ap_trapezoid(void)
{
	gfx_SetColor(0);
	gfx_FillRectangle(52,52,253,150);
	gfx_PrintStringXY("1:  Isosceles Trapezoid",80,52);
	gfx_PrintStringXY("2:  All other Trapezoids",80,67);
	unsigned int increment = get_Slider(80,52,2);
	gfx_SetColor(0);
	gfx_FillRectangle(52,52,253,150);
	gfx_PrintStringXY("Rules:",80,52);
	gfx_PrintStringXY("- Decimals allowed.",80,62);
	gfx_PrintStringXY("Large Base:",80,80);
	double large_base = get_Double(170,80);
	gfx_PrintStringXY("Small Base:",80,95);
	double small_base = get_Double(170,95);
	gfx_PrintStringXY("Height:",80,110);
	double height = get_Double(170,110);
	gfx_PrintStringXY("Area:   ",90,120);
	print_Double(.5*height*(small_base+large_base),3);
	gfx_PrintStringXY("Perimeter:   ",90,130);
	if (increment == 1) //trapezoid is isosceles
	{
		print_Double(small_base+large_base+height+sqrt(height*height+(large_base - small_base)*(large_base - small_base)),4);
	}else if (increment == 2)
	{
		print_Double(small_base+large_base+2*sqrt(height*height+(.5*(large_base-small_base))*(.5*(large_base-small_base))),4);
	}
}

void geometry_ap_others(void)
{
	gfx_SetColor(0);
	gfx_FillRectangle(52,52,253,150);
	gfx_PrintStringXY("Rules:",80,52);
	gfx_PrintStringXY("- Decimals allowed.",90,62);
	gfx_PrintStringXY("- All sides must be congruent.",90,72);
	gfx_PrintStringXY("Number of Sides:",80,90);
	double num_of_sides = get_Double(200,90);
	gfx_PrintStringXY("Side:",80,100);
	double side = get_Double(120,100);
	gfx_PrintStringXY("Area:   ",90,120);
	print_Double(num_of_sides*side*side/(4*(tan(pi/180*pi/num_of_sides))),5);
	gfx_PrintStringXY("Perimeter:   ",90,130);
	print_Double(num_of_sides*side,5);
}
