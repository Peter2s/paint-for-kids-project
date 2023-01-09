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
	int length = max(abs(point1.x - point2.x), abs(point1.y - point2.y));
	int centerOfX = point1.x + (length / 2);
	int centerOfY = (point1.y + (length / 2));
	
	
	int resizedLength = length * factor;
	int resizedTopLeftX = centerOfX - (resizedLength / 2);
	int resizedTopLeftY = centerOfY - (resizedLength / 2);
	int resizedBottomRightX = resizedLength + resizedTopLeftX;
	int resizedBottomRightY = resizedLength + resizedTopLeftY;
	//x > 0 && x < UI.width
		//&& y > UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight;


	if (resizedTopLeftX > 0 && resizedTopLeftX < UI.width
		&& resizedTopLeftY > UI.ToolBarHeight && resizedTopLeftY < UI.height - UI.StatusBarHeight
		&& resizedBottomRightX > 0 && resizedBottomRightX < UI.width
		&& resizedBottomRightY > UI.ToolBarHeight && resizedBottomRightY < UI.height - UI.StatusBarHeight) {
		length = resizedLength;
		point1.x = resizedTopLeftX;
		point1.y = resizedTopLeftY;

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