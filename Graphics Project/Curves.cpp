#include "Curves.h"

Curves::Curves(){

}
void Curves::drawCurveBezier(HDC hdc, Point& p1, Point& p2, Point& p3, Point& p4, COLORREF color){

	double x, y;
	for (double t = 0; t <= 1; t += 0.0001){

		x = ((1 - t)*(1 - t)*(1 - t)*p1.x) + (3 * (1 - t)*(1 - t)*t*p2.x) + (3 * (1 - t)*t*t*p3.x) + (t*t*t*p4.x);
		y = ((1 - t)*(1 - t)*(1 - t)*p1.y) + (3 * (1 - t)*(1 - t)*t*p2.y) + (3 * (1 - t)*t*t*p3.y) + (t*t*t*p4.y);
		SetPixel(hdc, round(x), round(y), color);
	}
}

void Curves::drawCurvesHermite(HDC hdc, Point& p1, Point& p2, Point& p3, COLORREF color){
	for (double t = 0; t < 1; t += 0.001)
	{
		double x = p1.x + (t*double(4 * p2.x - 3 * p1.x - p3.x)) + (t*t*double(2 * p3.x + 2 * p1.x - 4 * p2.x));
		double y = p1.y + (t*double(4 * p2.y - 3 * p1.y - p3.y)) + (t*t*double(2 * p3.y + 2 * p1.y - 4 * p2.y));
		//cout<<x<<" "<<y<<endl;
		SetPixel(hdc, x, y, color);
	}

}

void Curves::drawCurvesSplines(HDC hdc, Point& P0, Point& P1, Point& P2, Point& P3){

}

Curves::~Curves(){

}


