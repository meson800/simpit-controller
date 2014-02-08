//Copyright (c) 2013 Christopher Johnstone(meson800)
//The MIT License - See ../../../LICENSE for more info

#ifndef MACRO_EXPANDER
#define MACRO_EXPANDER

#include "Orbitersdk.h"
#include "OrbiterAPI.h"

#include <string>
#include <sstream>


class MacroExpander
{
public:
	static void expandString(std::string& string);

private:
	static std::string macroToText(std::string macro);
	static int doubleToDecimalInt(double value, int decimalPlaces);

};

#endif