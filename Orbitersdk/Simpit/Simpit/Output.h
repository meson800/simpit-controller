#ifndef SIMPIT_OUTPUT
#define SIMPIT_OUTPUT

#include "IO.h"

class IO;

class Output : public IO
{
public:
	Output(boost::function<void (Event)> _handle) : IO(_handle) {handleEventFunc = _handle;}

};
//Include user definitions, switch state 1/0 and where it should target
#endif