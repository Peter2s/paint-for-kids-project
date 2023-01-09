#include "CCircle.h"


CCircle::CCircle(Point P1, int len, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	ID = ++circID;
	center = P1;
	radius = len;
}
CCircle::CCircle() {}; //default constructor

int CCircle::circID = 0;

void CCircle::DrawMe(GUI* pGUI) const
{
	//Call Output::DrawRect to draw a Square on the screen	
	pGUI->DrawCircle(center, radius, FigGfxInfo, Selected);
}

void CCircle::Save(ofstream& OutFile) {

		OutFile << "CCircle\t"
		<< this->ID << "\t" 
		<< this->center.x << "\t" 
		<< this->center.y << "\t"
		<< this->radius << "\t"

		<< this->ColorString(this->FigGfxInfo.DrawClr) << "\t";

	if (this->FigGfxInfo.isFilled)
		OutFile << this->ColorString(this->FigGfxInfo.FillClr) << "\n";
	else
		OutFile << "NO_FILL\n";
}

void CCircle::Load(ifstream& Infile) {

	string s;
	Infile >> ID >> center.x >> center.y >> radius;

	Infile >> s;
	FigGfxInfo.DrawClr = this->ColorObject(s);

	Infile >> s;
	if (s == "NO_FILL")
		FigGfxInfo.isFilled = false;
	else
	{
		FigGfxInfo.FillClr = this->ColorObject(s);
		FigGfxInfo.isFilled = true;
	}
	this->FigGfxInfo.BorderWdth = 3; //pass 3 as default value for borderWidth
	this->SetSelected(false);

}

bool CCircle::Resize(float factor, GUI* pGUI) {
	
	if (
		pGUI->isBorderInDrawingArea(center, radius * factor)
		) {
		radius *= factor;
		
		return true;
	}
	return false;

}

bool CCircle::PointInShape(int x, int y) const {
	return 
		(x - center.x)* (x - center.x) + (y - center.y)* (y - center.y) <= radius* radius 
		
		;
}
void CCircle::Move(GUI* pGUI,Point point) {
	
	if (
		pGUI->isBorderInDrawingArea(point, radius)
		) {
		center.x = point.x;
		center.y = point.y;

	}
	
};