#ifndef _BinaryTree_H_
#define _BinaryTree_H_

template<class DataType>
class CBinaryTree{
public:
	typedef CBinaryTree<DataType> Node;
	DataType m_data;
	Node* m_parent;
	Node* m_left;
	Node* m_right;
public:
	CBinaryTree();
	~CBinaryTree();

	void Destroy();
	int Count();
};

template<class DataType>
CBinaryTree<DataType>::CBinaryTree(){
	m_parent = 0;
	m_left = 0;
	m_right = 0;
}

template<class DataType>
CBinaryTree<DataType>::~CBinaryTree(){
	Destroy();
}

template<class DataType>
void CBinaryTree<DataType>::Destroy(){
	if(m_left) delete m_left;
	m_left = 0;
	if(m_right) delete m_right;
	m_right;
}

template<class DataType>
int CBinaryTree<DataType>::Count(){
	int c = 1;
	if(m_left) c+= m_left->Count();
	if(m_right) c+= m_right->Count();
	return c;
}

// 전위 운행
template <class DataType>
void Preorder( CBinaryTree<DataType>* p_node, void (*p_process)(CBinaryTree<DataType>*) )
{
    // if the node exists
    if( p_node )
    {
        // process the current node
        p_process( p_node );

        // process the left child
        if( p_node->m_left )
            Preorder( p_node->m_left );

        // process the right node
        if( p_node->m_right )
            Preorder( p_node->m_right );
    }
}

// 중위 운행
template <class DataType>
void Inorder( CBinaryTree<DataType>* p_node, void (*p_process)(CBinaryTree<DataType>*) )
{
    // if the node exists
    if( p_node )
    {
        // process the left node
        if( p_node->m_left )
            Preorder( p_node->m_left );

        // process the current node
        p_process( p_node );

        // process the right node
        if( p_node->m_right )
            Preorder( p_node->m_right );
    }
}

// 후위 운행
template <class DataType>
void Postorder( CBinaryTree<DataType>* p_node, void (*p_process)(CBinaryTree<DataType>*) )
{
    // if the node exists
    if( p_node )
    {
        // process the left node
        if( p_node->m_left )
            Preorder( p_node->m_left );

        // process the right node
        if( p_node->m_right )
            Preorder( p_node->m_right );

        // process the current node
        p_process( p_node );
    }
}

// 노드의 가장 많은 수준을 알아낸다.
template<class DataType>
int GetDepth( CBinaryTree<DataType>* p_tree ){
    // start off with -1 for the depth of each child
    int left = -1;
    int right = -1;

    // calculate the depth of the left child
    if( p_tree->m_left != 0 )
        left = GetDepth( p_tree->m_left );

    // calculate the depth of the right child
    if( p_tree->m_right != 0 )
        right = GetDepth( p_tree->m_right );

    // take the larger of the two depths, add one, and return.
    return ( left > right ? left : right ) + 1;
}

#endif