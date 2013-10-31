#ifndef THREAD_SAFE_OUTPUT
#define THREAD_SAFE_OUTPUT

#include "Output.h"
#include "Event.h"

#include <queue>
#include <Windows.h>


class ThreadSafeOutput : public Output
{
public:
	ThreadSafeOutput(boost::function<void (Event)> _handle);
	~ThreadSafeOutput();
	void handleEvent(Event ev);
	void virtual threadSafeHandleEvent(Event ev) {}
	void PostStep(double simt, double simdt, double mjd);

private:
	//our queue and CRITIAL_SECTION to make sure orbiter doesn't blow up
	std::queue<Event> queuedEvents;
	CRITICAL_SECTION ourCritSection;
};

#endif