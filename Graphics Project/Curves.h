#pragma once
class Curves
{
public:
	virtual void drawCurve () const = 0;
};


class CurvesBezier : public Curves
{
public:
	virtual void drawCurve () const {			
	
	}

};


class CurvesHermite : public Curves
{
public:
	virtual void drawCurve () const {

	}

};

class CurvesSplines : public Curves
{
public:
	virtual void drawCurve () const {

	}

};