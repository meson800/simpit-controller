//Copyright (c) 2013 Christopher Johnstone(meson800)
//The MIT License - See ../../../LICENSE for more info

#ifndef HOOK_OBSERVER
#define HOOK_OBSERVER

#include "PanelClickRecorderOutput.h"
class PanelClickRecorderOutput;


extern class HookObserver
{
public:
	HookObserver() {}
	void h_handlePanelMouseEvent(int id, int ev, int mx, int my);
	void setUpReciever(PanelClickRecorderOutput * _callbackClass);
private:
	PanelClickRecorderOutput * callbackClass;
} observer;

#endif