//Copyright (c) 2013 Christopher Johnstone(meson800)
//The MIT License - See ../../../LICENSE for more info

#include "SerialInput.h"

SerialInput::~SerialInput()
{
	DeleteCriticalSection(&critSection);
	
}


DWORD WINAPI SerialThreadFunction( LPVOID lpParam ) 
{ 
	((SerialInput *)(lpParam))->readSerialThread();
	return 0;
}

void SerialInput::SimulationStart()
{
	//init serial
 	serial = new Serial(comPort);

	serial->WriteData("f", 1);

	buffer = "";

	//make the argument for our function to access
	SerialInput * thisInput = this;
	//do windows threading
	HANDLE hThread = CreateThread(
		NULL,                   // default security attributes
		NULL,                      // use default stack size  
		SerialThreadFunction,       // thread function name
		thisInput,          // argument to thread function 
		NULL,                      // use default creation flags 
		NULL);   // returns nothing

	//detach the thread
	CloseHandle(hThread);
}

void SerialInput::SimulationEnd()
{
	EnterCriticalSection(&critSection);
	stopSerial = true;
	LeaveCriticalSection(&critSection);
}


void SerialInput::load(const char * key, const char * value)
{
	if (strcmp(key, "com_port") == 0)
	{
		strcpy(comPort,value);
	}
	else if (strcmp(key, "format_string") == 0)
	{
		strcpy(formatString, value);
	}

	else
	{
		Event thisEvent;
		char text[255];
		if (sscanf(value, "%i %i \"%254[^\"]\"", &(thisEvent.id), &(thisEvent.state), text) == 3)
		{
			outputEvents[Event(thisEvent)] = std::string(text);
		}
	}
}


void SerialInput::readSerialThread()
{

	while(true)
	{
		//check if we should exit
		bool exit;
		EnterCriticalSection(&critSection);
		exit = stopSerial;
		LeaveCriticalSection(&critSection);

		if (exit)
		{
			delete serial;
			return;
		}

		char readChar;

		//read data
		if (serial->ReadData(&readChar,1) != -1)
			buffer.push_back(readChar);

		//see if we have a complete event
		while (buffer.size() >= 7 && buffer.substr(buffer.find_first_of('.'),7).size() >= 7 && buffer.find_first_of('.')!=std::string::npos)
		{
			char * cbuffer = new char [7];
			strcpy(cbuffer,buffer.substr(buffer.find_first_of('.'),7).c_str());
			int switchNum, newState;
			sscanf(cbuffer,formatString,&switchNum,&newState);
			buffer = buffer.substr(buffer.find("/")+1,buffer.length() - 7);

			if (currentEvents.count(switchNum) == 0)
			{
				currentEvents[switchNum] = newState;
				//send event upstream
				SimpitObserver::handleEvent(Event(switchNum, newState));
			}
			else
			{
				if (currentEvents[switchNum] != newState)
				{
					//send event upstream
					SimpitObserver::handleEvent(Event(switchNum, newState));
					//update current events
					currentEvents[switchNum] = newState;
				}
			}

		}
	}

}