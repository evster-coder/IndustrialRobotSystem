#pragma once
#include "LoggerImpl.h"
#include <fstream>

class FileLogger : public LoggerImpl {
private:
	//объект файлового потока
	ofstream* fileWriter;
public:
	FileLogger(string filename);
	~FileLogger();

	//печать текста в файл
	void printLog(string text) override;
};