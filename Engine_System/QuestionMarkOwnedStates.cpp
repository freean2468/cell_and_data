#include "../BaseHeader.h"

///////////////////////////////////////////////////////////
// Usual State
///////////////////////////////////////////////////////////
void CQuestionMarkUsual::Enter(CQuestionMark* pQuestionMark){
	_nCount = 0;
}

void CQuestionMarkUsual::Execute(CQuestionMark* pQuestionMark){
	CBody* t_pBody = pQuestionMark->GetBody();

	t_pBody->GetPriPos()->x = pQuestionMark->GetOrigin()->GetPriPos()->x;
	t_pBody->GetPriPos()->y = pQuestionMark->GetOrigin()->GetPriPos()->y + 70.0f;

	// 바디 계산	
	switch(t_pBody->GetAngleState()){
		case true:
			// Max라면
			t_pBody->GetPriRot()->z += 0.05f;
			if(t_pBody->GetPriRot()->z >= D3DX_PI * 0.06f)
				t_pBody->SetAngleState(false);
			break;
		case false:
			// Min라면
			t_pBody->GetPriRot()->z -= 0.05f;
			if(t_pBody->GetPriRot()->z <= D3DX_PI * 0.01f){
				_nCount++;
				t_pBody->SetAngleState(true);
			}
			break;
	}

	if(_nCount >= 1){
		t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a -= 0.01f;
	}

	if(t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a <= 0.0f)
		pQuestionMark->SetIsDie(true);

	pQuestionMark->RenderOrgan();
}

void CQuestionMarkUsual::Exit(CQuestionMark* pQuestionMark){

}

bool CQuestionMarkUsual::OnMessage(CQuestionMark* agent, const Telegram& _rMsg){
	return false;
}