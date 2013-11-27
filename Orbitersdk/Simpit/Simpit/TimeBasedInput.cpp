#include "TimeBasedInput.h"
void TimeBasedInput::load(FILEHANDLE inputFile)
{
	char *line;
	while (oapiReadScenario_nextline(inputFile,line))
	{
		if (line[0] != ';')
		{
			int eventId, eventState;
			float dt;
			
			//read a sim start type of switch, type 0

			//format
			//SIMULATION_START eventId eventState
			if (sscanf(line,"SIMULATION_START %i %i",&eventId, &eventState) == 2)
			{
				dt = 0;
				inputs.push_back(TimeSpec(0,dt,Event(eventId,eventState)));
			}

			//type 1
			//format
			//REAL_TIME dt eventId eventState
			if (sscanf(line,"REAL_TIME %f %i %i",&dt, &eventId, &eventState) == 3)
			{
				inputs.push_back(TimeSpec(1,dt,Event(eventId,eventState)));
			}

			//type 2
			//format
			//SIM_TIME dt eventId eventState
			if (sscanf(line,"SIM_TIME %f %i %i",&dt, &eventId, &eventState) == 3)
			{
				inputs.push_back(TimeSpec(2,dt,Event(eventId,eventState)));
			}
			
		}
		
	}
}

void TimeBasedInput::SimulationStart()
{
	//handle all of the case 0 inputs
	for (unsigned int i = 0; i < inputs.size(); i++)
	{
		if(inputs[i].type == 0)
			SimpitObserver::handleEvent(inputs[i].eventToFire);
	}
}

void TimeBasedInput::PostStep(double simt, double simdt, double mjd)
{
	//now run through all of the switches.  If they are type 1, use the simt value
	//If they are type 2, use the "time" function

	//in all, if the difference between simt/time is greater than dt, fire the event
	for (unsigned int i = 0; i < inputs.size(); i++)
	{
		switch (inputs[i].type)
		{
		case 0:
			//do nothing, we already fired the event
			break;
		case 2:
			//use simt and abs, as we could have gone backwards in time beacuse of scenario editor
			if (abs(simt - inputs[i].time) > inputs[i].dt)
			{
				//fire the event
				SimpitObserver::handleEvent(inputs[i].eventToFire);
				//update the time variable
				inputs[i].time = simt;
			}
			break;
		case 1:
			//use time and abs, just in case they set their clock back
			if (abs(time(NULL) - inputs[i].time) > inputs[i].dt)
			{
				//fire the event
				SimpitObserver::handleEvent(inputs[i].eventToFire);
				//update the time variable
				inputs[i].time = (double)time(NULL);
			}
			break;
		default:
			break;
		}
	}
}