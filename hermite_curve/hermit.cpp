#include "hermit.h"
#include <windows.h>
#include <cmath>
hermit::hermit()
{}
void hermit::Drawpoint(HDC hdc, int x, int y, int xc, int yc, COLORREF c)
{
	SetPixel(hdc, x + xc, y + yc, c);
	SetPixel(hdc, -x + xc, y + yc, c);
	SetPixel(hdc, x + xc, -y + yc, c);
	SetPixel(hdc, -x + xc, -y + yc, c);
}
Vector4 operator*(Matrix4 M, Vector4& b) // right multiplication of M by b
{
	Vector4 res;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			res[i] += M[i][j] * b[j];
	return res;
}
double DotProduct(Vector4 & a, Vector4 & b) //multiplying a raw vector by a column vector
{
	return a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3];
}
Vector4 hermit::GetHermiteCoeff(double x0, double s0, double x1, double s1)
{
	static double H[16] = { 2,1,-2,1,-3,-2,3,-1,0,1,0,0,1,0,0,0 };
	static Matrix4 basis(H);
	Vector4 v(x0, s0, x1, s1);
	return basis * v;
}

void hermit::DrawHermiteCurve(HDC hdc, Vector2& P0, Vector2& T0, Vector2& P1, Vector2& T1, int numpoints, COLORREF color)
{
	Vector4 xcoeff = GetHermiteCoeff(P0.x, T0.x, P1.x, T1.x);
	Vector4 ycoeff = GetHermiteCoeff(P0.y, T0.y, P1.y, T1.y);
	if (numpoints < 2)return;
	double dt = 1.0 / (numpoints - 1);
	for (double t = 0; t <= 1; t += dt)
	{
		Vector4 vt;
		vt[4] = 1;
		for (int i = 2; i >= 0; i--)vt[i] = vt[i] * t;
		int x = round(DotProduct(xcoeff, vt));
		int y = round(DotProduct(xcoeff, vt));
		SetPixel(hdc, x, y, color);
	}
	
};

hermit::~hermit()
{
	
}