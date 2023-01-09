#ifndef PICK_BY_TYPE_H
#define PICK_BY_TYPE_H
#include "Action.h"
#include "..\Figures\CFigure.h"
class PickByType :
	public Action
{
	CFigure* Fig;
	Point P;
	int  numberOfFigures, rand_fig_no, picked_fig_no, wrongSelect, rightSelect;
	int figs[7];
	void PirntScore(int);
public:
	PickByType(ApplicationManager*);
	~PickByType();
	void ReadActionParameters();
	void Execute();
};
#endif