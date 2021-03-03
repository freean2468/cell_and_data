#include "SpreadEffect.h"
#include <d3dx9math.h>

CSpreadEffect::CSpreadEffect(const char* _pAdress, D3DXVECTOR3* _pvPos, D3DXCOLOR _Color)	: CBaseEffect(SPREAD)
{
	LoadEntityData(_pAdress);

	UniformOrganColor(_Color);

	m_pvPos = _pvPos;
}

CSpreadEffect::~CSpreadEffect(){

}

void CSpreadEffect::Update(double _dTimeElapsed){
	*(GetBody()->GetPriPos()) = *m_pvPos;

	GetBody()->IncreaseSca(0.01f);
	GetBody()->DecreaseAlpha(0.01f);
	Recycle(GetBody());

	for(int i = 0; i < this->GetAttachmentArray()->GetSize(); ++i){
		GetAttachment(i)->IncreaseSca(0.01f);
		GetAttachment(i)->DecreaseAlpha(0.01f);
		Recycle(GetAttachment(i));
	}
}

void CSpreadEffect::Render(){
	this->RenderOrgan();
}

void CSpreadEffect::Recycle(COrgan* _pOrgan){
	if(_pOrgan->GetAlpha() <= 0.0f){
		_pOrgan->SetAlpha(1.0f);
		_pOrgan->SetPriSca(&D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
}