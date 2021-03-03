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
	//	NULL, // IDirectMusic �������̽��� �ҿ�
	//	NULL, // IDirectSound �������̽��� �ҿ�
	//	NULL, // ������ �ڵ�
	//	DMUS_APATH_DYNAMIC_3D , // ����Ʈ�� ������Ľ�Ÿ����
	//	128, // �����ս� ä���� ��
	//	DMUS_AUDIOF_ALL, // �ŵ�������� ���
	//	NULL // ����� �Ķ����, ����Ʈ�� ���
	//);

	CHAR strPath[512];

	sprintf_s(strPath, 512, "");

	// Windows �� �̵�� ���丮�� �˻��Ѵ�.
	//if( GetWindowsDirectory( strPath, MAX_PATH+1 ) == 0 ) return 0;
	//strcat( strPath, "\\media" );

	// Unicode �� ��ȯ�Ѵ�.
	WCHAR wstrSearchPath[MAX_PATH + 1];
	MultiByteToWideChar( CP_ACP, 0, strPath, -1, wstrSearchPath, MAX_PATH );
	wstrSearchPath[MAX_PATH] = 0;

	// �˻� ���丮�� �����Ѵ�.
	m_pLoader->SetSearchDirectory(
		GUID_DirectMusicAllTypes, // �˻��ϴ� ������ Ÿ��
		wstrSearchPath, // �˻��ϴ� ���
		FALSE // ��ü �����͸� Ŭ���� ���� �ʴ´�
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
		NULL, // IDirectMusic �������̽��� �ҿ�
		NULL, // IDirectSound �������̽��� �ҿ�
		NULL, // ������ �ڵ�
		DMUS_APATH_DYNAMIC_3D , // ����Ʈ�� ������Ľ�Ÿ����
		128, // �����ս� ä���� ��
		DMUS_AUDIOF_ALL, // �ŵ�������� ���
		NULL // ����� �Ķ����, ����Ʈ�� ���
	);

	CHAR strPath[512];

	sprintf_s(strPath, 512, "");

	// Windows �� �̵�� ���丮�� �˻��Ѵ�.
	//if( GetWindowsDirectory( strPath, MAX_PATH+1 ) == 0 ) return 0;
	//strcat( strPath, "\\media" );

	// Unicode �� ��ȯ�Ѵ�.
	WCHAR wstrSearchPath[MAX_PATH + 1];
	MultiByteToWideChar( CP_ACP, 0, strPath, -1, wstrSearchPath, MAX_PATH );
	wstrSearchPath[MAX_PATH] = 0;

	// �˻� ���丮�� �����Ѵ�.
	m_pLoader->SetSearchDirectory(
		GUID_DirectMusicAllTypes, // �˻��ϴ� ������ Ÿ��
		wstrSearchPath, // �˻��ϴ� ���
		FALSE // ��ü �����͸� Ŭ���� ���� �ʴ´�
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

// Midi��
IDirectMusicSegment8* CMP3Manager::LoadMusic(WCHAR* FileName, IDirectMusicSegment8* Segment){
	// Ŭ���� �ĺ���, ������ �������̽��� ID, ���ϸ�, �������̽��� �޴� ������
	if (FAILED(m_pLoader->LoadObjectFromFile(CLSID_DirectMusicSegment, 
		IID_IDirectMusicSegment8, FileName, (LPVOID*) &Segment)))
	{
		LoadMusicError();
		return NULL;
	}

	// ���� �ٿ�ε�
	Segment->Download( m_pPerformance );
	Segment->SetRepeats( DMUS_SEG_REPEAT_INFINITE );
	return Segment;
}

void CMP3Manager::StopMusic(IDirectMusicSegment8* Segment){
	m_pPerformance->Stop(
		Segment, // ��� ���׸�Ʈ(segment)�� �����Ѵ�
		NULL, // ��� ���׸�Ʈ(segment) ���¸� �����Ѵ�
		0, // ��� �ǽ��Ѵ�
		0 // �÷���
	);
}

void CMP3Manager::PlayMusic(IDirectMusicSegment8* Segment){
	// ���� ���
	HRESULT hr = m_pPerformance->PlaySegmentEx(
		Segment, // �����ϴ� ���׸�Ʈ(segment)
		NULL, // ������� �ʴ´�
		NULL, // Ʈ�����(transaction)��
		DMUS_SEGF_DEFAULT | DMUS_SEGF_SECONDARY, // �÷���
		0, // ���� Ÿ��, 0 �� ���
		NULL, // ���׸�Ʈ(segment) ���¸� �޴� ������
		NULL, // �����ϴ� ��ü
		NULL // ����� �н�, ����Ʈ�� �ƴ� ���
	);
}

long CMP3Manager::ChangeVolume(long nVolume){
	long nLastVolumeReturn;
	m_nVolume = nVolume;// - MUSIC_VOLUME_RANGE;

	nLastVolumeReturn = m_nLastVolume;
	m_nLastVolume = m_nVolume;

	// 0�� �ְ� �Ҹ� -5000�� ���� ���¼Ҹ�.
	m_pPerformance->SetGlobalParam( GUID_PerfMasterVolume, (void*)&nVolume, sizeof(long) );                    

	return nLastVolumeReturn;
}

//////////////////////////////////////////
//���⼭���ʹ� mp3��
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

	hr=m_pSeeking->SetRate(1);//����� ����
	hr=m_pControl->Run();//����
}

void CMP3Manager::StopMusic(){
	m_pControl->Stop();//����
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

	hr=m_pSeeking->SetRate(1);//����� ����
	m_pSeeking->SetPositions(&lStartPos,AM_SEEKING_AbsolutePositioning, NULL,AM_SEEKING_NoPositioning);
	hr=m_pControl->Run();//����

	OnFade();
	FadeInOut(true);
}

void CMP3Manager::Loop(){
	if (IsEnd())//������ ������ ����� �Ѵ�,
	{
		LONGLONG lStartPos = 0;//������ ���� ������ 0���� ���� �� ó�� ��ġ��
		
		//�ϴ� ������ ���������� �ѹ� ���� ���� �ش�.
		//m_pControl->Stop();
		
		//�ٽ� ��ġ ������ ��´�.
		m_pSeeking->SetPositions(&lStartPos,AM_SEEKING_AbsolutePositioning, NULL,AM_SEEKING_NoPositioning);
		
		//�ٽ� ó������ ������ ��� �Ѵ�.
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