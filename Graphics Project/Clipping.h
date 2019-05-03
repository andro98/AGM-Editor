#pragma once
#include<vector>
#include"Point.h"
using namespace std;


class Clipping{

private:
	vector<Point> myPoints;

	void DrawRectangle ();

public:

	Clipping (vector<Point> myPoints){
		DrawRectangle ();
		this->myPoints = myPoints;
	}


};