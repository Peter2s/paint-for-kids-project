#include "ActionAddTriangle.h"
#include "..\Figures\CTriangle.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"

ActionAddTriangle::ActionAddTriangle(ApplicationManager * pApp):Action(pApp)
{}

//Execute the action
void ActionAddTriangle::Execute()
{
	Point P1,P2,P3;

	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();


	GfxInfo SqrGfxInfo;
	SqrGfxInfo.isFilled = false;	//default is not filled
	//get drawing, filling colors and pen width from the interface
	SqrGfxInfo.DrawClr = pGUI->getCrntDrawColor();
	SqrGfxInfo.FillClr = pGUI->getCrntFillColor();
	SqrGfxInfo.BorderWdth = pGUI->getCrntPenWidth();


	//Step 1 - Read Square data from the user

	
	//Read 1st point and store in point P1
	pGUI->PrintMessage("New Triangle: Click at first point");
	pGUI->GetPointClicked(P1.x, P1.y);
	if (!pGUI->isPointInDrawingArea(P1.x, P1.y)) {
		pGUI->PrintMessage("New Triangle: Action aborted, can't draw outside the drawing area");
		return;
	}
	
	//Read 2nd point and store in point P2
	pGUI->PrintMessage("New Triangle: Click at second point");
	/*while (pGUI->GetButtonState(LEFT_BUTTON, P2.x, P2.y) == BUTTON_UP) {
		pGUI->DrawRectangle(P1, P2, SqrGfxInfo, true);
		SqrGfxInfo.DrawClr = pGUI->getBkGrndColor();
		pGUI->DrawRectangle(P1, P2, SqrGfxInfo, false);
		SqrGfxInfo.DrawClr = pGUI->getCrntDrawColor();
	}*/
	pGUI->GetPointClicked(P2.x, P2.y);
	if (!pGUI->isPointInDrawingArea(P2.x, P2.y)) {
		pGUI->PrintMessage("New Triangle: Action aborted, can't draw outside the drawing area");
		return;
	}
	
	
	pGUI->PrintMessage("New Triangle: Click at third point");
	pGUI->GetPointClicked(P3.x, P3.y);
	if (!pGUI->isPointInDrawingArea(P3.x, P3.y)) {
		pGUI->PrintMessage("New Triangle: Action aborted, can't draw outside the drawing area");
		return;
	}

	
	/*
	while(!pGUI->GetPointClicked(P2.x, P2.y)){
		pGUI->GetMouseCoord(P3.x, P3.y)
		CRectangle *R=new CRectangle(P1, P3, SqrGfxInfo);
	}
	*/
	pGUI->ClearStatusBar();


	//Step 2 - prepare square data
	//User has entered two points P1&P2
	//2.1- Identify the Top left corner of the square
	// Point topLeft ;
	// topLeft.x = P1.x<P2.x? P1.x: P2.x;
	// topLeft.y = P1.y<P2.y? P1.y: P2.y;

	//2.2- Calcuate square side legnth
	//The square side length would be the longer distance between the two points coordinates
	// int SideLength = max(abs(P1.x-P2.x), abs(P1.y-P2.y));

		
	//Step 3 - Create a Square with the parameters read from the user
	CTriangle*R=new CTriangle(P1, P2,P3, SqrGfxInfo);

	//Step 4 - Add the Square to the list of figures
	pManager->AddFigure(R);
}
