#pragma once
class Line
{
public:
	virtual void draw () const = 0;
};

class LineDDA :public Line
{
	virtual void draw () const{

	}
};

class LineMidPoint : public Line
{
	virtual void draw () const{

	}
};

class LineParam : public Line
{
	virtual void draw () const{

	}
};

