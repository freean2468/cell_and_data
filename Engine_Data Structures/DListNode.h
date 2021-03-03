#ifndef _DListNode_H_
#define _DListNode_H_

template<class Datatype>
class CDListNode{
public:
    Datatype m_data;
    CDListNode<Datatype>* m_next;
    CDListNode<Datatype>* m_previous;

public:
    void Delink();
    void InsertAfter(Datatype p_data);
    void InsertBefore(Datatype p_data);
};

template<class Datatype>
void CDListNode<Datatype>::Delink(){
    if( m_previous != 0 ) m_previous->m_next = m_next;

    if( m_next != 0 ) m_next->m_previous = m_previous;
}

template<class Datatype>
void CDListNode<Datatype>::InsertAfter(Datatype p_data){
    CDListNode<Datatype>* newnode = new CDListNode<Datatype>;
    newnode->m_data = p_data;
    newnode->m_next     = m_next;
    newnode->m_previous = this;

    if( m_next != 0 ) m_next->m_previous = newnode;

    m_next = newnode;
}

template<class Datatype>
void CDListNode<Datatype>::InsertBefore(Datatype p_data){
    CDListNode<Datatype>* newnode = new CDListNode<Datatype>;
    newnode->m_data = p_data;
    newnode->m_next     = this;
    newnode->m_previous = m_previous;

    if( m_previous != 0 ) m_previous->m_next = newnode;

    m_previous = newnode;
}

#endif