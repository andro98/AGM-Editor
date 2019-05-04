#include "Line.h"
#include<iostream>
using namespace std;

Line::Line (){

}
void Line::drawLineDDA (HDC hdc , int x1 , int y1 , int x2 , int y2 , COLORREF c){
	int DX = x2 - x1;
	int DY = y2 - y1;

	if ( abs (DX) >= abs (DY) )
	{
		if ( x1 > x2 )
		{
			swap (x1 , x2);
			swap (y1 , y2);
		}
		double m = (double)DY / DX;
		int x = x1;
		double y = y1;
		SetPixel (hdc , x , y , c);

		while ( x < x2 )
		{
			x++;
			y += m;
			SetPixel (hdc , x , y , c);
		}
	}
	else
	{
		if ( y1 > y2 )
		{
			swap (x1 , x2);
			swap (y1 , y2);
		}
		double m = (double)DX / DY;
		double x = x1;
		int y = y1;
		SetPixel (hdc , x , y , c);

		while ( y < y2 )
		{
			x += ( 1 / m );
			y++;
			SetPixel (hdc , x , y , c);
		}
	}

}
void Line::drawLineMidPoint (HDC hdc , int x1 , int y1 , int x2 , int y2 , COLORREF c){
	for ( double t = 0; t <= 1; t += 0.001 )
	{
		int X = Round (x1 + t*( x2 - x1 ));
		int Y = Round (y1 + t*( y2 - y1 ));
		SetPixel (hdc , X , Y , c);
	}
}
void Line::drawLineParam (HDC hdc , int x1 , int y1 , int x2 , int y2 , COLORREF c){

	int DX = abs (x2 - x1);
	int DY = abs (y2 - y1);

	double DT = 1.0 / ( max (DY , DX) + 1 );

	for ( double t = 0; t <= 1; t += DT )
	{
		int X = Round (x1 + t*( DX ));
		int Y = Round (y1 + t*( DY ));
		SetPixel (hdc , X , Y , c);
	}
}

Line::~Line (){
}