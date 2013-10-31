#include "SerialInput.h"

SerialInput::~SerialInput()
{
	disconnect = true;
	serial.~Serial();
}

void SerialInput::load(FILEHANDLE inputFile)
{
	//inputFile = this->readToSectionStart(inputFile,"SERIAL_INPUT");
	if (inputFile != 0)
	{
		char com [10];
		char *line;
		while (oapiReadScenario_nextline(inputFile,line))
		{
			if (line[0] != ';')
			{
				if (sscanf(line,"COM_PORT = %s", com) == 1)
				{
					serial = Serial(com);
					serial.WriteData("f",1);
			
					boost::thread workerThread(boost::bind(&SerialInput::readSerialThread,this));
				}
				if (sscanf(line,"FORMAT_STRING = %s", formatString) == 1)
				{}
			}
		}

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
					handleEventFunc(Event(switchNum,newState));
				}

			}
}