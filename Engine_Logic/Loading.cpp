#include "Loading.h"
#include "LoadingOwnedStates.h"

CLoading::CLoading(int _nEntityType):COrganEntity(_nEntityType),
									m_pMW(new CMessageWindow(-1, CMessageWindow::THIN)),
									m_nStepOfLoading(0)
{
	// 상태기계를 설정한다.
	m_pStateMachine = new CStateMachine<CLoading>(this);

	// 현재 Loading script는 아무것도 없지만
	// 후에 나중에 디자인의 필요성이 느껴질 때 추가하기 위해 이런 구조로 만듦.
	LoadEntityData("./script/SectionComposition/Loading/Loading.txt");
			
	// 처음 상태를 초기화
	m_pStateMachine->SetCurrentState(LoadingUsual->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);	
}

CLoading::~CLoading(){
	Delete< CStateMachine<CLoading>* >(m_pStateMachine);

	m_LoadingContents.clear();

	Delete<CMessageWindow*>(m_pMW);
}

void CLoading::Update(){
	if(m_nStepOfLoading==0 || m_nStepOfLoading==20 || m_nStepOfLoading==40 
		|| m_nStepOfLoading==60 || m_nStepOfLoading==80){
		m_pMW->GivenLine(m_LoadingContents[rand()%m_LoadingContents.size()]);
		m_nStepOfLoading++;
	}

	m_pStateMachine->Update();
	m_pMW->Update();
}

void CLoading::InitLoadingComponents(){
	m_nStepOfLoading = 0;
}

void CLoading::InitLoadingGameWorldContents(){
	m_LoadingContents.push_back("정보 세계 구축 중...");
	m_LoadingContents.push_back("동심의 세계 구축 중...");
	m_LoadingContents.push_back("세포 세계 구축 중...");
	m_LoadingContents.push_back("세포의 꿈틀림 조정 중...");
	m_LoadingContents.push_back("천방지축 세포 생성 중...");
	m_LoadingContents.push_back("먹잇감 생성 중...");
	m_LoadingContents.push_back("세포 성장 중...");
	m_LoadingContents.push_back("아픈 정보 삭제 중...");
	m_LoadingContents.push_back("세포 핵 탑재 중...");
	m_LoadingContents.push_back("이미지 탑재 중...");
	m_LoadingContents.push_back("정보 탑재 중...");
	m_LoadingContents.push_back("애니메이션 조정 중...");
	m_LoadingContents.push_back("정보 시각화 중...");
	m_LoadingContents.push_back("세계 구분 중...");
	m_LoadingContents.push_back("공간 분류 중...");
	m_LoadingContents.push_back("동심 탑재 중...");
	m_LoadingContents.push_back("로딩 안 하는 중...");
	m_LoadingContents.push_back("프로그램 노는 중...");
	m_LoadingContents.push_back("CPU 쉬는 중...");
	m_LoadingContents.push_back("정보 검색 중...");
	m_LoadingContents.push_back("순수한 세포 검색 중...");
	m_LoadingContents.push_back("이미지 검색 중...");
	m_LoadingContents.push_back("메모리 여행 중...");
	m_LoadingContents.push_back("바이러스 확산 중...");
	m_LoadingContents.push_back("인디게임개발자가 되는 중...");
	m_LoadingContents.push_back("데이터 여행 중...");
	m_LoadingContents.push_back("세포 이동 중...");
	m_LoadingContents.push_back("공간 확장 중...");
}