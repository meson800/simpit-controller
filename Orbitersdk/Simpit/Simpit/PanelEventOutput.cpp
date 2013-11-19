#include "PanelEventOutput.h"


void PanelEventOutput::load(FILEHANDLE inputFile)
{
	//inputFile = this->readToSectionStart(inputFile, "PANEL_EVENT_OUTPUT");
	char *line;
	while (oapiReadScenario_nextline(inputFile,line))
	{
		if (line[0] != ';')
		{
			std::string readString = line;
			//now see if it is our vessel name, a user definition, or a event
			if (sscanf(line,"VESSEL_NAME = %s", vesselName) != 1)
			{
				//check if this is a user def
				if (sscanf(line,"%*i %*i %*i %*i %*i") == 5)
				{
					int id;
					sscanf(readString.c_str(),"%i",&id);
					readString = readString.substr(readString.find(" ") + 1);
					int newState,mx,my,mouseEvent;
					while (sscanf(readString.c_str(),"%i %i %i %i", &newState,&mx,&my,&mouseEvent) >= 4)
					{
						userDefinitions[id][newState] = PanelMouseEvent(mx,my,mouseEvent);
						for (int i = 0; i < 4; i++)
							if (readString.find(" ") != std::string::npos)
								readString = readString.substr(readString.find(" ") + 1);
					}
				}
				else
				{
					int eventId,mouseEventId,userDefNum;
					if (sscanf(line,"%i %i %i", &eventId,&userDefNum, &mouseEventId) == 3)
						switches[eventId] = PanelMouseId(mouseEventId,userDefNum);
				}
		
			}
		}
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
