//Copyright (c) 2013 Christopher Johnstone(meson800)
//The MIT License - See ../../../LICENSE for more info

#ifndef SIMPIT_MANAGER
#define SIMPIT_MANAGER



#include <vector>
#include <cstring>
using namespace std;

#include "Orbitersdk.h"
#include "OrbiterAPI.h"
#include "Event.h"
#include "ModuleFactory.h"
#include "Log.h"

//include modules

#include "IO.h"








class SimpitManager : public oapi::Module
{
public:
	SimpitManager(HINSTANCE hDLL);
	void handleEvent(Event ev);
	void clbkSimulationStart(RenderMode mode);
	void clbkSimulationEnd();
	void clbkFocusChanged(OBJHANDLE old_focus, OBJHANDLE new_focus);
	void clbkPreStep(double simt, double simdt, double mjd);
	void clbkPostStep(double simt, double simdt, double mjd);


private:
	vector<IO *> modules;

};

#endif