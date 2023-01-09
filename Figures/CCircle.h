#ifndef CCIRCLE_H
#define CCIRCLE_H

#include "CFigure.h"

class CCircle : public CFigure
{
private:
	Point center;
	int radius;
public:

	static int circID;
	CCircle();
	CCircle(Point, int, GfxInfo);
	virtual void DrawMe(GUI*) const;
	void Save(ofstream&);
	void Load(ifstream&);
	virtual bool PointInShape(int,int) const;
	bool Resize(float factor, GUI* pGUI);
	void Move(GUI*, Point);
};

#endif