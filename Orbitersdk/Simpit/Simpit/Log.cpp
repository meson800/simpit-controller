#include "Log.h"

FILE * Log::logHandle = 0;

void Log::initLogging()
{
	if (logHandle == 0)
		logHandle = fopen("simpit_controller.log", "w");
	println("***Simpit Controller Log");
}

void Log::shutdownLogging()
{
	println("***Logging stopped");
	if (logHandle != 0)
		fclose(logHandle);
	logHandle = 0;
}

void Log::print(const char * string)
{
	if (logHandle != 0)
		fprintf(logHandle, "%s", string);
}

void Log::print(std::string string)
{
	print(string.c_str());
}

void Log::println(const char * string)
{
	if (logHandle != 0)
		fprintf(logHandle, "%s\n", string);
}

void Log::println(std::string string)
{
	println(string.c_str());
}

FILE * Log::returnLogHandle()
{
	return logHandle;
}