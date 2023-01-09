#ifndef PICK_BY_TYPE_H
#define PICK_BY_TYPE_H
#include "Action.h"
#include "..\Figures\CFigure.h"
class PickByType :
	public Action
{
	CFigure* Fig;
	Point P;
	int  numberOfFigures, randomNumberOfFigure, numberOfPickedFigure, wrongSelect, rightSelect;
	int figs[7];
	void countOfFiguresInstances(CFigure*, GUI*);
	void onFigureClicked(CFigure*);
	void PirntScore(int);
public:
	PickByType(ApplicationManager*);
	void ReadActionParameters();
	void Execute();
};
#endif