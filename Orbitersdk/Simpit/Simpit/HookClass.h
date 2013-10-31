#include "vhl\vhl.h"
#include "OrbiterAPI.h"
#include "Orbitersdk.h"
#include <string>

class HookClass : public VHL_interface
{
public:
	void init(FILEHANDLE logFile) {file = logFile; oapiWriteLine(file,"Vessel Mouse Event Recorder Started");}
	void stop() { oapiCloseFile(file,FILE_APP);}
	void on_clbkPanelMouseEvent ( VESSEL2* vess, int id, int event, int mx, int my )
	{
		std::string result;
		result += id;
		result += " ";
		result += event;
		result += " ";
		result += mx;
		result += " ";
		result += my;
		oapiWriteLine(file,(char*)result.c_str());
	}

private:
	FILEHANDLE file;
		


};