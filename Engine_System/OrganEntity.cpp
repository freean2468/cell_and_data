#include "OrganEntity.h"
#include "EngineManager.h"
#include "../Engine_Misc/DirectUtils.h"

COrganEntity::COrganEntity(int _nEntityType):CBasicEntity(_nEntityType), 
											m_pBoundRadiusMesh(NULL),
                                            m_pBody(NULL),
											m_vChainPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
											m_vChainSca(D3DXVECTOR3(1.0f, 1.0f, 1.0f)),
											m_vChainRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
											m_vChainCen(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
{	
	for(int i = 0; i < m_Attachment.GetSize(); i++)
		m_Attachment.Get(i) = NULL;
	//// 애니메이션 변수
	//m_dwDelaytime = 300;

	//m_Timer.InitTimer(m_dwDelaytime);

	//D3DXCreateSphere(
	//	EngineMgr->GetpDevice(),
	//	this->GetRadius(),
	//	20,
	//	20,
	//	&m_pBoundRadiusMesh,
	//	0);
}

COrganEntity::~COrganEntity(){
	Delete<CBody*>(m_pBody);
	for(int i = m_Attachment.GetCount(); i > 0; i--){
		Delete<CAttachment*>(m_Attachment[i-1]);
	}
	Release<ID3DXMesh*>(m_pBoundRadiusMesh);
}

void COrganEntity::InitOrgan(){
	Delete<CBody*>(m_pBody);
	for(int i = 0; i < m_Attachment.GetSize(); i++)
		Delete<CAttachment*>(m_Attachment.Get(i));
}

void COrganEntity::LoadEntityData(const char* _pstrName){
	char line[256];
	char string[256];

	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vRot;
	D3DXVECTOR3 vSca;
	D3DXVECTOR3 vCen;

	// organ 사용여부 확인
	// bool을 사용시 오류
	int bIsOrgan = false;
	char cAdress[64];      // 텍스처 주소
	int nWidth;		       // 텍스처 가로 길이
	int nHeight;		   // 텍스처 세로 길이
	float fAlpha = 0.0f;

	FILE* fp;
	if(FAILED(fopen_s(&fp,_pstrName, "r")))
		return;

	// Entity Radius
	fgets(line, 256, fp);	
	sscanf(line, "%s %f ", string, &m_fRadius);

	// Pos Rot Sca Cen
	fgets(line, 256, fp);	

	// 어떤 텍스처를 입힐 지 스크립트 상에서 모두 정할 수 있다.
	// Organ Load
	// Body
	fgets(line, 256, fp);	
	sscanf(line, "%s %d %f %f %f %f %f %f %f %f %f %f %f %f %f %s %d %d", string, &bIsOrgan, &vPos.x, &vPos.y, &vPos.z, 
		&vSca.x, &vSca.y, &vSca.z, &vRot.x, &vRot.y, &vRot.z, &vCen.x, &vCen.y, &vCen.z, &fAlpha, cAdress, &nWidth, &nHeight);
	SetBody(new CBody(vPos, vSca, vRot, vCen));
	GetBody()->InitObject(EngineMgr->GetpDevice(), cAdress, nWidth, nHeight, fAlpha, 0);
	if(!bIsOrgan)GetBody()->m_bBodyFake = true;

	D3DXVECTOR3 t_vSca = D3DXVECTOR3(vSca.x, vSca.y, vSca.z);	// Body의 스케일링 비율을 임시로 저장 후 부속물에 전달

	int nIndex = 0;
	int nType = 0;

	// attachment
	fgets(line, 256, fp);	
	sscanf(line, "%s %d %f %f %f %f %f %f %f %f %f %f %f %f %f %s %d %d %d", string, &nIndex, &vPos.x, &vPos.y, &vPos.z, 
		&vSca.x, &vSca.y, &vSca.z, &vRot.x, &vRot.y, &vRot.z, &vCen.x, &vCen.y, &vCen.z, &fAlpha, cAdress, &nWidth, &nHeight, &nType);
	m_Attachment.Resize(nIndex);
	for(int i = 0; i < nIndex; i++){
		vPos.x *= t_vSca.x;		vPos.y *= t_vSca.y;		vPos.z *= t_vSca.z;	// 스케일링에 따른 비율 조정
		vCen.x *= t_vSca.x;		vCen.y *= t_vSca.y;		vCen.z *= t_vSca.z;

		SetAttachment(new CAttachment(GetBody(), vPos, vSca, vRot, vCen, nType), i);
		GetAttachment(i)->InitObject(EngineMgr->GetpDevice(), cAdress, nWidth, nHeight, fAlpha, 0);

		fgets(line, 256, fp);	
		sscanf(line, "%s %f %f %f %f %f %f %f %f %f %f %f %f %f %s %d %d %d", string, &vPos.x, &vPos.y, &vPos.z, 
			&vSca.x, &vSca.y, &vSca.z, &vRot.x, &vRot.y, &vRot.z, &vCen.x, &vCen.y, &vCen.z, &fAlpha, cAdress, &nWidth, &nHeight, &nType);
	}
	
	fclose(fp);
}

void COrganEntity::ResizeBoundRadius(){
	D3DXCreateSphere(EngineMgr->GetpDevice(),	GetRadius(), 20,	20,	&m_pBoundRadiusMesh,	0);
}

void COrganEntity::ResizeObject(float _fVal){
	SetRadius(GetRadius()*_fVal);

	ResizeBoundRadius();

	ResizeVertex(_fVal, _fVal);
}

void COrganEntity::ResizeObject(float _fWidth, float _fHeight){
	SetRadius(GetRadius()*((_fWidth+_fHeight)*0.5f));

	ResizeBoundRadius();

	ResizeVertex(_fWidth, _fHeight);
}

void COrganEntity::ResizeVertex(float _fWidth, float _fHeight){
	D3DXVECTOR3* t_pVec = NULL;
	float t_fAverage = (_fWidth+_fHeight)*0.5f;

	if(GetBody()){
		GetBody()->ResizeVertex(GetBody()->GetWidth()*_fWidth, GetBody()->GetHeight()*_fHeight);
	}

	for(int i = 0; i < m_Attachment.GetSize(); i++){
		GetAttachment(i)->ResizeVertex(GetAttachment(i)->GetWidth()*_fWidth, GetAttachment(i)->GetHeight()*_fHeight);

		t_pVec = GetAttachment(i)->GetPriPos();

		t_pVec->x *= t_fAverage;
		t_pVec->y *= t_fAverage;
		t_pVec->z *= t_fAverage;
	
		GetAttachment(i)->SetPriPos(t_pVec);

		t_pVec = GetAttachment(i)->GetPriCen();

		t_pVec->x *= t_fAverage;
		t_pVec->y *= t_fAverage;
		t_pVec->z *= t_fAverage;

		GetAttachment(i)->SetPriCen(t_pVec);
	}
}

void COrganEntity::RenderBoundMesh(){
	// Draw bounding volume in blue and at 10% opacity
	D3DMATERIAL9 blue = DU::BLUE_MTRL;
	blue.Diffuse.a = 0.5f; // 10% opacity

	EngineMgr->GetpDevice()->SetMaterial(&blue);
	EngineMgr->GetpDevice()->SetTexture(0, 0); // disable texture

	EngineMgr->GetpDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	EngineMgr->GetpDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	EngineMgr->GetpDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	D3DXMATRIXA16 mtMatrix;
	D3DXMatrixIdentity(&mtMatrix);

	// 방향에 맞는 고유한 pos를 구한다.
	D3DXVECTOR3* vOwnPosition;
	vOwnPosition = GetBody()->GetPriPos();
	
	D3DXMATRIXA16 mOwnPos;
	D3DXMatrixIdentity(&mOwnPos);

	D3DXMatrixTranslation(&mOwnPos, vOwnPosition->x, vOwnPosition->y, vOwnPosition->z);

	mtMatrix *= mOwnPos;

	EngineMgr->GetpDevice()->SetTransform(D3DTS_WORLD, &mtMatrix);

	m_pBoundRadiusMesh->DrawSubset(0);

	// 월드 좌표를 원점으로 되돌린다.
	D3DXMatrixIdentity(&mtMatrix);
	EngineMgr->GetpDevice()->SetTransform(D3DTS_WORLD, &mtMatrix);

	EngineMgr->GetpDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

void COrganEntity::Update(double _dTimeElapsed){
	CBasicEntity::Update();
}

void COrganEntity::RenderOrgan(){
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

void  COrganEntity::UniformOrganScaZero(){
	if(GetBody()){
		GetBody()->GetPriSca()->x = 0.0f;
		GetBody()->GetPriSca()->y = 0.0f;
		GetBody()->GetPriSca()->z = 0.0f;
	}

	for(int i = 0; i < m_Attachment.GetSize(); i++){
		GetAttachment(i)->GetPriSca()->x = 0.0f;
		GetAttachment(i)->GetPriSca()->y = 0.0f;
		GetAttachment(i)->GetPriSca()->z = 0.0f;
	}
}

void	COrganEntity::UniformOrganSca(float _fSca){
	if(GetBody()){
		GetBody()->GetPriSca()->x = _fSca;
		GetBody()->GetPriSca()->y = _fSca;
		GetBody()->GetPriSca()->z = _fSca;
	}

	for(int i = 0; i < m_Attachment.GetSize(); i++){
		GetAttachment(i)->GetPriSca()->x = _fSca;
		GetAttachment(i)->GetPriSca()->y = _fSca;
		GetAttachment(i)->GetPriSca()->z = _fSca;
	}
}

void	COrganEntity::UniformOrganAlpha(float _fAlpha){
	if(GetBody()){
		GetBody()->GetMtrl()->Diffuse.a = _fAlpha;
	}

	//if(GetMessage()){
	//	GetMessage()->GetMtrl()->Diffuse.a = _fAlpha;
	//}

	for(int i = 0; i < m_Attachment.GetSize(); i++){
		GetAttachment(i)->GetMtrl()->Diffuse.a = _fAlpha;
	}
}

void COrganEntity::UniformOrganColor(D3DXCOLOR _vColor){
	if(GetBody()){
		GetBody()->SetColor(&_vColor);
	}

	for(int i = 0; i < m_Attachment.GetSize(); i++){
		GetAttachment(i)->SetColor(&_vColor);
	}
}

CAttachment* COrganEntity::GetAttachmentFromType(int p_nType){
	for(int i = 0; i < m_Attachment.GetSize(); i++){
		if(m_Attachment[i]->GetAttType() == p_nType)
			return m_Attachment[i];
	}
	return NULL;
}

CAttachment* COrganEntity::GetAttachment(int _nIndex){
	return m_Attachment[_nIndex];
}

CArray<CAttachment*>* COrganEntity::GetAttachmentArray(){
	return &m_Attachment;
}

int COrganEntity::GetAttachmentIndex(int p_nType){
	for(int i = 0; i < m_Attachment.GetSize(); i++){
		if(m_Attachment.Get(i)->GetAttType() == p_nType)
			return i;
	}
	return -1;
}

void COrganEntity::RotationZOrgan(D3DXVECTOR3* _pvRot, float _fScalar){
	_pvRot->z += _fScalar;
}

void COrganEntity::RotationYOrgan(D3DXVECTOR3* _pvRot, float _fScalar){
	_pvRot->y += _fScalar;
}

void COrganEntity::RotationXOrgan(D3DXVECTOR3* _pvRot, float _fScalar){
	_pvRot->x += _fScalar;
}

void COrganEntity::TranslationXOrgan(D3DXVECTOR3* _vPos, float _fScalar){
	_vPos->x += _fScalar;
}

void COrganEntity::TranslationYOrgan(D3DXVECTOR3* _vPos, float _fScalar){
	_vPos->y += _fScalar;
}

void COrganEntity::TranslationZOrgan(D3DXVECTOR3* _vPos, float _fScalar){
	_vPos->z += _fScalar;
}

void COrganEntity::TranslationCenXOrgan(D3DXVECTOR3* _pvCen, float _fScalar){
	_pvCen->x += _fScalar;
}

void COrganEntity::TranslationCenYOrgan(D3DXVECTOR3* _pvCen, float _fScalar){
	_pvCen->y += _fScalar;
}

void COrganEntity::TranslationCenZOrgan(D3DXVECTOR3* _pvCen, float _fScalar){
	_pvCen->z += _fScalar;
}