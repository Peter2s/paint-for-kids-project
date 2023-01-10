#include "GUI.h"
#include <iostream>

//constructor make necessary initializations
GUI::GUI()
{
	//Initialize user interface parameters
	UI.InterfaceMode = MODE_DRAW;
	UI.width = 1350; 
	UI.height = 700; 
	UI.wx = 10;
	UI.wy = 10;


	UI.StatusBarHeight = 50;
	UI.ToolBarHeight = 77;
	UI.MenuItemWidth = 50;

	UI.DrawColor = BLUE;	//Drawing color
	UI.FillColor = GREEN;	//Filling color
	UI.MsgColor = WHITE;		//Messages color
	UI.BkGrndColor = WHITE;	//Background color
	UI.HighlightColor = KHAKI;	//This color should NOT be used to draw figures. use if for highlight only
	UI.StatusBarColor = LIGHTSLATEGRAY;
	UI.PenWidth = 3;	//width of the figures frames


	//Create the output window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	//Change the title
	pWind->ChangeTitle("Paint for Kids  OS Mansoura 43 - gourp 3");
	CreateDrawToolBar();
	CreateStatusBar();	
}

//======================================================================================//
//								Input Functions										    //
//======================================================================================//


void GUI::GetPointClicked(int& x, int& y) const
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}

string GUI::GetSrting() const
{
	string Label;
	char Key;
	while (1)
	{
		pWind->WaitKeyPress(Key);
		if (Key == 27)	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if (Key == 13)	//ENTER key is pressed
			return Label;
		if (Key == 8)	//BackSpace is pressed
			Label.resize(Label.size() - 1);
		else
			Label += Key;
		PrintMessage(Label);
	}
}

//This function reads the position where the user clicks to determine the desired action
ActionType GUI::MapInputToActionType() const
{
	int x, y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click
	PrintMessage("");
	if (UI.InterfaceMode == MODE_DRAW)	//GUI in the DRAW mode
	{
		//[1] If user clicks on the Toolbar
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			
			int ClickedItemOrder;
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			if (x <1.5* UI.MenuItemWidth && y >= 0 && y < UI.ToolBarHeight / 2) {
				ClickedItemOrder = (2*x / UI.MenuItemWidth);
			}
			else if (x < 1.5 * UI.MenuItemWidth && y >= UI.ToolBarHeight/2 && y <= UI.ToolBarHeight) {
				ClickedItemOrder = (2*x / UI.MenuItemWidth)+3;
			}else{
				ClickedItemOrder = ((x-1.5* UI.MenuItemWidth) / UI.MenuItemWidth)+6;
			}
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on
			
			//int ClickedItemOrder = (x / UI.MenuItemWidth);
			
			switch (ClickedItemOrder)
			{
			case ITM_SQUR: return DRAW_SQUARE;
			case ITM_RECT: return DRAW_RECT;
			case ITM_CIRC: return DRAW_CIRCLE;
			case ITM_TRIA: return DRAW_TRI;
			case ITM_LINE: return DRAW_LINE;
			case ITM_ELPS: return DRAW_ELPS;
			case ITM_HEXAGON: return DRAW_HEX;
			case DRAW_CLR:return CHNG_DRAW_CLR;
			case FILL_CLR: return CHNG_FILL_CLR;
			case BG_CHANGE: return CHNG_BK_CLR;
			case FIG_COLOR: return CHG_FIG_FILL_COLOR;
			case FIG_BORDER: return CHG_FIG_DRAW_COLOR;
			case ITM_LOAD: return LOAD;
			case ITM_SAVE: return SAVE;
			case ITM_EXIT: return EXIT;
			case ITM_Select: return SELECT;
			case ITM_MOVE: return MOVE;
			case ITM_Delete: return DEL;
			case ITM_Send_Back: return SEND_BACK;
			case ITM_Send_Front: return BRNG_FRNT;
			case ITM_TO_PLAY: return TO_PLAY;
			case ITM_RESIZE_QUARTER: return QUARTERED_RESIZE;
			case ITM_RESIZE_HALF: return HALFED_RESIZE;
			case ITM_RESIZE_DOUBLED: return DOUBLED_RESIZE;
			case ITM_RESIZE_QUADRUPLE: return QUADRUPLE_RESIZED;
			default: return EMPTY;	//A click on empty place in desgin toolbar
			}

		}

		//[2] User clicks on the drawing area
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;
		}

		//[3] User clicks on the status bar
		return STATUS;
	}
	else 	//GUI is in PLAY mode
	{
		
		if (y >= 0 && y < UI.ToolBarHeight) {
			int ClickedItemOrder = (x / UI.MenuItemWidth);

			switch (ClickedItemOrder)

			{
			case ITM_P_H_TYPE:return P_H_TYPE;
			case ITM_P_H_FILL:return P_H_FILL;
			case ITM_TO_DRAW:return TO_DRAW;
			case ITM_P_H_BOTH: return P_H_BOTH;
			default: return EMPTY;

			}

		}
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return PLAYING_AREA;
		}

		///TODO:
		//perform checks similar to Draw mode checks above
		//and return the correspoding action
		return TO_PLAY;	//just for now. This should be updated
	}

}
//======================================================================================//
//								Output Functions										//
//======================================================================================//

