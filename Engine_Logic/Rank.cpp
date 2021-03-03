#include "../Engine_System/SystemDefines.h"
#include "../Engine_System/OrganEntity.h"
#include "../Engine_Misc/RuntimeCmp.h"
#include "../Engine_System/StateMachine.h"
#include "../Engine_Misc/Utils.h"
#include "../Engine_System/Text.h"
#include "./RankOwnedStates.h"
#include "./Rank.h"
#include <string>

CRank::CRank(const char* _Adress, CRuntimeCmp<Ranking>::CMPMODE _eMode) : COrganEntity(-1),	m_eMode(_eMode),m_DataBase(CRuntimeCmp<Ranking>(_eMode))
{
	m_Adress = "./Script/SectionComposition/Rank/";
	m_Adress += _Adress;

	LoadEntityData(m_Adress.c_str());
	UniformOrganColor(D3DXCOLOR(-1.0f, 1.0f, -1.0f, 1.0f));
	UniformOrganSca(0.9f);

	m_Adress = "./Script/SectionComposition/Rank/Ranking/";
	m_Adress += _Adress;

	if(m_eMode == CRuntimeCmp<Ranking>::NORMAL){
		m_NewRanking = Ranking("-----", 1000);
	}
	else{
		m_NewRanking = Ranking("-----", -1);
	}

	m_pStateMachine = new CStateMachine<CRank>(this);

	// 처음 상태를 초기화
	m_pStateMachine->SetCurrentState(RankMain->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);

	for(int i = 0; i < 5; ++i){
		m_Name.push_back(new CText());
		m_Records.push_back(new CText());
	}

	this->LoadRankingFromScript();
}

CRank::~CRank(){
	Delete< CStateMachine<CRank>* >(m_pStateMachine);
	for(unsigned int i = 0; i < m_Records.size(); ++i)
		delete m_Records[i];
	for(unsigned int i = 0; i < m_Name.size(); ++i)
		delete m_Name[i];
}

void CRank::Update(double _dTimeElapsed){
	m_pStateMachine->Update();
}

void CRank::Render(){
	COrganEntity::RenderOrgan();

	RECT t_Rect;

	t_Rect.top = 100;
	t_Rect.bottom = -100;
	t_Rect.left = -200;
	t_Rect.right = 200;

	D3DXVECTOR3 t_vPos;

	t_vPos = *GetBody()->GetPriPos();
	
	t_vPos.x -= 60.0f;
	t_vPos.y += 34.0f;
	t_vPos.z = 0.0f;

	for(int i = 0; i < 5; ++i){
		m_Name[i]->PreRenderLine(&t_vPos);
		m_Name.at(i)->Update(&t_Rect);
		t_vPos.y -= 30.0f;
	}

	t_vPos = *GetBody()->GetPriPos();
	
	t_vPos.x += 200.0f;
	t_vPos.y += 34.0f;
	t_vPos.z = 0.0f;

	for(int i = 0; i < 5; ++i){
		m_Records[i]->PreRenderLine(&t_vPos);
		m_Records.at(i)->Update(&t_Rect);
		t_vPos.y -= 30.0f;
	}
}

void CRank::InitializeScript(){
	std::ofstream t_File;

	m_DataBase.clear();
	
	t_File.open(m_Adress, std::ios_base::out);

	if(!t_File){
		assert("Cann't open file");
	}

	for(int i = 0; i < 5; ++i){
		if(m_eMode == CRuntimeCmp<Ranking>::NORMAL){
			t_File << "----" << "	 " << 1000 << std::endl;
		}
		else{
			t_File << "----" << "	 " << -1 << std::endl;
		}		
	}

	this->LoadRankingFromScript();
}

void CRank::RecordRankingToScript(){
	std::ofstream t_File;

	m_DataBase.insert(this->m_NewRanking);

	t_File.open(m_Adress, std::ios_base::out);

	if(!t_File){
		assert("Cann't open file");
	}

	std::multiset<Ranking, CRuntimeCmp<Ranking> >::iterator t_Itr = m_DataBase.begin();

	for(int i = 0; i < 5; ++i, ++t_Itr){
		t_File << (*t_Itr).m_Name << "	 " << (*t_Itr).m_nRecord << std::endl;
	}

	m_DataBase.erase(t_Itr);
}

void CRank::LoadRankingFromScript(){
	std::ifstream t_File;

	t_File.open(m_Adress);

	if(!t_File){
		assert("Cann't open file");
	}

	std::string line;
	std::string t_Name;
	std::string t_Record;

	std::string::size_type begIdx;
	std::string::size_type endIdx;

	Ranking t_Ranking;

	for(int i = 0; i < 5; ++i){  
		std::getline(t_File, line);		

		const std::string delims(" \;");

		begIdx = line.find_first_not_of(delims);

		if(begIdx != std::string::npos){
			endIdx = line.find_first_of(delims, begIdx);

			if (endIdx == std::string::npos){
				endIdx = line.length();
			}
		}
    
		t_Name = line.substr(begIdx, endIdx);

		begIdx = line.find_first_not_of(delims, endIdx);

		if(begIdx != std::string::npos){
			endIdx = line.find_first_of(delims, begIdx);

			if (endIdx == std::string::npos){
				endIdx = line.length();
			}
		}
    
		t_Record = line.substr(begIdx, endIdx);
		t_Ranking.m_nRecord = atoi(t_Record.c_str());
		t_Ranking.m_Name = t_Name;
		this->m_DataBase.insert(t_Ranking);
	}
	this->SetRank();
}

void CRank::SetRank(){
	std::multiset<Ranking, CRuntimeCmp<Ranking> >::iterator t_Itr = m_DataBase.begin();

	for(int i = 0; i < 5; ++i, ++t_Itr){
		m_Name[i]->SetString((*t_Itr).m_Name);
		m_Records[i]->SetString((*t_Itr).m_nRecord);
	}
}