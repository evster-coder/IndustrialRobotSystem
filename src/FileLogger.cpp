#include "FileLogger.h"
#include "Logger.h"
#include <sstream>

FileLogger::FileLogger(string filename)
{
	//открываем файл на запись
	fileWriter = new ofstream();
	fileWriter->open(filename);
}

FileLogger::~FileLogger()
{
	//закрываем файл и удаляем
	fileWriter->close();
	delete fileWriter;
}

void FileLogger::printLog(string text)
{
	(*fileWriter) << text << endl;
}