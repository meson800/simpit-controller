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