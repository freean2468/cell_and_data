////////////////////////////////////////////////////
// Collision 담당 관리 클래스
////////////////////////////////////////////////////
#ifndef _CollisionManager_H_
#define _CollisionManager_H_

#include "../Game_Factor/Obstacle.h"
#include "../Game_Factor/CellEntity.h"

class CCollisionManager{
private:
	
private:
	CCollisionManager();
	CCollisionManager(const CCollisionManager&);
	CCollisionManager& operator =(const CCollisionManager&);

public:
	~CCollisionManager();
	static CCollisionManager* Instance(){
		static CCollisionManager instance;

		return &instance;
	}

	bool Overlapped(CObstacle* ob, double MinDistBetweenObstacles = 40.0);

	void EnforceNonPenetrationOtherEntity(CCellEntity* _pEntity);

	bool Collision2DRectWithPoint(RECT* _pRect, Vector2D* _pvPoint);
	bool Collision2DRectWithPoint(RECT* _pRect, D3DXVECTOR3* _pvPoint);
	bool Collision2DRadiusWithPoint(D3DXVECTOR3* _pvPos, float _fRadius, Vector2D* _pvPoint, float _fRadius2 = 0.0f);
	bool Collision2DRadiusWithPoint(D3DXVECTOR3* _pvPos, float _fRadius, D3DXVECTOR3* _pvPoint, float _fRadius2 = 0.0f);

	// 불완전
	bool Collision2DOrganByRect(COrgan* _pOrgan1, COrgan* _pOrgan2);
	bool Collision2DOrganByRect(CAttachment* _pOrgan1, COrgan* _pOrgan2);
	bool Collision2DOrganByRect(CAttachment* _pOrgan1, CAttachment* _pOrgan2);

	bool Collision2DOrganByRadius(COrgan* _pOrgan1, COrgan* _pOrgan2);
	bool Collision2DOrganByWidth(COrgan* _pOrgan1, COrgan* _pOrgan2);
	bool Collision2DOrganByHeight(COrgan* _pOrgan1, COrgan* _pOrgan2);
	bool Collision2DOrganByWidthByRadius(COrgan* _pOrgan1, COrgan* _pOrgan2);
	bool Collision2DOrganByHeightByRadius(COrgan* _pOrgan1, COrgan* _pOrgan2);

	bool Collision2DOrganByRadius(CAttachment* _pOrgan1, COrgan* _pOrgan2);
	bool Collision2DOrganByWidth(CAttachment* _pOrgan1, COrgan* _pOrgan2);
	bool Collision2DOrganByHeight(CAttachment* _pOrgan1, COrgan* _pOrgan2);
	bool Collision2DOrganByWidthByRadius(CAttachment* _pOrgan1, COrgan* _pOrgan2);
	bool Collision2DOrganByHeightByRadius(CAttachment* _pOrgan1, COrgan* _pOrgan2);

	bool Collision2DOrganByRadius(CAttachment* _pOrgan1, CAttachment* _pOrgan2);
	bool Collision2DOrganByWidth(CAttachment* _pOrgan1, CAttachment* _pOrgan2);
	bool Collision2DOrganByHeight(CAttachment* _pOrgan1, CAttachment* _pOrgan2);
	bool Collision2DOrganByWidthByRadius(CAttachment* _pOrgan1, CAttachment* _pOrgan2);
	bool Collision2DOrganByHeightByRadius(CAttachment* _pOrgan1, CAttachment* _pOrgan2);
};

#define CollisionMgr CCollisionManager::Instance()

#endif