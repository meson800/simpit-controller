//Code used with permission from Face (http://orbiter-forum.com/member.php?u=293)
//See http://orbiter-forum.com/showthread.php?p=338410&postcount=2 for more info

//Modifications to Face's code under Copyright (c) 2013 Christopher Johnstone
//The MIT License - See ../../../LICENSE for more info

// HookMethods.cpp: implementation of the HookMethods class.
//
//////////////////////////////////////////////////////////////////////
#pragma unmanaged
#include "orbitersdk.h"
#include "VesselHook.h"
#include "HookMethods.h"
#include "Queue.h"
#include <cstdio>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

HookMethods::HookMethods():VESSEL2(0,0)
{
}

/*HookMethods::~HookMethods()
{

}*/

#define PRETASK		bool hooked;											\
					LPDWORD *me=GetOriginalVtable((LPDWORD *)this, hooked);	\
					if (hooked)												\
					{														\
						FILE *l=GetEventLogFile();							\
						Queue *q=GetEventQueue();							\
						union Hook_Event *event=new union Hook_Event					

#define POSTTASK		q->Enqueue(event);									\
						fflush(l);											\
					}														\
					if (me!=0)

#define PRETASK2	bool hooked;											\
					LPDWORD *me=GetOriginalVtable((LPDWORD *)this, hooked);	\
					if (me!=0)

#define POSTTASK2	if (hooked)												\
					{														\
						FILE *l=GetEventLogFile();							\
						Queue *q=GetEventQueue();							\
						union Hook_Event *event=new union Hook_Event

#define POSTPOST2		q->Enqueue(event);									\
						fflush(l);											\
					}
					

// Callback functions
/*void HookMethods::clbkSetClassCaps (FILEHANDLE cfg){}
void HookMethods::clbkSaveState (FILEHANDLE scn){}
void HookMethods::clbkLoadStateEx (FILEHANDLE scn, void *status){}
void HookMethods::clbkSetStateEx (const void *status){}
void HookMethods::clbkPostCreation (){}
void HookMethods::clbkFocusChanged (bool getfocus, OBJHANDLE hNewVessel, OBJHANDLE hOldVessel){}
void HookMethods::clbkPreStep (double simt, double simdt, double mjd){}
void HookMethods::clbkPostStep (double simt, double simdt, double mjd){}
bool HookMethods::clbkPlaybackEvent (double simt, double event_t, const char *event_type, const char *event)
{
	return false;
}
void HookMethods::clbkVisualCreated (VISHANDLE vis, int refcount){}
void HookMethods::clbkVisualDestroyed (VISHANDLE vis, int refcount){}
void HookMethods::clbkDrawHUD (int mode, const HUDPAINTSPEC *hps, HDC hDC){}
*/
void HookMethods::clbkRCSMode (int mode)
{
	PRETASK;
	event->Mode.flag=0x0C | ((mode & 0x03) << 6);
	event->Mode.vessel=this->GetHandle();
	fprintf(l, "%d[%s]RCS %d\n", GetTickCount(), this->GetName(), mode);
	POSTTASK
	{
		_asm
		{		
			mov         eax,mode
			push        eax
			mov         eax,this
			mov         edx,dword ptr [eax]
			mov         eax,me
			mov         ecx,dword ptr [this]
			call        dword ptr [eax+30h]		
		}
	}
	else sprintf(oapiDebugString(), "HOOKING ERROR");
}

void HookMethods::clbkADCtrlMode (DWORD mode)
{
	PRETASK;
	event->Mode.flag=0x0D | (((unsigned char)mode & 0x07) << 5);
	event->Mode.vessel=this->GetHandle();
	fprintf(l, "%d[%s]ADC %d\n", GetTickCount(), this->GetName(), mode);
	POSTTASK
	{
		_asm
		{		
			mov         eax,mode
			push        eax
			mov         eax,this
			mov         edx,dword ptr [eax]
			mov         eax,me
			mov         ecx,dword ptr [this]
			call        dword ptr [eax+34h]		
		}
	}
	else sprintf(oapiDebugString(), "HOOKING ERROR");
}

