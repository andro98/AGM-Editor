#pragma once
#include <windows.h>
#include <cmath>
using namespace std;

class AGMEllipse
{
private:
	void Draw4point (HDC hdc , int x , int y , int xc , int yc , COLORREF c);
	int Round (double x);

public:
	
	AGMEllipse ();

	void drawEllipseDirect (HDC hdc , int a , int b , int xc , int yc , COLORREF color) ;

	void drawEllipsePolar (HDC hdc , int a , int b , int xc , int yc , COLORREF color) ;
		
	void drawEllipseMidPoint (HDC hdc , int a , int b , int xc , int yc , COLORREF color) ;

	~AGMEllipse ();
};
