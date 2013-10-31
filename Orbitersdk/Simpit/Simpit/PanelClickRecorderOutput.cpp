#include "PanelClickRecorderOutput.h"

void PanelClickRecorderOutput::load(FILEHANDLE inputFile)
{
	//inputFile = this->readToSectionStart(inputFile, "PANEL_CLICK_RECORDER");
	char *line;
	while (oapiReadScenario_nextline(inputFile,line))
	{
		if (line[0] != ';')
		{
			//now see if it is our vessel name
			if (sscanf(line,"VESSEL_NAME = %s", vesselName) == 1)
			{
				//set up hooking
				
			}
		}
	}
}

void PanelClickRecorderOutput::SimulationStart()
{
	OBJHANDLE hVessel = oapiGetVesselByName(vesselName);
	if (oapiIsVessel(hVessel))
		InstallVesselHook(&(VESSEL2)oapiGetVesselInterface(hVessel));
}

void PanelClickRecorderOutput::FocusChanged(OBJHANDLE old_focus, OBJHANDLE new_focus)
{

}

void PanelClickRecorderOutput::SimulationEnd()
{
	CleanUpHooking();
}