#ifndef SIMPIT_PANEL_MOUSE_EVENT
#define SIMPIT_PANEL_MOUSE_EVENT

class PanelMouseEvent
{
public:
	PanelMouseEvent() : mx(0), my(0), mouseEvent(0) {}
	PanelMouseEvent(int _mx, int _my, int _mouseEvent) : mx(_mx), my(_my), mouseEvent(_mouseEvent) {}
	int mx, my, mouseEvent;
};

#endif