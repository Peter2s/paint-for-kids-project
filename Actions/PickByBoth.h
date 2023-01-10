#ifndef PICK_BY_BOTH_H
#define PICK_BY_BOTH_H
#include "Action.h"
#include "..\Figures\CFigure.h"
class PickByBoth :
	public Action
{
	
	CFigure* Fig;
	Point P;
	int  no_combs, rand_fig_no, picked_comb_no, rightSelect, wrongSelect;
	int combinations[24];
	void PirntScore(int);

public:
	PickByBoth(ApplicationManager*);
	void ReadActionParameters();
	void Execute();

};
#endif