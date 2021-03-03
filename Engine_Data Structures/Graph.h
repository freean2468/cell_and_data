// 그래프를 대표하는 Graph 클래스
// 이 클래스는 모든 노드들을 관리하며 노드 추가 및 제거, 호 추가 및 제거, 호의 표시 및 제거, 노드 탐색 등
// 그래프에 관련된 모든 기능들을 제공한다.
#ifndef _Graph_H_
#define _Graph_H_

template<class NodeType, class ArcType> class CGraphArc;
template<class NodeType, class ArcType> class CGraphNode;
template<class NodeType, class ArcType> class CGraph;
template<class DataType> class CArray;
template<class DataType> class CLQueue;

template<class NodeType, class ArcType>
class CGraph{
public:
	typedef CGraphArc<NodeType, ArcType> Arc;
	typedef CGraphNode<NodeType, ArcType> Node;

	CArray<Node*> m_nodes;	// Node ㅗ인터들의 배열
	int m_count;			// 노드들의 개수를 뜻하는 정수 변수

public:
	CGraph(int p_size);
	~CGraph();

	bool AddNode(NodeType p_data, int p_index);
	void RemoveNode(int p_index);

	bool AddArc(int p_from, int p_to, ArcType p_weight);
	void RemoveArc(int p_from, int p_to);

	CGraphArc<NodeType, ArcType>* GetArc(int p_from, int p_to);

	void ClearMarks();

	void DepthFirst(Node* p_node, void (*p_process)(Node*));
	void BreadthFirst(Node* p_node, void (*p_process)(Node*));
};

template<class NodeType, class ArcType>
CGraph<NodeType, ArcType>::CGraph(int p_size)
: m_nodes(p_size){
	int i;
	for(i = 0; i<p_size; i++)
		m_nodes[i] = 0;
	m_count = 0;
}

template<class NodeType, class ArcType>
CGraph<NodeType, ArcType>::~CGraph(){
	int index;
	for(index = 0; index < m_nodes.m_size; index++){
		if(m_nodes[index] != 0)
			delete m_nodes[index];
	}
}

template<class NodeType, class ArcType>
bool CGraph<NodeType, ArcType>::AddNode(NodeType p_data, int p_index){
	if(m_nodes[p_index] !=)
		return false;
	m_nodes[p_index] = new Node;
	m_nodes[p_index]->m_data = p_data;
	m_nodes[p_index]->m_marked = false;
	m_count++;
	return true;
}

template<class NodeType, class ArcType>
void CGraph<NodeType, ArcType>::RemoveNode(int p_index){
	if(m_nodes[p_index] == 0)
		return;

	int node;
	Arc* arc;

	for(node = 0; node < m_node.Size(); node++){
		if(m_nodes[node] != 0){
			// 그 노드의 호들 중 제거할 노드를 가리키는 호들이 있는지 본다.
			arc = m_nodes[node]->GetArc(m_nodes[p_index]);
			// 제거할 노드를 가리키는 호가 존재한다면 arc는 0이 아니며,
			// 없다면 0이다.
			// 그 노드에서 p_index에 해당하는 노드(제거할 노드)를 가리키는 호가 존재한다면,
			// 그 호를 제거한다.
			if(arc != 0)
				RemoveArc(node, p_index);
		}
	}
	delete m_nodes[p_index];
	m_nodes[p_index] = 0;
	m_count--;
}

// 이 함수는 시작 노드 p_from에서 목표 노드 p_to노드를 가리키며
// 가중치가 p_weight인 호를 추가한다. 함수는 우선 두 노드들이 유효한지 점검하고,
// 둘 중 하나라도 유효하지 않다면 실패를 뜻하는 false를 반환한다.
template<class NodeType, class ArcType>
bool CGraph<NodeType, ArcType>::AddArc(int p_from, int p_to, ArcType p_weight){
	if(m_nodes[p_from] == 0 || m_nodes[p_to] == 0)
		return false;
	// 둘 다 유효하다면, 시작 노드에서 목표 노드를 가리키는 호가 이미 존재하는지 점검한다.
	if(m_ndoes[p_from]->GetArc(m_nodes[p_to]) != 0)
		return false;
	m_nodes[p_from]->AddArc(m_nodes[p_to], p_weight);
	return true;
}

template<class NodeType, class ArcType>
void CGraph<NodeType, ArcType>::RemoveArc(int p_from, int p_to){
	if(m_nodes[p_from] == 0 || m_nodes[p_to] == 0)
		return;
	m_nodes[p_from]->RemoveArc(m_nodes[p_to]);
}

template<class NodeType, class ArcType>
CGraphArc<NodeType, ArcType>* CGraph<NodeType, ArcType>::GetArc(int p_from, int p_to){
	if(m_nodes[p_from] == 0 || m_nodes[p_to] == 0)
		return 0;
	return m_nodes[p_from]->GetArc(m_nodes[p_to]);
}

template<class NodeType, class ArcType>
void CGraph<NodeType, ArcType>::ClearMarks(){
	int index;
	for(index = 0; index < m_nodes.m_size; index++){
		if(m_nodes[index] != 0)
			m_nodes[index]->m_marked = false;
	}
}

// 깊이 우선 탐색 함수
// 시작 노드를 가리키는 노드 포인터와 노드를 처리하는 데 쓰이는 함수를 가리키는 함수 포인터를 받는다.
template<class NodeType, class ArcType>
void CGraph<NodeType, ArcType>::DepthFirst(Node* p_node, void (*p_process)(Node*)){
	if(p_node == 0)
		return;

	p_process(p_node);
	p_node->m_marked = true;

	CDListIterator<CGraphArc <CCoordinates, int> > itr = p_node->m_arcList.GetIterator();

	// 현재 노드의 모든 호들을 훑으면서 아직 표시되지 않은 노드를 가리키는 호가 있으면
	// 그 노드에 대해 이 함수를 재귀적으로 호출
	for(itr.Start(); itr.Valid(); itr.Forth()){
		if(Itr.Item().m_node->m_marked == false){
			DepthFirst(Itr.Item().m_node, p_process);
		}
	}
}

// 너비 우선 탐색 함수
template<class NodeType, class ArcType>
void CGraph<NodeType, ArcType>::BreadthFirst(Node *p_node, void (*p_process)(Node*)){
	if(p_node == 0)
		retrurn;

	// 대기열과 호 반복자 생성
	CLQueue<Node*> quque;
	CDListIterator<Arc> itr;

	// 시작 노드를 대기열에 넣고 표시
	queue.Enqueue(p_node);
	p_node->m_marked = true;

	// 대기열이 빌 때까지
	while(queue.Count() != 0){
		// 대기열의 처음 노드를 처리한 다음
		p_process(queue.Front());
		itr = queue.Front()->m_arcList.GetIterator();
		for(itr.Start(); itr.Valid(); itr.Forth()){
			// 그 노드의 자식 노드들 중 표시가 되어 있지 않은 모든 노드들을
			// 대기열에 넣고 표시한다.
			if(Itr.Item().m_node->m_marked == false){
				Itr.Item().m_node->m_marked = true;
				queue.Enqueue(Itr.Item().m_node);
			}
		}
		// 그런 다음 처음 노드를 큐에서 뽑고 루프를 반복한다.
		queue.Dequeue();
	}
}

#endif