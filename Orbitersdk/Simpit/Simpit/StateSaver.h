#ifndef STATE_SAVER
#define STATE_SAVER

#include <Windows.h>
#include <vector>
#include <map>
#include <string>

#include "IO.h"

class StateSaver : public IO
{
public:
	StateSaver() {}
	void load(const char * key, const char * value);
	void loadScenarioState(FILEHANDLE scenario);
	void saveScenarioState(FILEHANDLE scenario);
	bool handleEventBlocking(Event ev);

private:
	void createListbox();
	std::vector < std::pair<int, int>> ranges;
	std::map<int, int> recordedEvents;
	std::map<int, int> currentEvents;
	std::map<int, std::string> eventToNameMapping;

};

#endif