//Copyright (c) 2013 Christopher Johnstone
//The MIT License - See ../../../LICENSE for more info

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