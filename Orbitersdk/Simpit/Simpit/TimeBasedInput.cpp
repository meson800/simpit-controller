#include "TimeBasedInput.h"
void TimeBasedInput::load(FILEHANDLE inputFile)
{
	char *line;
	while (oapiReadScenario_nextline(inputFile,line))
	{
		if (line[0] != ';')
		{
			int eventId, eventState;
			double dt;
			
			//read a sim start type of switch, type 0

			//format
			//SIMULATION_START eventId, eventState
			if (sscanf(line,"SIMULATION_START %i %i",&eventId, &eventState) == 2)
			{
				inputs.push_back(TimeSpec(0,dt,Event(eventId,eventState)));
			}

			//type 1
			//format
			//REAL_TIME dt eventId eventState
			if (sscanf(line,"REAL_TIME %d %i %i",&dt, &eventId, &eventState) == 3)
			{
				inputs.push_back(TimeSpec(1,dt,Event(eventId,eventState)));
			}

			//type 2
			//format
			//SIM_TIME dt eventId eventState
			if (sscanf(line,"SIM_TIME %d %i %i",&dt, &eventId, &eventState) == 3)
			{
				inputs.push_back(TimeSpec(2,dt,Event(eventId,eventState)));
			}
			
		}
		
	}
}