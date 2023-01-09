#include "PickByType.h"
#include "..\ApplicationManager.h"
#include "..\Figures\CEllipse.h"
#include "..\Figures\CHexagon.h"
#include "..\Figures\CSquare.h"
#include "..\Figures\CCircle.h"
#include "..\Figures\CLine.h"
#include "..\Figures\CRectangle.h"
#include "..\Figures\CTriangle.h"
#include "..\GUI\GUI.h"
#include <iostream>



PickByType::PickByType(ApplicationManager* pApp) :Action(pApp)
{
	numberOfFigures = 0;
	rightSelect = 0;
	wrongSelect = 0;
	for (int i = 0; i < 7; i++)
		figs[i] = 0;
}
void PickByType::PirntScore(int S)
{
	GUI* pGUI = pManager->GetGUI();

	string message;
	if (S == 1)
	{
		rightSelect++;
		message = "Right!, Your score is: " + to_string(rightSelect) + " Right, and " + to_string(wrongSelect) + " Wrong.";
		cout <<"==" << rightSelect;

	}
	else if (S == 0)
	{
		wrongSelect++;
		message = "Wrong!, Your score is: " + to_string(rightSelect) + " Right, and " + to_string(wrongSelect) + " Wrong.";
	}
	pGUI->PrintMessage(message);
}

void PickByType::ReadActionParameters()
{
	for (int i = 0; i < pManager->getFigCount(); i++)
	{
		Fig = pManager->DrawnFigs(i);
		if (dynamic_cast<CSquare*>(Fig))
			figs[0]++;
		else if (dynamic_cast<CEllipse*>(Fig))
			figs[1]++;
		else if (dynamic_cast<CHexagon*>(Fig))
			figs[2]++;
		else if (dynamic_cast<CCircle*>(Fig))
			figs[3]++;
		else if (dynamic_cast<CRectangle*>(Fig))
			figs[4]++;
		else if (dynamic_cast<CTriangle*>(Fig))
			figs[5]++;
		else figs[6]++;
	}		for (int i = 0; i < 7; i++)
		if (figs[i] != 0)numberOfFigures++;
}
void PickByType::Execute()
{
	GUI* pGUI = pManager->GetGUI();
	ReadActionParameters();
	if (numberOfFigures > 1)
	{
		CFigure* clickedFig;
		//Randomize
		rand_fig_no = rand() % pManager->getFigCount();
		//counting fig instances
		Fig = pManager->DrawnFigs(rand_fig_no);
		if (dynamic_cast<CSquare*>(Fig))
		{
			picked_fig_no = figs[0];
			pGUI->PrintMessage("Pick up all the Squares!");
		}
		else if (dynamic_cast<CEllipse*>(Fig))
		{
			picked_fig_no = figs[1];
			pGUI->PrintMessage("Pick up all the Ellipses!");
		}
		else if (dynamic_cast<CHexagon*>(Fig))
		{
			picked_fig_no = figs[2];
			pGUI->PrintMessage("Pick up all the Hexagones!");
		}
		else if (dynamic_cast<CCircle* > (Fig))
		{
			picked_fig_no = figs[3];
			pGUI->PrintMessage("Pick up all the Circles!");
		}
		else if (dynamic_cast<CRectangle*>(Fig))
		{
			picked_fig_no = figs[4];
			pGUI->PrintMessage("Pick up all the Rectangles!");
		}
		else if (dynamic_cast<CTriangle*>(Fig))
		{
			picked_fig_no = figs[5];
			pGUI->PrintMessage("Pick up all the Triangles!");
		}
		else {
			pGUI->PrintMessage(" Not figures");
		}
		
		while (picked_fig_no > 0)
		{
			{
				pGUI->GetPointClicked(P.x, P.y);
				if (P.y > UI.ToolBarHeight || P.x > (UI.MenuItemWidth * PLAY_ITM_COUNT))
				{
					clickedFig = pManager->GetFigure(P.x, P.y);
					if (clickedFig != NULL)
					{	
						 if ((dynamic_cast<CSquare*>(clickedFig)) && (dynamic_cast<CSquare*>(Fig)))
						{
							PirntScore(1);
							clickedFig->Hide();
							pManager->UpdateInterface();
							picked_fig_no--;
						}
						else if ((dynamic_cast<CEllipse*>(clickedFig)) && (dynamic_cast<CEllipse*>(Fig)))
						{
							PirntScore(1);
							clickedFig->Hide();
							pManager->UpdateInterface();
							picked_fig_no--;
						}
						
						else if ((dynamic_cast<CHexagon*>(clickedFig)) && (dynamic_cast<CHexagon*>(Fig)))
						 {
							 PirntScore(1);
							 clickedFig->Hide();
							 pManager->UpdateInterface();
							 picked_fig_no--;
						 }

						else if ((dynamic_cast<CCircle*>(clickedFig)) && (dynamic_cast<CCircle*>(Fig)))
						 {
							 PirntScore(1);
							 clickedFig->Hide();
							 pManager->UpdateInterface();
							 picked_fig_no--;
						 }

						else if ((dynamic_cast<CRectangle*>(clickedFig)) && (dynamic_cast<CRectangle*>(Fig)))
						 {
							 PirntScore(1);
							 clickedFig->Hide();
							 pManager->UpdateInterface();
							 picked_fig_no--;
						 }
						else if ((dynamic_cast<CTriangle*>(clickedFig)) && (dynamic_cast<CTriangle*>(Fig)))
						 {
							 PirntScore(1);
							 clickedFig->Hide();
							 pManager->UpdateInterface();
							 picked_fig_no--;
						 }
						else
						{
							PirntScore(0);
							clickedFig->Hide();
							pManager->UpdateInterface();
						}
					}
				}
				else
				{
					pGUI->PrintMessage(" game ended");
					picked_fig_no = -1;
				}
			}
			if (picked_fig_no == 0) {// when sclected all fiugre selceted
				PirntScore(3);
				if (rightSelect > wrongSelect) {
					pGUI->PrintMessage("You won!");
				}
				else {
					pGUI->PrintMessage("You lost!");
				}
			}
		}
	}
	else
		pGUI->PrintMessage("You must have at least two or more figures to play to play pick by figure!");
	for (int i = 0; i < pManager->getFigCount(); i++)
		pManager->DrawnFigs(i)->Show();
	pManager->UpdateInterface();

}