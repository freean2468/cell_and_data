#ifndef _WaveManager_H_
#define _WaveManager_H_

#include <dsound.h>

//입력값을 dB(decibel)로 바꿔주는 매크로 함수
#define DSVOLUME_TO_DB(volume)   ((DWORD)(-30*(100-volume)))  

class CWaveManager{
private:
	LPDIRECTSOUND8 m_lpDirectSound;

private:
	CWaveManager();	// standard constructor
	CWaveManager(const CWaveManager&);
	CWaveManager& operator =(const CWaveManager&);

public:
	~CWaveManager();
	static CWaveManager* Instance(){
		static CWaveManager instance;

		return &instance;
	}

	BOOL LoadWave(LPSTR lpFileName, LPDIRECTSOUNDBUFFER* lpDSBuffer);
	BOOL SetVolume(LPDIRECTSOUNDBUFFER lpDSBuffer, LONG lVolume);

	void Play(LPDIRECTSOUNDBUFFER lpDSBuffer, BOOL Loop);
	void Play(LPSTR lpFileName, BOOL Loop);
	void Stop(LPDIRECTSOUNDBUFFER lpDSBuffer);
};

#define WaveMgr CWaveManager::Instance()

#endif