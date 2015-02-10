//Copyright (c) 2013 Christopher Johnstone(meson800)
//The MIT License - See ../../../LICENSE for more info

#ifndef SIMPIT_SERIAL_INPUT
#define SIMPIT_SERIAL_INPUT

#include <string>
#include <map>
#include <Windows.h>

#include "SimpitObserver.h"
#include "Input.h"
#include "Serial.h"

//use std::thread

DWORD WINAPI SerialThreadFunction( LPVOID lpParam );

class SerialCommunication : public Input
{
public:
	SerialCommunication() : stopSerial(false)  { InitializeCriticalSection(&critSection); formatString[0] = 0; }
	~SerialCommunication();
	void load (const char * key, const char * value);
	void SimulationStart();
	void SimulationEnd();
	void save(FILEHANDLE outputFile) {}
	void readSerialThread();
	void handleEvent(Event ev);


private:
	std::map<Event, std::string> outputEvents;
	std::map<int, int> currentEvents;
	CRITICAL_SECTION critSection;
	bool stopSerial;
	Serial * serial;
	std::string buffer;
	char formatString [256];
	char comPort [256];
	bool disconnect;
};

#endif