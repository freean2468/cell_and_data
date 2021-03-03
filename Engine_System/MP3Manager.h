#ifndef _MusicManager_H_
#define _MusicManager_H_

#include <dmusici.h>
#include <strmif.h>
#include <control.h>

#define MUSIC_VOLUME_RANGE      ( 0-(DMUS_VOLUME_MIN/4) )

class CMP3Manager{
private:
	IDirectMusicLoader8 *m_pLoader;
	IDirectMusicPerformance8 *m_pPerformance;
	IDirectMusicAudioPath8 *m_pAudioPath;
	
	IGraphBuilder *m_pBuilde;		// 필터 그래프를 담당 한다.
	IMediaControl *m_pControl;		// 컨트롤 담당
	IMediaEventEx *m_pEvent;		// 이벤트 담당
	IMediaSeeking *m_pSeeking;		// 스트리밍 조절을 담당.

	IBasicAudio *m_pAudio;			// 사운드 볼륨, LR 밸런스 조절

	char m_Adress[50];
	char m_OldAdress[50];

	long m_nCode;								// 다렉쇼 현 재생 위치 확인
	LONGLONG m_nOldPos;					// 전에 재생하던 곡의 위치 저장

	long m_nVolume;							// dB 수치
	long m_nLastVolume;
	
	float m_fVolume;						// 실제 볼륨 수치
	float m_fFrequency;					// 볼륨 조절 빈도 수치
	bool m_bFadeUse;						// FadeIn,Out 사용 여부
	bool m_bFade;								// true == IN, false == OUT

	bool m_bIsBgmPlaying;

private:
	CMP3Manager(const CMP3Manager&);
	CMP3Manager& operator =(const CMP3Manager&);

public:
	CMP3Manager();	// standard constructor
	~CMP3Manager();
	static CMP3Manager* Instance(){
		static CMP3Manager instance;

		return &instance;
	}

	__inline IDirectMusicPerformance8* GetPerformance() { return m_pPerformance; }
	__inline bool IsBgmPlaying() const { return m_bIsBgmPlaying; }

	bool Initialize();
	IDirectMusicSegment8* LoadMusic(WCHAR* FileName, IDirectMusicSegment8* Segment);
	void LoadMusicError();
	void Terminate();
	void Reset();

	// Mid & Wav
	void PlayMusic(IDirectMusicSegment8* Segment);
	void StopMusic(IDirectMusicSegment8* Segment);

	long ChangeVolume(long _nVolume);

	// MP3
	void LoadMusic(const char* _pFilename);
	void PlayMusic();
	void StopMusic();
	void ReplayMusic();
	void Loop();
	bool IsEnd();

	void RestoreRecentPos(){m_pSeeking->GetCurrentPosition(&m_nOldPos);}
	
	void PutVolume(float _fVolume);
	float GetVolume(){return m_fVolume;}

	void Fade();
	void OnFade(){m_bFadeUse = true;}
	void OffFade(){m_bFadeUse = false;}
	void FadeInOut(bool _bNew){OnFade(); m_bFade = _bNew;}

	float GetFrequency(){return m_fFrequency;}
	void SetFrequency(float _fFrequency){m_fFrequency = _fFrequency;}
};

#define MP3Mgr CMP3Manager::Instance()

#endif