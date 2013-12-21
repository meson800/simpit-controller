//Copyright (c) 2013 Christopher Johnstone(meson800)
//The MIT License - See ../../../LICENSE for more info

#ifndef KEY_OUTPUT
#define KEY_OUTPUT

#include <map>
#include <string>
#include <Windows.h>
#include <OrbiterAPI.h>

#include "Output.h"
#include "Event.h"

class KeyOutput : public Output
{
public:
	KeyOutput() : Output() {}
	void load(const char * key, const char * value);
	void handleEvent(Event ev);

private:
	void SendString(const char * string, DWORD dwFlags);
	void SendStringAuto(const char * string);

	//pair is between vesselClass and keys
	std::map<Event,std::pair<std::string, std::string>> outputs;

};

#endif