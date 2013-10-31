#define STRICT 1
#define ORBITER_MODULE
#include "Orbitersdk.h"
#include "Windows.h"


#include <Windows.h>


#include "MFD_Stuff.h"
HINSTANCE hDLL;

#include "SimpitManager.h"

DLLCLBK void InitModule (HINSTANCE hModule)
{
	 

	HINSTANCE hDLL = hModule;
	g_hInst = hDLL; // remember the instance handle
	
	//init the MFD stuff
	InitMFD(hDLL);

	//register module
	oapiRegisterModule(new SimpitManager(hDLL));

}

