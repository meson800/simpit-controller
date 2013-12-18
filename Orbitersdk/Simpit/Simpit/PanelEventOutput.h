#ifndef SIMPIT_PANEL_EVENT_OUTPUT
#define SIMPIT_PANEL_EVENT_OUTPUT

#include "ThreadSafeOutput.h"
#include "PanelMouseEvent.h"
#include "PanelMouseId.h"

#include <map>
#include <string>
#include <queue>
#include <Windows.h>

class PanelEventOutput : public ThreadSafeOutput
{
public:
	PanelEventOutput() {}
	void load(const char * key, const char * value);
	void save(FILEHANDLE outputFile);
	void threadSafeHandleEvent(Event ev);

private:
	//our maps which store information about virtual button-event info
	std::map<int, std::map<int, PanelMouseEvent>> userDefinitions;
	std::map<int, PanelMouseId> switches;



	
	char vesselName [256];
};
#endif