#ifndef _AStack_H_
#define _AStack_H_

template<class Datatype>
class CAStack : public CArray<Datatype>{
public:
	int m_top;

public:
	CAStack(int p_size);
	
	bool Push(Datatype p_data);
	void Pop();
	Datatype Top();
	int Count();
};

template<class Datatype>
CAStack<Datatype>::CAStack(int p_size) : CArray<Datatype>(p_size){
	m_top = 0;
}

template<class Datatype>
bool CAStack<Datatype>::Push(Datatype p_data){
	if(m_size != m_top){
		m_array[m_top] = p_data;
		m_top++;
		return true;
	}
	return false;
}

template<class Datatype>
void CAStack<Datatype>::Pop(){
	if(m_top > 0) m_top--;
}

template<class Datatype>
Datatype CAStack<Datatype>::Top(){
	return m_array[m_top -1];
}

template<class Datatype>
int CAStack<Datatype>::Count(){
	return m_top;
}

#endif