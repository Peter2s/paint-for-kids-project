#ifndef CRECTANGLE_H
#define CRECTANGLE_H

#include "CFigure.h"

class CRectangle : public CFigure
{
private:
	Point point1;	
	Point point2;
public:
	static int rectID;
	CRectangle();
	CRectangle(Point , Point, GfxInfo FigureGfxInfo );
	virtual void DrawMe(GUI*) const;
	void Save(ofstream&);
	void Load(ifstream&);
	virtual bool PointInShape(int, int) const;
	bool Resize(float factor, GUI* pGUI);
	void Move(GUI*, Point);
};

#endif