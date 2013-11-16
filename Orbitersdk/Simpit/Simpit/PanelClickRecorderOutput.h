#ifndef PANEL_CLICK_RECORDER_OUTPUT
#define PANEL_CLICK_RECORDER_OUTPUT

#include <queue>
#include <string.h>

#include "HookObserver.h"
#include "PanelMouseEvent.h"
#include "Output.h"
#include "OrbiterAPI.h"
#include "Orbitersdk.h"
#include "VesselHook.h"
#include "HookMethods.h"


class PanelClickRecorderOutput : public Output
{
public:
	PanelClickRecorderOutput(boost::function<void (Event)> _handle) :  Output(_handle) {handleEventFunc = _handle;}
	void load(FILEHANDLE inputFile);
	void save(FILEHANDLE outputFile) {}
	void SimulationStart();
	void SimulationEnd();
	void FocusChanged(OBJHANDLE old_focus, OBJHANDLE new_focus);
	void handlePanelMouseEvent(int id, int ev, int mx, int my);
	void handleEvent(Event ev);




private:
	std::queue<PanelMouseEvent*> recordingQueue;
	char logName [256];
	char recordLogName [256];
	char vesselName[255];
	bool record;
	int currentUserDefId;
};

#endif