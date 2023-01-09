#ifndef CTRIANGLE_H
#define CTRIANGLE_H

#include "CFigure.h"

class CTriangle : public CFigure
{
private:
	Point point1;	
	Point point2;
	Point point3;
public:
	static int triaID;
	CTriangle();
	CTriangle(Point , Point, Point, GfxInfo FigureGfxInfo );
	virtual void DrawMe(GUI*) const;
	void Save(ofstream&);
	void Load(ifstream&);
	virtual bool PointInShape(int, int) const;
	bool Resize(float factor, GUI* pGUI);
};

#endif