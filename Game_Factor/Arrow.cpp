#include "Arrow.h"
#include "../Engine_System/EngineManager.h"
#include "Virus.h"
#include "Data.h"
#include "Controller.h"
#include "WorldManager.h"
#include "../Engine_System/CameraManager.h"

CArrow::CArrow() : CBasicEntity(-1){
	InitObject(EngineMgr->GetpDevice(), "./Image/UserInterface/Arrow/Arrow.dds", 50, 65, 1.0f, 0);
	SetColor(&D3DXCOLOR(-1.0f, 1.0f, -1.0f, 1.0f));
}

CArrow::~CArrow(){

}

void CArrow::Update(double _dTimeElapsed){
	CVirus* t_pVirus = Controller->GetController();
	CData* t_pClosestData = NULL;

	if(Controller->GetController()->IsAlive()){
		if(WorldMgr->GetMapParam()->m_nFirstData > 0){
			std::list<CData*>::iterator t_itr;
			
			for(t_itr = WorldMgr->GetWorld()->GetData().begin(); t_itr != WorldMgr->GetWorld()->GetData().end(); ++t_itr){
				if(!(*t_itr)->IsAlive()){continue;}

				if((*t_itr)->GetGrowth()->less_equal(t_pVirus->GetGrowth())){
					if(!t_pClosestData){
						t_pClosestData = (*t_itr);
					}
					else{
						Vector2D t_vDistWithClosest = t_pClosestData->GetPos2D() - t_pVirus->GetPos2D();
						Vector2D t_vDistWidthNew = (*t_itr)->GetPos2D() - t_pVirus->GetPos2D();

						if(t_vDistWithClosest.LengthSq() > t_vDistWidthNew.LengthSq()){
							t_pClosestData = (*t_itr);
						}
					}
				}				
			}

			if(t_pClosestData){
				if(EngineMgr->IsViewOut(t_pClosestData->GetPos3D()))	{
					D3DXVECTOR3 t_vPos = *t_pClosestData->GetPos3D();

					//if(t_vPos.x > t_pVirus->GetPos2D().x + SYSTEMWIDTH/2){
					//	t_vPos.x = t_pVirus->GetPos2D().x + SYSTEMWIDTH/2;
					//}
					//if(t_vPos.x < t_pVirus->GetPos2D().x - SYSTEMWIDTH/2){
					//	t_vPos.x = t_pVirus->GetPos2D().x - SYSTEMWIDTH/2;
					//}
					//if(t_vPos.y > t_pVirus->GetPos2D().y + SYSTEMHEIGHT/2){
					//	t_vPos.y = t_pVirus->GetPos2D().y + SYSTEMHEIGHT/2;
					//}
					//if(t_vPos.y	 < t_pVirus->GetPos2D().y - SYSTEMHEIGHT/2){
					//	t_vPos.y	= t_pVirus->GetPos2D().y - SYSTEMHEIGHT/2;
					//}

					D3DXVECTOR3 t_vDist = t_vPos - *t_pVirus->GetPos3D();
					this->GetRot3D()->z = DU::CalAngleConsiderTexture(t_vDist);
					t_vDist*=0.7f;
					t_vDist+=*t_pVirus->GetPos3D();
					SetPos(&t_vDist);

					CameraMgr->GetCamera()->GetPosition(&t_vPos);

					GetPos3D()->z = t_vPos.z + 700.0f;

					CBasicEntity::Render();
				}
			}
		}
	}
}