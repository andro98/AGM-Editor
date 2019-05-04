#pragma once
#include "Windows.h"
#include <vector>
#include <cmath>
#include"Point.h"


class Vector4
{
	double v[4];
public:
	Vector4(double a = 0, double b = 0, double c = 0, double d = 0)
	{
		v[0] = a; v[1] = b; v[2] = c; v[3] = d;
	}
	Vector4(double a[])
	{
		memcpy(v, a, 4 * sizeof(double));
	}
	double& operator[](int i)
	{
		return v[i];
	}
};
class Matrix4
{
	Vector4 M[4];
public:
	Matrix4(double A[])
	{
		memcpy(M, A, 16 * sizeof(double));
	}
	Vector4& operator[](int i)
	{
		return M[i];
	}
};

class Curves
{
public:
	Curves(){

	}
	Vector4 GetHermiteCoeff(double x0, double s0, double x1, double s1);
	void drawCurveBezier(HDC hdc, Point& p1, Point& p2, Point& p3, Point& p4, COLORREF color);
	void drawCurvesHermite(HDC hdc, Point& p1, Point& p2, Point& p3, COLORREF color);
	void drawCurvesSplines(HDC hdc, Point& P0, Point& P1, Point& P2, Point& P3);
	~Curves(){

	}
};



