#ifndef _Tree_H_
#define _Tree_H_

template<class DataType> class CDLinkedList;
template<class DataType> class CDListIterator;

template<class DataType>
class CTree{
public:
	typedef CTree<DataType> Node;

	DataType						m_data;				// 자료를 저장할 변수
	Node*								m_parent;			// 부모 노드에 대한 포인터
	CDLinkedList<Node*> m_children;		// 자식 노드들을 담을 연결 목록

public:
	CTree();
	~CTree();

	void Destroy();
	int Count();
};

template<class DataType>
CTree<DataType>::CTree(){
	// 부모 포인터가 0인 트리 노드는 루트 노드로 간주
	m_parent = 0;	
	//CDLinkedList 클래스에 이미 생성자가 있으므로 m_children 목록은 자동적으로
	// 초기화 된다
}

template<class DataType>
CTree<DataType>::~CTree(){
	Destroy();
}

// 이 함수는 재귀적으로 작동하게 된다.
// 자식 노드가 삭제될 때 Destroy()함수 호출
template<class DataType>
void CTree<DataType>::Destroy(){
	CDListIterator<Node*> itr = m_children.GetIterator();
	Node* node = NULL;
	itr.Start();

	while(itr.Valid()){
		node = itr.Item();
		m_children.Remove(itr);
		//delete node;
	}
	//// 노드가 하나도 없다면 반복문에 들어가기 전에 함수가 끝나야 한다.
	//while(1){
	//	// 꼬리라면 (노드가 하나밖에 없다면) 이 if문으로 들어와 반복문을 끝낸다	
	//	node = Itr.Item();
	//	m_children.Remove(itr);
	//	delete node;
	//	if(itr.Valid() == false){
	//		break;
	//	}
	//}
}

// 이 함수 역시 재귀적, 트리에 있는 노드들의 개수를 돌려준다.
template<class DataType>
int CTree<DataType>::Count(){
	int c = 1;	// 1은 현재 노드를 의미

	// 자식 목록에 대한 반복자를 얻고 그 목록의 각 노드(트리)의 자식 노드들의 개수를 c에 누적시킨다.
	CDListIterator<Node*> itr = m_children.GetIterator();

	for(itr.Start(); itr.Valid(); itr.Forth())
		c += itr.Item()->Count();

	return c;
}

#endif