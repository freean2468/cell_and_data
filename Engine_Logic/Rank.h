#ifndef _Rank_H_
#define _Rank_H_

#include <string>
#include "../Engine_System/OrganEntity.h"
#include "../Engine_System/StateMachine.h"
#include "../Engine_System/Text.h"
#include "../Engine_Misc/RuntimeCmp.h"
#include <set>
#include <fstream>

struct Ranking{
	std::string m_Name;
	int			m_nRecord;

	Ranking(){}
	Ranking(std::string _Name, int _nRecord):m_Name(_Name), m_nRecord(_nRecord){}

	bool operator==(const Ranking& _Rank)const{
		return (m_nRecord == _Rank.m_nRecord);
  }

	bool operator<(const Ranking& _Rank)const{
		return (m_nRecord < _Rank.m_nRecord);
  }

	bool operator>(const Ranking& _Rank)const{
		return (m_nRecord > _Rank.m_nRecord);
  }
};

class CRank : public COrganEntity{
private:
	std::string m_Adress;
	CStateMachine<CRank>* m_pStateMachine;

	std::vector<CText*> m_Name;
	std::vector<CText*> m_Records;
	
	std::ifstream m_File;
	CRuntimeCmp<Ranking>::CMPMODE m_eMode;

	Ranking m_NewRanking;
	std::multiset< Ranking, CRuntimeCmp<Ranking> > m_DataBase;

public:
	CRank(const char* _Adress, CRuntimeCmp<Ranking>::CMPMODE _eMode);
	~CRank();

	virtual void Update(double _dTimeElapsed = SYSTEM_FRAME_INTERVAL_VER_60);
	virtual void Render();

	void InitializeScript();
	void RecordRankingToScript();
	void LoadRankingFromScript();
	void SetRank();

	CStateMachine<CRank>* GetFSM()const{return m_pStateMachine;}

	void SetNew(Ranking t_Ranking){m_NewRanking = t_Ranking;}
};

#endif