#ifndef _DListIterator_H_
#define _DListIterator_H_

template<class Datatype> class CDListNode;
template<class Datatype> class CDLinkedList;
template<class Datatype> class CDListIterator;

template<class Datatype>
class CDListIterator{
public:
	CDListNode<Datatype>* m_node;
  CDLinkedList<Datatype>* m_list;

public:
  CDListIterator(CDLinkedList<Datatype>* p_list = 0, CDListNode<Datatype>* p_node = 0);

  void Start();
  void End();
  void Forth();
  void Back();
  Datatype& Item();
  bool Valid();
  bool operator==(CDListIterator<Datatype>& p_rhs);
};

template<class Datatype>
CDListIterator<Datatype>::CDListIterator(CDLinkedList<Datatype>* p_list = 0, CDListNode<Datatype>* p_node = 0){
  m_list = p_list;
  m_node = p_node;
}

template<class Datatype>
void CDListIterator<Datatype>::Start(){
  if( m_list != 0 ) m_node = m_list->m_head;
}

template<class Datatype>
void CDListIterator<Datatype>::End(){
  if( m_list != 0 ) m_node = m_list->m_tail;
}

template<class Datatype>
void CDListIterator<Datatype>::Forth(){
  if( m_node != 0 ) m_node = m_node->m_next;
}

template<class Datatype>
void CDListIterator<Datatype>::Back(){
  if( m_node != 0 ) m_node = m_node->m_previous;
}

template<class Datatype>
Datatype& CDListIterator<Datatype>::Item(){
  return m_node->m_data;
}

template<class Datatype>
bool CDListIterator<Datatype>::Valid(){
  return (m_node != 0);
}

template<class Datatype>
bool CDListIterator<Datatype>::operator==(CDListIterator<Datatype>& p_rhs){
  if(m_node == p_rhs.m_node && m_list == p_rhs.m_list){
      return true;
  }
  return false;
}

#endif