#include "Organ.h"
#include "../Engine_Misc/DirectUtils.h"

COrgan::COrgan():CBasicEntity(-1),
				m_vPrimitivePos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
				m_vPrimitiveSca(D3DXVECTOR3(1.0f, 1.0f, 1.0f)),
				m_vPrimitiveRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),	
				m_vPrimitiveCen(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
				m_fAveRadius(0.0f),
				m_bAngleState(true),
				m_bMoveState(true),
				m_bScaleState(true),
				m_fVelocity(((float)(rand() % 10) + 4)/10.0f),
				m_bShearUse(false),
				m_bShearState(true),
				m_vOldPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
				m_fShearDegree((float)(rand() % 3) + 3.3f),
				m_fTraceX(0.0f),
				m_fTraceY(0.0f),
				m_fBaseScaX(0.0f),
				m_fBaseScaY(0.0f),
				m_fBaseAlternateSca(0.0f)
{
	m_Rect.right = (LONG)GetRight();
	m_Rect.left = (LONG)GetLeft();
	m_Rect.top = (LONG)GetTop();
	m_Rect.bottom = (LONG)GetBottom();
}

COrgan::COrgan(D3DXVECTOR3 _vPos, D3DXVECTOR3 _vSca, D3DXVECTOR3 _vRot, D3DXVECTOR3 _vCen):	CBasicEntity(-1),
																							m_vPrimitivePos(_vPos),
																							m_vPrimitiveSca(_vSca),
																							m_vPrimitiveRot(_vRot),	
																							m_vPrimitiveCen(_vCen),
																							m_fAveRadius((GetWidthHalf() + GetHeightHalf())*0.5f),
																							m_bAngleState(true),
																							m_bMoveState(true),
																							m_bScaleState(true),
																							m_fVelocity(((float)(rand() % 10) + 4)/10.0f),
																							m_bShearUse(false),
																							m_bShearState(true),
																							m_vOldPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
																							m_fShearDegree((float)(rand() % 3) + 3.3f),
																							m_fTraceX(0.0f),
																							m_fTraceY(0.0f),
																							m_fBaseScaX(0.0f),
																							m_fBaseScaY(0.0f),
																							m_fBaseAlternateSca(0.0f)
{
	m_Rect.right = (LONG)GetRight();
	m_Rect.left = (LONG)GetLeft();
	m_Rect.top = (LONG)GetTop();
	m_Rect.bottom = (LONG)GetBottom();
}

COrgan::~COrgan(){

}

void COrgan::Shear(D3DXVECTOR3* _pvPos, D3DXMATRIXA16* _pmX, D3DXMATRIXA16* _pmY, D3DXMATRIXA16* _pmZ){
	if(m_bShearUse == false)
		return;

	static float fDegree = 0.0f;

	switch(m_bShearState){
		case true:			
			D3DXMatrixTranslation(_pmX, _pvPos->x, 0.0f, 0.0f);
			D3DXMatrixTranslation(_pmY, 0.0f, _pvPos->y, 0.0f);
			D3DXMatrixTranslation(_pmZ, 0.0f, 0.0f, _pvPos->z);

			fDegree += 1.0f;
			break;
		case false:			
			D3DXMatrixTranslation(_pmX, _pvPos->x, 0.0f, 0.0f);
			D3DXMatrixTranslation(_pmY, 0.0f, _pvPos->y, 0.0f);
			D3DXMatrixTranslation(_pmZ, 0.0f, 0.0f, _pvPos->z);

			fDegree -= 1.0f;
			break;
	}

	if(fDegree/D3DX_PI > 2.0 * D3DX_PI) 
		m_bShearState = false;
	else if(fDegree <= 0.0f) 
		m_bShearState = true;
}

void COrgan::Shear(D3DXMATRIXA16* _pmMatrix){
	if(m_bShearUse == false)
		return;

	switch(m_bShearState){
		case true:
			SetShearDegree(GetShearDegree() + 0.01f);
			break;
		case false:
			SetShearDegree(GetShearDegree() - 0.01f);
			break;
	}

	*_pmMatrix->m[0,1] = 1/tan(GetShearDegree()/D3DX_PI);

	if(GetShearDegree() > 5.5f) m_bShearState = false;
	else if(GetShearDegree() < 4.5f) m_bShearState = true;
}

void COrgan::BigAndSmall(float _fMaxSca, float _fMinSca, float _fFrequency){
	switch(GetScaleState()){
		case true:
			GetPriSca()->x += _fFrequency;
			GetPriSca()->y += _fFrequency;

			if(GetPriSca()->x > _fMaxSca){
				SetScaState(false);
			}
			break;
		case false:
			GetPriSca()->x -= _fFrequency;
			GetPriSca()->y -= _fFrequency;

			if(GetPriSca()->x < _fMinSca){
				SetScaState(true);
			}
			break;
	}
}

void COrgan::BigAndSmallXYAlternately(float _fMaxSca, float _fFrequency){
	switch(GetScaleState()){
		case true:
			GetPriSca()->x += _fFrequency;
			GetPriSca()->y -= _fFrequency;
			
			m_fBaseAlternateSca += _fFrequency;

			if(m_fBaseAlternateSca > _fMaxSca){
				SetScaState(false);
			}
			break;
		case false:
			GetPriSca()->x -= _fFrequency;
			GetPriSca()->y += _fFrequency;

			m_fBaseAlternateSca -= _fFrequency;

			if(m_fBaseAlternateSca < -_fMaxSca){
				SetScaState(true);
			}
			break;
	}
}

void COrgan::BigAndSmallX(float _fMaxSca, float _fMinSca, float _fFrequency){
	switch(GetScaleState()){
		case true:
			GetPriSca()->x += _fFrequency;

			if(GetPriSca()->x > _fMaxSca){
				SetScaState(false);
			}
			break;
		case false:
			GetPriSca()->x -= _fFrequency;

			if(GetPriSca()->x < _fMinSca){
				SetScaState(true);
			}
			break;
	}
}

int COrgan::BigAndSmallY(float _fMaxSca, float _fMinSca, float _fFrequency){
	switch(GetScaleState()){
		case true:
			GetPriSca()->y += _fFrequency;

			if(GetPriSca()->y > _fMaxSca){
				SetScaState(false);
				return false;
			}
			break;
		case false:
			GetPriSca()->y -= _fFrequency;

			if(GetPriSca()->y < _fMinSca){
				SetScaState(true);
				return true;
			}
			break;
	}

	return -1;
}

void COrgan::RoundTripX(float _fDistance, float _fFrequency){
	switch(GetMoveState()){
		case true:
			GetPriPos()->x += _fFrequency;
			m_fTraceX += _fFrequency;

			if(_fDistance < m_fTraceX)
				SetMoveState(false);
			break;
		case false:
			GetPriPos()->x -= _fFrequency;
			m_fTraceX -= _fFrequency;

			if(-_fDistance > m_fTraceX)
				SetMoveState(true);
			break;
	}
}

void COrgan::RoundTripY(float _fDistance, float _fFrequency){
	switch(GetMoveState()){
		case true:
			GetPriPos()->y += _fFrequency;
			m_fTraceY += _fFrequency;

			if(_fDistance < m_fTraceY)
				SetMoveState(false);
			break;
		case false:
			GetPriPos()->y -= _fFrequency;
			m_fTraceY -= _fFrequency;

			if(-_fDistance > m_fTraceY)
				SetMoveState(true);
			break;
	}
}

// 체인 벡터는 계속 쌓이고 쌓인다.
void COrgan::SettingOrgan(D3DXVECTOR3* _pvChainPos, D3DXVECTOR3* _pvChainSca, D3DXVECTOR3* _pvChainRot, D3DXVECTOR3* _pvChainCen){
	// 현재 신체기관에 연결된 신체기관에 넘겨줄 Transform 양
	// 체인 벡터에서 신체 기관이 바꿔야할 중점 위치를 전달시킨다.
	// 오른쪽 방향이 기준이다.
	_pvChainCen->x = m_vPrimitiveCen.x + _pvChainCen->x;
	_pvChainCen->y = m_vPrimitiveCen.y + _pvChainCen->y;
	_pvChainCen->z = m_vPrimitiveCen.z + _pvChainCen->z;

	_pvChainPos->x = m_vPrimitivePos.x + _pvChainPos->x;
	_pvChainPos->y = m_vPrimitivePos.y + _pvChainPos->y;
	_pvChainPos->z = m_vPrimitivePos.z + _pvChainPos->z;
				 
	_pvChainSca->x = m_vPrimitiveSca.x * _pvChainSca->x;
	_pvChainSca->y = m_vPrimitiveSca.y * _pvChainSca->y;
	_pvChainSca->z = m_vPrimitiveSca.z * _pvChainSca->z;
				 
	_pvChainRot->x = m_vPrimitiveRot.x + _pvChainRot->x;
	_pvChainRot->y = m_vPrimitiveRot.y + _pvChainRot->y;
	_pvChainRot->z = m_vPrimitiveRot.z + _pvChainRot->z;
}

// 체인 벡터는 계속 쌓이고 쌓인다.
void COrgan::SettingOrgan(D3DXVECTOR3* _pvChainPos, D3DXVECTOR3* _pvChainCen){
	// 현재 신체기관에 연결된 신체기관에 넘겨줄 Transform 양
	// 체인 벡터에서 신체 기관이 바꿔야할 중점 위치를 전달시킨다.
	// 오른쪽 방향이 기준이다.
	_pvChainCen->x = m_vPrimitiveCen.x + _pvChainCen->x;
	_pvChainCen->y = m_vPrimitiveCen.y + _pvChainCen->y;
	_pvChainCen->z = m_vPrimitiveCen.z + _pvChainCen->z;

	_pvChainPos->x = m_vPrimitivePos.x + _pvChainPos->x;
	_pvChainPos->y = m_vPrimitivePos.y + _pvChainPos->y;
	_pvChainPos->z = m_vPrimitivePos.z + _pvChainPos->z;
}

// 체인 벡터는 계속 쌓이고 쌓인다.
void COrgan::SettingJointOrgan(D3DXVECTOR3* _pvChainRot, D3DXVECTOR3* _pvChainCen){
	// 현재 신체기관에 연결된 신체기관에 넘겨줄 Transform 양
	// 체인 벡터에서 신체 기관이 바꿔야할 중점 위치를 전달시킨다.
	// 오른쪽 방향이 기준이다.
	_pvChainCen->x = m_vPrimitiveCen.x + _pvChainCen->x;
	_pvChainCen->y = m_vPrimitiveCen.y + _pvChainCen->y;
	_pvChainCen->z = m_vPrimitiveCen.z + _pvChainCen->z;

	_pvChainRot->x = m_vPrimitiveRot.x + _pvChainRot->x;
	_pvChainRot->y = m_vPrimitiveRot.y + _pvChainRot->y;
	_pvChainRot->z = m_vPrimitiveRot.z + _pvChainRot->z;
}

// 렌더링에 앞서 지정해야 할 초기 렌더 상태를 지정한다.
// 회전 벡터는 cur face모드를 위해 있음
void COrgan::preRender(D3DXVECTOR3* _pvRot){
	// ZBuffer 연산 꺼줌
	m_pDevice->SetRenderState(D3DRS_ZENABLE,FALSE);
	m_pDevice->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);

	m_pDevice->SetRenderState(D3DRS_LIGHTING, true);

	m_pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	m_pDevice->SetRenderState(D3DRS_SPECULARENABLE, true);

	m_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);

	// 알파채널1 = 난반사 컬러로 알파 지정
	// 알파채널2 = Texture 컬러로 알파 지정
	m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
	m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);
	// 두 알파채널을 곱하여 조정하여 최종 결과물 결정
	m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	

	// 블렌딩 인수를 지정하여 알파 성분이 투명도를 결정하도록 함
	m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
}

