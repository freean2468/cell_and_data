#ifndef _AQueue_H_
#define _AQueue_H_

template<class Datatype>
class CAQueue: public CArray<Datatype>{
public:
	int m_front;
	int m_count;
public:
	CAQueue(int p_size);
	bool Enqueue(Datatype p_data);
	void Dequeue();
	inline Datatype Front();
	// Resize 함수를 그냥 사용하면 대기열이 깨져버린다.

	Datatype& operator[](int p_index);
};

template<class Datatype>
CAQueue<Datatype>::CAQueue(int p_size):Array<Datatype>(p_size){
	m_front = 0;
	m_count = 0;
}

template<class Datatype>
bool CAQueue<Datatype>::Enqueue(Datatype p_data){
	if(m_size != m_count){
		m_array[(m_count + m_front) % m_size] = p_data;
		m_count++;
		return true;
	}
	return false;
}

template<class Datatype>
void CAQueue<Datatype>::Dequeue(){
	if(m_count > 0){
		m_count--;
		m_front++;
		if(m_front == m_size) m_front = 0;
	}
}

template<class Datatype>
Datatype CAQueue<Datatype>::Front(){
	return m_array[m_front];
}

template<class Datatype>
Datatype& CAQueue<Datatype>::operator [](int p_index){
	return m_array[(p_index + m_front) & m_size];
}

#endif