window* GUI::CreateWind(int w, int h, int x, int y) const
{
	window* pW = new window(w, h, x, y);
	pW->SetBrush(UI.BkGrndColor);
	pW->SetPen(UI.BkGrndColor, 1);
	pW->DrawRectangle(0, UI.ToolBarHeight, w, h);
	return pW;
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::CreateStatusBar() const
{
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::ClearStatusBar() const
{
	//Clear Status bar by drawing a filled white Square
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::CreateDrawToolBar() const
{
	UI.InterfaceMode = MODE_DRAW;

	//You can draw the tool bar icons in any way you want.
	//Below is one possible way

	//First prepare List of images for each menu item
	//To control the order of these images in the menu, 
	//reoder them in UI_Info.h ==> enum DrawMenuItem
	string MenuItemImages[DRAW_ITM_COUNT];
	MenuItemImages[ITM_SQUR] = "images\\MenuItems\\Menu_Sqr.jpg";
	MenuItemImages[ITM_RECT] = "images\\MenuItems\\Rect.jpg";
	MenuItemImages[ITM_CIRC] = "images\\MenuItems\\Circle.jpg";
	MenuItemImages[ITM_TRIA] = "images\\MenuItems\\Triangle.jpg";
	MenuItemImages[ITM_LINE] = "images\\MenuItems\\Line.jpg";
	MenuItemImages[ITM_ELPS] = "images\\MenuItems\\Menu_Elps.jpg";
	MenuItemImages[ITM_HEXAGON] = "images\\MenuItems\\Menu_Hexagon.jpg";
	MenuItemImages[DRAW_CLR] = "images\\MenuItems\\drawm.jpg";
	MenuItemImages[FILL_CLR] = "images\\MenuItems\\fillc.jpg";
	MenuItemImages[BG_CHANGE] = "images\\MenuItems\\bgcolor.jpg";
	MenuItemImages[FIG_COLOR] = "images\\MenuItems\\FigColor.jpg";
	MenuItemImages[FIG_BORDER] = "images\\MenuItems\\chgShapeBorder.jpg";
	MenuItemImages[ITM_Select] = "images\\MenuItems\\Menu_Select.jpg";
	MenuItemImages[ITM_MOVE] = "images\\MenuItems\\Move.jpg";
	MenuItemImages[ITM_Delete] = "images\\MenuItems\\DELETE.jpg";
	MenuItemImages[ITM_Send_Back] = "images\\MenuItems\\sendtoback.jpg";
	MenuItemImages[ITM_Send_Front] = "images\\MenuItems\\bringtofront.jpg";
	MenuItemImages[ITM_SAVE] = "images\\MenuItems\\SAVE.jpg";
	MenuItemImages[ITM_LOAD] = "images\\MenuItems\\LOAD.jpg";
	MenuItemImages[ITM_TO_PLAY] = "images\\MenuItems\\playm.jpg";
	MenuItemImages[ITM_RESIZE_QUARTER] = "images\\MenuItems\\onefourth.jpg";
	MenuItemImages[ITM_RESIZE_HALF] = "images\\MenuItems\\half.jpg";
	MenuItemImages[ITM_RESIZE_DOUBLED] = "images\\MenuItems\\2times.jpg";
	MenuItemImages[ITM_RESIZE_QUADRUPLE] = "images\\MenuItems\\4times.JPG";
	MenuItemImages[ITM_EXIT] = "images\\MenuItems\\Menu_Exit.jpg";
	


	//TODO: Prepare images for each menu item and add it to the list
	
	for (int i = 0; i < 3; i++)
		pWind->DrawImage(MenuItemImages[i], i * UI.MenuItemWidth/2, 0, UI.MenuItemWidth/2, UI.ToolBarHeight/2);
	for (int i = 3; i < 6; i++)
		pWind->DrawImage(MenuItemImages[i], (i - 3) * UI.MenuItemWidth/2, UI.ToolBarHeight / 2, UI.MenuItemWidth/2, UI.ToolBarHeight/2);
	for (int i = 6; i < DRAW_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], (i-4.5) * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);
	
	/*
	//Draw menu item one image at a time
	for (int i = 0; i < DRAW_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], (i-0) * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);
	*/


	//Draw a line under the toolbar
	pWind->SetPen(LIGHTSLATEGRAY, 5);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);

}
void GUI::CreateColorToolBar() const
{
	///TODO: write code to create Play mode menu
	string MenuItemImages[COLOR_ITM_COUNT];
	MenuItemImages[ITM_BLACK] = "images\\MenuItems\\black.jpg";
	MenuItemImages[ITM_WHITE] = "images\\MenuItems\\white.jpg";
	MenuItemImages[ITM_RED] = "images\\MenuItems\\red.jpg";
	MenuItemImages[ITM_GREEN] = "images\\MenuItems\\green.jpg";
	MenuItemImages[ITM_BLUE] = "images\\MenuItems\\blue.jpg";
	MenuItemImages[ITM_PINK] = "images\\MenuItems\\pink.jpg";
	MenuItemImages[ITM_PURPLE] = "images\\MenuItems\\purple.jpg";


	//TODO: Prepare images for each menu item and add it to the list

	//Draw menu item one image at a time
	for (int i = 0; i < COLOR_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::CreatePlayToolBar() const
{
	UI.InterfaceMode = MODE_PLAY;
	///TODO: write code to create Play mode menu

	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(0, 0, UI.width, UI.height - UI.ToolBarHeight);

	string MenuItemImages2[PLAY_ITM_COUNT];
	MenuItemImages2[ITM_P_H_TYPE] = "images\\MenuItems\\Pickbyshape.jpg";
	MenuItemImages2[ITM_P_H_FILL] = "images\\MenuItems\\Pickbycolor.jpg";
	MenuItemImages2[ITM_P_H_BOTH] = "images\\MenuItems\\Pickbyboth.jpg";
	MenuItemImages2[ITM_TO_DRAW] = "images\\MenuItems\\drawcolor1.jpg";

	//Draw menu item one image at a time
	for (int i = 0; i < PLAY_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages2[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);



	//Draw a line under the toolbar
	pWind->SetPen(BLUE, 5);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);

}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::ClearDrawArea() const
{
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight);

}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::ClearToolBarArea() const
{
	pWind->SetPen(WHITE, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);

}
void GUI::PrintMessage(string msg) const	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar

	pWind->SetPen(UI.MsgColor, 50);
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	pWind->DrawString(10, UI.height - (int)(UI.StatusBarHeight / 1.2), msg);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::setBgColor(color c) const	//get current drwawing color
{
	UI.BkGrndColor = c;
}

color GUI::getCrntDrawColor() const	//get current drwawing color
{
	return UI.DrawColor;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////

int GUI::getCrntPenWidth() const		//get current pen width
{
	return UI.PenWidth;
}
void GUI::setCrntDrawColor(color c) const	//set current drwawing color
{
	UI.DrawColor = c;
}

color GUI::getCrntFillColor() const	//get current filling color
{
	return UI.FillColor;
}
////////////////////////////////
void GUI::setCrntFillColor(color c) const	//get current drwawing color
{
	UI.filled_OR_not = true;

	UI.FillColor = c;

}

//======================================================================================//
//								Figures Drawing Functions								//
//======================================================================================//

void GUI::DrawSquare(Point P1, int length, GfxInfo RectGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = RectGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, RectGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (RectGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else
		style = FRAME;


	pWind->DrawRectangle(P1.x, P1.y, P1.x + length, P1.y + length, style);
	//pWind->DrawLine(P1.x, P1.y, P1.x + length, P1.y + length, style);

}
void GUI::DrawCircle(Point P1, int length, GfxInfo RectGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = RectGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, RectGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (RectGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else
		style = FRAME;


	pWind->DrawCircle(P1.x, P1.y, length, style);
	//pWind->DrawLine(P1.x, P1.y, P1.x + length, P1.y + length, style);

}
void GUI::DrawRectangle(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = RectGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, RectGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (RectGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else
		style = FRAME;


	pWind->DrawRectangle(P1.x, P1.y, P2.x, P2.y, style);
	//pWind->DrawLine(P1.x, P1.y, P1.x + length, P1.y + length, style);

}
void GUI::DrawLine(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = RectGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, RectGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (RectGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else
		style = FRAME;


	// pWind->DrawCircle(P1.x, P1.y, length, style);
	pWind->DrawLine(P1.x, P1.y, P2.x, P2.y, style);

}
void GUI::DrawTriangle(Point P1, Point P2, Point P3, GfxInfo RectGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = RectGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, RectGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (RectGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else
		style = FRAME;


	pWind->DrawTriangle(P1.x, P1.y, P2.x, P2.y, P3.x, P3.y, style);
	
	//pWind->DrawLine(P1.x, P1.y, P2.x, P2.y, style);
	//pWind->DrawLine(P2.x, P2.y, P3.x, P3.y, style);
	//pWind->DrawLine(P3.x, P3.y, P1.x, P1.y, style);

}
void GUI::DrawEllipse(Point P1, Point P2, GfxInfo ElpsGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = ElpsGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, ElpsGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (ElpsGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(ElpsGfxInfo.FillClr);
	}
	else
		style = FRAME;
	pWind->DrawEllipse(P1.x, P1.y, P2.x, P2.y, style);
}

void GUI::DrawHexagon(Point P1, Point P2, GfxInfo HexGfxInfo, bool selected)
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = HexGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, HexGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (HexGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(HexGfxInfo.FillClr);
	}
	else
		style = FRAME;
	Point points[6];
	getHexagonPoints(P1, P2, points);
	int XS[6];
	int YS[6];
	for (int i = 0; i < 6; i++) {
		XS[i] = points[i].x;
		YS[i] = points[i].y;
	}
	pWind->DrawPolygon(XS, YS, 6, style);
}


void GUI::getHexagonPoints(Point P1, Point P2, Point * vertics) {
	


	int radius = sqrt(pow(P1.x - P2.x, 2) + pow(P1.y - P2.y, 2));

	vertics[0].x = P2.x;
	vertics[0].y = P2.y;
	//float angle = 0; 
	int angle = 0;
	for (int i = 0; i < 6; i++) {
		
		vertics[i].x = (float)P1.x + (radius * cos(angle*3.14/180));
		vertics[i].y = (float)P1.y + (radius * sin(angle * 3.14/180));
		angle += 60;// (3.14 / 3);
	}

}





bool GUI::allPointsInDrawingArea(Point * point, int count) const
{
	for (int i = 0; i < count; i++) {
		if (!isPointInDrawingArea(point[i].x, point[i].y))
			return false;
	}
	return true;
}

bool GUI::isPointInDrawingArea(int x, int y) const
{
	return x > 0 && x < UI.width
		&& y > UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight;

}
bool GUI::isBorderInDrawingArea(Point center, int radius) const
{
	return
		center.y + radius < UI.height
		&&
		center.x + radius < UI.width
		&&
		center.x - radius > 0
		&&
		center.y - radius > UI.ToolBarHeight
	;
}

//////////////////////////////////////////////////////////////////////////////////////////
GUI::~GUI()
{
	delete pWind;
}

