#define STRICT 1
#define ORBITER_MODULE
#include "Orbitersdk.h"
#include "Windows.h"


#include <Windows.h>

#include "Log.h"
#include "MFD_Stuff.h"
HINSTANCE hDLL;

#include "SimpitObserver.h"
#include "SimpitManager.h"

DLLCLBK void InitModule (HINSTANCE hModule)
{
	 
	//start logging
	Log::initLogging();

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

DLLCLBK void ExitModule(HINSTANCE hModule)
{
	//shutdown logging
	Log::shutdownLogging();

	//shutdown the MFD stuff
	ShutdownMFD(hModule);
}

