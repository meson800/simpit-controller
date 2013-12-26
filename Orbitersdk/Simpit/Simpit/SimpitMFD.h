//Copyright (c) 2013 Christopher Johnstone(meson800)
//The MIT License - See ../../../LICENSE for more info

#ifndef SIMPIT_MFD
#define SIMPIT_MFD

#include <map>
#include <Windows.h>

#include "resource.h"
#include "MFDWindow.h"
#include "orbitersdk.h"
#include "MFDAPI.h"
#include "Output.h"
#include "Event.h"



#include "HelperDLL.h"

class SimpitMFD : public Output
{
public:
	SimpitMFD(HINSTANCE hDLL);
	~SimpitMFD();
	void load(const char * key, const char * value);
	void save(FILEHANDLE outputFile) {}
	void handleEvent(Event ev);
	void SimulationStart();
	void SimulationEnd() {}

private:
	HINSTANCE moduleHandle;
	RECT mfdPos;
	MFDWindow * window;
	int mfdRegion [4];
	std::map<Event,std::pair<int,int>> buttonMapping;
	bool hasRegion;

	static int convertToButtonClass[15];
};

#endif