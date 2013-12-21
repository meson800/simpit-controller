//Copyright (c) 2013 Christopher Johnstone(meson800)
//The MIT License - See ../../../LICENSE for more info

#ifndef MODULE_FACTORY
#define MODULE_FACTORY

#include <OrbiterAPI.h>
#include <Orbitersdk.h>
#include <string>

#include "StateObserver.h"

#include "IO.h"

#include "SerialInput.h"
#include "TimeBasedInput.h"
#include "SimpitMFD.h"
#include "ExternalOutput.h"
#include "PanelClickRecorderOutput.h"
#include "PanelEventOutput.h"
#include "KeyOutput.h"
#include "StateSaver.h"

class ModuleFactory
{
public:
	//creates all of the modules into the vector
	static void createModules(vector<IO *>& moduleVector, HINSTANCE hDLL);
private:
	//inside each module's block of configuration, it calls each module's load function with
	//the key value pair.  This seperates the loading code from each of the modules
	static void loadModuleFromFile(IO * module, FILEHANDLE configFile);
};

#endif