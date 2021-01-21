#include "Logger.h"
#include <sstream>

void Logger::setImplementation(LoggerImpl* _implementation)
{
	impl = _implementation;
}

void Logger::printText(string text)
{
	impl->printLog(text);
}

LoggerImpl* Logger::impl = new FileLogger("logs.txt");
