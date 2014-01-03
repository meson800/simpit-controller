//Code used with permission from Face (http://orbiter-forum.com/member.php?u=293)
//Download Face's code from http://www.snoopie.at/face/omp/download/OrbiterHooking.zip
//See http://orbiter-forum.com/showthread.php?p=338410&postcount=2 for more info

//Modifications to Face's code under Copyright (c) 2013 Christopher Johnstone(meson800)
//The MIT License - See ../../../LICENSE for more info

// VesselHook.h: interface for the VesselHook class.
//
//////////////////////////////////////////////////////////////////////

#include <cstdio>
#define EVENTLOGFILE		"Modules\\Plugin\\Events.log"

#if !defined(AFX_VESSELHOOK_H__91C69961_7CB8_11DB_BD29_0002442A51E7__INCLUDED_)
#define AFX_VESSELHOOK_H__91C69961_7CB8_11DB_BD29_0002442A51E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Queue;
class HookMethods;
class VesselHook
{
public:
	// Constructor	
	VesselHook ();
	int Link (LPDWORD *lpVtabl);
	int Unlink();
	DWORD *Vtabl;
	int VesselCount;
		
private:	
	LPDWORD pVtabl;
	int hookVtable(bool on);	
};

static Queue *HookQueue=0;
static FILE *EventLogFile;
static HookMethods *HookMethodObject=0;
static unsigned char HookTableSize=254;
static int VesselTableSize=-2;
static DWORD HookTable[128];
static VesselHook* VesselTable[128];
static DWORD VesselInstanceTable[16384];
static bool HookEnabled=true;
static bool EventsEnabled=false;
int InstallVesselHook(VESSEL2 *link);
int registerVesselInstance(VESSEL2 *link);
int RemoveVesselHook(VESSEL2 *link);
int unregisterVesselInstance(VESSEL2 *link);
LPDWORD *GetOriginalVtable(LPDWORD *me, bool &hooked);
bool hookVesselInternal(unsigned char pos, DWORD vTab, VESSEL2 *link);
bool unhookVesselInternal(unsigned char pos);
void CleanUpHooking();
FILE *GetEventLogFile();
Queue *GetEventQueue();
void SetHookEnabled(bool enabled);
void SetEventsEnabled(bool enabled);
bool GetEventsEnabled();

#endif // !defined(AFX_VESSELHOOK_H__91C69961_7CB8_11DB_BD29_0002442A51E7__INCLUDED_)
