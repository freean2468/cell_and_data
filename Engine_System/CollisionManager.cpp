#include "CollisionManager.h"
#include "../Game_Factor/WorldManager.h"
#include "../Engine_System/EntityType.h"
#include "../Engine_Math&Physics/Rectangle.h"
#include "../Engine_Math&Physics/Geometry.h"

CCollisionManager::CCollisionManager(){
	
}

CCollisionManager::~CCollisionManager(){
	
}

bool CCollisionManager::Overlapped(CObstacle* ob, double MinDistBetweenObstacles){
	std::vector<CObstacle*>::const_iterator it;

  for (it=WorldMgr->GetWorld()->GetObstacles().begin(); it != WorldMgr->GetWorld()->GetObstacles().end(); ++it){
    if (TwoCirclesOverlapped(ob->GetPos2D(),
                             ob->GetRadius()+MinDistBetweenObstacles,                             
                             (*it)->GetPos2D(),
                             (*it)->GetRadius()))
    {
      return true;
    }
  }

  return false;
}

void CCollisionManager::EnforceNonPenetrationOtherEntity(CCellEntity* _pEntity){
	for(std::list<CData*>::const_iterator t_itr = WorldMgr->GetWorld()->GetData().begin();
		t_itr != WorldMgr->GetWorld()->GetData().end(); ++t_itr)
	{
		if(!(*t_itr)) continue;
		if(!(*t_itr)->IsAlive()) continue;
    if (*t_itr == _pEntity) continue;
		if((*t_itr)->GetEntityType() != DATA) continue;

    Vector2D ToEntity = _pEntity->GetPos2D() - (*t_itr)->GetPos2D();

    double DistFromEachOther = ToEntity.Length();
    double AmountOfOverLap = (*t_itr)->GetRadius() + _pEntity->GetRadius() - DistFromEachOther;

    if (AmountOfOverLap > 0){
      _pEntity->SetPos(_pEntity->GetPos2D() + (ToEntity/DistFromEachOther) * AmountOfOverLap);
    }
	}

	for(std::list<CVacine*>::const_iterator t_itr = WorldMgr->GetWorld()->GetVacine().begin();
		t_itr != WorldMgr->GetWorld()->GetVacine().end(); ++t_itr)
	{
		if(!(*t_itr)) continue;
		if(!(*t_itr)->IsAlive()) continue;
    if (*t_itr == _pEntity) continue;

    Vector2D ToEntity = _pEntity->GetPos2D() - (*t_itr)->GetPos2D();

    double DistFromEachOther = ToEntity.Length();
    double AmountOfOverLap = (*t_itr)->GetRadius() + _pEntity->GetRadius() - DistFromEachOther;

    if (AmountOfOverLap > 0){
      _pEntity->SetPos(_pEntity->GetPos2D() + (ToEntity/DistFromEachOther) * AmountOfOverLap);
    }
	}
}

bool CCollisionManager::Collision2DRectWithPoint(RECT* _pRect, D3DXVECTOR3* _pvPoint){
	Vector2D t_vPos((double)_pvPoint->x, (double)_pvPoint->y);

	CRectangle t_Rectangle((float)_pRect->left, (float)_pRect->right, (float)_pRect->bottom, (float)_pRect->top);

	if(t_Rectangle.InternalPoint(&t_vPos))
		return true;

	return false;
}

bool CCollisionManager::Collision2DRectWithPoint(RECT* _pRect, Vector2D* _pvPoint){
	CRectangle t_Rectangle((float)_pRect->left, (float)_pRect->right, (float)_pRect->bottom, (float)_pRect->top);

	if(t_Rectangle.InternalPoint(_pvPoint))
		return true;

	return false;
}

bool CCollisionManager::Collision2DRadiusWithPoint(D3DXVECTOR3* _pvPos, float _fRadius, Vector2D* _pvPoint, float _fRadius2){
	Vector2D t_vDist = Vector2D((double)_pvPos->x, (double)_pvPos->y) -	Vector2D((double)_pvPoint->x, 	(double)_pvPoint->y);

	float t_fVal = _fRadius + _fRadius2 - (float)t_vDist.Length();

	if(t_fVal >= 0.0f){		return true;	}
	else{									return false;	}
}

