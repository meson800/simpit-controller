#include "StateSaver.h"

void StateSaver::load(const char * key, const char * value)
{
	//load ranges
	if (strcmp(key, "range") == 0)
	{
		int first, second;
		if (sscanf(value, " %i %i", &first, &second) == 2)
			ranges.push_back(std::make_pair(first, second));
	}
	//load mapping
	if (strcmp(key, "mapping") == 0)
	{
		int map_key;
		char map_value [256];
		if (sscanf(value, " %i %s", &map_key, map_value) == 2)
			eventToNameMapping[map_key] = std::string(map_value);
	}
}

void StateSaver::loadScenarioState(FILEHANDLE scenario)
{
	char * line;
	while (oapiReadScenario_nextline(scenario, line))
	{
		//load the recorded event
		int ev_id, ev_state;
		if (sscanf(line, "%i %i", &ev_id, &ev_state) == 2)
			recordedEvents[ev_id] = ev_state;
	}
}

void StateSaver::saveScenarioState(FILEHANDLE scenario)
{
	for (std::map<int, int>::iterator it = currentEvents.begin(); it != currentEvents.end(); it++)
	{
		char lineToWrite[100];
		sprintf(lineToWrite, "%i %i", it->first, it->second);
		oapiWriteLine(scenario, lineToWrite);
	}
}