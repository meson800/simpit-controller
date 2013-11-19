#include "SimpitObserver.h"

//init to NULL so we know if it is good or not
SimpitManager * SimpitObserver::manager = NULL;

void SimpitObserver::setUpManager(SimpitManager * _manager)
{
	manager = _manager;
}

void SimpitObserver::handleEvent(Event ev)
{
	if (manager)
		manager->handleEvent(ev);
}