void HookMethods::clbkHUDMode (int mode)
{
	PRETASK;
	event->Mode.flag=0x0E | ((mode & 0x03) << 6);
	event->Mode.vessel=this->GetHandle();
	fprintf(l, "%d[%s]HUD %d\n", GetTickCount(), this->GetName(), mode);
	POSTTASK
	{
		_asm
		{		
			mov         eax,mode
			push        eax
			mov         eax,this
			mov         edx,dword ptr [eax]
			mov         eax,me
			mov         ecx,dword ptr [this]
			call        dword ptr [eax+38h]		
		}
	}
	else sprintf(oapiDebugString(), "HOOKING ERROR");
}

void HookMethods::clbkMFDMode (int mfd, int mode)
{
	PRETASK;
	event->Mode.flag=0x0F;
	event->Mode.vessel=this->GetHandle();
	event->Mode.idx=mode;
	event->Mode.md=mfd;
	fprintf(l, "%d[%s]MFD(%d) %d\n", GetTickCount(), this->GetName(), mfd, mode);
	POSTTASK
	{
		_asm
		{		
			mov         eax,mode
			push        eax
			mov         eax,mfd
			push        eax
			mov         eax,this
			mov         edx,dword ptr [eax]
			mov         eax,me
			mov         ecx,dword ptr [this]
			call        dword ptr [eax+3Ch]		
		}
	}
	else sprintf(oapiDebugString(), "HOOKING ERROR");
}

void HookMethods::clbkNavMode (int mode, bool active)
{
	PRETASK;
	event->Mode.flag=0x10 | (active?0x80:0x00);
	event->Mode.vessel=this->GetHandle();
	event->Mode.md=mode;
	fprintf(l, "%d[%s]NAV(%d) %d\n", GetTickCount(), this->GetName(), mode, active);
	POSTTASK
	{
		_asm
		{		
			mov         al,active
			push        eax
			mov         eax,mode
			push        eax
			mov         eax,this
			mov         edx,dword ptr [eax]
			mov         eax,me
			mov         ecx,dword ptr [this]
			call        dword ptr [eax+40h]		
		}	
	}
	else sprintf(oapiDebugString(), "HOOKING ERROR");
}

void HookMethods::clbkDockEvent (int dock, OBJHANDLE mate)
{
	PRETASK;
	event->Mode.flag=0x11 | (mate!=0?0x80:0x00);
	event->Mode.vessel=this->GetHandle();
	event->Mode.idx=(unsigned short int)dock;
	fprintf(l, "%d[%s]DCK(%d) %p\n", GetTickCount(), this->GetName(), dock, mate);
	POSTTASK
	{
		_asm
		{		
			mov         eax,mate
			push        eax
			mov         eax,dock
			push        eax
			mov         eax,this
			mov         edx,dword ptr [eax]
			mov         eax,me
			mov         ecx,dword ptr [this]
			call        dword ptr [eax+44h]		
		}
	}
	else sprintf(oapiDebugString(), "HOOKING ERROR");
}

