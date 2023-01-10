#pragma once
#ifndef PICK_BY_FILL_H
#define PICK_BY_FILL_H
#include "Action.h"
#include "..\Figures\CFigure.h"
#include "..\ApplicationManager.h"
#endif

class PickByFill :
	public Action
{
	CFigure* Fig = NULL;
	int  numberOfColors, randomNumberOfFigure, numberOfPickedColor, wrongSelect, rightSelect;
	int clrs[7];
	Point P;
	color AssignColor(CFigure*);
	void countOfFiguresColors(CFigure*,GUI*);
	void onFigureClicked(CFigure*,GUI*);
	void PirntScore(int);
public:
	PickByFill(ApplicationManager*);
	void ReadActionParameters();
	void Execute();

};

