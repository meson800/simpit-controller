#include "SimpitManager.h"

SimpitManager::SimpitManager(HINSTANCE hDLL) : Module(hDLL)
{
	FILEHANDLE configFile = oapiOpenFile("simpit_config.cfg",FILE_IN,CONFIG);
	char *moduleName;
	while (oapiReadScenario_nextline(configFile,moduleName))
	{
		//when we haven't reached an EOF, then this must be a module name;
		//ignore comments
		if (strcmp(moduleName,"") != 0)
		{
			if (strcmp(moduleName, "BEGIN PANEL_EVENT_OUTPUT") == 0)
				modules.push_back(new PanelEventOutput());
			else if(strcmp(moduleName, "BEGIN SERIAL_INPUT") == 0)
				modules.push_back(new SerialInput());
			else if(strcmp(moduleName, "BEGIN PANEL_CLICK_RECORDER") == 0)
				modules.push_back(new PanelClickRecorderOutput());
			else if(strcmp(moduleName, "BEGIN SIMPIT_MFD") == 0)
				modules.push_back(new SimpitMFD(hDLL));

			//now give it the file to load
			modules.back()->load(configFile);
		}
	}

}

void SimpitManager::handleEvent(Event ev)
{
	for (unsigned int i = 0; i < modules.size(); i++)
	{
		modules[i]->handleEvent(ev);
	}
}
void SimpitManager::clbkSimulationStart(RenderMode mode)
{
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