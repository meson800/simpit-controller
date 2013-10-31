#ifndef SIMPIT_SERIAL_INPUT
#define SIMPIT_SERIAL_INPUT

#include <string>
#include <boost/thread.hpp>

#include "Input.h"
#include "Serial.h"


class SerialInput : public Input
{
public:
	SerialInput(boost::function<void (Event)> _handle) : Input(_handle), serial("COM3") {handleEventFunc = _handle;}
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