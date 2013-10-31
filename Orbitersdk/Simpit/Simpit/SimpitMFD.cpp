#include "SimpitMFD.h"

SimpitMFD::SimpitMFD(boost::function<void (Event)> _handle, HINSTANCE hDLL): Output(_handle)
{
	handleEventFunc = _handle;
	moduleHandle = hDLL;
	hasRegion = false;
	
}

SimpitMFD::~SimpitMFD()
{
	delete moduleHandle;
}

void SimpitMFD::load(FILEHANDLE inputFile)
{
	char *line;
	while (oapiReadScenario_nextline(inputFile,line))
	{
		if (line[0] != ';')
		{
			int left,top,right,bottom;
			if (sscanf(line,"POSITION %i %i %i %i",&left,&top,&right,&bottom) == 4)
			{
				mfdPos.left = left;
				mfdPos.top = top;
				mfdPos.right = right;
				mfdPos.bottom = bottom;
			}
			if (sscanf(line,"REGION %i %i %i %i",&left,&top,&right,&bottom) == 4)
			{
				hasRegion = true;
				mfdRegion[0] = left;
				mfdRegion[1] = top;
				mfdRegion[2] = right;
				mfdRegion[3] = bottom;
			}

			int eventId,eventState,buttonId;
			if (sscanf(line,"%i %i %i",&eventId,&eventState,&buttonId) == 3)
			{
				buttonMapping[new Event(eventId,eventState)] = buttonId ;
			}
			
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
	if (buttonMapping.count(&ev))
		window->ProcessButton(buttonMapping[&ev],PANEL_MOUSE_LBDOWN);
}
