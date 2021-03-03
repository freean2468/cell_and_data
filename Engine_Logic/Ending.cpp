#include "Ending.h"
#include "EndingOwnedStates.h"

CEnding::CEnding(int _nID):COrganEntity(_nID){
	// ���±�踦 �����Ѵ�.
	m_pStateMachine = new CStateMachine<CEnding>(this);

	// ��� ����
	LoadEntityData("./script/SectionComposition/Ending/Ending.txt");
			
	// ó�� ���¸� �ʱ�ȭ
	m_pStateMachine->SetCurrentState(EndingMain->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);

	this->GetAttachmentFromType(DARK)->SetAlpha(0.0f);
}

CEnding::~CEnding(){
	Delete< CStateMachine<CEnding>* >(m_pStateMachine);
}

void CEnding::Update(double _dTimeElapsed){
	m_pStateMachine->Update();
}

void CEnding::RenderOrgan(){
	if(GetBody()){
		BodySetting();
		GetBody()->Render(GetChainPos(), GetChainSca(), GetChainRot(), GetChainCen());
	}
	
	InitChainVector();

	if(GetAttachmentArray()->GetSize()){
		for(int i = 0; i < GetAttachmentArray()->GetSize(); i++){
			BodySetting();
			GetAttachmentArray()->Get(i)->Render(GetChainPos(), GetChainSca(), GetChainRot(), GetChainCen());
			InitChainVector();
		}
	}

	InitChainVector();
}