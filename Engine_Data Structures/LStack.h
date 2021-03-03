#ifndef _LStack_H_
#define _LStack_H_

template<class Datatype>
class CLStack : public CDLinkedList<Datatype>{
public:
	void Push(Datatype p_Data);
	void Pop();
	Datatype Top();
	int Count();
};

template<class Datatype>
void CLStack<Datatype>::Push(Datatype p_data){
	Append(p_data);
}

template<class Datatype>
void CLStack<Datatype>::Pop(){
	RemoveTail();
}

// Top 함수는 스택이 비어 있으면 제대로 작동하지 않는다.
template<class Datatype>
Datatype CLStack<Datatype>::Top(){
	return m_tail->m_data;
}

template<class Datatype>
int CLStack<Datatype>::Count(){
	return m_count;
}

#endif