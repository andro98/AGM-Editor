#pragma once
#include"Point.h"
#include<Windows.h>


class Curves
{
public:
	Curves();
	void drawCurveBezier(HDC hdc, Point& P0, Point& P1, Point& P2, Point& P3, COLORREF color);
	void drawCurvesHermite(HDC hdc, Point& P1, Point& T2, Point& P3, COLORREF color);
	void drawCurvesSplines(HDC hdc, Point& P0, Point& P1, Point& P2, Point& P3);
	~Curves();
};



