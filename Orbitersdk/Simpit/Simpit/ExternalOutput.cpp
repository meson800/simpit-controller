//Copyright (c) 2013 Christopher Johnstone(meson800)
//The MIT License - See ../../../LICENSE for more info

#include "ExternalOutput.h"
void ExternalOutput::load(const char * key, const char * value)
{
	if (strcmp(key, "output") == 0)
	{
		Event thisEvent;
		programInfo thisInfo;
		if (sscanf(value, "%i %i \"%254[^\"]\" \"%254[^\"]\"", &(thisEvent.id), &(thisEvent.state), &(thisInfo.name), &(thisInfo.args)) == 4)
		{
			eventMapping[Event(thisEvent)] = thisInfo;
		}
	}

}

void ExternalOutput::handleEvent(Event ev)
{
	//check to see if it is even in the map
	if (eventMapping.count(ev))
	{
		STARTUPINFO         siStartupInfo;
		PROCESS_INFORMATION piProcessInfo;

		memset(&siStartupInfo, 0, sizeof(siStartupInfo));
		memset(&piProcessInfo, 0, sizeof(piProcessInfo));

		siStartupInfo.cb = sizeof(siStartupInfo);

		//run program name and args through MacroExpander
		std::string name = eventMapping[ev].name;
		std::string args = eventMapping[ev].args;

		//insert space into args
		args.insert(args.begin(), ' ');

		MacroExpander::expandString(name);
		MacroExpander::expandString(args);

		CreateProcess((char*)name.c_str(),     // Application name
                     (char*)args.c_str(),                 // Application arguments
                     0,0,FALSE,CREATE_DEFAULT_ERROR_MODE,0,0,&siStartupInfo,&piProcessInfo);
	}


}