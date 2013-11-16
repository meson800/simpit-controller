#include "HookObserver.h"

HookObserver observer;

void HookObserver::h_handlePanelMouseEvent(int id, int ev, int mx, int my)
{
	if (callbackClass)
		callbackClass->handlePanelMouseEvent(id,ev,mx,my);
}

void HookObserver::setUpReciever(PanelClickRecorderOutput * _callbackClass)
{
	callbackClass = _callbackClass;
}