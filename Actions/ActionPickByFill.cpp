#include "ActionPickByFill.h"
#include "..\ApplicationManager.h"
#include "..\Figures\CEllipse.h"
#include "..\Figures\CHexagon.h"
#include "..\Figures\CSquare.h"
#include "..\GUI\GUI.h"




PickByFill::PickByFill(ApplicationManager* pApp) :Action(pApp)
{
	numberOfColors = 0;
	wrongSelect = 0;
	rightSelect = 0;
	for (int i = 0; i < 7; i++)
		clrs[i] = 0;
}


void PickByFill::ReadActionParameters()
{
	for (int i = 0; i < pManager->getFigCount(); i++) {
		Fig = pManager->DrawnFigs(i);
		if (Fig->GetGfxInfo().isFilled) //counts color occurance.
		{
			if (Fig->GetGfxInfo().FillClr == BLACK)
				clrs[0]++;
			else if (Fig->GetGfxInfo().FillClr == WHITE)
				clrs[1]++;
			else if (Fig->GetGfxInfo().FillClr == BLUE)
				clrs[2]++;
			else if (Fig->GetGfxInfo().FillClr == GREEN)
				clrs[3]++;
			else if (Fig->GetGfxInfo().FillClr == RED)
				clrs[4]++;
			else if (Fig->GetGfxInfo().FillClr == PINK)
				clrs[5]++;
			else if (Fig->GetGfxInfo().FillClr == PURPLE)
				clrs[6]++;
		}
		
	}

	for (int i = 0; i < 7; i++)
		if (clrs[i] != 0)numberOfColors++;


}


void PickByFill::Execute()
{
	GUI* pGUI = pManager->GetGUI();
	ReadActionParameters();

	if (numberOfColors > 1)
	{
		//Figure clicked to be hidden
		CFigure* clickedFig;
		// get random number from figures
		randomNumberOfFigure = rand() % pManager->getFigCount();
		//Counting the the color instances.
		Fig = pManager->DrawnFigs(randomNumberOfFigure);
		if (Fig->GetGfxInfo().isFilled)
			countOfFiguresColors(Fig, pGUI);
		int figuresNumberMustPicked = numberOfPickedColor;
		while (numberOfPickedColor > 0)
		{
			if (wrongSelect >= figuresNumberMustPicked) break;
			pGUI->GetPointClicked(P.x, P.y);
			if (P.y > UI.ToolBarHeight || P.x > (UI.MenuItemWidth * PLAY_ITM_COUNT))
			{
				clickedFig = pManager->GetFigure(P.x, P.y);
				if (clickedFig != NULL)
					onFigureClicked(clickedFig, pGUI);
			}
			else
			{
				pGUI->PrintMessage(" game ended");
				numberOfPickedColor = -1;
			}
		}

		if (numberOfPickedColor == 0) // when sclected all fiugre selceted
			pGUI->PrintMessage("You won!");
		else if (wrongSelect == figuresNumberMustPicked)
			pGUI->PrintMessage("You lost!");
	}
	else 			pGUI->PrintMessage("You must have at least two or more colors to play pick by color!");
	for (int i = 0; i < pManager->getFigCount(); i++)
		pManager->DrawnFigs(i)->Show();
	pManager->UpdateInterface();
}

void PickByFill::countOfFiguresColors(CFigure* Fig,GUI* pGUI){
	if (Fig->GetGfxInfo().FillClr == BLACK)
	{
		numberOfPickedColor = clrs[0];
		pGUI->PrintMessage("Pick up figures colored black!");
	}
	else if (Fig->GetGfxInfo().FillClr == WHITE)
	{
		numberOfPickedColor = clrs[1];
		pGUI->PrintMessage("Pick up figures colored white!");
	}
	else if (Fig->GetGfxInfo().FillClr == BLUE)
	{
		numberOfPickedColor = clrs[2];
		pGUI->PrintMessage("Pick up figures colored blue!");

	}
	else if (Fig->GetGfxInfo().FillClr == GREEN)
	{
		numberOfPickedColor = clrs[3];
		pGUI->PrintMessage("Pick up figures colored green!");

	}
	else if (Fig->GetGfxInfo().FillClr == RED)
	{
		numberOfPickedColor = clrs[4];
		pGUI->PrintMessage("Pick up figures colored red!");

	}
	else if (Fig->GetGfxInfo().FillClr == PINK)
	{
		numberOfPickedColor = clrs[5];
		pGUI->PrintMessage("Pick up figures colored pink!");

	}
	else if (Fig->GetGfxInfo().FillClr == PURPLE)
	{
		numberOfPickedColor = clrs[6];
		pGUI->PrintMessage("Pick up figures colored purple!");

	}
}
void PickByFill::onFigureClicked(CFigure* clickedFig,GUI* pGUI) {
	if ((!(Fig->GetGfxInfo().isFilled)) && (!(clickedFig->GetGfxInfo().isFilled)))
	{
		PirntScore(1);
		clickedFig->Hide();
		pManager->UpdateInterface();
		pGUI->ClearDrawArea();
		numberOfPickedColor--;
	}

	else if (clickedFig->GetGfxInfo().isFilled && clickedFig->GetGfxInfo().FillClr == AssignColor(Fig))
	{
		PirntScore(1);
		clickedFig->Hide();
		pManager->UpdateInterface();
		numberOfPickedColor--;
	}
	else
	{
		PirntScore(0);
		clickedFig->Hide();
		pManager->UpdateInterface();
	}

}
color PickByFill::AssignColor(CFigure* Fig)
{
	if (Fig->GetGfxInfo().isFilled)
	{
		if (Fig->GetGfxInfo().FillClr == BLACK)
			return BLACK;
		else if (Fig->GetGfxInfo().FillClr == WHITE)
			return WHITE;
		else if (Fig->GetGfxInfo().FillClr == BLUE)
			return BLUE;
		else if (Fig->GetGfxInfo().FillClr == GREEN)
			return GREEN;
		else if (Fig->GetGfxInfo().FillClr == RED)
			return RED;
		else if (Fig->GetGfxInfo().FillClr == PINK)
			return PINK;
		else if (Fig->GetGfxInfo().FillClr == PURPLE)
			return PURPLE;
	}
}
void PickByFill::PirntScore(int S)
{
	GUI* pGUI = pManager->GetGUI();

	string message;
	if (S == 1)
	{
		rightSelect++;
		message = "correct!, Your score is: " + to_string(rightSelect) + " correct and " + to_string(wrongSelect) + " incorrect";
	}
	else if (S == 0)
	{
		wrongSelect++;
		message = "incorrect!, Your score is: " + to_string(rightSelect) + " correct, and " + to_string(wrongSelect) + " incorrect";
	}
	pGUI->PrintMessage(message);
}