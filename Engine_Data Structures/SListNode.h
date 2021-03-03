#ifndef _SListNode_H_
#define _SListNode_H_

template<class Datatype>
class CSListNode{
public:
	Datatype m_data;
	CSListNode<Datatype*> m_next;

public:
	void InsertAfter(Datatype p_data);
};

template<class Datatype>
void CSListNode<Datatype>::InsertAfter(Datatype p_data){
	// 새 노드를 생성
	CSListNode<Datatype>* newnode = new CSListNode<Datatype>;
	newnode->m_data = p_data;
	// 새 노드가 다음 노드를 가리키게 한다.
	newnode->m_next = m_next;
	// 이전 노드가 새 노드를 가리키게 한다.
	m_next = newnode;
}

#endif