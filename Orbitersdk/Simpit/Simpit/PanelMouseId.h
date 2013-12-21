//Copyright (c) 2013 Christopher Johnstone
//The MIT License - See ../../../LICENSE for more info

#ifndef SIMPIT_PANEL_MOUSE_ID
#define SIMPIT_PANEL_MOUSE_ID

class PanelMouseId
{
public:
	PanelMouseId() : eventId(0), userDef(0) {}
	PanelMouseId(int _eventId, int _userDef) : eventId(_eventId), userDef(_userDef) {}
	int eventId, userDef;
};

#endif