// 오브젝트를 그린다.
void COrgan::Render(D3DXVECTOR3* _pvPos, D3DXVECTOR3* _pvSca, D3DXVECTOR3* _pvRot, D3DXVECTOR3* _pvCen){
	preRender(_pvRot);

	D3DXMATRIXA16 mtMatrix;
	D3DXMatrixIdentity(&mtMatrix);

	D3DXMatrixTranslation(&m_mPos, _pvPos->x, _pvPos->y, _pvPos->z);

	D3DXMATRIXA16 _pmX, _pmY, _pmZ;
	D3DXMatrixIdentity(&_pmX);
	D3DXMatrixIdentity(&_pmY);
	D3DXMatrixIdentity(&_pmZ);

	D3DXMatrixTranslation(&_pmX, _pvPos->x, 0.0f, 0.0f);
	D3DXMatrixTranslation(&_pmY, 0.0f, _pvPos->y, 0.0f);
	D3DXMatrixTranslation(&_pmZ, 0.0f, 0.0f, _pvPos->z);

//	Shear(_vPos, &_pmX, &_pmY, &_pmZ);

	// 원점을 바꾸기 위한 행렬
	D3DXMATRIXA16 _center;
	D3DXMatrixTranslation(&_center, _pvCen->x, _pvCen->y, _pvCen->z);

	D3DXMATRIXA16 rX, rY, rZ;
	D3DXMatrixIdentity(&rX);
	D3DXMatrixIdentity(&rY);
	D3DXMatrixIdentity(&rZ);
	D3DXMatrixRotationX(&rX, _pvRot->x);
	D3DXMatrixRotationY(&rY, _pvRot->y);
	D3DXMatrixRotationZ(&rZ, _pvRot->z);

	m_mRotation = rX*rY*rZ;

	D3DXMatrixScaling(&m_mScale, GetPriSca()->x, GetPriSca()->y, GetPriSca()->z);

	// own 계산은 자기만의 회전 각도를 적용할 때 쓰인다.
	D3DXMATRIXA16 ownRotationX, ownRotationY, ownRotationZ;
	D3DXVECTOR3* vOwnRotation = this->GetPriRot();
	D3DXMatrixRotationZ(&ownRotationZ, vOwnRotation->z);
	D3DXMatrixRotationY(&ownRotationY, vOwnRotation->y);
	D3DXMatrixRotationX(&ownRotationX, vOwnRotation->x);
	D3DXMATRIXA16 ownRotation;
	ownRotation = ownRotationX * ownRotationY * ownRotationZ;

	// 자신만의 Scaling
	D3DXMATRIXA16 ownScale;
	D3DXMatrixIdentity(&ownScale);
	D3DXMatrixTranslation(&ownScale, m_vSca.x, m_vSca.y, m_vSca.z);

	// 방향에 맞는 고유한 pos를 구한다.
	D3DXVECTOR3* vOwnPosition;
	vOwnPosition = GetPriPos();
	
	// 고유한 center를 구한다.
	D3DXVECTOR3* vOwnCenter = this->GetPriCen();
	D3DXMATRIXA16 mOwnPos;
	D3DXMATRIXA16 mOwnCen;
	D3DXMatrixIdentity(&mOwnPos);
	D3DXMatrixIdentity(&mOwnCen);

	D3DXMatrixTranslation(&mOwnPos, vOwnPosition->x, vOwnPosition->y, vOwnPosition->z);
	D3DXMatrixTranslation(&mOwnCen, vOwnCenter->x, vOwnCenter->y, vOwnCenter->z);

	// 시어 적용
	Shear(&mOwnPos);

	D3DXMATRIXA16 Inverse1;
	D3DXMatrixIdentity(&Inverse1);
	D3DXMatrixInverse(&Inverse1, 0, &_center);

	D3DXMATRIXA16 Inverse3;
	D3DXMatrixIdentity(&Inverse3);
	D3DXMatrixInverse(&Inverse3, 0, &mOwnCen);

	mtMatrix *= m_mScale * ownScale * mOwnCen * ownRotation * mOwnPos * Inverse3 * _center * rZ * rX * Inverse1 * rY * _pmX * _pmY * _pmZ;

	m_mWorld = mtMatrix;

	m_pDevice->SetTransform(D3DTS_WORLD, &mtMatrix);

	// 재질과 텍스처를 활성화한다.
	m_pDevice->SetMaterial(&m_Mtrl);
	m_pDevice->SetTexture(0, m_pTexture);

	m_pDevice->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);	// 2차원 텍스처 사용
