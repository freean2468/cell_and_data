#include "Body.h"
#include "../Engine_Misc/DirectUtils.h"

CBody::CBody(D3DXVECTOR3 _vPos, D3DXVECTOR3 _vSca, 
						 D3DXVECTOR3 _vRot, D3DXVECTOR3 _vCen):COrgan(_vPos, _vSca, _vRot, _vCen),
																										m_bBodyFake(false),
																										m_bAngleState(true)
{
}

CBody::~CBody(){

}

// ü�� ���ʹ� ��� ���̰� ���δ�.
void CBody::SettingOrgan(D3DXVECTOR3* _pvChainPos, D3DXVECTOR3* _pvChainSca, D3DXVECTOR3* _pvChainRot, D3DXVECTOR3* _pvChainCen){
	// ���� ��ü����� ����� ��ü����� �Ѱ��� Transform ��
	// ü�� ���Ϳ��� ��ü ����� �ٲ���� ���� ��ġ�� ���޽�Ų��.
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

// ������Ʈ�� �׸���.
void CBody::Render(D3DXVECTOR3* _vPos, D3DXVECTOR3* _pvSca, D3DXVECTOR3* _pvRot, D3DXVECTOR3* _pvCen){
	if(!m_bBodyFake){
		preRender(_pvRot);

		D3DXMATRIXA16 mtMatrix;
		D3DXMatrixIdentity(&mtMatrix);

		D3DXMatrixTranslation(&m_mPos, _vPos->x, _vPos->y, _vPos->z);

		D3DXMatrixScaling(&m_mScale, _pvSca->x, _pvSca->y, _pvSca->z);

		// own ����� �ڱ⸸�� ȸ�� ������ ������ �� ���δ�.
		D3DXMATRIXA16 ownRotationX, ownRotationY, ownRotationZ;
		D3DXVECTOR3* vOwnRotation = this->GetPriRot();
		D3DXMatrixRotationZ(&ownRotationZ, vOwnRotation->z);
		D3DXMatrixRotationY(&ownRotationY, vOwnRotation->y);
		D3DXMatrixRotationX(&ownRotationX, vOwnRotation->x);
		D3DXMATRIXA16 ownRotation;
		ownRotation = ownRotationX * ownRotationY * ownRotationZ;

		// ���⿡ �´� ������ pos�� ���Ѵ�.
		D3DXVECTOR3* vOwnPosition;
		vOwnPosition = GetPriPos();
		
		// ������ center�� ���Ѵ�.
		D3DXVECTOR3* vOwnCenter = this->GetPriCen();
		D3DXMATRIXA16 mOwnPos;
		D3DXMATRIXA16 mOwnCen;
		D3DXMatrixIdentity(&mOwnPos);
		D3DXMatrixIdentity(&mOwnCen);

		D3DXMatrixTranslation(&mOwnPos, vOwnPosition->x, vOwnPosition->y, vOwnPosition->z);
		D3DXMatrixTranslation(&mOwnCen, vOwnCenter->x, vOwnCenter->y, vOwnCenter->z);

		Shear(&mOwnPos);

		mtMatrix *= m_mScale * ownRotationY * ownRotationZ * ownRotationX * mOwnPos;

		m_mWorld = mtMatrix;

		m_pDevice->SetTransform(D3DTS_WORLD, &mtMatrix);

		// ������ �ؽ�ó�� Ȱ��ȭ�Ѵ�.
		m_pDevice->SetMaterial(&m_Mtrl);
		m_pDevice->SetTexture(0, m_pTexture);

		m_pDevice->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);	// 2���� �ؽ�ó ���
	//	m_pDevice->SetTextureStageState( 0, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_CAMERASPACEPOSITION );	/// ī�޶� ��ǥ�� ��ȯ

		m_pDevice->SetStreamSource(0, m_pQuad, 0, sizeof(Vertex));
		m_pDevice->SetFVF(Vertex::FVF);

		// Ȱ��ȭ�� �ؽ�ó�� �̿��� �⺻���� �׸���.
		//m_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);	
		m_pDevice->SetIndices(m_pIndex);
		m_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 6, 0, 2);

		// ���� ��ǥ�� �������� �ǵ�����.
		D3DXMatrixIdentity(&mtMatrix);
		m_pDevice->SetTransform(D3DTS_WORLD, &mtMatrix);

		postRender();
	}
}

void CBody::Render(){
	if(!m_bBodyFake){
		preRender(GetPriRot());

		D3DXMATRIXA16 mtMatrix;
		D3DXMatrixIdentity(&mtMatrix);

		// own ����� �ڱ⸸�� ȸ�� ������ ������ �� ���δ�.
		D3DXMATRIXA16 ownRotationX, ownRotationY, ownRotationZ;
		D3DXVECTOR3* vOwnRotation = this->GetPriRot();
		D3DXMatrixRotationZ(&ownRotationZ, vOwnRotation->z);
		D3DXMatrixRotationY(&ownRotationY, vOwnRotation->y);
		D3DXMatrixRotationX(&ownRotationX, vOwnRotation->x);
		D3DXMATRIXA16 ownRotation;
		ownRotation = ownRotationX * ownRotationY * ownRotationZ;

		// ���⿡ �´� ������ pos�� ���Ѵ�.
		D3DXVECTOR3* vOwnPosition;
		vOwnPosition = GetPriPos();
		
		// ������ center�� ���Ѵ�.
		D3DXVECTOR3* vOwnCenter = this->GetPriCen();
		D3DXMATRIXA16 mOwnPos;
		D3DXMATRIXA16 mOwnCen;
		D3DXMatrixIdentity(&mOwnPos);
		D3DXMatrixIdentity(&mOwnCen);

		D3DXMatrixTranslation(&mOwnPos, vOwnPosition->x, vOwnPosition->y, vOwnPosition->z);
		D3DXMatrixTranslation(&mOwnCen, vOwnCenter->x, vOwnCenter->y, vOwnCenter->z);

		Shear(&mOwnPos);

		mtMatrix *= ownRotationZ * ownRotationX * ownRotationY * mOwnPos;

		m_mWorld = mtMatrix;

		m_pDevice->SetTransform(D3DTS_WORLD, &mtMatrix);

		// ������ �ؽ�ó�� Ȱ��ȭ�Ѵ�.
		m_pDevice->SetMaterial(&m_Mtrl);
		m_pDevice->SetTexture(0, m_pTexture);

		m_pDevice->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);	// 2���� �ؽ�ó ���
	//	m_pDevice->SetTextureStageState( 0, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_CAMERASPACEPOSITION );	/// ī�޶� ��ǥ�� ��ȯ

		m_pDevice->SetStreamSource(0, m_pQuad, 0, sizeof(Vertex));
		m_pDevice->SetFVF(Vertex::FVF);

		// Ȱ��ȭ�� �ؽ�ó�� �̿��� �⺻���� �׸���.
		//m_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);	
		m_pDevice->SetIndices(m_pIndex);
		m_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 6, 0, 2);

		// ���� ��ǥ�� �������� �ǵ�����.
		D3DXMatrixIdentity(&mtMatrix);
		m_pDevice->SetTransform(D3DTS_WORLD, &mtMatrix);

		postRender();
	}
}