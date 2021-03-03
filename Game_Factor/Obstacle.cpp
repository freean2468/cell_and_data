#include "Obstacle.h"

CObstacle::CObstacle(double _dX, double _dY, double _dResize):COrganEntity()
{
	LoadEntityData("./Script/GameWorld/Obstacle.txt");

	GetBody()->SetColor(&D3DXCOLOR(1.0f, 1.0f, -1.0f, 1.0f));

	ResizeObject((float)_dResize);
	
	this->SetPos(_dX, _dY);

	GetBody()->GetPriPos()->x = (float)_dX;
	GetBody()->GetPriPos()->y = (float)_dY;
}

CObstacle::CObstacle(Vector2D _vPos, double _dResize):COrganEntity()
{
	LoadEntityData("./Script/GameWorld/Obstacle.txt");
	
	GetBody()->SetColor(&D3DXCOLOR(1.0f, 1.0f, -1.0f, 1.0f));

	ResizeObject((float)_dResize);

	SetPos(_vPos);

	GetBody()->GetPriPos()->x = (float)_vPos.x;
	GetBody()->GetPriPos()->y = (float)_vPos.y;
}

void CObstacle::Update(double _dTimeElapsed){
	//if(Controller->GetController()->GetGrowth()->IsGrowth(CGrowth::FIRST)){
	//	this->UniformSca(0.2f);
	//}
	//else if(Controller->GetController()->GetGrowth()->IsGrowth(CGrowth::SECOND)){
	//	this->UniformSca(0.5f);
	//}
	//else if(Controller->GetController()->GetGrowth()->IsGrowth(CGrowth::THIRD)){
	//	this->UniformSca(0.8f);
	//}
}