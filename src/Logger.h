#pragma once
#include "LoggerImpl.h"
#include "FileLogger.h"

//абстракция логгера
class Logger {
private:
	//реализация логгера
	static LoggerImpl* impl;
public:

	//печать текста
	static void printText(string text);

	//установка реализации
	static void setImplementation(LoggerImpl* _implementation);
};
