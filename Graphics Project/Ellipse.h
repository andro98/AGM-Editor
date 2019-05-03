#pragma once
class Ellipse
{
public:
	virtual void drawEllipse () const = 0;
};


class EllipseDirect : public Ellipse
{
	virtual void drawEllipse () const{

	}
};

class EllipsePolar : public Ellipse
{
	virtual void drawEllipse () const{

	}
};

class EllipseMidPoint : public Ellipse
{
	virtual void drawEllipse () const{

	}
};