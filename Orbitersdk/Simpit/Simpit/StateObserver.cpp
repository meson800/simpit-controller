//Copyright (c) 2013 Christopher Johnstone(meson800)
//The MIT License - See ../../../LICENSE for more info

#include "StateObserver.h"
StateSaver * StateObserver::saver = 0;

void opcLoadState(FILEHANDLE scn)
{
	if (StateObserver::saver != 0)
		StateObserver::saver->loadScenarioState(scn);
}

void opcSaveState(FILEHANDLE scn)
{
	if (StateObserver::saver != 0)
		StateObserver::saver->saveScenarioState(scn);
}