////////////////////////////////////////////////////
// Section 관리 클래스
////////////////////////////////////////////////////
#ifndef _SectionManager_H_
#define _SectionManager_H_

#include "Section.h"

class CSectionManager{
public:
	typedef enum Signpost {MAINMENU, CREDIT, STAGE, EVENT} SIGNPOST;

public:
	CSection* m_pSection;
	SIGNPOST m_eSignpost;

private:
	CSectionManager():m_pSection(new CSection()){}
	CSectionManager(const CSectionManager&);
	CSectionManager& operator =(const CSectionManager&);

public:
	~CSectionManager(){
		Delete<CSection*>(m_pSection);
	}
	static CSectionManager* Instance(){
		static CSectionManager instance;

		return &instance;
	}

	CSection* GetSection(){return m_pSection;}
	void SetSign(SIGNPOST _eSign){m_eSignpost = _eSign;}
	SIGNPOST GetSign(){return m_eSignpost;}
};

#define SectionMgr CSectionManager::Instance()

#endif