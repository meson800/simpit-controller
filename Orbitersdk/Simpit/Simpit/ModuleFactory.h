#ifndef MODULE_FACTORY
#define MODULE_FACTORY

#include <OrbiterAPI.h>
#include <Orbitersdk.h>

#include "IO.h"

#include "SerialInput.h"
#include "TimeBasedInput.h"
#include "SimpitMFD.h"
#include "ExternalOutput.h"
#include "PanelClickRecorderOutput.h"
#include "PanelEventOutput.h"

class ModuleFactory
{
public:
	void createModules(vector<IO *>& moduleVector, HINSTANCE hDLL);
};

#endif