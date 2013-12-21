//Copyright (c) 2013 Christopher Johnstone
//The MIT License - See ../../../LICENSE for more info

#ifndef SIMPIT_SERIAL_INPUT
#define SIMPIT_SERIAL_INPUT

#include <string>
#include <Windows.h>

#include "SimpitObserver.h"
#include "Input.h"
#include "Serial.h"

//use std::thread

DWORD WINAPI SerialThreadFunction( LPVOID lpParam );

class SerialInput : public Input
{
public:
	SerialInput() : serial("COM3") {}
	~SerialInput();
	void load (const char * key, const char * value);
	void save(FILEHANDLE outputFile) {}
	void readSerialThread();

private:
	Serial serial;
	std::string buffer;
	char formatString [256];
	bool disconnect;
};

#endif