bool CCollisionManager::Collision2DRadiusWithPoint(D3DXVECTOR3* _pvPos, float _fRadius, D3DXVECTOR3* _pvPoint, float _fRadius2){
	Vector2D t_vDist = Vector2D((double)_pvPos->x, (double)_pvPos->y) -	Vector2D((double)_pvPoint->x, 	(double)_pvPoint->y);

	float t_fVal = _fRadius + _fRadius2 - (float)t_vDist.Length();

	if(t_fVal >= 0.0f){		return true;	}
	else{									return false;	}
}

bool CCollisionManager::Collision2DOrganByRect(COrgan* _pOrgan1, COrgan* _pOrgan2){
	Vector2D t_vDist = Vector2D(_pOrgan1->GetPriPos()->x, _pOrgan1->GetPriPos()->y) -
											Vector2D(_pOrgan2->GetPriPos()->x, _pOrgan2->GetPriPos()->y);

	float t_fDist = (float)t_vDist.Length();

	CRectangle t_Rectangle1(_pOrgan1->GetLeft(), _pOrgan1->GetRight(), _pOrgan1->GetBottom(), _pOrgan1->GetTop());
	CRectangle t_Rectangle2(_pOrgan2->GetLeft(), _pOrgan2->GetRight(), _pOrgan2->GetBottom(), _pOrgan2->GetTop());

	if(t_fDist <= _pOrgan1->GetWidthHalf() + _pOrgan2->GetWidthHalf()){
		if(t_Rectangle1.IntersectionRectangle(&t_Rectangle2))
			return true;
	}

	if(t_fDist <= _pOrgan1->GetHeightHalf() + _pOrgan2->GetHeightHalf()){		
		if(t_Rectangle1.IntersectionRectangle(&t_Rectangle2))
			return true;
	}

	return false;
}

bool CCollisionManager::Collision2DOrganByRect(CAttachment* _pOrgan1, COrgan* _pOrgan2){
	Vector2D t_vDist = Vector2D(_pOrgan1->GetPriPos()->x, _pOrgan1->GetPriPos()->y) -
											Vector2D(_pOrgan2->GetPriPos()->x, _pOrgan2->GetPriPos()->y);

	float t_fDist = (float)t_vDist.Length();

	CRectangle t_Rectangle1(_pOrgan1->GetLeft(), _pOrgan1->GetRight(), _pOrgan1->GetBottom(), _pOrgan1->GetTop());
	CRectangle t_Rectangle2(_pOrgan2->GetLeft(), _pOrgan2->GetRight(), _pOrgan2->GetBottom(), _pOrgan2->GetTop());

	if(t_fDist <= _pOrgan1->GetWidthHalf() + _pOrgan2->GetWidthHalf()){
		if(t_Rectangle1.IntersectionRectangle(&t_Rectangle2))
			return true;
	}

	if(t_fDist <= _pOrgan1->GetHeightHalf() + _pOrgan2->GetHeightHalf()){		
		if(t_Rectangle1.IntersectionRectangle(&t_Rectangle2))
			return true;
	}

	return false;
}

bool CCollisionManager::Collision2DOrganByRect(CAttachment* _pOrgan1, CAttachment* _pOrgan2){
	Vector2D t_vDist = Vector2D(_pOrgan1->GetPriPos()->x, _pOrgan1->GetPriPos()->y) -
											Vector2D(_pOrgan2->GetPriPos()->x, _pOrgan2->GetPriPos()->y);

	float t_fDist = (float)t_vDist.Length();

	CRectangle t_Rectangle1(_pOrgan1->GetLeft(), _pOrgan1->GetRight(), _pOrgan1->GetBottom(), _pOrgan1->GetTop());
	CRectangle t_Rectangle2(_pOrgan2->GetLeft(), _pOrgan2->GetRight(), _pOrgan2->GetBottom(), _pOrgan2->GetTop());

	if(t_fDist <= _pOrgan1->GetWidthHalf() + _pOrgan2->GetWidthHalf()){
		if(t_Rectangle1.IntersectionRectangle(&t_Rectangle2))
			return true;
	}

	if(t_fDist <= _pOrgan1->GetHeightHalf() + _pOrgan2->GetHeightHalf()){		
		if(t_Rectangle1.IntersectionRectangle(&t_Rectangle2))
			return true;
	}

	return false;
}

bool CCollisionManager::Collision2DOrganByRadius(COrgan* _pOrgan1, COrgan* _pOrgan2){
	Vector2D t_vDist = Vector2D(_pOrgan1->GetPriPos()->x, _pOrgan1->GetPriPos()->y) -
											Vector2D(_pOrgan2->GetPriPos()->x, _pOrgan2->GetPriPos()->y);

	float t_fVal = _pOrgan1->GetAveRadius() + _pOrgan2->GetAveRadius() - (float)t_vDist.Length();

	if(t_fVal >= 0.0f){		return true;	}
	return false;
}

