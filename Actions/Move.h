#ifndef MOVE_H
#define MOVE_H
#include "Action.h"
#pragma once

class Move : public Action
{
public:
	Move(ApplicationManager* pApp);

	virtual void Execute();
};
#endif





