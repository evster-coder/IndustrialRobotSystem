#pragma once
#include <string>

using namespace std;

class LoggerImpl {
public:
	virtual void printLog(string text) = 0;
};