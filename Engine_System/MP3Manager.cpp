#include "MP3Manager.h"
#include <D3dx9core.h>
#include <dshow.h>
#include "../Engine_Misc/DirectUtils.h"
#include "../Engine_Misc/WindowUtils.h"
#include "App.h"

#define ISMUSICING				true

CMP3Manager::CMP3Manager(void):	m_nVolume(),
								m_nLastVolume(-1),
								m_bIsBgmPlaying(false),
								m_pPerformance(NULL),
								m_pBuilde(NULL),
								m_pControl(NULL),
								m_pEvent(NULL),
								m_pSeeking(NULL),
								m_pAudio(NULL),														
								m_nCode(0),
								m_nOldPos(0),
								m_bFadeUse(false),
								m_bFade(true),
								m_fFrequency(1.0f)
{
	IDirectMusicAudioPath8	*dmAudioPath;

	CoInitialize(NULL);

	CoCreateInstance(CLSID_DirectMusicPerformance, NULL, CLSCTX_INPROC,
		IID_IDirectMusicPerformance8,(void**) &m_pPerformance );

	CoCreateInstance(CLSID_DirectMusicLoader, NULL, CLSCTX_INPROC, 
		IID_IDirectMusicLoader8,	(void**) &m_pLoader);

	CoCreateInstance(CLSID_FilterGraph,NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder,(void**)&m_pBuilde);

	m_pBuilde->QueryInterface(IID_IMediaControl, (void**)&m_pControl);

	m_pBuilde->QueryInterface(IID_IMediaEvent, (void**)&m_pEvent);

	m_pBuilde->QueryInterface(IID_IMediaSeeking, (void**)&m_pSeeking);

	m_pBuilde->QueryInterface(IID_IBasicAudio, (void**)&m_pAudio);

	//m_pPerformance->InitAudio(
	//	NULL, // IDirectMusic 인터페이스는 불요
	//	NULL, // IDirectSound 인터페이스는 불요
	//	NULL, // 윈도우 핸들
	//	DMUS_APATH_DYNAMIC_3D , // 디폴트의 오디오파스타이프
	//	128, // 퍼포먼스 채널의 수
	//	DMUS_AUDIOF_ALL, // 신디사이저의 기능
	//	NULL // 오디오 파라미터, 디폴트를 사용
	//);

	CHAR strPath[512];

	sprintf_s(strPath, 512, "");

	// Windows 의 미디어 디렉토리를 검색한다.
	//if( GetWindowsDirectory( strPath, MAX_PATH+1 ) == 0 ) return 0;
	//strcat( strPath, "\\media" );

	// Unicode 로 변환한다.
	WCHAR wstrSearchPath[MAX_PATH + 1];
	MultiByteToWideChar( CP_ACP, 0, strPath, -1, wstrSearchPath, MAX_PATH );
	wstrSearchPath[MAX_PATH] = 0;

	// 검색 디렉토리를 설정한다.
	m_pLoader->SetSearchDirectory(
		GUID_DirectMusicAllTypes, // 검색하는 파일의 타입
		wstrSearchPath, // 검색하는 장소
		FALSE // 개체 데이터를 클리어 하지 않는다
	);

	//m_pPerformance->GetDefaultAudioPath(&dmAudioPath);

	//ChangeVolume(0);

	//dmAudioPath->SetVolume(0,0);
}

CMP3Manager::~CMP3Manager(void){
	StopMusic();
	Terminate();
}

