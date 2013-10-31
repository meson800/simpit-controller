#ifndef SIMPIT_MFD
#define SIMPIT_MFD

#include <map>
#include <Windows.h>
#include "MFDWindow.h"
#include "orbitersdk.h"
#include "MFDAPI.h"
#include "Output.h"
#include "Event.h"



#include "HelperDLL.h"

class SimpitMFD : public Output
{
public:
	SimpitMFD(boost::function<void (Event)> _handle, HINSTANCE hDLL);
	~SimpitMFD();
	void load(FILEHANDLE inputFile);
	void save(FILEHANDLE outputFile) {}
	void handleEvent(Event ev);
	void SimulationStart();
	void SimulationEnd() {}

private:
	HINSTANCE moduleHandle;
	RECT mfdPos;
	MFDWindow * window;
	int mfdRegion [4];
	std::map<Event *,int> buttonMapping;
	bool hasRegion;
};

#endif