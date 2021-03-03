#include <string.h>
#include "MyString.h"

CMyString::CMyString(){ 
	strcpy_s(m_string, 128, "");
}

CMyString::CMyString(char* p_strString){
	strcpy_s(m_string, 128, p_strString);
}

bool CMyString::operator==(const CMyString& r_cRight){ 
	return !strcmp(m_string, r_cRight.m_string); 
}