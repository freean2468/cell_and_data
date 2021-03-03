#ifndef _Bitvector_H_
#define _Bitvector_H_

#include <stdio.h>
#include <d3d9.h>

class CBitvector{
protected:
	unsigned long int* m_array;
	int m_size;

public:
	CBitvector(int p_size);
	~CBitvector();

	void Resize(int p_size);
	void Set(int p_index, bool p_value);
	void ClearAll();
	void SetAll();
	bool WriteFile(const char* p_filename);
	bool ReadFile(const char* p_filename);

	bool operator[](int p_index);
};

#endif