bool CMP3Manager::Initialize(){
	IDirectMusicAudioPath8	*dmAudioPath;

	CoInitialize(NULL);

	CoCreateInstance(CLSID_DirectMusicLoader, NULL, CLSCTX_INPROC, 
		IID_IDirectMusicLoader8,	(void**) &m_pLoader);

	CoCreateInstance(CLSID_DirectMusicPerformance, NULL, CLSCTX_INPROC,
		IID_IDirectMusicPerformance8,(void**) &m_pPerformance );

	CoCreateInstance(CLSID_FilterGraph,NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder,(void**)&m_pBuilde);

	m_pBuilde->QueryInterface(IID_IMediaControl, (void**)&m_pControl);

	m_pBuilde->QueryInterface(IID_IMediaEvent, (void**)&m_pEvent);

	m_pBuilde->QueryInterface(IID_IMediaSeeking, (void**)&m_pSeeking);

	m_pBuilde->QueryInterface(IID_IBasicAudio, (void**)&m_pAudio);

	m_pPerformance->InitAudio(
		NULL, // IDirectMusic 인터페이스는 불요
		NULL, // IDirectSound 인터페이스는 불요
		NULL, // 윈도우 핸들
		DMUS_APATH_DYNAMIC_3D , // 디폴트의 오디오파스타이프
		128, // 퍼포먼스 채널의 수
		DMUS_AUDIOF_ALL, // 신디사이저의 기능
		NULL // 오디오 파라미터, 디폴트를 사용
	);

	CHAR strPath[512];

	sprintf_s(strPath, 512, "");

	// Windows 의 미디어 디렉토리를 검색한다.
	//if( GetWindowsDirectory( strPath, MAX_PATH+1 ) == 0 ) return 0;
	//strcat( strPath, "\\media" );

	// Unicode 로 변환한다.
	WCHAR wstrSearchPath[MAX_PATH + 1];
	MultiByteToWideChar( CP_ACP, 0, strPath, -1, wstrSearchPath, MAX_PATH );
	wstrSearchPath[MAX_PATH] = 0;

	// 검색 디렉토리를 설정한다.
	m_pLoader->SetSearchDirectory(
		GUID_DirectMusicAllTypes, // 검색하는 파일의 타입
		wstrSearchPath, // 검색하는 장소
		FALSE // 개체 데이터를 클리어 하지 않는다
	);

	m_pPerformance->GetDefaultAudioPath(&dmAudioPath);

	ChangeVolume(0);

	dmAudioPath->SetVolume(0,0);

	PutVolume(100.0f);

	return true;
}

void CMP3Manager::Terminate(){
	Release<IGraphBuilder*>(m_pBuilde);
	Release<IMediaControl*>(m_pControl);
	Release<IMediaEventEx*>(m_pEvent);
	Release<IMediaSeeking*>(m_pSeeking);
	Release<IBasicAudio*>(m_pAudio);

	//m_pPerformance->CloseDown();
	m_pLoader->Release();
	//m_pPerformance->Release();
	CoUninitialize();
}

void CMP3Manager::LoadMusicError(){
	m_pPerformance->CloseDown();
	m_pLoader->Release();
	m_pPerformance->Release();
}

// Midi용
IDirectMusicSegment8* CMP3Manager::LoadMusic(WCHAR* FileName, IDirectMusicSegment8* Segment){
	// 클래스 식별자, 목적의 인터페이스의 ID, 파일명, 인터페이스를 받는 포인터
	if (FAILED(m_pLoader->LoadObjectFromFile(CLSID_DirectMusicSegment, 
		IID_IDirectMusicSegment8, FileName, (LPVOID*) &Segment)))
	{
		LoadMusicError();
		return NULL;
	}

	// 음악 다운로드
	Segment->Download( m_pPerformance );
	Segment->SetRepeats( DMUS_SEG_REPEAT_INFINITE );
	return Segment;
}

void CMP3Manager::StopMusic(IDirectMusicSegment8* Segment){
	m_pPerformance->Stop(
		Segment, // 모든 세그먼트(segment)를 정지한다
		NULL, // 모든 세그먼트(segment) 상태를 정지한다
		0, // 즉시 실시한다
		0 // 플래그
	);
}

void CMP3Manager::PlayMusic(IDirectMusicSegment8* Segment){
	// 음악 재생
	HRESULT hr = m_pPerformance->PlaySegmentEx(
		Segment, // 연주하는 세그먼트(segment)
		NULL, // 사용하지 않는다
		NULL, // 트랜잭션(transaction)용
		DMUS_SEGF_DEFAULT | DMUS_SEGF_SECONDARY, // 플래그
		0, // 시작 타임, 0 은 즉시
		NULL, // 세그먼트(segment) 상태를 받는 포인터
		NULL, // 정지하는 개체
		NULL // 오디오 패스, 디폴트가 아닌 경우
	);
}