bool CCollisionManager::Collision2DOrganByWidth(COrgan* _pOrgan1, COrgan* _pOrgan2){
	Vector2D t_vDist = Vector2D(_pOrgan1->GetPriPos()->x, _pOrgan1->GetPriPos()->y) -
											Vector2D(_pOrgan2->GetPriPos()->x, _pOrgan2->GetPriPos()->y);
	
	float t_fVal = _pOrgan1->GetWidthHalf() + _pOrgan2->GetWidthHalf() - (float)t_vDist.Length();

	if(t_fVal >= 0.0f){		return true;	}
	return false;
}

bool CCollisionManager::Collision2DOrganByHeight(COrgan* _pOrgan1, COrgan* _pOrgan2){
	Vector2D t_vDist = Vector2D(_pOrgan1->GetPriPos()->x, _pOrgan1->GetPriPos()->y) -
											Vector2D(_pOrgan2->GetPriPos()->x, _pOrgan2->GetPriPos()->y);
	
	float t_fVal = _pOrgan1->GetHeightHalf() + _pOrgan2->GetHeightHalf() - (float)t_vDist.Length();

	if(t_fVal >= 0.0f){		return true;	}
	return false;
}

bool CCollisionManager::Collision2DOrganByWidthByRadius(COrgan* _pOrgan1, COrgan* _pOrgan2){
	Vector2D t_vDist = Vector2D(_pOrgan1->GetPriPos()->x, _pOrgan1->GetPriPos()->y) -
											Vector2D(_pOrgan2->GetPriPos()->x, _pOrgan2->GetPriPos()->y);
	
	float t_fVal = _pOrgan1->GetWidthHalf() + _pOrgan2->GetAveRadius() - (float)t_vDist.Length();

	if(t_fVal >= 0.0f){		return true;	}
	return false;
}

bool CCollisionManager::Collision2DOrganByHeightByRadius(COrgan* _pOrgan1, COrgan* _pOrgan2){
	Vector2D t_vDist = Vector2D(_pOrgan1->GetPriPos()->x, _pOrgan1->GetPriPos()->y) -
											Vector2D(_pOrgan2->GetPriPos()->x, _pOrgan2->GetPriPos()->y);
	
	float t_fVal = _pOrgan1->GetHeightHalf() + _pOrgan2->GetAveRadius() - (float)t_vDist.Length();

	if(t_fVal >= 0.0f){		return true;	}
	return false;
}

bool CCollisionManager::Collision2DOrganByRadius(CAttachment* _pOrgan1, COrgan* _pOrgan2){
	Vector2D t_vDist = Vector2D(_pOrgan1->GetBody()->GetPriPos()->x, _pOrgan1->GetBody()->GetPriPos()->y) -
											Vector2D(_pOrgan2->GetPriPos()->x, _pOrgan2->GetPriPos()->y);

	float t_fVal = _pOrgan1->GetAveRadius() + _pOrgan2->GetAveRadius() - (float)t_vDist.Length();

	if(t_fVal >= 0.0f){		return true;	}
	return false;
}

bool CCollisionManager::Collision2DOrganByWidth(CAttachment* _pOrgan1, COrgan* _pOrgan2){
	Vector2D t_vDist = Vector2D(_pOrgan1->GetPriPos()->x, _pOrgan1->GetPriPos()->y) -
											Vector2D(_pOrgan2->GetPriPos()->x, _pOrgan2->GetPriPos()->y);
	
	float t_fVal = _pOrgan1->GetWidthHalf() + _pOrgan2->GetWidthHalf() - (float)t_vDist.Length();

	if(t_fVal >= 0.0f){		return true;	}
	return false;
}

bool CCollisionManager::Collision2DOrganByHeight(CAttachment* _pOrgan1, COrgan* _pOrgan2){
	Vector2D t_vDist = Vector2D(_pOrgan1->GetBody()->GetPriPos()->x, _pOrgan1->GetPriPos()->y) -
											Vector2D(_pOrgan2->GetPriPos()->x, _pOrgan2->GetPriPos()->y);
	
	float t_fVal = _pOrgan1->GetHeightHalf() + _pOrgan2->GetHeightHalf() - (float)t_vDist.Length();

	if(t_fVal >= 0.0f){		return true;	}
	return false;
}

