//Copyright (c) 2013 Christopher Johnstone(meson800)
//The MIT License - See ../../../LICENSE for more info

#include "MacroExpander.h"

void MacroExpander::expandString(std::string& string)
{
	//loop while we still have macros (defined by angle brackets)
	while (string.find(">") != std::string::npos)
	{
		int firstPos, secondPos, length;
		firstPos = string.find_first_of("<");
		secondPos = string.find_first_of(">");
		length = secondPos - firstPos + 1;

		//check that we found them
		if (firstPos != -1 && secondPos != -1)
		{
			string.replace(firstPos, length, macroToText(string.substr(firstPos, length)));
		}
	}
}

std::string MacroExpander::macroToText(std::string macro)
{
	VESSEL * focusVessel = oapiGetFocusInterface();
	//format is <name option i decimalPlaces>
	double value;

	//get macro name, id, and possibly int
	char name[256];
	int option;
	int decimalPlaces;

	int numArguments = sscanf_s(macro.c_str(),"<%255s %i i %i>", name, &option, &decimalPlaces);
	std::string type_name = name;

	//switch different macros
	if (type_name.compare("fuel_percent") == 0)
	{
		PROPELLANT_HANDLE fuel_handle = focusVessel->GetPropellantHandleByIndex(option);
		value = oapiGetPropellantMass(fuel_handle) / oapiGetPropellantMaxMass(fuel_handle);
	}
	else if (type_name.compare("fuel_mass") == 0)
	{
		if (option == -1)
		{
			value = focusVessel->GetTotalPropellantMass();
		}
		else
		{
			PROPELLANT_HANDLE fuel_handle = focusVessel->GetPropellantHandleByIndex(option);
			value = oapiGetPropellantMass(fuel_handle);
		}

	}

	std::ostringstream toStringConverter;
	if (numArguments >= 3)
	{
		//convert value to integer
		toStringConverter << doubleToDecimalInt(value, decimalPlaces);
	}
	else
	{
		//just return the double
		toStringConverter << value;
	}
	return toStringConverter.str();
}

int MacroExpander::doubleToDecimalInt(double value, int decimalPlaces)
{
	return (int)(value * pow((double)10,(double)decimalPlaces));
}