/*void HookMethods::clbkAnimate (double simt){}
int  HookMethods::clbkConsumeDirectKey (char *keystate)
{
	return 0;
}*/
int  HookMethods::clbkConsumeBufferedKey (DWORD key, bool down, char *keystate)
{
	int retvalue=0;
	PRETASK2
	{
		_asm
		{
			mov         eax,keystate
			push        eax
			mov         al,down
			push        eax
			mov         eax,key
			push        eax
			mov         eax,this
			mov         edx,dword ptr [eax]
			mov         eax,me
			mov         ecx,dword ptr [this]
			call        dword ptr [eax+50h]
			mov			retvalue, eax
		}
		if (retvalue!=0)
		{
			POSTTASK2;
			event->Key.flag=0x14 | (down?0x80:0x00);
			event->Key.vessel=this->GetHandle();
			event->Key.key=(char)key;
			char state=	KEYMOD_LSHIFT(keystate)		?0x01:0;
			state|=		KEYMOD_RSHIFT(keystate)		?0x02:0;
			state|=		KEYMOD_LCONTROL(keystate)	?0x04:0;
			state|=		KEYMOD_RCONTROL(keystate)	?0x08:0;
			state|=		KEYMOD_LALT(keystate)		?0x10:0;
			state|=		KEYMOD_RALT(keystate)		?0x20:0;
			event->Key.state=state;
			event->Key.mjd=oapiGetSimMJD();
			fprintf(l, "%d[%s]K(%d)%d: %X\n", GetTickCount(), this->GetName(), key, down, state);
			POSTPOST2;
		}
	}
	else sprintf(oapiDebugString(), "HOOKING ERROR");
	return retvalue;	
}
/*bool HookMethods::clbkLoadGenericCockpit ()
{
	return false;
}
bool HookMethods::clbkLoadPanel (int id)
{
	return false;
}*/
bool HookMethods::clbkPanelMouseEvent (int id, int ev, int mx, int my)
{
	observer.h_handlePanelMouseEvent(id,ev,mx,my);
	bool retvalue=true;
	PRETASK2	
	{
		_asm
		{
			mov         eax,my
			push        eax
			mov         eax,mx
			push        eax
			mov         eax,ev
			push        eax
			mov         eax,id
			push        eax
			mov         eax,this
			mov         edx,dword ptr [eax]
			mov         eax,me
			mov         ecx,dword ptr [this]
			call        dword ptr [eax+5Ch]
			mov			retvalue, al
		}
		if (retvalue)
		{
			POSTTASK2;
			event->Mouse.flag=0x17;
			event->Mouse.vessel=this->GetHandle();
			event->Mouse.id=id;
			event->Mouse.event=ev;
			event->Mouse.mx=mx;
			event->Mouse.my=my;
			event->Mouse.mjd=oapiGetSimMJD();
			fprintf(l, "%d[%s]M(%d) %d: %d %d\n", GetTickCount(), this->GetName(), ev, id, mx, my);
			POSTPOST2;
		}
	}
	else sprintf(oapiDebugString(), "HOOKING ERROR");
	return retvalue;
}
/*bool HookMethods::clbkPanelRedrawEvent (int id, int event, SURFHANDLE surf)
{
	return false;
}
bool HookMethods::clbkLoadVC (int id)
{
	return false;
}*/
bool HookMethods::clbkVCMouseEvent (int id, int ev, VECTOR3 &p)
{
	bool retvalue=true;
	PRETASK2
	{
		_asm
		{
			mov         eax,p
			push        eax
			mov         eax,ev
			push        eax
			mov         eax,id
			push        eax
			mov         eax,this
			mov         edx,dword ptr [eax]
			mov         eax,me
			mov         ecx,dword ptr [this]
			call        dword ptr [eax+68h]
			mov			retvalue, al
		}
		if (retvalue)
		{
			POSTTASK2;
			event->VC.flag=0x1A;
			event->VC.vessel=this->GetHandle();
			event->VC.id=id;
			event->VC.event=ev;
			event->VC.x=(float)p.x;
			event->VC.y=(float)p.y;
			event->VC.z=(float)p.z;
			event->VC.mjd=oapiGetSimMJD();
			fprintf(l, "%d[%s]VCM(%d) %d: %9.6f %9.6f %9.6f\n", GetTickCount(), this->GetName(), ev, id, p.x, p.y, p.z);
			POSTPOST2;
		}
	}
	else sprintf(oapiDebugString(), "HOOKING ERROR");
	return retvalue;
}
/*bool HookMethods::clbkVCRedrawEvent (int id, int event, SURFHANDLE surf)
{
	return false;
}*/