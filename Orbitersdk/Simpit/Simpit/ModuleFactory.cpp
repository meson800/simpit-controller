#include "ModuleFactory.h"

void ModuleFactory::createModules(vector<IO *>& moduleVector, HINSTANCE hDLL)
{
	FILEHANDLE configFile = oapiOpenFile("simpit_config.cfg", FILE_IN, CONFIG);
	char *moduleName;
	while (oapiReadScenario_nextline(configFile, moduleName))
	{
		//when we haven't reached an EOF, then this must be a module name;
		//ignore comments
		if (strcmp(moduleName, "") != 0)
		{
			if (strcmp(moduleName, "BEGIN PANEL_EVENT_OUTPUT") == 0)
				moduleVector.push_back(new PanelEventOutput());
			else if (strcmp(moduleName, "BEGIN SERIAL_INPUT") == 0)
				moduleVector.push_back(new SerialInput());
			else if (strcmp(moduleName, "BEGIN PANEL_CLICK_RECORDER") == 0)
				moduleVector.push_back(new PanelClickRecorderOutput());
			else if (strcmp(moduleName, "BEGIN SIMPIT_MFD") == 0)
				moduleVector.push_back(new SimpitMFD(hDLL));
			else if (strcmp(moduleName, "BEGIN EXTERNAL_OUTPUT") == 0)
				moduleVector.push_back(new ExternalOutput());
			else if (strcmp(moduleName, "BEGIN TIME_BASED_INPUT") == 0)
				moduleVector.push_back(new TimeBasedInput());

			//now give it the file to load
			moduleVector.back()->load(configFile);
		}
	}
}