#ifndef PANEL_CLICK_RECORDER_OUTPUT
#define PANEL_CLICK_RECORDER_OUTPUT

#include "Output.h"
#include "OrbiterAPI.h"
#include "Orbitersdk.h"
#include "VesselHook.h"


class PanelClickRecorderOutput : public Output
{
public:
	PanelClickRecorderOutput(boost::function<void (Event)> _handle) : Output(_handle) {handleEventFunc = _handle;}
	void load(FILEHANDLE inputFile);
	void save(FILEHANDLE outputFile) {}
	void SimulationStart();
	void SimulationEnd();
	void FocusChanged(OBJHANDLE old_focus, OBJHANDLE new_focus);
	void handleEvent(Event ev);



private:
	char vesselName[255];
	bool record;
};

#endif