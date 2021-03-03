#ifndef _Array2D_H_
#define _Array2D_H_

template <class Datatype>
class CArray2D{
public:
	Datatype* m_array;
	int m_width;		// 가로
	int m_height;		// 세로

public:
	CArray2D();
	CArray2D(int p_height, int p_width);
	~CArray2D();

	Datatype& Get(int p_y, int p_x);
	void FullArray(int p_height, int p_width);
	void Resize(int p_height, int p_width);
	int GetWidth();
	int GetHeight();
	int GetSize();
};

template<class Datatype>
CArray2D<Datatype>::CArray2D(){
	m_array = 0;
	m_width = 0;
	m_height = 0;
}

template<class Datatype>
CArray2D<Datatype>::CArray2D(int p_height, int p_width){
	m_array = new Datatype[p_width * p_height];
	m_width = p_width + 1;
	m_height = p_height + 1;
}

template<class Datatype>
CArray2D<Datatype>::~CArray2D(){
	if(m_array != 0)
		delete[] m_array;
	m_array = 0;
}

template<class Datatype>
Datatype& CArray2D<Datatype>::Get(int p_y, int p_x){
	// p_y = 행, p_x = 열
	return m_array[p_y * m_width + p_x];
}

template<class Datatype>
void CArray2D<Datatype>::FullArray(int p_height, int p_width){
	if(p_width >= m_width){
		Resize(m_height, p_width+1);
	}
	if(p_height >= m_height){
		Resize(p_height+1, m_width);
	}
}

template<class Datatype>
void CArray2D<Datatype>::Resize(int p_height, int p_width){
	Datatype* newarray = new Datatype[p_width * p_height];
	if(newarray == 0) return;

	int x, y, t1, t2;
	int minx = (p_width < m_width ? p_width : m_width);
	int miny = (p_height < m_height ? p_height : m_height);

	for(y = 0; y < miny; y++){
		t1 = y * p_width;
		t2 = y * m_width;
		for(x = 0; x < minx; x++){
			newarray[t1 + x] = m_array[t2 + x];
		}
	}
	if(m_array != 0)
		delete[] m_array;
	m_array = newarray;
	m_width = p_width;
	m_height = p_height;
}

template<class Datatype>
int CArray2D<Datatype>::GetWidth(){
	return m_width;
}

template<class Datatype>
int CArray2D<Datatype>::GetHeight(){
	return m_height;
}

template<class Datatype>
int CArray2D<Datatype>::GetSize(){
	return m_width * m_height;
}

#endif