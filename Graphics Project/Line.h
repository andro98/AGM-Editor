#pragma once
#include <windows.h>

class Line
{
public:
	Line ();
	void drawLineDDA (HDC hdc , int x1 , int y1 , int x2 , int y2 , COLORREF c);
	void drawLineMidPoint (HDC hdc , int x1 , int y1 , int x2 , int y2 , COLORREF c);
	void drawLineParam (HDC hdc , int x1 , int y1 , int x2 , int y2 , COLORREF c);

	int Round (double x)
	{
		return (int)( x + 0.5 );
	}
	~Line ();
};


								 