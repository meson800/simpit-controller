//Copyright (c) 2013 Christopher Johnstone(meson800)
//The MIT License - See ../../../LICENSE for more info

#include "SerialInput.h"

SerialInput::~SerialInput()
{
	disconnect = true;
	serial.~Serial();
}


DWORD WINAPI SerialThreadFunction( LPVOID lpParam ) 
{ 
	((SerialInput *)(lpParam))->readSerialThread();
	return 0;
}

void SerialInput::load(const char * key, const char * value)
{
	if (strcmp(key, "com_port") == 0)
	{
		serial = Serial((char *)value);
		serial.WriteData("f",1);
					
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
	else if (strcmp(key, "format_string") == 0)
	{
		strcpy(formatString, value);
	}
}


void SerialInput::readSerialThread()
{
	char readChar;
			while (!disconnect)
			{
				//read data
				if (serial.ReadData(&readChar,1) != -1)
					buffer.push_back(readChar);

				//see if we have a complete event
				while (buffer.size() >= 7 && buffer.substr(buffer.find_first_of('.'),7).size() >= 7 && buffer.find_first_of('.')!=std::string::npos)
				{
					char * cbuffer = new char [7];
					strcpy(cbuffer,buffer.substr(buffer.find_first_of('.'),7).c_str());
					int switchNum, newState;
					sscanf(cbuffer,formatString,&switchNum,&newState);
					buffer = buffer.substr(buffer.find("/")+1,buffer.length() - 7);

					//send event upstream
					SimpitObserver::handleEvent(Event(switchNum,newState));
				}

			}
}