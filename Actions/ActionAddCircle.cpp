#include "ActionAddCircle.h"
#include "..\Figures\CCircle.h"
#include "..\ApplicationManager.h"
#include "..\GUI\GUI.h"

ActionAddCircle::ActionAddCircle(ApplicationManager* pApp) :Action(pApp)
{}

//Execute the action
void ActionAddCircle::Execute()
{
	Point P1, P2;

	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();


	GfxInfo SqrGfxInfo;
	SqrGfxInfo.isFilled = false;	//default is not filled
	//get drawing, filling colors and pen width from the interface
	SqrGfxInfo.DrawClr = pGUI->getCrntDrawColor();
	SqrGfxInfo.FillClr = pGUI->getCrntFillColor();
	SqrGfxInfo.BorderWdth = pGUI->getCrntPenWidth();


	//Step 1 - Read Circle data from the user

	pGUI->PrintMessage("New Circle: Click at first point");
	//Read 1st point and store in point P1
	/*do {
		pGUI->GetPointClicked(P1.x, P1.y);
	} while (! pGUI->isPointInDrawingArea(P1.x, P1.y));*/
	

	pGUI->GetPointClicked(P1.x, P1.y);
	if (!pGUI->isPointInDrawingArea(P1.x, P1.y)) {
		pGUI->PrintMessage("New Circle: Action aborted, can't draw outside the drawing area");
		return;
	}

	pGUI->PrintMessage("New Circle: Click at second point");
	//Read 2nd point and store in point P2
	pGUI->GetPointClicked(P2.x, P2.y);
	
	// calc Radius
	int radius = max(abs(P1.x - P2.x), abs(P1.y - P2.y));
	if (!pGUI->isPointInDrawingArea(P2.x, P2.y) || !pGUI->isBorderInDrawingArea(P1, radius)) {
		pGUI->PrintMessage("New Circle: Action aborted, can't draw outside the drawing area");
		return;
	}

	pGUI->ClearStatusBar();



	//Step 3 - Create a Circle with the parameters read from the user
	CCircle* R = new CCircle(P1, radius, SqrGfxInfo);

	//Step 4 - Add the Circle to the list of figures
	pManager->AddFigure(R);

}
