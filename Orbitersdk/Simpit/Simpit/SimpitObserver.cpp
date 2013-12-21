//Copyright (c) 2013 Christopher Johnstone
//The MIT License - See ../../../LICENSE for more info

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