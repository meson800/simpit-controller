#ifndef SIMPIT_MANAGER
#define SIMPIT_MANAGER



#include <vector>
#include <cstring>
using namespace std;

#include "Orbitersdk.h"
#include "OrbiterAPI.h"
#include "Event.h"

//include modules


#include "SerialInput.h"
#include "TimeBasedInput.h"

#include "SimpitMFD.h"
#include "ExternalOutput.h"
#include "PanelClickRecorderOutput.h"
#include "PanelEventOutput.h"








class SimpitManager : public oapi::Module
{
public:
	SimpitManager(HINSTANCE hDLL);
	void handleEvent(Event ev);
	void clbkSimulationStart(RenderMode mode);
	void clbkSimulationEnd(RenderMode mode);
	void clbkFocusChanged(OBJHANDLE old_focus, OBJHANDLE new_focus);
	void clbkPreStep(double simt, double simdt, double mjd);
	void clbkPostStep(double simt, double simdt, double mjd);


private:
	vector<IO *> modules;

};

#endif