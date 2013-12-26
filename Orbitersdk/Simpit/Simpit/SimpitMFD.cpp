//Copyright (c) 2013 Christopher Johnstone(meson800)
//The MIT License - See ../../../LICENSE for more info

#include "SimpitMFD.h"

int SimpitMFD::convertToButtonClass [15] = { 15, 13, 11, 9, 7, 5, 14, 12, 10, 8, 6, 4, 3, 2, 1 };

SimpitMFD::SimpitMFD(HINSTANCE hDLL)
{
	moduleHandle = hDLL;
	hasRegion = false;
	
}

SimpitMFD::~SimpitMFD()
{
	delete moduleHandle;
}

void SimpitMFD::load(const char * key, const char * value)
{
	if (strcmp(key, "position") == 0)
	{
		int left, top, right, bottom;
		if (sscanf(value, "%i %i %i %i", &left, &top, &right, &bottom) == 4)
		{
			mfdPos.left = left;
			mfdPos.top = top;
			mfdPos.right = right;
			mfdPos.bottom = bottom;
		}
	}
	else if (strcmp(key, "region") == 0)
	{
		int left, top, right, bottom;
		if (sscanf(value, "%i %i %i %i", &left, &top, &right, &bottom) == 4)
		{
			hasRegion = true;
			mfdRegion[0] = left;
			mfdRegion[1] = top;
			mfdRegion[2] = right;
			mfdRegion[3] = bottom;
		}
	}
	else if (strcmp(key, "event") == 0)
	{
		int eventId, eventState, buttonId;
		if (sscanf(value, "%i %i %i", &eventId, &eventState, &buttonId) == 3)
		{
			buttonMapping[Event(eventId, eventState)] = buttonId;
		}
	}
}

void SimpitMFD::SimulationStart()
{
	MFDSPEC spec = {{0,0,mfdPos.right - mfdPos.left,mfdPos.bottom - mfdPos.top},6,6,10,10};
	window = new MFDWindow (moduleHandle, spec);
	oapiRegisterExternMFD (window, spec);
	MoveWindow(window->returnDialog(),mfdPos.left,mfdPos.top,mfdPos.right,mfdPos.bottom,SWP_SHOWWINDOW);
	
	if (hasRegion)
		HelperDLL::Helpers::SetWindowRegion(window->returnDialog(),mfdRegion[0],mfdRegion[1],mfdRegion[2],
			mfdRegion[3],true);
	
}

void SimpitMFD::handleEvent(Event ev)
{
	if (buttonMapping.count(ev))
	{
		HWND mfdWindow = window->returnDialog();

		//find the correct button
		HWND buttonWindow = GetDlgItem(mfdWindow, IDC_BUTTON1 + buttonMapping[ev]);
		if (buttonWindow != NULL)
		{
			SendMessage(buttonWindow, WM_LBUTTONDOWN, 1, 0);
			SendMessage(buttonWindow, WM_LBUTTONUP, 1, 0);
		}
	}
		//window->ProcessButton(buttonMapping[ev],PANEL_MOUSE_LBDOWN);
}
