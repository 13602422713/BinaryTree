#include "BinarySearchTree.h"

template <typename T>
class AVLTree:public BinarySearchTree<T>
{
public:
	AVLTree(int size,int rootIndex,T data);
	AVLTree(vector<T> vect);
	virtual ~AVLTree();

	//get
	vector<T> getResult();

	//add/delete
	virtual bool addNode(int index,T data);
	virtual bool insert(int index,T data, BiTreeNode<T> *pNode);
	virtual bool deleteMinNode();
	virtual bool deleteMaxNode();

	virtual bool deleteNodeByIndex(int index);						//删除节点（使用索引）
	virtual bool deleteNodeByNode(BiTreeNode<T> *pNode);			//删除节点（使用地址）
	virtual bool deleteNodeByData(T data);							//删除节点（使用数据）
private:
	void RightRotate(BiTreeNode<T> *root);
	void LeftRotate(BiTreeNode<T> *root);
	void RightBalance();
	void LeftBalance();

};


template <typename T>
AVLTree<T>::AVLTree(int size,int rootIndex,T data):BinarySearchTree(size, rootIndex ,data)
{
	
}

template <typename T>
AVLTree<T>::AVLTree(vector<T> vect):BinarySearchTree((int)vect.size(),0,vect[0])
{
	unsigned int size = vect.size();
	for(unsigned int i=1;i<size;i++)
	{
		this->addNode(i,vect[i]);
	}
}

template <typename T>
AVLTree<T>::~AVLTree()
{
	
}



template <typename T>
void AVLTree<T>::RightRotate(BiTreeNode<T> *root)
{
	BiTreeNode<T> newRoot = root->getLChild();
	root->setLChild( newRoot->getRChild() );
	newRoot-setRChild( root );
	root = newRoot;
}

template <typename T>
void AVLTree<T>::LeftRotate(BiTreeNode<T> *root)
{
	BiTreeNode<T> newRoot = root->getRChild();
	root->setRChild( newRoot->getLChild() );
	newRoot-setLChild( root );
	root = newRoot;
}


template <typename T>
void AVLTree<T>::RightBalance()
{
	
}

template <typename T>
void AVLTree<T>::LeftBalance()
{
	BiTreeNode<T> LChildNode = m_pRoot->getLChild();
	switch( newRoot->getBalanceFactor() )
	{
	case 1://left heigher
		newRoot->setBalanceFactor(0);
		m_pRoot->setBalanceFactor( newRoot->getBalanceFactor() );
		RightRotate(m_pRoot);
		break;
	case -1://right heigher
		BiTreeNode<T> RChildNode = LChildNode->getRChild();
		switch ( RChildNode ->getBalanceFactor() )
		{
		case 1:
			m_pRoot->setBalanceFactor(-1);
			LChildNode-setBalanceFactor(0);
			break;
		case:
			LChildNode
			m_pRoot->setBalanceFactor(LChildNode->getBalanceFactor())
			break;
		case:
			break;
		}
		break;
	}
}
