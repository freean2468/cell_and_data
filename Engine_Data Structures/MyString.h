////////////////////////////////////////////////////////////
// STL ÀÇ CString Èä³» ÇÔ¼ö
////////////////////////////////////////////////////////////
#ifndef _MyString_H_
#define _MyString_H_

class CMyString{
public:
	char m_string[128];

	CMyString();
	CMyString(char* p_strString);
	bool operator==(const CMyString& r_cRight);
};

#endif