#include "ThreadSafeOutput.h"

ThreadSafeOutput::ThreadSafeOutput()
{
	//set up critical section for below
	InitializeCriticalSection(&ourCritSection);
}

ThreadSafeOutput::~ThreadSafeOutput()
{
	DeleteCriticalSection(&ourCritSection);
}

void ThreadSafeOutput::handleEvent(Event ev)
{
	//push this to our queue to get processed at the next PostStep so Orbiter doesn't explode from being thread-unsafe

	//BEGIN CRITICAL SECTION
	EnterCriticalSection(&ourCritSection);

	queuedEvents.push(ev);

	LeaveCriticalSection(&ourCritSection);
	//END CRITICAL SECTION
}

void ThreadSafeOutput::PostStep(double simt, double simdt, double mjd)
{
	EnterCriticalSection(&ourCritSection);

	while(!queuedEvents.empty())
	{
		threadSafeHandleEvent(queuedEvents.front());
		queuedEvents.pop();
	}

	LeaveCriticalSection(&ourCritSection);
}