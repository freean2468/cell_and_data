#ifndef _ScriptLoader_H_
#define _ScriptLoader_H_

#include "FileLoaderBase.h"
#include <vector>

class CScriptLoader : public CFileLoaderBase {
private:
	int m_nIndex;
	int m_nMaxIndex;

	std::vector<int> m_ID;
	std::vector<std::string> m_Script;

public:
  CScriptLoader(const char* _pstrFile);
	~CScriptLoader(){}

public:
	void Update();

	int GetIndex(){return m_nIndex;}
	void IncreaseIndex(){m_nIndex++;}

	int GetMaxIndex(){return m_nMaxIndex;}

	int GetID(){return m_ID[m_nIndex];}
	std::string GetScript(){return m_Script[m_nIndex];}

	bool NextScript();
};

#endif