#include "Log.h"

CLog::CLog(std::string _title){
	title = _title + "_log.txt";
	fp = fopen(title.c_str(), "w");
	fclose(fp);
}

CLog::~CLog(){
	
}

void CLog::insertLog(std::string context){
	fp = fopen(title.c_str(), "a");
	fwrite(context.c_str(), context.size(), 1, fp);
	fclose(fp);
}