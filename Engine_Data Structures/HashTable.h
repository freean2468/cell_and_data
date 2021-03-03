#ifndef _HashTable_H_
#define _HashTable_H_

template<class KeyType, class DataType>
class CHashTable{
public:
	int m_size;
	int m_count;
	CArray<CDLinkedList < CHashEntry<KeyType, DataType> > > m_table;
	unsigned long int (*m_hash)(KeyType);

public:
	CHashTable(int p_size, unsigned long int (*p_hash)(KeyType));
	void Insert(KeyType p_key, DataType p_data);
	CHashEntry<KeyType, DataType>* Find(KeyType p_key);
	bool Remove(KeyType p_key);
};

template<class KeyType, class DataType>
CHashTable<KeyType, DataType>::CHashTable(int p_size, unsigned long int (*p_hash)(KeyType)) : m_table(p_size){
	// 크기, 해시 함수, 개수를 설정
	m_size = p_size;
	m_hash = p_hash;
	m_count = 0;
}

template<class KeyType, class DataType>
void CHashTable<KeyType, DataType>::Insert(KeyType p_key, DataType p_data){
	CHashEntry<KeyType, DataType> entry;
	entry.m_data = p_data;
	entry.m_key = p_key;
	int index = m_hash(p_key) % m_size;
	m_table[index].Append(entry);
	m_count++;
}

template<class KeyType, class DataType>
CHashEntry<KeyType, DataType>* CHashTable<KeyType, DataType>::Find(KeyType p_key){
	int index = m_hash(p_key) % m_size;
	CDListIterator< CHashEntry<KeyType, DataType> > itr = m_table[index].GetIterator();

	if(itr.m_node != 0){

		itr.Start();
		while(1){
			if(Itr.Item().m_key == p_key) 
				return &(Itr.Item());
			
			if(itr.Valid()) return 0;
			
			itr.Forth();
		}
	}
	return 0;
}

template<class KeyType, class DataType>
bool CHashTable<KeyType, DataType>::Remove(KeyType p_key){
	int index = m_hash(p_key) % m_size;
	CDListIterator<Entry> itr = m_table[index].GetIterator();
	while(1){
		if(Itr.Item().m_key == p_key){
			m_table[index].Remove(itr);
			m_count--;
			return true;
		}
		if(itr.Valid() == false) return 0;
		itr.Forth();
	}
}

#endif