long CMP3Manager::ChangeVolume(long nVolume){
	long nLastVolumeReturn;
	m_nVolume = nVolume;// - MUSIC_VOLUME_RANGE;

	nLastVolumeReturn = m_nLastVolume;
	m_nLastVolume = m_nVolume;

	// 0이 최고 소리 -5000이 낮은 없는소리.
	m_pPerformance->SetGlobalParam( GUID_PerfMasterVolume, (void*)&nVolume, sizeof(long) );                    

	return nLastVolumeReturn;
}

//////////////////////////////////////////
//여기서부터는 mp3용
//////////////////////////////////////////

// Range : 0.001f~100.0f
void CMP3Manager::PutVolume(float _fVolume){
	if(_fVolume <= 0.0f)		   _fVolume = 0.001f;
	else if(_fVolume > 100.0f) _fVolume = 100.0f;

	m_pAudio->put_Volume(static_cast<long>(-1000.0f * log10(100.0f/_fVolume)));

	m_fVolume = _fVolume;
}		

void CMP3Manager::Fade(){
	float t_fVolume = GetVolume();

	if(m_bFadeUse){
		if(m_bFade){
			if(t_fVolume + m_fFrequency <= 100.0f){
				PutVolume(t_fVolume + m_fFrequency);
				return;
			}
			else{
				PutVolume(100.0f);
				OffFade();
				return;
			}
		}
		else{
			if(t_fVolume - m_fFrequency > 0.0f){
				PutVolume(t_fVolume - m_fFrequency);
				return;
			}
			else{
				PutVolume(0.001f);
				OffFade();
				return;
			}
		}
	}
}

void CMP3Manager::LoadMusic(const char* _pFilename){	 
	HRESULT hr;

	strcpy_s(m_OldAdress, 50, m_Adress);
	strcpy_s(m_Adress, 50, _pFilename);
	
	hr =  m_pBuilde->RenderFile(CharToWChar(_pFilename),NULL);
	PutVolume(100.0f);
}

void CMP3Manager::PlayMusic(){
	HRESULT hr;

	hr=m_pSeeking->SetRate(1);//재생률 설정
	hr=m_pControl->Run();//실행
}

void CMP3Manager::StopMusic(){
	m_pControl->Stop();//멈춤
}

void CMP3Manager::ReplayMusic(){
	HRESULT hr;

	Reset();

	strcpy_s(m_Adress, 50, m_OldAdress);

	hr =  m_pBuilde->RenderFile(CharToWChar(m_OldAdress),NULL);

	LONGLONG lStartPos = m_nOldPos;

	if(FAILED(m_pSeeking->GetAvailable(0, &m_nOldPos))){
		m_nOldPos = 0;
	}

	hr=m_pSeeking->SetRate(1);//재생률 설정
	m_pSeeking->SetPositions(&lStartPos,AM_SEEKING_AbsolutePositioning, NULL,AM_SEEKING_NoPositioning);
	hr=m_pControl->Run();//실행

	OnFade();
	FadeInOut(true);
}

void CMP3Manager::Loop(){
	if (IsEnd())//음악이 끝나면 재시작 한다,
	{
		LONGLONG lStartPos = 0;//음악의 시작 지점을 0으로 지정 즉 처음 위치로
		
		//일단 음악이 끝났음으로 한번 정지 시켜 준다.
		//m_pControl->Stop();
		
		//다시 위치 설정을 잡는다.
		m_pSeeking->SetPositions(&lStartPos,AM_SEEKING_AbsolutePositioning, NULL,AM_SEEKING_NoPositioning);
		
		//다시 처음부터 음악을 재생 한다.
		m_pControl->Run();
	}
}

bool CMP3Manager::IsEnd(){
	m_pEvent->WaitForCompletion(0,&m_nCode);

	if (m_nCode == EC_COMPLETE){
		return true;	
	}
	else{
		return false;	
	}
}

void CMP3Manager::Reset(){
	Release<IGraphBuilder*>(m_pBuilde);

	CoCreateInstance(CLSID_FilterGraph,NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder,(void**)&m_pBuilde);

	m_pBuilde->QueryInterface(IID_IMediaControl, (void**)&m_pControl);

	m_pBuilde->QueryInterface(IID_IMediaEvent, (void**)&m_pEvent);

	m_pBuilde->QueryInterface(IID_IMediaSeeking, (void**)&m_pSeeking);

	m_pBuilde->QueryInterface(IID_IBasicAudio, (void**)&m_pAudio);
}