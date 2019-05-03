#pragma once
#include<vector>
#include"Point.h" 
#include <windows.h>
using namespace std;

Point VIntersect (Point& v1 , Point& v2 , int xedge)
{
	Point res;
	res.x = xedge;
	res.y = v1.y + ( xedge - v1.x )*( v2.y - v1.y ) / ( v2.x - v1.x );
	return res;
}
Point HIntersect (Point& v1 , Point& v2 , int yedge)
{
	Point res;
	res.y = yedge;
	res.x = v1.x + ( yedge - v1.y )*( v2.x - v1.x ) / ( v2.y - v1.y );
	return res;
}

bool InLeft (Point& v , int edge)
{
	return v.x >= edge;
}
bool InRight (Point& v , int edge)
{
	return v.x <= edge;
}
bool InTop (Point& v , int edge)
{
	return v.y >= edge;
}
bool InBottom (Point& v , int edge)
{
	return v.y <= edge;
}


class Clipping{

private:
	typedef bool (*IsInFunc)( Point& v , int edge );
	typedef Point (*IntersectFunc)( Point& v1 , Point& v2 , int edge );
	

	//IsInFunc Inleft = InLeft;
	//IsInFunc Inright = InRight;
	//IsInFunc Intop = InTop;
	//IsInFunc Inbottom = InBottom;

	//IntersectFunc vIntersect = VIntersect;
	//IntersectFunc hIntersect = HIntersect;

	

	vector<Point> ClipWithEdge (vector<Point> p , int edge , IsInFunc In , IntersectFunc Intersect)
	{
		vector<Point> OutList;
		Point v1 = p[p.size () - 1];
		bool v1_in = In (v1 , edge);
		for ( int i = 0; i<(int)p.size (); i++ )
		{
			Point v2 = p[i];
			bool v2_in = In (v2 , edge);
			if ( !v1_in && v2_in )
			{
				OutList.push_back (Intersect (v1 , v2 , edge));
				OutList.push_back (v2);
			}
			else if ( v1_in && v2_in ) OutList.push_back (v2);
			else if ( v1_in ) OutList.push_back (Intersect (v1 , v2 , edge));
			v1 = v2;
			v1_in = v2_in;
		}
		return OutList;
	}

	int Round (double x)
	{
		return (int)( x + 0.5 );
	}

	int xleft = 300;
	int ytop = 100;
	int xright = 1000;
	int ybottom = 600;	

public:

	Clipping (){
	}

	void DrawRectangle (HDC myHdc){
		HPEN hPen = CreatePen (PS_DASH , 1 , RGB (0 ,0, 0));
		HPEN hOldPen = (HPEN)SelectObject (myHdc , hPen);

		MoveToEx (myHdc , xleft , ytop , NULL);
		LineTo (myHdc , xright , ytop);

		MoveToEx (myHdc , xright , ytop , NULL);
		LineTo (myHdc , xright , ybottom);

		MoveToEx (myHdc , xright , ybottom , NULL);
		LineTo (myHdc , xleft , ybottom);

		
		MoveToEx (myHdc , xleft , ybottom , NULL);
		LineTo (myHdc , xleft , ytop);

		SelectObject (myHdc , hOldPen);
		DeleteObject (hPen);
	}

	void PolygonClip (HDC hdc , vector<Point> p)
	{
		vector<Point> vlist;
		for ( int i = 0; i < p.size(); i++ ){
			vlist.push_back (Point (p[i].x , p[i].y));
		}


		vlist = ClipWithEdge (vlist , xleft , InLeft , VIntersect);
		vlist = ClipWithEdge (vlist , ytop , InTop , HIntersect);
		vlist = ClipWithEdge (vlist , xright , InRight , VIntersect);
		vlist = ClipWithEdge (vlist , ybottom , InBottom , HIntersect);


		HPEN hPen = CreatePen (PS_STYLE_MASK , 1 , RGB (255 , 0 , 0));
		HPEN hOldPen = (HPEN)SelectObject (hdc , hPen);

		Point v1 = vlist[vlist.size () - 1];
		for ( int i = 0; i<(int)vlist.size (); i++ )
		{
			Point v2 = vlist[i];
			MoveToEx (hdc , Round (v1.x) , Round (v1.y) , NULL);
			LineTo (hdc , Round (v2.x) , Round (v2.y));
			v1 = v2;
		}

		SelectObject (hdc , hOldPen);
		DeleteObject (hPen);
	}


	void DrawInitialPolygon (HDC hdc, vector<Point> myPoints){
		HPEN hPen = CreatePen (PS_DOT , 1 , RGB (0 , 0 , 255));
		HPEN hOldPen = (HPEN)SelectObject (hdc , hPen);
		Point v1 = myPoints[myPoints.size () - 1];
		for ( int i = 0; i<(int)myPoints.size (); i++ )
		{
			Point v2 = myPoints[i];
			MoveToEx (hdc , Round (v1.x) , Round (v1.y) , NULL);
			LineTo (hdc , Round (v2.x) , Round (v2.y));
			v1 = v2;
		}
		SelectObject (hdc , hOldPen);
		DeleteObject (hPen);
	}
};