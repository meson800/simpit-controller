#ifndef LOG_CLASS
#define LOG_CLASS

#include <Windows.h>
#include <string>

class Log
{
public:
	static void initLogging();
	static void shutdownLogging();
	static void print(const char * string);
	static void print(std::string string);
	static void println(const char * string);
	static void println(std::string string);
	static FILE * returnLogHandle();
private:
	static FILE * logHandle;
};

#endif