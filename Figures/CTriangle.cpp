#include "CTriangle.h"

CTriangle::CTriangle(Point P1, Point P2, Point P3, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	ID = ++triaID;
	point1 = P1;
	point2 = P2;
	point3 = P3;
}
CTriangle::CTriangle() {}; //default constructor

int CTriangle::triaID = 0;

void CTriangle::DrawMe(GUI* pGUI) const
{
	//Call Output::DrawRect to draw a Rectangle on the screen	
	pGUI->DrawTriangle(point1, point2, point3, FigGfxInfo, Selected);
	

}

void CTriangle::Save(ofstream& OutFile) {

	OutFile << "CTriangle\t"
		<< this->ID << "\t"
		<< this->point1.x << "\t"
		<< this->point1.y << "\t"
		<< this->point2.x << "\t"
		<< this->point2.y << "\t"
		<< this->point3.x << "\t"
		<< this->point3.y << "\t"

		<< this->ColorString(this->FigGfxInfo.DrawClr) << "\t";

	if (this->FigGfxInfo.isFilled)
		OutFile << this->ColorString(this->FigGfxInfo.FillClr) << "\n";
	else
		OutFile << "NO_FILL\n";
}

void CTriangle::Load(ifstream& Infile) {

	string s;
	Infile >> ID >> point1.x >> point1.y >> point2.x >> point2.y >> point3.x >> point3.y;

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

bool CTriangle::Resize(float factor, GUI* pGUI) {
	Point center,p1,p2,p3;
	center.x = (point1.x + point2.x + point3.x) / 3;
	center.y = (point1.y + point2.y + point3.y) / 3;
	p1.x = center.x + (point1.x - center.x) * factor;
	p1.y = center.y + (point1.y - center.y) * factor;
	p2.x = center.x + (point2.x - center.x) * factor;
	p2.y = center.y + (point2.y - center.y) * factor;
	p3.x = center.x + (point3.x - center.x) * factor;
	p3.y = center.y + (point3.y - center.y) * factor;
	if (
		min(p1.x,p2.x,p3.x)> 0 
		&& max(p1.x, p2.x, p3.x) < UI.width
		&& min(p1.y, p2.y, p3.y) > UI.ToolBarHeight 
		&& max(p1.y, p2.y, p3.y) < UI.height - UI.StatusBarHeight) 
	{
		point1.x = p1.x;
		point1.y = p1.y;
		point2.x = p2.x;
		point2.y = p2.y;
		point3.x = p3.x;
		point3.y = p3.y;

		return true;
	}
	return false;
}

float area(int x1, int y1, int x2, int y2, int x3, int y3)
{
	return abs((x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2.0);
};
bool CTriangle::PointInShape(int x, int y) const {
	//split the triangle to 3 triangles with the point in center
	// if the 3 areas are equal to the area of the triangle then the point is in the triangle

	
	float A = area(point1.x, point1.y, point2.x, point2.y, point3.x, point3.y);

	/* Calculate area of triangle P23 */
	float A1 = area(x, y, point2.x, point2.y, point3.x, point3.y);

	/* Calculate area of triangle P13 */
	float A2 = area(point1.x, point1.y, x, y, point3.x, point3.y);

	/* Calculate area of triangle P12 */
	float A3 = area(point1.x, point1.y, point2.x, point2.y, x, y);

	/* Check if sum of A1, A2 and A3 is same as A */
	return (A == A1 + A2 + A3);

	
}
void CTriangle::Move(GUI* pGUI, Point point) 
{
	Point center, p1, p2, p3;
	int factor = 1;
	center.x = (point1.x + point2.x + point3.x) / 3;
	center.y = (point1.y + point2.y + point3.y) / 3;
	p1.x = point.x + (point1.x - center.x) * factor;
	p1.y = point.y + (point1.y - center.y) * factor;
	p2.x = point.x + (point2.x - center.x) * factor;
	p2.y = point.y + (point2.y - center.y) * factor;
	p3.x = point.x + (point3.x - center.x) * factor;
	p3.y = point.y + (point3.y - center.y) * factor;
	if (
		min(p1.x, p2.x, p3.x) > 0
		&& max(p1.x, p2.x, p3.x) < UI.width
		&& min(p1.y, p2.y, p3.y) > UI.ToolBarHeight
		&& max(p1.y, p2.y, p3.y) < UI.height - UI.StatusBarHeight)
	{
		point1.x = p1.x;
		point1.y = p1.y;
		point2.x = p2.x;
		point2.y = p2.y;
		point3.x = p3.x;
		point3.y = p3.y;

	}
};