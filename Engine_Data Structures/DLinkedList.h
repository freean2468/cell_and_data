#ifndef _DLinkedList_H_
#define _DLinkedList_H_

#include "DListNode.h"
#include "DListIterator.h"

template<class Datatype>
class CDLinkedList{
public:
	CDListNode<Datatype>* m_head;
  CDListNode<Datatype>* m_tail;
  int m_count;

public:
    CDLinkedList();
    ~CDLinkedList();

    void Append(Datatype p_data);
    void Prepend(Datatype p_data);
    void RemoveHead();
    void RemoveTail();
    void InsertAfter(CDListIterator<Datatype>& p_iterator, Datatype p_data);
    void InsertBefore(CDListIterator<Datatype>& p_iterator, Datatype p_data);
    void Remove(CDListIterator<Datatype>& p_iterator);
    CDListIterator<Datatype> GetIterator();
    int Size();
    bool SaveToDisk(char* p_filename);
    bool ReadFromDisk(char* p_filename);
};

template<class Datatype>
CDLinkedList<Datatype>::CDLinkedList(){
    m_head = 0;
    m_tail = 0;
    m_count = 0;
}

template<class Datatype>
CDLinkedList<Datatype>::~CDLinkedList(){
    CDListNode<Datatype>* node = m_head;
    CDListNode<Datatype>* next;

    while( node != 0 ){
        next = node->m_next;

        delete node;

        node = next;
    }
}

template<class Datatype>
void CDLinkedList<Datatype>::Append(Datatype p_data){
  if( m_head == 0 ){
      m_head = m_tail = new CDListNode<Datatype>;
      m_head->m_data = p_data;
      m_head->m_next = 0;
      m_head->m_previous = 0;
  }
  else{
      m_tail->InsertAfter( p_data );
      m_tail = m_tail->m_next;
  }
  m_count++;
}

template<class Datatype>
void CDLinkedList<Datatype>::Prepend(Datatype p_data){
    if( m_head == 0 )    {
        m_head = m_tail = new CDListNode<Datatype>;
        m_head->m_data = p_data;
        m_head->m_next = 0;
        m_head->m_previous = 0;
    }
    else    {
        m_head->InsertBefore( p_data );
        m_head = m_head->m_previous;
    }
    m_count++;
}

template<class Datatype>
void CDLinkedList<Datatype>::RemoveHead(){
    CDListNode<Datatype>* node = 0;

    if( m_head != 0 )    {
        node = m_head->m_next;

        delete m_head;
        m_head = node;

        if( m_head == 0 )
            m_tail = 0;
        else
            m_head->m_previous = 0;

        m_count--;
    }
}

template<class Datatype>
void CDLinkedList<Datatype>::RemoveTail(){
    CDListNode<Datatype>* node = 0;

    if( m_tail != 0 )    {
        node = m_tail->m_previous;

        delete m_tail;
        m_tail = node;

        if( m_tail == 0 )
            m_head = 0;
        else
            m_tail->m_next = 0;

        m_count--;
    }
}

template<class Datatype>
void CDLinkedList<Datatype>::InsertAfter(CDListIterator<Datatype>& p_iterator, Datatype p_data){
    if( p_iterator.m_node != 0 ){
        p_iterator.m_node->InsertAfter( p_data );

        if( p_iterator.m_node == m_tail )
            m_tail = m_tail->m_next;

        m_count++;
    }
    else{
        Append( p_data );
    }
}

template<class Datatype>
void CDLinkedList<Datatype>::InsertBefore(CDListIterator<Datatype>& p_iterator, Datatype p_data){
    if( p_iterator.m_node != 0 )    {
        p_iterator.m_node->InsertBefore( p_data );

        if( p_iterator.m_node == m_head )
            m_head = m_head->m_previous;

        m_count++;
    }
    else    {
        Prepend( p_data );
    }
}

template<class Datatype>
void CDLinkedList<Datatype>::Remove(CDListIterator<Datatype>& p_iterator){
  CDListNode<Datatype>* node;

	if( p_iterator.m_node == 0 ) return;

  node = p_iterator.m_node;

  if( node == m_head ){
      m_head = m_head->m_next;
  }
  else if( node == m_tail ){
      m_tail = m_tail->m_previous;
  }

	p_iterator.Forth();

  node->Delink();
  delete node;
	node = NULL;

  if( m_head == 0 ) m_tail = 0;
    
  m_count--;
}

template<class Datatype>
CDListIterator<Datatype> CDLinkedList<Datatype>::GetIterator(){
    return CDListIterator<Datatype>( this, m_head );
}

template<class Datatype>
int CDLinkedList<Datatype>::Size(){
    return m_count;
}

template<class Datatype>
bool CDLinkedList<Datatype>::SaveToDisk(char* p_filename){
    FILE* outfile = 0;
    CDListNode<Datatype>* itr = m_head;

    outfile = fopen( p_filename, "wb" );

    if( outfile == 0 ) return false;

    fwrite( &m_count, sizeof( int ), 1, outfile );

    while( itr != 0 )    {
        fwrite( &(itr->m_data), sizeof( Datatype ), 1, outfile );
        itr = itr->m_next;
    }

    fclose( outfile );

    return true;
}

template<class Datatype>
bool CDLinkedList<Datatype>::ReadFromDisk(char* p_filename)
{
    FILE* infile = 0;
    Datatype buffer;
    int count = 0;

    infile = fopen( p_filename, "rb" );

    if( infile == 0 ) return false;

    fread( &count, sizeof( int ), 1, infile );

    while( count != 0 ){
        fread( &buffer, sizeof( Datatype ), 1, infile );
        Append( buffer );
        count--;
    }

    fclose( infile );

    return true;
}

#endif