//Copyright (c) 2013 Christopher Johnstone(meson800)
//The MIT License - See ../../../LICENSE for more info

#include "SimpitManager.h"

SimpitManager::SimpitManager(HINSTANCE hDLL) : Module(hDLL)
{
	ModuleFactory::createModules(modules, hDLL);

}

void SimpitManager::handleEvent(Event ev)
{
	fprintf(Log::returnLogHandle(), "Captured event:id=%i\tstate=%i\n",ev.id, ev.state);
	for (unsigned int i = 0; i < modules.size(); i++)
	{
		if (modules[i]->handleEventBlocking(ev) == true)
			return;
	}
}
void SimpitManager::clbkSimulationStart(RenderMode mode)
{
	Log::println("*Simulation Start");
	for (unsigned int i = 0; i < modules.size(); i++)
	{
		modules[i]->SimulationStart();
	}
}
void SimpitManager::clbkFocusChanged(OBJHANDLE old_focus, OBJHANDLE new_focus)
{
	for (unsigned int i = 0; i < modules.size(); i++)
	{
		modules[i]->FocusChanged(old_focus,new_focus);
	}
}
void SimpitManager::clbkSimulationEnd(RenderMode mode)
{
	Log::println("*Simulation End");
	for (unsigned int i = 0; i < modules.size(); i++)
	{
		modules[i]->SimulationEnd();
	}
}

void SimpitManager::clbkPreStep(double simt, double simdt, double mjd)
{
	for (unsigned int i = 0; i < modules.size(); i++)
	{
		modules[i]->PreStep(simt,simdt,mjd);
	}
}

void SimpitManager::clbkPostStep(double simt, double simdt, double mjd)
{
	for (unsigned int i = 0; i < modules.size(); i++)
	{
		modules[i]->PostStep(simt,simdt,mjd);
	}
}