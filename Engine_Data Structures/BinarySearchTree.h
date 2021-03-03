#ifndef _BinarySearchTree_H_
#define _BinarySearchTree_H_

template<class DataType> class CBinaryTree;

// 실제의 BST 클래스는 하나의 컨테이너일 뿐이다.
template<class DataType>
class CBinarySearchTree{
public:	
	typedef CBinaryTree<DataType> Node;
	Node* m_root;							// 이진 트리, 루트 노드에 대한 포인터
	int (*m_compare)(DataType, DataType);	// 비교 함수를 가리키는 함수 포인터

public:
	CBinarySearchTree(int (*p_compare)(DataType, DataType));
	~CBinarySearchTree();

	void Insert(DataType p_data);
	CBinaryTree<DataType>* Find(DataType p_data);
};

// 비교 함수는 트리에 자료를 삽입할 떄 쓰이며, 자료들이 트리에 삽입된 후 비교 함수가 바뀌면 결과적으로 그 트리의 유효성이 깨지게 된다.
template<class DataType>
CBinarySearchTree<DataType>::CBinarySearchTree(int (*p_compare)(DataType, DataType)){
	m_root = 0;
	m_compare = p_compare;
}

template<class DataType>
CBinarySearchTree<DataType>::~CBinarySearchTree(){
	if(m_root != 0) delete m_root;
}

// 일반적으로 BST는 중복된 자료의 삽입을 허용하지 않지만, 이 Insert함수는 자료의 중복을 점검하지 않는다.
// 게다가 이 BST 클래스는 노드의 제거를 지원하지 않으므로, 중복된 자료를 트리에 삽입하면 결국
// 공간이 낭비된다. Find 함수는 중복된 자료를 결코 찾지 못하므로(그냥 첫번쨰로 만나는 것을
// 돌려줄 뿐이다), 중복된 자료는 아무 의미 없이 공간만 차지하게 된다.
template<class DataType>
void CBinarySearchTree<DataType>::Insert(DataType p_data){
	Node* current = m_root;
	if(m_root == 0)
		m_root = new Node(p_data);
	else{
		while(current != 0){
			if(m_compare(p_data, current->m_data) < 0){
				if(current->m_left == 0){
					current->m_left = new Node(p_data);
					current->m_left->m_parent = current;
					current = 0;
				}
				else
					current = current->m_left;
			}
			else{
				if(current->m_right = 0){
					current->m_right = new Node(p_data);
					current->m_right->m_parent = current;
					current = 0;
				}
				else
					current = current->m_right;
			}
		}
	}
}

template<class DataType>
CBinaryTree<DataType>* CBinarySearchTree<DataType>::Find(DataType p_data){
	Node* current = m_root;
	int temp;
	while(current != 0){
		temp = m_compare(p_data, current->m_data);
		if( temp == 0)
			return curreunt;
		if(temp <0)
			current = current->m_left;
		else
			current = current->m_right;
	}
	return 0;
}

#endif