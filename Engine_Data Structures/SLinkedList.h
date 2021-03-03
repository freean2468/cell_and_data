#ifndef _SLinkedList_H_
#define _SLinkedList_H_

template<class Datatype> class CSListNode;
template<class Datatype> class CSListIterator;

template<class Datatype>
class CSLinkedList{
public:
	CSListNode<Datatype>* m_head;
	CSListNode<Datatype>* m_tail;
	int m_count;

public:
	CSLinkedList();
	~CSLinkedList();

	void Append(Datatype p_data);
	void Prepend(Datatype p_data);
	void RemoveHead();
	void RemoveTail();
	CSListIterator<Datatype> GetIterator();
	void Insert(CSListIterator<Datatype>& p_iterator, Datatype p_data);
	void Remove(CSListIterator<Datatype>& p_iterator);
};

template<class Datatype>
CSLinkedList<Datatype>::CSLinkedList(){
	m_head = 0;
	m_tail = 0;
	m_count = 0;
}

template<class Datatype>
CSLinkedList<Datatype>::~CSLinkedList(){
	// 임시 노드 포인터
	CSListNode<Datatype>* itr = m_head;
	CSListNode<Datatype>* next;

	while(itr != m_tail){
		//다음 노드에 대한 포인터를 보존
		next = itr->m_next;

		// 현재 노드를 삭제
		delete itr;

		// 다음 노드를 현재 노드로 설정
		itr = next;
	}
}

template<class Datatype>
void CSLinkedList<Datatype>::Append(Datatype p_data){
	// 목록이 비어 있는지?
	if(m_head == 0){
		// 비어 있다면 새 노드가 머리가 되게 한다.
		m_head = m_tail = new CSListNode<Datatype>;
		
		m_head->m_data = p_data;
		
		m_head->m_next = m_tail;
	}
	else{
		// 꼬리 다음에 새 노드를 삽입하고, 그 노드를 꼬리로 만든다.
		m_tail->InsertAfter(p_data);
		m_tail = m_tail->m_next;
	}
	m_count++;
}

template<class Datatype>
void CSLinkedList<Datatype>::Prepend(Datatype p_data){
	// 새 노드를 생성
	SListNode<Datatype>* newnode = new SListNode<Datatype>;
	newnode->m_data = p_data;
	newnode->m_next = m_head;

	// 머리 노드를 설정하고, 필요하다면 꼬리 노드도 설정한다.
	m_head = newnode;
	if(m_tail ==0) m_tail = m_head;

	m_count++;
}

template<class Datatype>
void CSLinkedList<Datatype>::RemoveHead(){
	SListNode<Datatype>* node = 0;

	if(m_head != 0){
		// 머리의 다음 노드를 가리키는 포인터를 보존
		node = m_head->m_next;

		// 머리를 삭제하고, 다음 노드가 머리가 되게 한다.
		delete m_head;
		m_head = node;

		// m_head가 0이라면 목록이 완전히 빈 것이다.
		// 따라서 꼬리 포인터도 0으로 설정해야 한다.
		if(m_head == 0) m_tail = 0;

		m_count--;
	}
}

template<class Datatype>
void CSLinkedList<Datatype>::RemoveTail(){
	SListNode<Datatype>* node = m_head;

	// 목록이 비어 있지 않은 경우에만 노드를 제거한다.
	if(m_head != 0){
		// 머리와 꼬리가 같은 노드라면 목록에는 노드가
		// 하나 뿐인 것이다. 그 노드를 제거하면 된다.
		if(m_head == m_tail){
			// 그 노드를 제거하고 두 포인터들을 모두 0으로 설정한다.
			delete m_head;
			m_head = m_tail = 0;
		}
		else{
			// 꼬리 노드 직전의 노드를 찾는다.
			while(node->m_next != m_tail) node = node->m_next;
			// 직전의 노드가 꼬리 노드가 되게 하고, 원래의 꼬리 노드를 삭제한다.
			m_tail = node;
			delete node ->m_next;
			node->m_next = 0;
		}
		m_count--;
	}
}

template<class Datatype>
CSListIterator<Datatype> CSLinkedList<Datatype>::GetIterator(){
	return CSListIterator<Datatype>(this, m_head);
}

template<class Datatype>
void CSLinkedList<Datatype>::Insert(CSListIterator<Datatype>& p_iterator, Datatype p_data){
	// 반복자가 이 목록에 속하지 않는다면 아무 일도 하지 않는다.
	if(p_iterator.m_list != this) return;

	if(p_iterator.m_node != 0){
		// 반복자가 유효하다면 새 노드를 삽입
		p_iterator.m_node->InsertAfter(p_data);

		// 반복자가 꼬리 노드를 가리키고 있다면, 새로 삽입된 노드가 꼬리 노드가 되게 한다.
		if(p_iterator.m_node == m_tail) m_tail = p_iterator.m_node->m_next;

		m_count++;
	}
	else{
		// 반복자가 유효하지 않다면 항목을 목록 끝에 추가한다.
		Append(p_data);
	}
}

template<class Datatype>
void CSLinkedList<Datatype>::Remove(CSListIterator<Datatype>& p_iterator){
	CSListNode<Datatype>* node = m_head;

	// 반복자가 이 목록에 속한 것이 아니라면 아무 것도 하지 않는다.
	if(p_iterator.m_list != this) return;

	// 반복자가 유효하지 않으면 아무 것도 하지 않는다.
	if(p_iterator.m_node == 0) return;

	if(p_iterator.m_node == m_head){ // 제거할 노드가 머리이면
		// 반복자를 다음 노드로 옮기고, 머리 노드를 제거한다.
		p_iterator.Forth();
		RemoveHead();
	}
	else{
		// 제거할 노드가 머리가 아니면,제거할 노드의 바로 전 노드를 찾는다.
		while(node->m_next != p_iterator.m_node) node = node->m_next;

		// 반복자를 전진시킨다.
		p_iterator.Forth();

		// 제거할 노드가 꼬리 노드라면, 꼬리 노드를 갱신한다.
		if(node->m_next == m_tail) m_tail = node;

		// 노드를 제거한다.
		delete node->m_next;

		// 목록을 다시 연결시킨다.
		node->m_next = p_iterator.Start;
	}
	m_count--;
}

#endif