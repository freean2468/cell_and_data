////////////////////////////////////////////////////
// Effect 담당 관리 클래스
////////////////////////////////////////////////////
#ifndef _EffectManager_H_
#define _EffectManager_H_

#include "../Engine_Data Structures/Array.h"
#include "../Engine_Data Structures/DLinkedList.h"
#include "Attachment.h"
#include "BaseEffect.h"
#include "../Engine_Misc/DirectUtils.h"

class CEffectManager{
public:
	typedef enum PlaneType{BLACK=0, WHITE} PLANETYPE;

private:
	// BG Effect
	CArray<CAttachment*> m_Plane;	    // 환면 전환 효과
	bool m_bFade;											// true -> ++, false -> --
	bool m_bPlaneUse;									// Plane 사용 여부

	// Small scale Effect
	CDLinkedList<CBaseEffect*> m_BaseEffect; // 베이스 이펙트 클래스

	DU::BoundingBox m_Box;
	
	D3DXVECTOR3 m_vPos;
	D3DXVECTOR3 m_vSca;
	D3DXVECTOR3 m_vRot;

	PLANETYPE m_ePlaneType;

private:
	CEffectManager();
	CEffectManager(const CEffectManager&);
	CEffectManager& operator =(const CEffectManager&);

public:
	~CEffectManager();
	static CEffectManager* Instance(){
		static CEffectManager instance;

		return &instance;
	}

	// Effect 업데이트
	void EffectUpdate();
	void PreEffectUpdate();
	void PostEffectUpdate();

	// BG 배경 효과 영역 설정
	bool CheckOverRange(CAttachment* _pAtt);

	// 배경 효과 정보 셋팅
	void SetBGEffectInfoOnRandom(CAttachment* _pAtt);

	// AlphaPlane
	void AlphaPlaneUpdate();
	void SetPlaneType(PLANETYPE _eType){m_ePlaneType = _eType;}
	void SetPlaneUse(bool _bUse){m_bPlaneUse = _bUse;}
	void SetFade(bool _bFade){m_bFade = _bFade;}
	bool GetFade(){return m_bFade;}
	bool GetPlaneUse(){return m_bPlaneUse;}

	void FadeOutBlackPlane();
	void FadeInBlackPlane();
	void FadeOutWhitePlane();
	void FadeInWhitePlane();
	bool IfBlackFadeInEnd(){if(!m_bFade && !m_bPlaneUse){return true;}else{return false;}}
	bool IfBlackFadeOutEnd(){if(m_bFade && !m_bPlaneUse){return true;}else{return false;}}
	bool IfWhiteFadeInEnd(){if(!m_bFade && !m_bPlaneUse){return true;}else{return false;}}
	bool IfWhiteFadeOutEnd(){if(m_bFade && !m_bPlaneUse){return true;}else{return false;}}

	// small Scale
	CDLinkedList<CBaseEffect*>* GetSmallEffectList(){return &m_BaseEffect;}
	void SmallScaleEffectUpdate();
	void SmallScaleEffectDelete();
};

#define EffectMgr CEffectManager::Instance()

#endif