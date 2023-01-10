#ifndef CLINE_H
#define CLINE_H

#include "CFigure.h"

class CLine : public CFigure
{
private:
	Point point1;	
	Point point2;
public:
	static int lineID;
	CLine();
	CLine(Point , Point, GfxInfo FigureGfxInfo );
	virtual void DrawMe(GUI*) const;
	void Save(ofstream&);
	void Load(ifstream&);
	virtual bool PointInShape(int, int) const;
	bool Resize(float factor, GUI* pGUI);
	void Move(GUI*, Point);
};

#endif