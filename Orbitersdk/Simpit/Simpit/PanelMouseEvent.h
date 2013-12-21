//Copyright (c) 2013 Christopher Johnstone(meson800)
//The MIT License - See ../../../LICENSE for more info

#ifndef SIMPIT_PANEL_MOUSE_EVENT
#define SIMPIT_PANEL_MOUSE_EVENT

class PanelMouseEvent
{
public:
	PanelMouseEvent() : id(0),mx(0), my(0), mouseEvent(0) {}
	PanelMouseEvent(int _id, int _ev, int _mx, int _my) : id(_id), mouseEvent(_ev), mx(_mx), my(_my) {}
	PanelMouseEvent(int _mx, int _my, int _mouseEvent) : mx(_mx), my(_my), mouseEvent(_mouseEvent) {}
	int mx, my, mouseEvent, id;
};

#endif