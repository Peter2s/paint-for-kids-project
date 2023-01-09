#include "ActionLoad.h"
#include "..\ApplicationManager.h"
#include"..\Figures\CSquare.h"
#include"..\Figures\CEllipse.h"
#include"..\Figures\CHexagon.h"
#include"..\Figures\CLine.h"
#include"..\Figures\CRectangle.h"
#include"..\Figures\CTriangle.h"
#include"..\Figures\CCircle.h"
#include "..\GUI\GUI.h"
#include <fstream>
#include "String.h"


ActionLoad::ActionLoad(ApplicationManager* pApp, int FigCount) : Action(pApp)
{
	//FileName = "temp";
	FigCnt = FigCount;    //We need the figure number to write it on the file
	GUI* pGUI = pManager->GetGUI();
}

void ActionLoad::ReadActionParameters()
{
	GUI* pGUI = pManager->GetGUI();
	pGUI->ClearStatusBar();
	pGUI->PrintMessage(" Input file name here "); // show msg for get file name
	name = pGUI->GetSrting(); //read file name
	nameTxt = (name + ".txt");
}


void ActionLoad::Execute()
{
	
	GUI* pGUI = pManager->GetGUI();
	ReadActionParameters();
	ifstream InputFile;   //object of ofstream to write on the disk
	
		InputFile.open("SavedFiles\\" + nameTxt );  // openedFileName holds the path of the loaded file
		pGUI->ClearDrawArea();

		bool flag = false;
		if (InputFile.fail()) //Check the FileName and loop till be Valid name
		{
			pGUI->PrintMessage("File not found!");
		}
		else
		{
			if (InputFile.is_open())
			{
				//read from the file the current draw clr & fill clr &number of figuers 
				CFigure* pFig = NULL;
				int numberOfFiguers;
				string DrawClr, FillClr, BgClr;

				InputFile >> DrawClr;
				UI.DrawColor = pManager->ColorObject(DrawClr);
				
				InputFile >> FillClr;
				UI.FillColor = pManager->ColorObject(FillClr);

				InputFile >> BgClr;
				UI.BkGrndColor = pManager->ColorObject(BgClr);

				InputFile >> numberOfFiguers;
				//cleaning the figlist before loading the file
				pManager->ClearFigList();
				// Loop all figures ,identify the type ,then create an obj of the specified type,add to the figlist  after the loading it
				for (int i = 0; i < numberOfFiguers; i++)
				{
					string shapeType;
					InputFile >> shapeType;
					if (shapeType == "CSquare") {
						pFig = new CSquare;
					}
					else if (shapeType == "CEllipse") {
						pFig = new CEllipse;
					}
					else if (shapeType == "CHexagon") {
						pFig = new CHexagon;
					}
					else if (shapeType == "CLine") {
						pFig = new CLine;
					}
					else if (shapeType == "CRectangle") {
						pFig = new CRectangle;
					}
					else if (shapeType == "CTriangle") {
						pFig = new CTriangle;
					}
					else if (shapeType == "CCircle") {
						pFig = new CCircle;
					}

					//loading the parameters of each figure
					pFig->Load(InputFile);
					if (pFig != NULL)
					{
						//seneding it to the application manager to add them
						pManager->AddFigure(pFig);
					}
				}
			};

			pManager->UpdateInterface();     //Draw the figure list

			pGUI->PrintMessage("Graph Loaded Successfully");
			Sleep(1000);
			pGUI->ClearStatusBar();
				InputFile.close();
				//close the file after looping 

			}
		}