//	_pDevice->SetTextureStageState( 0, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_CAMERASPACEPOSITION );	/// 카메라 좌표계 변환

	m_pDevice->SetStreamSource(0, m_pQuad, 0, sizeof(Vertex));
	m_pDevice->SetFVF(Vertex::FVF);

	// 활성화된 텍스처를 이용해 기본형을 그린다.
	//_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);	
	m_pDevice->SetIndices(m_pIndex);
	m_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 6, 0, 2);

	// 월드 좌표를 원점으로 되돌린다.
	D3DXMatrixIdentity(&mtMatrix);
	m_pDevice->SetTransform(D3DTS_WORLD, &mtMatrix);

	postRender();
}

void COrgan::RenderApplyScale(D3DXVECTOR3* _pvPos, D3DXVECTOR3* _pvSca, D3DXVECTOR3* _pvCen){
	preRender(&D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	D3DXMATRIXA16 mtMatrix;
	D3DXMatrixIdentity(&mtMatrix);

	D3DXMatrixTranslation(&m_mPos, _pvPos->x, _pvPos->y, _pvPos->z);

	D3DXMATRIXA16 _pmX;
	D3DXMATRIXA16 _pmY;
	D3DXMATRIXA16 _pmZ;
	D3DXMatrixIdentity(&_pmX);
	D3DXMatrixIdentity(&_pmY);
	D3DXMatrixIdentity(&_pmZ);

	D3DXMatrixTranslation(&_pmX, _pvPos->x, 0.0f, 0.0f);
	D3DXMatrixTranslation(&_pmY, 0.0f, _pvPos->y, 0.0f);
	D3DXMatrixTranslation(&_pmZ, 0.0f, 0.0f, _pvPos->z);

	// 원점을 바꾸기 위한 행렬
	D3DXMATRIXA16 _center;
	D3DXMatrixTranslation(&_center, _pvCen->x, _pvCen->y, _pvCen->z);

	D3DXMatrixScaling(&m_mScale, GetPriSca()->x, GetPriSca()->y, GetPriSca()->z);

	// own 계산은 자기만의 회전 각도를 적용할 때 쓰인다.
	D3DXMATRIXA16 ownRotationX, ownRotationY, ownRotationZ;
	D3DXVECTOR3* vOwnRotation = this->GetPriRot();
	D3DXMatrixRotationZ(&ownRotationZ, vOwnRotation->z);
	D3DXMatrixRotationY(&ownRotationY, vOwnRotation->y);
	D3DXMatrixRotationX(&ownRotationX, vOwnRotation->x);
	D3DXMATRIXA16 ownRotation;
	ownRotation = ownRotationX * ownRotationY * ownRotationZ;

	// 자신만의 Scaling
	D3DXMATRIXA16 ownScale;
	D3DXMatrixIdentity(&ownScale);
	D3DXMatrixTranslation(&ownScale, m_vSca.x, m_vSca.y, m_vSca.z);

	// 방향에 맞는 고유한 pos를 구한다.
	D3DXVECTOR3* vOwnPosition;
	vOwnPosition = GetPriPos();
	
	// 고유한 center를 구한다.
	D3DXVECTOR3* vOwnCenter = this->GetPriCen();
	D3DXMATRIXA16 mOwnPos;
	D3DXMATRIXA16 mOwnCen;
	D3DXMatrixIdentity(&mOwnPos);
	D3DXMatrixIdentity(&mOwnCen);

	D3DXMatrixTranslation(&mOwnPos, vOwnPosition->x, vOwnPosition->y, vOwnPosition->z);
	D3DXMatrixTranslation(&mOwnCen, vOwnCenter->x, vOwnCenter->y, vOwnCenter->z);

	D3DXMATRIXA16 Inverse1;
	D3DXMatrixIdentity(&Inverse1);
	D3DXMatrixInverse(&Inverse1, 0, &_center);

	D3DXMATRIXA16 Inverse3;
	D3DXMatrixIdentity(&Inverse3);
	D3DXMatrixInverse(&Inverse3, 0, &mOwnCen);

	mtMatrix *= mOwnCen * ownRotation * mOwnPos * Inverse3 * m_mScale * ownScale * _pmX * _pmY * _pmZ;

	m_mWorld = mtMatrix;

	m_pDevice->SetTransform(D3DTS_WORLD, &mtMatrix);

	// 재질과 텍스처를 활성화한다.
	m_pDevice->SetMaterial(&m_Mtrl);
	m_pDevice->SetTexture(0, m_pTexture);

	m_pDevice->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);	// 2차원 텍스처 사용
//	_pDevice->SetTextureStageState( 0, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_CAMERASPACEPOSITION );	/// 카메라 좌표계 변환

	m_pDevice->SetStreamSource(0, m_pQuad, 0, sizeof(Vertex));
	m_pDevice->SetFVF(Vertex::FVF);

	// 활성화된 텍스처를 이용해 기본형을 그린다.
	//_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);	
	m_pDevice->SetIndices(m_pIndex);
	m_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 6, 0, 2);

	// 월드 좌표를 원점으로 되돌린다.
	D3DXMatrixIdentity(&mtMatrix);
	m_pDevice->SetTransform(D3DTS_WORLD, &mtMatrix);

	postRender();
}