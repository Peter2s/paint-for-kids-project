#ifndef UI_INFO_H
#define UI_INFO_H

#include "..\CMUgraphicsLib\CMUgraphics.h"

//User Interface information file.
//This file contains info that is needed by Input and Output classes to
//handle the user interface

enum GUI_MODE	//Graphical user interface mode
{
	MODE_DRAW,	//Drawing mode (startup mode)
	MODE_PLAY	//Playing mode
};

enum DrawMenuItem //The items of the Draw menu (you should add more items)
{
	//Note: Items are ordered here as they appear in menu
	//If you want to change the menu items order, change the order here
	ITM_SQUR,		//Square item in menu
	ITM_RECT,		//Rectangle item in menu
	ITM_CIRC,		//Circle item in menu
	ITM_TRIA,		//Triangle item in menu
	ITM_LINE,		//Line item in menu
	ITM_ELPS,		//Elipce item in menu
	ITM_HEXAGON,	//Hexa item in menu
	DRAW_CLR,
	FILL_CLR,
	BG_CHANGE,
	FIG_COLOR,
	FIG_BORDER,
	ITM_Select,
	ITM_MOVE,
	ITM_Delete,
	ITM_Send_Back,
	ITM_Send_Front,
	//Ellipse item in menu

//TODO: Add more items names here
	ITM_SAVE,//save item
	ITM_LOAD,//load a graph
	
	ITM_RESIZE_QUARTER,
	ITM_RESIZE_HALF,
	ITM_RESIZE_DOUBLED,
	ITM_RESIZE_QUADRUPLE,
	ITM_TO_PLAY,
	ITM_EXIT,		//Exit item

	DRAW_ITM_COUNT		//no. of menu items ==> This should be the last line in this enum

};

enum PlayMenuItem //The items of the Play menu (you should add more items)
{
	//Note: Items are ordered here as they appear in menu
	//If you want to change the menu items order, change the order here

	//TODO: Add more items names here
	ITM_P_H_TYPE,		//Play and hide by type item in menu
	ITM_P_H_FILL,
	ITM_P_H_BOTH,
	ITM_TO_DRAW,
	PLAY_ITM_COUNT		//no. of menu items ==> This should be the last line in this enum

};
enum SetColor
{
	ITM_BLACK,
	ITM_WHITE,
	ITM_RED,
	ITM_GREEN,
	ITM_BLUE,
	ITM_PINK,
	ITM_PURPLE,
	COLOR_ITM_COUNT
};

__declspec(selectany) //This line to prevent "redefinition error"

struct UI_Info	//User Interface Info.
{
	GUI_MODE InterfaceMode;
	bool filled_OR_not = false;
	int	width, height,	//Window width and height
		wx, wy,			//Window starting coordinates
		StatusBarHeight,	//Status Bar Height
		ToolBarHeight,		//Tool Bar Height (distance from top of window to bottom line of toolbar)
		MenuItemWidth;		//Width of each item in toolbar menu


	color DrawColor;		//Drawing color
	color FillColor;		//Filling color
	color HighlightColor;	//Highlighting color
	color MsgColor;			//Messages color
	color BkGrndColor;		//Background color
	color StatusBarColor;	//Status bar color
	int PenWidth;			//width of the pen that draws shapes

	/// Add more members if needed

}UI;	//create a global object UI

#endif