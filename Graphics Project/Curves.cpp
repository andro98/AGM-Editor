#include "Curves.h"
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
void Curves::drawCurvesHermite(HDC hdc, Point& P0, Point& T0, Point& P1, Point& T1, int numpoints)
{
	Vector4 xcoeff = GetHermiteCoeff(P0.x, T0.x, P1.x, T1.x);
	Vector4 ycoeff = GetHermiteCoeff(P0.y, T0.y, P1.y, T1.y);
	if (numpoints < 2)return;
	double dt = 1.0 / (numpoints - 1);
	for (double t = 0; t <= 1; t += dt)
	{
		Vector4 vt;
		vt[3] = 1;
		for (int i = 2; i >= 0; i--)vt[i] = vt[i] * t;
		int x = round(DotProduct(xcoeff, vt));
		int y = round(DotProduct(ycoeff, vt));
		if (t == 0){ MoveToEx(hdc, x, y, NULL); }
		else { LineTo(hdc, x, y); }
	}
}
void Curves::drawCurvesSplines(HDC hdc, Point P[], int n, double c, int numpix)
{
	double c1 = 1 - c;
	Point T0(c1 * (P[2].x - P[0].x), c1 * (P[2].y - P[0].y));
	for (int i = 2; i < n - 1; i++)
	{
		Point T1(c1 * (P[i + 1].x - P[i - 1].x), c1 * (P[i + 1].y - P[i - 1].y));
		Curves::drawCurvesHermite(hdc, P[i - 1], T0, P[i], T1, numpix);
		T0 = T1;
	}
}
Vector4 Curves::GetHermiteCoeff(double x0, double s0, double x1, double s1)
{
	static double H[16] = { 2,1,-2,1,-3,-2,3,-1,0,1,0,0,1,0,0,0 };
	static Matrix4 basis(H);
	Vector4 v(x0, s0, x1, s1);
	return basis * v;
}
void Curves::drawCurveBezier(HDC hdc, Point& P0, Point& P1, Point& P2, Point& P3, int numpoints)
{
	Point T0(3 * (P1.x - P0.x), 3 * (P1.y - P0.y));
	Point T1(3 * (P3.x - P2.x), 3 * (P3.y - P2.y));
	Curves::drawCurvesHermite(hdc, P0, T0, P3, T1, numpoints);
}

