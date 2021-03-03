#ifndef _Array3D_H_
#define _Array3D_H_

template <class Datatype>
class CArray3D{
public:
	Datatype* m_array;
	int m_width;
	int m_height;
	int m_depth;
public:
	CArray3D(int p_width, int p_height, int p_depth);
	~CArray3D();

	Datatype& Get(int p_x, int p_y, int p_z);
	void Resize(int p_width, int p_height, int p_depth);
	int GetWidth();
	int GetHeight();
	int GetDepth();
	int GetSize();
};

template<class Datatype>
CArray3D<Datatype>::CArray3D(int p_width, int p_height, int p_depth){
	m_array = new Datatype[p_width * p_height * p_depth];
	m_width = p_width;
	m_height = p_height;
	m_depth = p_depth;
}

template<class Datatype>
CArray3D<Datatype>::~CArray3D(){
	if(m_array != 0)
		delete[] m_array;
	m_array = 0;
}

template<class Datatype>
Datatype& CArray3D<Datatype>::Get(int p_x, int p_y, int p_z){
	return m_array[(p_z * m_width * m_height) + (p_y * m_width) + p_x];
}

template<class Datatype>
void CArray3D<Datatype>::Resize(int p_width, int p_height, int p_depth){
	Datatype* newarray = new Datatype[p_width * p_height * p_depth];
	if(newarray == 0) return;

	int x, y, z, t1, t2, t3, t4;
	int minx = (p_width < m_width ? p_width : m_width);
	int miny = (p_height < m_height ? p_height : m_height);
	int minz = (p_depth < m_depth ? p_depth : m_depth);

	for(z = 0; z < minz; z++){
		t1 = z * p_width * p_height;
		t2 = z * m_width * m_height;
		for(y = 0; y < miny; y++){
			t3 = y * p_width;
			t4 = y * m_width;
			for(x = 0; x < minx; x++){
				newarray[t1 + t3 + x] = m_array[t2 + t4 + x];
			}
		}
	}
	if(m_array != 0)
		delete[] m_array;
	m_array = newarray;
	m_width = p_width;
	m_height = p_height;
	m_depth = p_depth;
}

template<class Datatype>
int CArray3D<Datatype>::GetWidth(){
	return m_width;
}

template<class Datatype>
int CArray3D<Datatype>::GetHeight(){
	return m_height;
}

template<class Datatype>
int CArray3D<Datatype>::GetDepth(){
	return m_depth;
}

template<class Datatype>
int CArray3D<Datatype>::GetSize(){
	return m_width * m_height * m_depth;
}

#endif