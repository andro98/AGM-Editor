#pragma once
#include <windows.h>
#include <cmath>
#include<vector>
#include "Point.h"

using namespace std;

class AGMEllipse
{
private:
	void Draw4point (HDC hdc , int x , int y , int xc , int yc , COLORREF c, vector <Point>&allpoint);
	int Round (double x);

public:
	
	AGMEllipse ();

	void drawEllipseDirect (HDC hdc , int a , int b , int xc , int yc , COLORREF color,vector<Point>&allpoint) ;

	void drawEllipsePolar (HDC hdc , int a , int b , int xc , int yc , COLORREF color, vector<Point>&allpoint) ;
		
	void drawEllipseMidPoint (HDC hdc , int a , int b , int xc , int yc , COLORREF color, vector<Point>&allpoint) ;

	~AGMEllipse ();
};
