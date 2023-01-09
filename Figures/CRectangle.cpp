#include "CRectangle.h"

CRectangle::CRectangle(Point P1, Point P2, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	ID = ++rectID;
	point1 = P1;
	point2 = P2;
}
CRectangle::CRectangle() {}; //default constructor

int CRectangle::rectID = 0;

void CRectangle::DrawMe(GUI* pGUI) const
{
	//Call Output::DrawRect to draw a Rectangle on the screen	
	pGUI->DrawRectangle(point1, point2, FigGfxInfo, Selected);
	

}

void CRectangle::Save(ofstream& OutFile) {

	OutFile << "CRectangle\t"
		<< this->ID << "\t"
		<< this->point1.x << "\t"
		<< this->point1.y << "\t"
		<< this->point2.x << "\t"
		<< this->point2.y << "\t"

		<< this->ColorString(this->FigGfxInfo.DrawClr) << "\t";

	if (this->FigGfxInfo.isFilled)
		OutFile << this->ColorString(this->FigGfxInfo.FillClr) << "\n";
	else
		OutFile << "NO_FILL\n";
}

void CRectangle::Load(ifstream& Infile) {

	string s;
	Infile >> ID >> point1.x >> point1.y >> point2.x >> point2.y;

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

bool CRectangle::Resize(float factor, GUI* pGUI) {
	int centerOfX = (point2.x + point1.x) / 2;
	int centerOfY = (point2.y + point1.y) / 2;
	int HorizontalSpace = point2.x - point1.x;
	int VerticalSpace = point2.y - point1.y;
	HorizontalSpace *= factor;
	VerticalSpace *= factor;
	int resizedBottomRightX = centerOfX + (HorizontalSpace / 2);
	int resizedBottomRightY = centerOfY + (VerticalSpace / 2);
	int resizedTopLeftX = centerOfX - (HorizontalSpace / 2);
	int resizedTopLeftY = centerOfY - (VerticalSpace / 2);



	if (resizedTopLeftX > 0 && resizedTopLeftX < UI.width && resizedTopLeftY > UI.ToolBarHeight && resizedTopLeftY < UI.height - UI.StatusBarHeight
		&& resizedBottomRightX > 0 && resizedBottomRightX < UI.width && resizedBottomRightY > UI.ToolBarHeight && resizedBottomRightY < UI.height - UI.StatusBarHeight) {

		point1.x = resizedTopLeftX;
		point1.y = resizedTopLeftY;
		point2.x = resizedBottomRightX;
		point2.y = resizedBottomRightY;
		return true;
	}
	return false;

}

bool CRectangle::PointInShape(int x, int y) const {
	
	return 
		( (x >= point1.x && x <= point2.x) && (y >= point1.y && y <= point2.y) )
		|| 
		( (x >= point2.x && x <= point1.x) && (y >= point1.y && y <= point2.y) )
		||
		((x >= point2.x && x <= point1.x) && (y >= point2.y && y <= point1.y))
		||
		((x >= point1.x && x <= point2.x) && (y >= point2.y && y <= point1.y))
		;
}
void CRectangle::Move(GUI* pGUI, Point point) 
{
	int centerOfX = point.x;
	int centerOfY = point.y;
	int HorizontalSpace = point2.x - point1.x;
	int VerticalSpace = point2.y - point1.y;
	int resizedBottomRightX = centerOfX + (HorizontalSpace / 2);
	int resizedBottomRightY = centerOfY + (VerticalSpace / 2);
	int resizedTopLeftX = centerOfX - (HorizontalSpace / 2);
	int resizedTopLeftY = centerOfY - (VerticalSpace / 2);



	if (resizedTopLeftX > 0 && resizedTopLeftX < UI.width && resizedTopLeftY > UI.ToolBarHeight && resizedTopLeftY < UI.height - UI.StatusBarHeight
		&& resizedBottomRightX > 0 && resizedBottomRightX < UI.width && resizedBottomRightY > UI.ToolBarHeight && resizedBottomRightY < UI.height - UI.StatusBarHeight) {

		point1.x = resizedTopLeftX;
		point1.y = resizedTopLeftY;
		point2.x = resizedBottomRightX;
		point2.y = resizedBottomRightY;
	}

};