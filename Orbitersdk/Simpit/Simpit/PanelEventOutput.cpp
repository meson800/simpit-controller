//Copyright (c) 2013 Christopher Johnstone
//The MIT License - See ../../../LICENSE for more info

#include "PanelEventOutput.h"


void PanelEventOutput::load(const char * key, const char * value)
{
	std::string readString = value;

	if (strcmp(key, "vessel_name") == 0)
	{
		strcpy(vesselName, value);
	}
	// check if this is a user def
	else if (strcmp(key, "user_def") == 0)
	{
		int id;
		sscanf(readString.c_str(), "%i", &id);
		readString = readString.substr(readString.find(" ") + 1);
		int newState, mx, my, mouseEvent;
		while (sscanf(readString.c_str(), "%i %i %i %i", &newState, &mx, &my, &mouseEvent) >= 4)
		{
			userDefinitions[id][newState] = PanelMouseEvent(mx, my, mouseEvent);
			for (int i = 0; i < 4; i++)
			if (readString.find(" ") != std::string::npos)
				readString = readString.substr(readString.find(" ") + 1);
		}
	}
	else if (strcmp(key, "event") == 0)
	{
		int eventId,mouseEventId,userDefNum;
		if (sscanf(value,"%i %i %i", &eventId,&userDefNum, &mouseEventId) == 3)
			switches[eventId] = PanelMouseId(mouseEventId,userDefNum);
	}
}

void PanelEventOutput::save(FILEHANDLE outputFile) {}

void PanelEventOutput::threadSafeHandleEvent(Event ev)
{
	OBJHANDLE hSimVessel = oapiGetVesselByName(vesselName);
	//check to see if we even have a key with the correct ID
	if(switches.count(ev.id))
	{
		PanelMouseEvent toClick = userDefinitions[switches[ev.id].userDef][ev.state];
	
		
		if (hSimVessel != NULL)
		{
			//vessel exists, so create the interface
			VESSEL2 *simVessel = (VESSEL2 *)oapiGetVesselInterface(hSimVessel);
			//and send the event!
			simVessel->clbkPanelMouseEvent(switches[ev.id].eventId,toClick.mouseEvent,toClick.mx,toClick.my);
		}
	}

}
