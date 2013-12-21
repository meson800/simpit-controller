//Copyright (c) 2013 Christopher Johnstone
//The MIT License - See ../../../LICENSE for more info

#define STRICT 1
#define ORBITER_MODULE
#include "Orbitersdk.h"
#include "Windows.h"


#include <Windows.h>


#include "MFD_Stuff.h"
HINSTANCE hDLL;

#include "SimpitObserver.h"
#include "SimpitManager.h"

DLLCLBK void InitModule (HINSTANCE hModule)
{
	 

	HINSTANCE hDLL = hModule;
	g_hInst = hDLL; // remember the instance handle
	
	//init the MFD stuff
	InitMFD(hDLL);

	//set the manager up so stuff can hook
	SimpitManager * manager = new SimpitManager(hDLL);
	SimpitObserver::setUpManager(manager);
	//register module
	oapiRegisterModule(manager);

}

