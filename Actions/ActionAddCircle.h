#ifndef ACTION_ADD_CIRCLE_H
#define ACTION_ADD_CIRCLE_H

#include "Action.h"

//Add Circle Action class
class ActionAddCircle : public Action
{
public:
	ActionAddCircle(ApplicationManager* pApp);

	//Add Circle to the ApplicationManager
	virtual void Execute();

};

#endif