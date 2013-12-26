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

class SerialInput : public Input
{
public:
	SerialInput() : stopSerial(false)  {InitializeCriticalSection(&critSection);}
	~SerialInput();
	void load (const char * key, const char * value);
	void SimulationStart();
	void SimulationEnd();
	void save(FILEHANDLE outputFile) {}
	void readSerialThread();

private:
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