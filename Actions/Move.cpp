#include "Move.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"

Move::Move(ApplicationManager* pApp) :Action(pApp)
{

}

void Move::Execute()
{
	GUI* pGUI = pManager->GetGUI();
	CFigure* figure = pManager->getSelected();
	
	if (figure == NULL) {
		pGUI->PrintMessage("Select the shape you want to Move");
		Point point;
		pGUI->GetPointClicked(point.x, point.y);
		figure = pManager->GetFigure(point.x, point.y);
	}
	
	if (figure != NULL) {
		Point point;
		/**/
		while (pGUI->pWind->GetButtonState(LEFT_BUTTON, point.x, point.y) == BUTTON_UP) {
			//sleep(.1);
			figure->Move(pGUI,point);
			pGUI->ClearDrawArea();
			pManager->UpdateInterface();
		}
		
		pGUI->GetPointClicked(point.x, point.y);
		/**/figure->Move(pGUI, point);
		pGUI->ClearDrawArea();
		pManager->UpdateInterface();
		
		
		
	}
	
}