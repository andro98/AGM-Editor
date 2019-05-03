#include"Ellipse.h"


AGMEllipse::AGMEllipse (){

}

void AGMEllipse::Draw4point (HDC hdc , int x , int y , int xc , int yc , COLORREF c)
{
	SetPixel (hdc , x + xc , y + yc , c);
	SetPixel (hdc , -x + xc , y + yc , c);
	SetPixel (hdc , x + xc , -y + yc , c);
	SetPixel (hdc , -x + xc , -y + yc , c);
}

int AGMEllipse::Round (double x)
{
	return (int)x + 0.5;
}

void AGMEllipse::drawEllipseDirect (HDC hdc , int a , int b , int xc , int yc , COLORREF color){
	int x = 0;
	int y = b;
	int b2 = b*b;
	int a2 = a*a;
	while ( ( x*b2 ) < ( y*a2 ) )
	{
		x = x + 1;
		y = b*sqrt (( 1 - ( x*x ) / a2 ));
		Draw4point (hdc , x , y , xc , yc , color);
	}
	x = a;
	y = 0;
	while ( ( y*a2 ) < ( x*b2 ) )
	{
		y = y + 1;
		x = a*sqrt (( 1 - ( y*y ) / b2 ));
		Draw4point (hdc , x , y , xc , yc , color);
	}
}

void AGMEllipse::drawEllipsePolar (HDC hdc , int a , int b , int xc , int yc , COLORREF color){
	for ( double theta = 0; theta <= 6.28; theta += 0.01 )
	{
		int XC = Round (xc + a*cos (theta));
		int YC = Round (yc + b*sin (theta));
		SetPixel (hdc , XC , YC , color);
	}
}


void AGMEllipse::drawEllipseMidPoint (HDC hdc , int a , int b , int xc , int yc , COLORREF color) {
	double d2;
	int x = 0;
	int y = b;
	int a2 = ( a*a );
	int b2 = ( b*b );
	double d1 = b2 - ( a2*b ) + ( 0.25*b );
	Draw4point (hdc , x , y , xc , yc , color);
	//To draw region 1 in the AGMEllipse
	while ( ( ( y - 0.5 )*a2 ) <= ( ( x + 1 )*b2 ) )
	{   //inside
		if ( d1 < 0 )
		{
			d1 += pow (( 2 * x ) , 2)*b2;

		}
		else {
			d1 += ( ( ( -2 * y ) + 2 )*a2 ) + ( ( ( 2 * x ) + 3 )*b2 );
			y--;
		}
		x++;
		Draw4point (hdc , x , y , xc , yc , color);
	}
	//region 2
	d2 = ( pow (x + 0.5 , 2)*b2 ) + ( pow (y - 1 , 2)*a2 ) - ( a2*b2 );
	while ( y > 0 )
	{
		if ( d2 < 0 )
		{
			d2 += ( ( 2 * x ) + 2 ) + ( a2*( ( -2 * y ) + 3 ) );

			x++;
		}
		else {
			d2 += ( ( -2 * y ) + 3 )*a2;
		}
		y--;
		Draw4point (hdc , x , y , xc , yc , color);
	}
}


AGMEllipse::~AGMEllipse (){

}