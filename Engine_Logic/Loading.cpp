#include "Loading.h"
#include "LoadingOwnedStates.h"

CLoading::CLoading(int _nEntityType):COrganEntity(_nEntityType),
									m_pMW(new CMessageWindow(-1, CMessageWindow::THIN)),
									m_nStepOfLoading(0)
{
	// ���±�踦 �����Ѵ�.
	m_pStateMachine = new CStateMachine<CLoading>(this);

	// ���� Loading script�� �ƹ��͵� ������
	// �Ŀ� ���߿� �������� �ʿ伺�� ������ �� �߰��ϱ� ���� �̷� ������ ����.
	LoadEntityData("./script/SectionComposition/Loading/Loading.txt");
			
	// ó�� ���¸� �ʱ�ȭ
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
	m_LoadingContents.push_back("���� ���� ���� ��...");
	m_LoadingContents.push_back("������ ���� ���� ��...");
	m_LoadingContents.push_back("���� ���� ���� ��...");
	m_LoadingContents.push_back("������ ��Ʋ�� ���� ��...");
	m_LoadingContents.push_back("õ������ ���� ���� ��...");
	m_LoadingContents.push_back("���հ� ���� ��...");
	m_LoadingContents.push_back("���� ���� ��...");
	m_LoadingContents.push_back("���� ���� ���� ��...");
	m_LoadingContents.push_back("���� �� ž�� ��...");
	m_LoadingContents.push_back("�̹��� ž�� ��...");
	m_LoadingContents.push_back("���� ž�� ��...");
	m_LoadingContents.push_back("�ִϸ��̼� ���� ��...");
	m_LoadingContents.push_back("���� �ð�ȭ ��...");
	m_LoadingContents.push_back("���� ���� ��...");
	m_LoadingContents.push_back("���� �з� ��...");
	m_LoadingContents.push_back("���� ž�� ��...");
	m_LoadingContents.push_back("�ε� �� �ϴ� ��...");
	m_LoadingContents.push_back("���α׷� ��� ��...");
	m_LoadingContents.push_back("CPU ���� ��...");
	m_LoadingContents.push_back("���� �˻� ��...");
	m_LoadingContents.push_back("������ ���� �˻� ��...");
	m_LoadingContents.push_back("�̹��� �˻� ��...");
	m_LoadingContents.push_back("�޸� ���� ��...");
	m_LoadingContents.push_back("���̷��� Ȯ�� ��...");
	m_LoadingContents.push_back("�ε���Ӱ����ڰ� �Ǵ� ��...");
	m_LoadingContents.push_back("������ ���� ��...");
	m_LoadingContents.push_back("���� �̵� ��...");
	m_LoadingContents.push_back("���� Ȯ�� ��...");
}