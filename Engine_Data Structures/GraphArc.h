#ifndef _GraphArc_H_
#define _GraphArc_H_

template<class NodeType, class ArcType> class CGraphNode;

// 그래프의 호를 대표하는 간단한 클래스,
// 노드를 가리키는 포인터 하나와 호에 부여된 가중치 하나를 저장한다.
template<class NodeType, class ArcType>
class CGraphArc{
public:
	CGraphNode<NodeType, ArcType>* m_node;
	ArcType m_weight;
};

#endif