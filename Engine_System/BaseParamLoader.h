#ifndef _BaseParamLoader_H_
#define _BaseParamLoader_H_

//-----------------------------------------------------------------------------
//
//  Name:   CBaseParamLoader.h
//
//  Desc:   ������ �������� �κ��� ��ġ���� �ε�
//-----------------------------------------------------------------------------

#include "FileLoaderBase.h"

class CBaseParamLoader : public CFileLoaderBase{
public:
  CBaseParamLoader(const char* _pstrFile);
	~CBaseParamLoader(){}
};

#endif