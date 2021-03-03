#ifndef _BaseParamLoader_H_
#define _BaseParamLoader_H_

//-----------------------------------------------------------------------------
//
//  Name:   CBaseParamLoader.h
//
//  Desc:   게임의 기초적인 부분의 수치들을 로드
//-----------------------------------------------------------------------------

#include "FileLoaderBase.h"

class CBaseParamLoader : public CFileLoaderBase{
public:
  CBaseParamLoader(const char* _pstrFile);
	~CBaseParamLoader(){}
};

#endif