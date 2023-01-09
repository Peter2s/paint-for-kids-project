#ifndef ACTION_LOAD_H
#define ACTION_LOAD_H
#include "Action.h"

class ActionLoad : public Action
{
private:

	string name; //name of file inputed by the user
	string nameTxt; //name of file.txt
	int FigCnt; //fiugre count
public:
	ActionLoad(ApplicationManager* pApp, int FigCount);
	virtual void ReadActionParameters();
	virtual void Execute();

	//void LoadPlayMode();
};

#endif