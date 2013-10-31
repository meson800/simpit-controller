#include "ExternalOutput.h"
void ExternalOutput::load(FILEHANDLE inputFile)
{
	char *line;
	while (oapiReadScenario_nextline(inputFile,line))
	{
		if (line[0] != ';')
		{
			Event thisEvent;
			programInfo thisInfo;
			if (sscanf(line,"%i,%i,\"%254[^\"]\",\"%254[^\"]\"",&(thisEvent.id),&(thisEvent.state),&(thisInfo.name),&(thisInfo.args)) == 4)
			{
				eventMapping[new Event(thisEvent)] = thisInfo;
			}
			
		}
		
	}
}

void ExternalOutput::handleEvent(Event ev)
{
	//check to see if it is even in the map
	if (eventMapping.count(&ev))
	{
	}


}