#include "ScriptLoader.h"
#include "../Engine_System/CameraManager.h"
#include <d3dx9math.h>
#include "../Game_Factor/Controller.h"
#include "../Engine_Logic/EventManager.h"
#include "TextOwnedStates.h"

CScriptLoader::CScriptLoader(const char* _pstrFile):CFileLoaderBase(_pstrFile),
													m_nIndex(0),
													m_nMaxIndex(0)
{
	m_nIndex = 0;
	m_nMaxIndex = 0;

	m_ID.clear();
	m_Script.clear();

	while(eof() == false){
		m_ID.push_back(GetNextParameterInt());
		m_Script.push_back(GetNextScriptAsString());
		m_nMaxIndex++;
	}
}

void CScriptLoader::Update(){
	D3DXVECTOR3 t_vPos(0.0f, 0.0f, 0.0f);

	CameraMgr->GetCamera()->GetPosition(&t_vPos);

	if(GetID() == 0){
		EventMgr->GetBalloon()->GivenLine(GetScript());
		*(EventMgr->GetBalloon()->GetPos3D()) = *(Controller->GetController()->GetBody()->GetPriPos());
		
		EventMgr->GetBalloon()->GetPos3D()->y += 140.0f;
		EventMgr->GetBalloon()->GetPos3D()->z = t_vPos.z + 700.0f;

		EventMgr->GetBalloon()->GetText()->GetFSM()->ChangeState(TextTyping->Instance());

		if(!EngineMgr->IsViewOut(Controller->GetController()->GetBody()->GetPriPos())){
			EventMgr->GetBalloon()->Update();
		}
	}

	if(GetID() == 1 || EventMgr->GetShowFriend()){
		*(EventMgr->GetFriend()->GetPriPos()) = t_vPos;
		EventMgr->GetFriend()->GetPriPos()->x += 250.0f;
		EventMgr->GetFriend()->GetPriPos()->y -= 180.0f;
		EventMgr->GetFriend()->GetPriPos()->z += 700.0f;

		EventMgr->GetBalloon()->GivenLine(GetScript());
		*(EventMgr->GetBalloon()->GetPos3D()) = *(EventMgr->GetFriend()->GetPriPos());
		
		EventMgr->GetBalloon()->GetPos3D()->y += 160.0f;
		EventMgr->GetBalloon()->GetPos3D()->z = t_vPos.z + 700.0f;

		EventMgr->GetBalloon()->GetText()->GetFSM()->ChangeState(TextTyping->Instance());

		EventMgr->GetFriend()->Render();

		if(GetID() == 1) EventMgr->GetBalloon()->Update();
	}

	if(GetID() == 2 || EventMgr->GetShowLove()){
		*(EventMgr->GetLove()->GetPriPos()) = t_vPos;
		EventMgr->GetLove()->GetPriPos()->x -= 250.0f;
		EventMgr->GetLove()->GetPriPos()->y -= 180.0f;
		EventMgr->GetLove()->GetPriPos()->z += 700.0f;

		EventMgr->GetBalloon()->GivenLine(GetScript());
		*(EventMgr->GetBalloon()->GetPos3D()) = *(EventMgr->GetLove()->GetPriPos());
		
		EventMgr->GetBalloon()->GetPos3D()->y += 160.0f;
		EventMgr->GetBalloon()->GetPos3D()->z = t_vPos.z + 700.0f;

		EventMgr->GetBalloon()->GetText()->GetFSM()->ChangeState(TextTyping->Instance());

		EventMgr->GetLove()->Render();

		if(GetID() == 2)EventMgr->GetBalloon()->Update();
	}
}

bool CScriptLoader::NextScript(){
	m_nIndex++;
	
	if(m_nIndex == m_nMaxIndex)
		return true;
	else
		return false;
}