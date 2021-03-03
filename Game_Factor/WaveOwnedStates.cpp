#include "WaveOwnedStates.h"

///////////////////////////////////////////////////////////
// Usual State
///////////////////////////////////////////////////////////
void CWaveUsual::Enter(CWave* pWave){
	
}

void CWaveUsual::Execute(CWave* pWave){
	pWave->RenderOrgan();
}

void CWaveUsual::Exit(CWave* pWave){

}

bool CWaveUsual::OnMessage(CWave* agent, const Telegram& _rMsg){
	return false;
}