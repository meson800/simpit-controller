#ifndef SIMPIT_OBSERVER
#define SIMPIT_OBSERVER

#include "Event.h"
#include "SimpitManager.h"

class SimpitManager;

class SimpitObserver
{
public:
	static void setUpManager(SimpitManager * _manager);
	static void handleEvent(Event ev);
private:
	static SimpitManager * manager;
};


#endif