#include "../BaseHeader.h"

CMyString::CMyString(){ 
	::strcpy_s(m_string, 1, "");
}

CMyString::CMyString(char* p_strString){
	::strcpy_s(m_string,256, p_strString);
}

bool CMyString::operator==(const CMyString& r_cRight){ 
	return !strcmp(m_string, r_cRight.m_string); 
}