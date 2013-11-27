#ifndef TIME_BASED_INPUT
#define TIME_BASED_INPUT

#include <vector>
#include <ctime>

#include "Input.h"
#include "Event.h"

#include "SimpitObserver.h"

struct TimeSpec
{
	TimeSpec(int _type, double dt,Event _ev) : type(_type), time(dt), eventToFire(_ev) {}
	int type;	//type 0 = sim start, type 1 = sim time interval, type 2 = actual interval	
	double time;
	Event eventToFire;
};


class TimeBasedInput : public Input
{
public:
	TimeBasedInput () {}
	void load (FILEHANDLE inputFile);
	void PostStep(double simt, double simdt, double mjd);

private:
	vector<TimeSpec> inputs;
};


#endif