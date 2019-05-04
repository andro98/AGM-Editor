#include "hermit.cpp"
#include "hermit.h"
class spline:hermit
{
public:
	spline();
	void DrawCardinalSpline(HDC hdc, hermit::Vector2 P[], int n, double c, int numpix);
	~spline();

private:

};

spline::spline()
{
}
void DrawCardinalSpline(HDC hdc, hermit::Vector2 P[], int n, double c, int numpix)
{
	double c1 = 1 - c;
	hermit h;
	hermit::Vector2 T0(c1 * (P[2].x - P[0].x), c1 * (P[2].y - P[0].y));
	for (int i = 2; i < n - 1; i++)
	{
		hermit::Vector2 T1(c1 * (P[i + 1].x - P[i - 1].x), c1 * (P[i + 1].y - P[i - 1].y));
		h.DrawHermiteCurve(hdc, P[i - 1], T0, P[i], T1, numpix);
		T0 = T1;
	}
}
spline::~spline()
{
}