//Code used with permission from Face (http://orbiter-forum.com/member.php?u=293)
//See http://orbiter-forum.com/showthread.php?p=338410&postcount=2 for more info

//Modifications to Face's code under Copyright (c) 2013 Christopher Johnstone(meson800)
//The MIT License - See ../../../LICENSE for more info

// HookMethods.h: interface for the HookMethods class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HOOKMETHODS_H__46970382_7FE2_11DB_BD29_0002442A51E7__INCLUDED_)
#define AFX_HOOKMETHODS_H__46970382_7FE2_11DB_BD29_0002442A51E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "HookObserver.h"

union Hook_Event
{
	struct
	{
		union
		{
			OBJHANDLE vessel;
			struct
			{
				unsigned short int ID;
				char res1;
				char res2;
			};
		};
		char flag;
		char md;
		unsigned short int idx;
	} Mode;
	struct
	{		
		union
		{
			OBJHANDLE vessel;
			struct
			{
				unsigned short int ID;
				char res1;
				char res2;
			};
		};
		char flag;
		char state;
		char key;
		char fill2;
		double mjd;
	} Key;
	struct
	{
		union
		{
			OBJHANDLE vessel;
			struct
			{
				unsigned short int ID;
				char res1;
				char res2;
			};
		};
		char flag;
		char event;
		char fill1;
		char fill2;
		int id;
		int mx;
		int my;
		int fill3;
		double mjd;
	} Mouse;
	struct
	{
		union
		{
			OBJHANDLE vessel;
			struct
			{
				unsigned short int ID;
				char res1;
				char res2;
			};
		};
		char flag;
		char event;
		char fill1;
		char fill2;
		int id;
		float x;
		float y;
		float z;
		double mjd;
	} VC;	
};

class HookMethods :VESSEL2
{
public:
	// Constructor	
	HookMethods ();	
	// Callback functions
	/*virtual void clbkSetClassCaps (FILEHANDLE cfg);
	virtual void clbkSaveState (FILEHANDLE scn);
	virtual void clbkLoadStateEx (FILEHANDLE scn, void *status);
	virtual void clbkSetStateEx (const void *status);
	virtual void clbkPostCreation ();
	virtual void clbkFocusChanged (bool getfocus, OBJHANDLE hNewVessel, OBJHANDLE hOldVessel);
	virtual void clbkPreStep (double simt, double simdt, double mjd);
	virtual void clbkPostStep (double simt, double simdt, double mjd);
	virtual bool clbkPlaybackEvent (double simt, double event_t, const char *event_type, const char *event);
	virtual void clbkVisualCreated (VISHANDLE vis, int refcount);
	virtual void clbkVisualDestroyed (VISHANDLE vis, int refcount);
	virtual void clbkDrawHUD (int mode, const HUDPAINTSPEC *hps, HDC hDC);*/
	virtual void clbkRCSMode (int mode);
	virtual void clbkADCtrlMode (DWORD mode);
	virtual void clbkHUDMode (int mode);
	virtual void clbkMFDMode (int mfd, int mode);
	virtual void clbkNavMode (int mode, bool active);
	virtual void clbkDockEvent (int dock, OBJHANDLE mate);
	/*virtual void clbkAnimate (double simt);
	virtual int  clbkConsumeDirectKey (char *keystate);*/
	virtual int  clbkConsumeBufferedKey (DWORD key, bool down, char *keystate);
	/*virtual bool clbkLoadGenericCockpit ();
	virtual bool clbkLoadPanel (int id);*/
	virtual bool clbkPanelMouseEvent (int id, int ev, int mx, int my);
	/*virtual bool clbkPanelRedrawEvent (int id, int event, SURFHANDLE surf);
	virtual bool clbkLoadVC (int id);*/
	virtual bool clbkVCMouseEvent (int id, int ev, VECTOR3 &p);
	//virtual bool clbkVCRedrawEvent (int id, int event, SURFHANDLE surf);
};

#endif // !defined(AFX_HOOKMETHODS_H__46970382_7FE2_11DB_BD29_0002442A51E7__INCLUDED_)
