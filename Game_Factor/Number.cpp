#include "Number.h"
#include "NumberOwnedStates.h"

CNumber::CNumber(int _nValue, int _nEntityType) : COrganEntity(0), m_nValue(_nValue)
{
	// 상태기계를 설정한다.
	m_pStateMachine = new CStateMachine<CNumber>(this);

	LoadEntityData("./script/UserInterface/Number/Number.txt");

	// 처음 상태를 초기화
	m_pStateMachine->SetCurrentState(NumberNormal->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);

	this->UniformOrganColor(D3DXCOLOR(-1.0f, 1.0f, -1.0f, 1.0f));
	this->UniformOrganSca(0.5f);
}

CNumber::~CNumber(){
	Delete< CStateMachine<CNumber>* >(m_pStateMachine);
}

void CNumber::Update(double _dTimeElapsed){
	m_pStateMachine->Update();
}

void CNumber::RenderOrgan(){
	int i = 0;

	if(GetAttachmentArray()->GetSize()){
		for(; i < GetAttachmentArray()->GetSize(); i++){
			if(GetValue() == i){
				BodySetting();
				GetAttachmentArray()->Get(i)->Render(GetChainPos(), GetChainSca(), GetChainRot(), GetChainCen());
				InitChainVector();
				break;
			}
		}
	}

	InitChainVector();
}