#ifndef SIMPIT_INPUT
#define SIMPIT_INPUT

#include "IO.h"

class Input : public IO
{
public:
	Input(boost::function<void (Event)> _handle) : IO(_handle) {handleEventFunc = _handle;}
	void handleEvent(Event ev) {}
};

#endif