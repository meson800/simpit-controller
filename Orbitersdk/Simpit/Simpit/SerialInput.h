#ifndef SIMPIT_SERIAL_INPUT
#define SIMPIT_SERIAL_INPUT

#include <string>
#include <boost/thread.hpp>

#include "SimpitObserver.h"
#include "Input.h"
#include "Serial.h"



class SerialInput : public Input
{
public:
	SerialInput() : serial("COM3") {}
	~SerialInput();
	void load (FILEHANDLE inputFile);
	void save(FILEHANDLE outputFile) {}

private:
	Serial serial;
	std::string buffer;
	char formatString [255];
	void readSerialThread();
	bool disconnect;
};

#endif