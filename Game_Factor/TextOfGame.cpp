#include "TextOfGame.h"
#include "TextOfGameOwnedStates.h"
#include "../Engine_System/CameraManager.h"
#include "UIManager.h"

CTextOfGame::CTextOfGame(int _nEntityType) : COrganEntity(0), 
											m_pTimer(new CCrudeTimer()),
											m_pAdress(new CText()),
											m_pScore(new CText()),
											m_bTimeActive(false)
{
	// 상태기계를 설정한다.
	m_pStateMachine = new CStateMachine<CTextOfGame>(this);

	LoadEntityData("./script/UserInterface/TextOfGame/TextOfGame.txt");

	// 처음 상태를 초기화
	m_pStateMachine->SetCurrentState(TextOfGameMain->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);

	this->UniformOrganColor(D3DXCOLOR(-1.0f, 1.0f, -1.0f, 1.0f));

	D3DXVECTOR3 t_vPos(0.0f, 0.0f, 0.0f);

	CameraMgr->GetCamera()->GetPosition(&t_vPos);

	m_pTime = new CNumberArray(&t_vPos, 5, 0, 100);

	m_pScore->SetFontScale(2);
}

CTextOfGame::~CTextOfGame(){
	Delete< CStateMachine<CTextOfGame>* >(m_pStateMachine);
	Delete< CCrudeTimer* >(m_pTimer);
	Delete< CText* >(m_pAdress);
	Delete< CText* >(m_pScore);
	Delete< CNumberArray* >(m_pTime);
}

void CTextOfGame::Initialize(){
	m_pTime->Initialize();
	this->OffTime();
	Delete< CCrudeTimer* >(m_pTimer);
	m_pTimer = new CCrudeTimer();

}

void CTextOfGame::Update(double _dTimeElapsed){
	m_pStateMachine->Update();

	D3DXVECTOR3 t_vPos(0.0f, 0.0f, 0.0f);

	CameraMgr->GetCamera()->GetPosition(&t_vPos);

	if(IsTimeActive()){
		this->UpdateTimer();

		t_vPos.x += 170.0f;
		t_vPos.y += 100.0f;
		t_vPos.z += 400.0f;

		GetTime()->GetPos3D()->x = t_vPos.x;
		GetTime()->GetPos3D()->y = t_vPos.y;
		GetTime()->GetPos3D()->z = t_vPos.z;

		GetTime()->Update();
		GetTime()->Render();
	}
}

void CTextOfGame::UpdateAdress(){
	D3DXVECTOR3 t_vPos(0.0f, 0.0f, 0.0f);

	CameraMgr->GetCamera()->GetPosition(&t_vPos);

	t_vPos.y += 100.0f;
	t_vPos.z += 400.0f;

	GetAdress()->PreRenderLine(&t_vPos);

	RECT t_Rect;

	t_Rect.left = -100;
	t_Rect.right = 100;
	t_Rect.top = 100;
	t_Rect.bottom = -100;

	GetAdress()->Update(&t_Rect);
}

void CTextOfGame::UpdateScore(){
	D3DXVECTOR3 t_vPos = *(UIMgr->GetGauge()->GetBody()->GetPriPos());

	char t_char[10];
	std::string t_String;

	_itoa_s((int)UIMgr->GetGauge()->GetPresentGauge(), &t_char[0], 10, 10);

	t_String += t_char;
	t_String += " Byte";

	m_pScore->SetString(t_String);

	m_pScore->PreRenderLine(&t_vPos);

	m_pScore->Update(NULL);
}