//Copyright (c) 2013 Christopher Johnstone(meson800)
//The MIT License - See ../../../LICENSE for more info

#ifndef SIMPIT_IO
#define SIMPIT_IO
#include "OrbiterAPI.h"
#include "Orbitersdk.h"

#include <string>

#include "Event.h"

class IO
{
public:
	IO(){}
	void virtual load(const char * key, const char * value) = 0;
	void virtual save(FILEHANDLE outputFile){}
	FILEHANDLE readToSectionStart(FILEHANDLE file, std::string name);
	void virtual handleEvent(Event ev) {}
	bool virtual handleEventBlocking(Event ev) { handleEvent(ev); return false; }
	void virtual SimulationStart() {}
	void virtual SimulationEnd() {}
	void virtual PreStep(double simt, double simdt, double mjd) {}
	void virtual PostStep(double simt, double simdt, double mjd) {}
	void virtual FocusChanged(OBJHANDLE old_focus, OBJHANDLE new_focus) {}
};

#endif