bool CCollisionManager::Collision2DOrganByWidthByRadius(CAttachment* _pOrgan1, COrgan* _pOrgan2){
	Vector2D t_vDist = Vector2D(_pOrgan1->GetBody()->GetPriPos()->x, _pOrgan1->GetPriPos()->y) -
											Vector2D(_pOrgan2->GetPriPos()->x, _pOrgan2->GetPriPos()->y);
	
	float t_fVal = _pOrgan1->GetWidthHalf() + _pOrgan2->GetAveRadius() - (float)t_vDist.Length();

	if(t_fVal >= 0.0f){		return true;	}
	return false;
}

bool CCollisionManager::Collision2DOrganByHeightByRadius(CAttachment* _pOrgan1, COrgan* _pOrgan2){
	Vector2D t_vDist = Vector2D(_pOrgan1->GetBody()->GetPriPos()->x, _pOrgan1->GetPriPos()->y) -
											Vector2D(_pOrgan2->GetPriPos()->x, _pOrgan2->GetPriPos()->y);
	
	float t_fVal = _pOrgan1->GetHeightHalf() + _pOrgan2->GetAveRadius() - (float)t_vDist.Length();

	if(t_fVal >= 0.0f){		return true;	}
	return false;
}

bool CCollisionManager::Collision2DOrganByRadius(CAttachment* _pOrgan1, CAttachment* _pOrgan2){
	Vector2D t_vDist = Vector2D(_pOrgan1->GetBody()->GetPriPos()->x, _pOrgan1->GetPriPos()->y) -
											Vector2D(_pOrgan2->GetBody()->GetPriPos()->x, _pOrgan2->GetPriPos()->y);

	float t_fVal = _pOrgan1->GetAveRadius() + _pOrgan2->GetAveRadius() - (float)t_vDist.Length();

	if(t_fVal >= 0.0f){		return true;	}
	return false;
}

bool CCollisionManager::Collision2DOrganByWidth(CAttachment* _pOrgan1, CAttachment* _pOrgan2){
	Vector2D t_vDist = Vector2D(_pOrgan1->GetBody()->GetPriPos()->x , _pOrgan1->GetPriPos()->y) -
											Vector2D(_pOrgan2->GetBody()->GetPriPos()->x, _pOrgan2->GetPriPos()->y);
	
	float t_fVal = _pOrgan1->GetWidthHalf() + _pOrgan2->GetWidthHalf() - (float)t_vDist.Length();

	if(t_fVal >= 0.0f){		return true;	}
	return false;
}

bool CCollisionManager::Collision2DOrganByHeight(CAttachment* _pOrgan1, CAttachment* _pOrgan2){
	Vector2D t_vDist = Vector2D(_pOrgan1->GetBody()->GetPriPos()->x, _pOrgan1->GetPriPos()->y) -
											Vector2D(_pOrgan2->GetBody()->GetPriPos()->x, _pOrgan2->GetPriPos()->y);
	
	float t_fVal = _pOrgan1->GetHeightHalf() + _pOrgan2->GetHeightHalf() - (float)t_vDist.Length();

	if(t_fVal >= 0.0f){		return true;	}
	return false;
}

bool CCollisionManager::Collision2DOrganByWidthByRadius(CAttachment* _pOrgan1, CAttachment* _pOrgan2){
	Vector2D t_vDist = Vector2D(_pOrgan1->GetBody()->GetPriPos()->x, _pOrgan1->GetPriPos()->y) -
											Vector2D(_pOrgan2->GetBody()->GetPriPos()->x, _pOrgan2->GetPriPos()->y);
	
	float t_fVal = _pOrgan1->GetWidthHalf() + _pOrgan2->GetAveRadius() - (float)t_vDist.Length();

	if(t_fVal >= 0.0f){		return true;	}
	return false;
}

bool CCollisionManager::Collision2DOrganByHeightByRadius(CAttachment* _pOrgan1, CAttachment* _pOrgan2){
	Vector2D t_vDist = Vector2D(_pOrgan1->GetBody()->GetPriPos()->x, _pOrgan1->GetPriPos()->y) -
											Vector2D(_pOrgan2->GetBody()->GetPriPos()->x, _pOrgan2->GetPriPos()->y);
	
	float t_fVal = _pOrgan1->GetHeightHalf() + _pOrgan2->GetAveRadius() - (float)t_vDist.Length();

	if(t_fVal >= 0.0f){		return true;	}
	return false;
}