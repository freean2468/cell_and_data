#include "Attachment.h"

CAttachment::CAttachment(D3DXVECTOR3 _vPos, D3DXVECTOR3 _vSca, D3DXVECTOR3 _vRot, D3DXVECTOR3 _vCen, int _nAttType) :
																									COrgan(_vPos, _vSca, _vRot, _vCen),
																										m_pBody(NULL),
																										m_nAttType(_nAttType)
{
}

CAttachment::CAttachment( CBody* _pBody, D3DXVECTOR3 _vPos, D3DXVECTOR3 _vSca, 
												 D3DXVECTOR3 _vRot, D3DXVECTOR3 _vCen, int _nAttType) :
																									COrgan(_vPos, _vSca, _vRot, _vCen),
																										m_pBody(_pBody),
																										m_nAttType(_nAttType)
{
}

CAttachment::~CAttachment(){

}

void CAttachment::RelationshipScaAndPos(D3DXVECTOR3* _pvVec){
	m_vPrimitiveSca.x = _pvVec->x; m_vPrimitiveSca.y = _pvVec->y; m_vPrimitiveSca.z = _pvVec->z;

	m_vPrimitivePos.x *= _pvVec->x;
	m_vPrimitivePos.y *= _pvVec->y;
	m_vPrimitivePos.z *= _pvVec->z;
}

void CAttachment::RelationshipScaAndPos(float _fX, float _fY, float _fZ){
	m_vPrimitiveSca.x = _fX; m_vPrimitiveSca.y = _fY; m_vPrimitiveSca.z = _fZ;

	m_vPrimitivePos.x *= _fX;
	m_vPrimitivePos.y *= _fY;
	m_vPrimitivePos.z *= _fZ;
}

void CAttachment::RelationshipScaAndPos(float _fVal){
	m_vPrimitiveSca.x = _fVal; m_vPrimitiveSca.y = _fVal; m_vPrimitiveSca.z = _fVal;

	m_vPrimitivePos.x *= _fVal;
	m_vPrimitivePos.y *= _fVal;
	m_vPrimitivePos.z *= _fVal;
}

void CAttachment::SetPriSca(D3DXVECTOR3* _pvVec){
	m_vPrimitiveSca.x = _pvVec->x; m_vPrimitiveSca.y = _pvVec->y; m_vPrimitiveSca.z = _pvVec->z;

	RelationshipScaAndPos(_pvVec->x, _pvVec->y, _pvVec->z);
}

void CAttachment::UniformSca(float _fSca){
	m_vPrimitiveSca.x = _fSca; m_vPrimitiveSca.y = _fSca; m_vPrimitiveSca.z = _fSca;

	RelationshipScaAndPos(_fSca);
}

void CAttachment::NoneRelateIncreaseSca(float _fFrequncy){
	GetPriSca()->x += _fFrequncy; GetPriSca()->y += _fFrequncy; GetPriSca()->z += _fFrequncy;
}

void CAttachment::NoneRelateDecreaseSca(float _fFrequncy){
	GetPriSca()->x -= _fFrequncy; GetPriSca()->y -= _fFrequncy; GetPriSca()->z -= _fFrequncy;
}

void CAttachment::IncreaseSca(float _fFrequncy){
	GetPriSca()->x += _fFrequncy; GetPriSca()->y += _fFrequncy; GetPriSca()->z += _fFrequncy;

	RelationshipScaAndPos(GetPriSca());
}

void CAttachment::DecreaseSca(float _fFrequncy){
	GetPriSca()->x -= _fFrequncy; GetPriSca()->y -= _fFrequncy; GetPriSca()->z -= _fFrequncy;

	RelationshipScaAndPos(GetPriSca());
}