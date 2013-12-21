//Copyright (c) 2013 Christopher Johnstone(meson800)
//The MIT License - See ../../../LICENSE for more info

#include "SimpitManager.h"

FILEHANDLE IO::readToSectionStart(FILEHANDLE file, std::string name)
{
	char * readLine;
	std::string sectionName = "BEGIN ";
	sectionName += name;
	while (oapiReadScenario_nextline(file,readLine))
	{
		if (sectionName.compare(readLine) == 0)
			return file;
	}
	return 0;
}

