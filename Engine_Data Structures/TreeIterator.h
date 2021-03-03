#ifndef _TreeIterator_H_
#define _TreeIterator_H_

template<class DataType> class CDListIterator;

template<class DataType>
class CTreeIterator{
public:
	typedef CTree<DataType> Node;
	Node * m_node;						// 현재 노드를 가리키는 포인터
	CDListIterator<Node*> m_childitr;	// 현재 노드의 현재 자식을 가리키는 반복자

public:
	CTreeIterator(Node* p_node = 0);
	
	void ResetIterator();

	// 수직 반복자 함수
	void Root();
	void Up();
	void Down();

	// 수평 반복자 함수
	void ChildForth();
  void ChildBack();
  void ChildStart();
  void ChildEnd();

	bool ChildValid();

  DataType& ChildItem();

  void AppendChild( Node* p_node );
  void PrependChild( Node* p_node );
  void InsertChildBefore( Node* p_node );
  void InsertChildAfter( Node* p_node );

  void RemoveChild();

	void operator= (Node* p_node);
};

template<class DataType>
CTreeIterator<DataType>::CTreeIterator(Node* p_node){
	// 배정연산자 호출
	*this = p_node;
}

// 배정 연산자는 상수 참조(const &)를 받는 것이 일반적이나, 이 배정 연산자는 트리 노드 포인터를 받는다.
template<class DataType>
void CTreeIterator<DataType>::operator =(Node* p_node){
	m_node = p_node;	// 반복자가 주어진 노드를 가리키게 한다.
	ResetIterator();	// m_childitr 반복자가 p_node의 첫 번째 자식 노드를 가리키게 만든다.
}

// 자식 반복자가 자식 목록의 첫 번째 노드를 가리키도록 만든다. 
//이 함수는 m_node 포인터가 변경될 때마다 호출된다.
template<class DataType>
void CTreeIterator<DataType>::ResetIterator(){
	// 현재 노드가 유효한지 점검
	if(m_node != 0){
		m_childitr = m_node->m_children.GetIterator();
	}
	else{
		m_childitr.m_list = 0;
		m_childitr.m_node = 0;
	}
}

// 반복자를 트리의 루트로 옮긴다.
template<class DataType>
void CTreeIterator<DataType>::Root(){
  if( m_node != 0 )
  {
	// 현재 노드의 부모가 0이 될 떄까지, 즉 루트에 도달할 때까지 계속 반복자를 한 수준 위로 올린다.
    while( m_node->m_parent != 0 )
    {
       m_node = m_node->m_parent;
    }
  }
  ResetIterator();
}

template<class DataType>
void CTreeIterator<DataType>::Up(){
	if(m_node != 0){
		m_node = m_node->m_parent;
	}
	ResetIterator();
}

template<class DataType>
void CTreeIterator<DataType>::Down(){
	if(m_childitr.Valid()){
		m_node = m_childItr.Item();
		ResetIterator();
	}
}

template<class DataType>
void CTreeIterator<DataType>::ChildForth(){
   m_childitr.Forth();
}

template<class DataType>
void CTreeIterator<DataType>::ChildBack(){
   m_childitr.Back();
}

template<class DataType>
void CTreeIterator<DataType>::ChildStart(){
   m_childitr.Start();
}

template<class DataType>
void CTreeIterator<DataType>::ChildEnd(){
   m_childitr.End();
}

template<class DataType>
bool CTreeIterator<DataType>::ChildValid(){
   return m_childitr.Valid();
}

template<class DataType>
DataType& CTreeIterator<DataType>::ChildItem(){
   return m_childitr.Item()->m_data;
}

template<class DataType>
void CTreeIterator<DataType>::AppendChild( Node* p_node ){
  if( m_node != 0 ){
    m_node->m_children.Append( p_node );
    p_node->m_parent = m_node;
  }
}

template<class DataType>
void CTreeIterator<DataType>::PrependChild( Node* p_node ){
  if( m_node != 0 ){
    m_node->m_children.Prepend( p_node );
    p_node->m_parent = m_node;
  }
}

template<class DataType>
void CTreeIterator<DataType>::InsertChildBefore( Node* p_node ){
  if( m_node != 0 ){
    m_node->m_children.InsertBefore( m_childitr, p_node );
    p_node->m_parent = m_node;
  }
}

template<class DataType>
void CTreeIterator<DataType>::InsertChildAfter( Node* p_node ){
  if( m_node != 0 ){
    m_node->m_children.InsertAfter( m_childitr, p_node );
    p_node->m_parent = m_node;
  }
}

template<class DataType>
void CTreeIterator<DataType>::RemoveChild(){
  if( m_node != 0 && m_childitr.Valid() ){
    m_childItr.Item()->m_parent = 0;
    m_node->m_children.Remove( m_childitr );
  }
}

// 임의의 종류의 트리에 대해서 전위운행하는 함수
// 함수 포인터가 가리키는 함수는 하나의 CTree포인터를 매개변수로 받고 아무 것도 반환하지 않아야 한다.
// 어떤 함수를 모든 노드에 대해 작동시키고 싶다면 이 함수를 호출
template<class DataType>
void Preorder(CTree<DataType>* p_node, void (*p_process)(CTree<DataType>*)){
	// 주어진 노드에 대해 p_process 함수 포인터의 함수 호출
	p_process(p_node);

	// 주어진 노드의 자식 목록을 가리키는 반복자 생성
	CDListIterator< CTree<DataType>* > itr = p_node->m_children.GetIterator();

	// 이 반복자를 이용해서 각 자식 노드에 대해 Preorder를 호출
	for(itr.Start(); itr.Valid(); itr.Forth())
		Preorder(Itr.Item(), p_process);
}

// 임의의 종류의 트리에 대해서 후위운행하는 함수
template <class DataType>
void Postorder( CTree<DataType>* p_node, void (*p_process)(CTree<DataType>*) )
{
  // loop through each child and process it
  CDListIterator< CTree<DataType>* > itr = p_node->m_children.GetIterator();

  for( itr.Start(); itr.Valid(); itr.Forth() )
     Postorder( Itr.Item(), p_process );

  // process the current node
  p_process( p_node );
}

#endif