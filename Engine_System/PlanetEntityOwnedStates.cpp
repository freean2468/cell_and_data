#include "PlanetEntityOwnedstates.h"

///////////////////////////////////////////////////////////
// PlanetEntityNormal
///////////////////////////////////////////////////////////
void CPlanetEntityNormal::Enter(CPlanetEntity* _pPlanetEntity){
	
}

void CPlanetEntityNormal::Execute(CPlanetEntity* _pPlanetEntity){
	
}

void CPlanetEntityNormal::Exit(CPlanetEntity* _pPlanetEntity){
	
}

///////////////////////////////////////////////////////////
// PlanetEntityCreation
///////////////////////////////////////////////////////////
void CPlanetEntityCreation::Enter(CPlanetEntity* _pPlanetEntity){
	_pPlanetEntity->GetGravity()->SetGravity(0.6f);
}

void CPlanetEntityCreation::Execute(CPlanetEntity* _pPlanetEntity){
	if(_pPlanetEntity->GetGravity()->GetGravity() < 0.99f){
		_pPlanetEntity->GetGravity()->IncreaseGravity(0.002f);
	}
}

void CPlanetEntityCreation::Exit(CPlanetEntity* _pPlanetEntity){
	
}

///////////////////////////////////////////////////////////
// PlanetEntityDie
///////////////////////////////////////////////////////////
void CPlanetEntityDie::Enter(CPlanetEntity* _pPlanetEntity){
	
}

void CPlanetEntityDie::Execute(CPlanetEntity* _pPlanetEntity){
	if(_pPlanetEntity->GetGravity()->GetGravity() > 0.8f){
		_pPlanetEntity->GetGravity()->DecreaseGravity(0.002f);
	}

	if(_pPlanetEntity->GetGravity()->GetGravity() <= 0.8f){
		_pPlanetEntity->OnHide();
	}
}

void CPlanetEntityDie::Exit(CPlanetEntity* _pPlanetEntity){
	
}

///////////////////////////////////////////////////////////
// PlanetEntityDark
///////////////////////////////////////////////////////////
void CPlanetEntityDark::Enter(CPlanetEntity* _pPlanetEntity){
	
}

void CPlanetEntityDark::Execute(CPlanetEntity* _pPlanetEntity){
	_pPlanetEntity->GetMtrl()->Diffuse.b -= 0.02f;
	_pPlanetEntity->GetMtrl()->Diffuse.r -= 0.02f;
	_pPlanetEntity->GetMtrl()->Diffuse.g -= 0.02f;
}

void CPlanetEntityDark::Exit(CPlanetEntity* _pPlanetEntity){
	
}