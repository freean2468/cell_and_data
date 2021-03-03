#include "EffectManager.h"
#include "EngineManager.h"
#include "../Engine_Data Structures/DLinkedList.h"
#include "CameraManager.h"

CEffectManager::CEffectManager() : m_vPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),			// 위치 벡터
								m_vSca(D3DXVECTOR3(1.0f, 1.0f, 1.0f)),		// 크기 벡터
								m_vRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),		// 회전 벡터
								m_bPlaneUse(false),
								m_bFade(true)
{
	// Plane
	m_ePlaneType = BLACK;

	m_Plane.Resize(2);

	m_vSca.x = 1.0f; m_vSca.y = 1.0f; m_vSca.z = 1.0f;

	m_Plane.Get(0) = new CAttachment(m_vPos, m_vSca, m_vRot, m_vPos, 0);
	m_Plane.Get(0)->InitObject(EngineMgr->GetpDevice(), "./Image/Effect/Plane/BlackPlane.dds", 100, 100, 1.0f, 0);

	m_Plane.Get(1) = new CAttachment(m_vPos, m_vSca, m_vRot, m_vPos, 0);
	m_Plane.Get(1)->InitObject(EngineMgr->GetpDevice(), "./Image/Effect/Plane/WhitePlane.dds", 100, 100, 1.0f, 0);	
}

CEffectManager::~CEffectManager(){
	// 반복자 생성
	CDListIterator<CBaseEffect*> itr;
	
	itr = m_BaseEffect.GetIterator();
	
	for(itr.Start(); itr.Valid();){
		m_BaseEffect.Remove(itr);
	}
}

void CEffectManager::PreEffectUpdate(){

}

void CEffectManager::PostEffectUpdate(){
	
}

void CEffectManager::EffectUpdate(){
	SmallScaleEffectUpdate();

	// Delete
	SmallScaleEffectDelete();		
}

void CEffectManager::FadeInBlackPlane(){
	EffectMgr->SetPlaneType(CEffectManager::BLACK);
	EffectMgr->SetFade(false);
	EffectMgr->SetPlaneUse(true);
	m_Plane[BLACK]->SetAlpha(1.0f);
}

void CEffectManager::FadeOutBlackPlane(){
	EffectMgr->SetPlaneType(CEffectManager::BLACK);
	EffectMgr->SetFade(true);
	EffectMgr->SetPlaneUse(true);
	m_Plane[BLACK]->SetAlpha(0.0f);
}

void CEffectManager::FadeInWhitePlane(){
	EffectMgr->SetPlaneType(CEffectManager::WHITE);
	EffectMgr->SetFade(true);
	EffectMgr->SetPlaneUse(true);
	m_Plane[WHITE]->SetAlpha(0.0f);
}

void CEffectManager::FadeOutWhitePlane(){
	EffectMgr->SetPlaneType(CEffectManager::WHITE);
	EffectMgr->SetFade(false);
	EffectMgr->SetPlaneUse(true);
	m_Plane[WHITE]->SetAlpha(1.0f);
}

void CEffectManager::AlphaPlaneUpdate(){
	D3DXVECTOR3 t_vTemp = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 t_vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	CAttachment* _pAtt;

	if(m_bPlaneUse){
		CameraMgr->GetCamera()->GetPosition(&t_vPos);

		switch(m_ePlaneType){
			case BLACK:	
				_pAtt = m_Plane.Get(0);				
				break;
			case WHITE:	
				_pAtt = m_Plane.Get(1);
				break;
		}

		_pAtt->GetPriPos()->x = t_vPos.x;
		_pAtt->GetPriPos()->y = t_vPos.y;
		_pAtt->GetPriPos()->z = 50.0f + t_vPos.z;

		_pAtt->Render(&t_vTemp, &t_vTemp, &t_vTemp, &t_vTemp);

		switch(m_bFade){
			case true:
				_pAtt->GetMtrl()->Diffuse.a += 0.01f;

				if(_pAtt->GetMtrl()->Diffuse.a > 1.0f)
					m_bPlaneUse = false;
				break;
			case false:
				_pAtt->GetMtrl()->Diffuse.a -= 0.01f;

				if(_pAtt->GetMtrl()->Diffuse.a < 0.0f){
					m_bPlaneUse = false;
				}
				break;
		}
	}
}

void CEffectManager::SmallScaleEffectUpdate(){
	CDListIterator<CBaseEffect*> itr = m_BaseEffect.GetIterator();
	
	for(itr.Start(); itr.Valid(); itr.Forth()){
		if(!EngineMgr->IsViewOut(itr.Item()->GetBody()->GetPriPos())){
			itr.Item()->Update();
		}
	}
}
	
void CEffectManager::SmallScaleEffectDelete(){
	// 반복자 생성
	CDListIterator<CBaseEffect*> itr;
	
	itr = m_BaseEffect.GetIterator();
	
	for(itr.Start(); itr.Valid();){
		if(!itr.Item()->IsAlive()){
			Delete<CBaseEffect*>(itr.Item());
			m_BaseEffect.Remove(itr);
		}
		else{
			itr.Forth();
		}
	}
}

void CEffectManager::SetBGEffectInfoOnRandom(CAttachment* _pAtt){
	float t_fTemp = (rand() % 7 + 1) * 0.1f;
	float fAlpha = 0.0f;

	_pAtt->GetPriPos()->x = (float)(abs(m_Box._max.x - m_Box._min.x) * t_fTemp) - abs(m_Box._min.x);
	_pAtt->GetPriPos()->y = (float)(abs(m_Box._max.y - m_Box._min.y) * t_fTemp) - abs(m_Box._min.y);
	_pAtt->GetPriPos()->z = (float)m_Box._min.z - 50.0f;
		
	_pAtt->GetMtrl()->Diffuse.a = fAlpha;
}

bool CEffectManager::CheckOverRange(CAttachment* _pAtt){
	if(_pAtt->GetPriPos()->x > m_Box._max.x)
		return true;

	return false;
}