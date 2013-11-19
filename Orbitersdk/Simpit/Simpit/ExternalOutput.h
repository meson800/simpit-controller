#ifndef EXTERNAL_OUTPUT_HEADER
#define EXTERNAL_OUTPUT_HEADER

#include <map>

#include "Event.h"
#include "Output.h"

struct programInfo
{
	char name [255];
	char args [255];
};

class ExternalOutput : public Output
{
public:
	ExternalOutput(){}
	void load(FILEHANDLE inputFile);
	void save(FILEHANDLE outputFile) {}
	void handleEvent(Event ev);

private:
	std::map<Event *,programInfo> eventMapping;
};

#endif