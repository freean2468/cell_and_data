#ifndef _SListIterator_H_
#define _SListIterator_H_

template<class Datatype> class CSListNode;
template<class Datatype> class CSLinkedList;
template<class Datatype> class CSListIterator;

template<class Datatype>
class CSListIterator{
public:
	CSListNode<Datatype>* m_node;
	CSLinkedList<Datatype>* m_list;
public:
	CSListIterator(CSLinkedList<Datatype>* p_list = 0, CSListNode<Datatype>* p_node = 0);

	void Start();
	void Forth();
	Datatype& Item();
	bool Valid();
};

template<class Datatype>
CSListIterator<Datatype>::CSListIterator(CSLinkedList<Datatype>* p_list = 0, CSListNode<Datatype>* p_node = 0){
	m_list = p_list;
	m_node = p_node;
}

template<class Datatype>
void CSListIterator<Datatype>::Start(){
	if(m_list != 0) m_node = m_list->m_head;
}

template<class Datatype>
void CSListIterator<Datatype>::Forth(){
	if(m_node != m_list->m_tail) m_node = m_node->m_next;
}

template<class Datatype>
Datatype& CSListIterator<Datatype>::Item(){
	return m_node->m_data;
}

template<class Datatype>
bool CSListIterator<Datatype>::Valid(){
	// 현재 노드가 꼬리라면 false를 리턴
	if(m_list->m_tail != m_node){
		return true;	
	}
	else if(m_list->m_tail == m_node){
		return false;
	}
}

#endif