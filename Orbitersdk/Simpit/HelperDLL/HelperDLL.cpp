// This is the main DLL file.

#include <afxwin.h>

#include "HelperDLL.h"

void HelperDLL::Helpers::SetWindowRegion(HWND window,CRgn region, bool redraw)
{
	SetWindowRgn(window,region,redraw);
	return;
}

void HelperDLL::Helpers::SetWindowRegion(HWND window,int left, int top, int right, int bottom, bool redraw)
{
	CRgn region;
	region.CreateRectRgn(left,top,right,bottom);
	SetWindowRgn(window,region,redraw);
	return;
}
