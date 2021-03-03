#ifndef _LOG_H_
#define _LOG_H_

#include <string>
#include <stdio.h>

class CLog{
private:
	FILE *fp;
	std::string title;

public:
	CLog(){};
	CLog(std::string _title);
	~CLog();

	void insertLog(std::string context);
};

#endif