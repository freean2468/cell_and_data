#include "LogoOwnedStates.h"
#include "../Engine_System/CameraManager.h"
#include "../Engine_System/EffectManager.h"
#include "../Engine_System/Timer.h"
#include "Logo.h"

///////////////////////////////////////////////////////////
// Start State
///////////////////////////////////////////////////////////
void CLogoStart::Enter(CLogo* pLogo){
	CameraMgr->SetMode(CCameraManager::SECTION);
	m_pTimer = NULL;
}

void CLogoStart::Execute(CLogo* pLogo){
	if(EffectMgr->IfBlackFadeInEnd()){
		if(!m_pTimer) m_pTimer = new CTimer(2000);

		if(m_pTimer->IsElapseTimer()){
			EffectMgr->FadeOutBlackPlane();
		}
	}

	pLogo->RenderOrgan();
}

void CLogoStart::Exit(CLogo* pLogo){
	Delete<CTimer*>(m_pTimer);
}

bool CLogoStart::OnMessage(CLogo* agent, const Telegram& _rMsg){
	return false;
}