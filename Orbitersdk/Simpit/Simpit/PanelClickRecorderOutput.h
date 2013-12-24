//Copyright (c) 2013 Christopher Johnstone(meson800)
//The MIT License - See ../../../LICENSE for more info

#ifndef PANEL_CLICK_RECORDER_OUTPUT
#define PANEL_CLICK_RECORDER_OUTPUT

#include <queue>
#include <string.h>
#include <string>

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
	PanelClickRecorderOutput(): hasHooked(false), record(false), currentUserDefId(0), logName("Modules\\Plugin\\SimpitRecorderLog.log"),
		recordLogName("EventRecorderOutput.log") {}
	void load(const char * key, const char * value);
	void save(FILEHANDLE outputFile) {}
	void PreStep(double simt, double simdt, double mjd);
	void SimulationEnd();
	void FocusChanged(OBJHANDLE old_focus, OBJHANDLE new_focus);
	void handlePanelMouseEvent(int id, int ev, int mx, int my);
	void handleEvent(Event ev);




private:
	std::queue<PanelMouseEvent*> recordingQueue;
	std::string logName;
	std::string recordLogName;
	std::string vesselName;
	bool record;
	bool hasHooked;
	int currentUserDefId;
};

#endif