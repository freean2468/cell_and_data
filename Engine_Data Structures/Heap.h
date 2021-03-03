#ifndef _Heap_H_
#define _Head_H_

template<class DataType>
class CHeap : public CArray<DataType>{
public:
	int m_count;
	int (*m_compare)(DataType, DataType);

public:
	CHeap(int p_size, int (*p_compare)(DataType, DataType));

	void Enqueue(DataType p_data);
	void Dequeue();
	void WalkUp(int p_index);
	void WalkDown(int p_index);
};

template<class DataType>
CHeap<DataType>::CHeap(int p_size, int (*p_compare)(DataType, DataType))
: CArray<DataType>(p_size + 1){
	m_count = 0;
	m_compare = p_compare;
}

template<class DataType>
void CHeap<DataType>::Enqueue(DataType p_data){
	m_count++;
	if(m_count >= m_size) Resize(m_size * 2);
	m_array[m_count] = p_data;
	WalkUp(m_count);
}

template<class DataType>
void CHeap<DataType>::WalkUp(int p_index){
	int parent = p_index / 2;
	int child = p_index;
	DataType temp = m_array[child];

	while(parent > 0){
		if(m_compare(temp, m_array[parent])>0){
			m_array[child] = m_array[parent];
			child = parent;
			parent /= 2;
		}
		else
			break;
	}
	m_array[child] = temp;
}

template<class DataType>
void CHeap<DataType>::Dequeue(){
	if(m_count >= 1){
		m_array[1] = m_array[m_count];
		WalkDown(1);
		m_count--;
	}
}

template<class DataType>
void CHeap<DataType>::WalkDown(int p_index){
	int parent = p_index;
	int child = p_index * 2;
	DataType temp = m_array[parent];
	while(child < m_count){
		// 오른쪽 자식의 존재 여부를 판단
		if(child < m_count -1){
			// 오른쪽 자식이 더 크다면
			if(m_compare(m_array[child], m_array[child + 1]) < 0){
				child++; // 오른쪽 자식을 가리킨다.
			}
		}
		if(m_compare(temp, m_array[child]) < 0){
			m_array[parent] = m_array[child];
			parent = child;
			child *= 2;
		}
		else
			break;
	}
	m_array[parent] = temp;
}

#endif