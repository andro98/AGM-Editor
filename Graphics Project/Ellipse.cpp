#include"Ellipse.h"


AGMEllipse::AGMEllipse (){

}

void AGMEllipse::Draw4point (HDC hdc , int x , int y , int xc , int yc , COLORREF c,vector<Point>&allpoint)
{
	

	SetPixel(hdc, x + xc, y + yc, c); allpoint.push_back( Point(x + xc, y + yc));
	SetPixel (hdc , -x + xc , y + yc , c); allpoint.push_back( Point(-x + xc, y + yc));
	SetPixel (hdc , x + xc , -y + yc , c); allpoint.push_back( Point(x + xc, -y + yc));
	SetPixel (hdc , -x + xc , -y + yc , c); allpoint.push_back( Point(-x + xc, -y + yc));
}

int AGMEllipse::Round (double x)
{
	return (int)x + 0.5;
}

void AGMEllipse::drawEllipseDirect (HDC hdc , int a , int b , int xc , int yc , COLORREF color, vector<Point>&allpoint){
	double x = 0;
	double y = b;
	int b2 = b*b;
	int a2 = a*a;
	Draw4point(hdc, x, y, xc, yc, color,allpoint);
	while ((x*b2) <= (y*a2))
	{
		x = x + 1;
		double temp = sqrt((1 - ((x*x) / a2)));
		y = b*temp;
		Draw4point(hdc, x, Round(y), xc, yc, color,allpoint);
	}
	x = a;
	y = 0;
	Draw4point(hdc, x, y, xc, yc, color,allpoint);
	while ((y*a2) < (x*b2))
	{
		y = y + 1;
		double t = sqrt((1 - ((y*y) / b2)));
		x = a*t;
		Draw4point(hdc, Round(x), y, xc, yc, color,allpoint);
	}
}

void AGMEllipse::drawEllipsePolar (HDC hdc , int a , int b , int xc , int yc , COLORREF color , vector<Point>&allpoint){
	for ( double theta = 0; theta <= 6.28; theta += 0.01 )
	{
		int XC = Round (xc + a*cos (theta));
		int YC = Round (yc + b*sin (theta));
		SetPixel (hdc , XC , YC , color);
		
		allpoint.push_back( Point(XC, YC));
	}
}


void AGMEllipse::drawEllipseMidPoint (HDC hdc , int a , int b , int xc , int yc , COLORREF color, vector<Point>&allpoint) {

	double d2;
	int x = 0;
	int y = b;
	int a2 = (a*a);
	int b2 = (b*b);
	double d1 = b2 - (a2*b) + (0.25*b);
	Draw4point(hdc, x, y, xc, yc, color,allpoint);
	//To draw region 1 in the ellipse
	while (((y - 0.5)*a2)>((x + 1)*b2))
	{   //inside
		if (d1<0)
		{
			d1 += ((2 * x) + 3)*b2;

		}
		else {
			d1 += (((-2 * y) + 2)*a2) + (((2 * x) + 3)*b2);
			y--;
		}
		x++;
		Draw4point(hdc, x, y, xc, yc, color,allpoint);
	}
	//region 2
	d2 = (pow((x + 0.5), 2)*b2) + (pow((y - 1), 2)*a2) - (a2*b2);
	while (y>0)
	{
		if (d2<0)
		{
			d2 += (((2 * x) + 2)*b2) + (a2*((-2 * y) + 3));

			x++;
		}
		else {
			d2 += ((-2 * y) + 3)*a2;
		}
		y--;
		Draw4point(hdc, x, y, xc, yc, color,allpoint);
	}

}


AGMEllipse::~AGMEllipse (){

}