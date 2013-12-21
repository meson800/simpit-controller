//Copyright (c) 2013 Christopher Johnstone
//The MIT License - See ../../../LICENSE for more info

#include "KeyOutput.h"

void KeyOutput::load(const char * key, const char * value)
{
	if (strcmp(key, "output") == 0)
	{
		int id, state;
		Event ev;
		char keys[256] = "";
		char vesselClass[256]= "";
		if (sscanf(value,"%i %i %256s %256s", &id, &state, keys, vesselClass) >= 3)
		{
			ev.id = id;
			ev.state = state;
			std::string s_keys = keys;
			std::string s_vesselClass = vesselClass;

			outputs[ev] = std::make_pair(s_vesselClass, s_keys);
		}
	}
}

void KeyOutput::handleEvent(Event ev)
{
	if (outputs.count(ev) != 0)
	{
		//get focus vessel
		VESSEL * vessel = oapiGetFocusInterface();

		if (outputs[ev].first.compare("") != 0)
		{
			//if there was a provided class, only trigger the keypresses if the focus vessel
			//class equals the stored one
			if (outputs[ev].first.compare(vessel->GetClassNameA()) == 0)
			{
				//trigger the event
				SendStringAuto(outputs[ev].second.c_str());
			}
		}
		else
		{
			//always trigger the keypresses
			SendStringAuto(outputs[ev].second.c_str());
		}

	}
}

void KeyOutput::SendStringAuto(const char * string)
{
	//first, do some haacky hacks if they want to pause/unpause, as orbiter REALLY doesn't like ^p
	if (strcmp(string, "^p") == 0)
	{
		oapiSetPause(!oapiGetPause());
		return;
	}

	//first send keydown
	SendString(string, 0);
	//then send keyup
	SendString(string, KEYEVENTF_KEYUP);
}

void KeyOutput::SendString(const char * string, DWORD dwFlags)
{

	for (unsigned int i = 0; i < strlen(string); i++)
	{
		//some of the following adapted from
		//http://batchloaf.wordpress.com/2012/04/17/simulating-a-keystroke-in-win32-c-or-c-using-sendinput/

		INPUT ip;
		//generic setup
		ip.type = INPUT_KEYBOARD;
		ip.ki.wScan = 0;
		ip.ki.time = 0;	
		ip.ki.dwExtraInfo = 0;
		
		WORD virtual_keycode;
		//switch character and convert to keycode

		//uses same format as AutoHotKey
		//http://www.autohotkey.com/docs/commands/Send.htm
		//for the modifier keys
		switch (string[i])
		{
			case '+':
				//shift
				virtual_keycode = VK_SHIFT;
				break;
			case '^':
				//control
				virtual_keycode = VK_CONTROL;
				break;
			case '!':
				//alt
				virtual_keycode = 0x12;
				break;
			case '#':
				//windows key
				virtual_keycode = 0x5B;
				break;
			default:
				//use VkKeyScan to convert keycode
				virtual_keycode = VkKeyScan(string[i]);
				break;
		}
		
		//send keystroke
		ip.ki.wVk = virtual_keycode;
		ip.ki.dwFlags = dwFlags;
		SendInput(1, &ip, sizeof(INPUT));
	}
}