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
	void virtual load(FILEHANDLE inputFile) = 0;
	void virtual save(FILEHANDLE outputFile){}
	FILEHANDLE readToSectionStart(FILEHANDLE file, std::string name);
	void virtual handleEvent(Event ev) {}
	void virtual SimulationStart() {}
	void virtual SimulationEnd() {}
	void virtual PreStep(double simt, double simdt, double mjd) {}
	void virtual PostStep(double simt, double simdt, double mjd) {}
	void virtual FocusChanged(OBJHANDLE old_focus, OBJHANDLE new_focus) {}
};

#endif