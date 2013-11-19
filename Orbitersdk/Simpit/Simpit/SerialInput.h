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
	void load (FILEHANDLE inputFile);
	void save(FILEHANDLE outputFile) {}
	void readSerialThread();

private:
	Serial serial;
	std::string buffer;
	char formatString [255];
	bool disconnect;
};

#endif