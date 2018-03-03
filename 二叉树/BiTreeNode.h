#ifndef _BITREENODE_H
#define _BITREENODE_H
#include<iostream>
using namespace std;


template <typename T>
class BiTreeNode
{
public:
	BiTreeNode();
	BiTreeNode(int index,T data);
	virtual ~BiTreeNode();
	//get data
	int getIndex();
	T getData();
	BiTreeNode *getParent();
	BiTreeNode *getLChild();
	BiTreeNode *getRChild();
	BiTreeNode *getInorderPrecursor();					//获取中序前驱
	BiTreeNode *getInorderSubsequence();				//获取中序后继
	//set data
	void setIndex(int index);
	void setData(T data);
	void setParenet(BiTreeNode *Node);
	void setLChild(BiTreeNode *Node);
	void setRChild(BiTreeNode *Node);
	//else
	BiTreeNode *NodeSearch(int index);					//通过索引搜索节点（以本节点作为根寻找树的某个节点）
	int NodeLeavesStatistics(int leaves = 0);			//统计叶子数
	int NodeChildrenNodeHeigh();						//统计子节点的最大高度（包含本节点）/（以本节点作为根求树的高度）
	int NodeChildrenStatistics();						//统计子节点数(包含本节点)
	int NodeDelete();									//删除节点
	//traversal
	void NodePreorderTraversal();
	void NodeInorderTraversal();
	void NodeSubsequentTraversal();
	
	//use in balance tree.
	int getBalanceFactor();
	bool setBalanceFactor(int balance);

private:
	int m_iIndex;
	T m_tData;
	BiTreeNode *m_pParent;
	BiTreeNode *m_pLeftChild;
	BiTreeNode *m_pRightChild;
	//struct NodeWidth<T> stNodeWidth;

	//use in balance tree.
	int m_iBalancefactor;
};

template <typename T>
BiTreeNode<T>::BiTreeNode()
{
	m_iIndex = 0;
	m_tData = 0;
	m_pParent = NULL;
	m_pLeftChild = NULL;
	m_pRightChild = NULL;
}

template <typename T>
BiTreeNode<T>::BiTreeNode(int index,T data)
{
	m_iIndex = index;
	m_tData = data;
	m_pParent = NULL;
	m_pLeftChild = NULL;
	m_pRightChild = NULL;
}

template <typename T>
BiTreeNode<T>::~BiTreeNode()
{
	if(m_pLeftChild != NULL)
	{
		m_pLeftChild->NodeDelete();
		m_pLeftChild = NULL;
	}
	if(m_pRightChild != NULL)
	{
		m_pRightChild->NodeDelete();
		m_pRightChild = NULL;
	}
	m_pParent = NULL;
}
/*-----------------------getdata------------------------*/
template <typename T>
int BiTreeNode<T>::getIndex()
{
	return m_iIndex;
}


template <typename T>
T BiTreeNode<T>::getData()
{
	return m_tData;
}

template <typename T>
BiTreeNode<T> *BiTreeNode<T>::getParent()
{
	return m_pParent;
}

template <typename T>
BiTreeNode<T> *BiTreeNode<T>::getLChild()
{
	return m_pLeftChild;
}

template <typename T>
BiTreeNode<T> *BiTreeNode<T>::getRChild()
{
	return m_pRightChild;
}

template <typename T>
BiTreeNode<T> *BiTreeNode<T>::getInorderPrecursor()
{
	/*
		condition 1: Node has left child.
		condition 2: Node hasn't left child,and it is its father right child.
		condition 3: Node hasn't left child,and it is its father left child.
	*/
	/*condition 1:node has left child*/
	if(NULL != this->getLChild())
	{
		BiTreeNode *tempNode=this->getLChild();
		while(NULL != tempNode->getRChild() )
		{
			tempNode=tempNode->getRChild();
		}
		return  tempNode;
	}
	else
	{
		BiTreeNode *fatherNode=this->getParent();
		if(NULL == fatherNode)
		{
			return NULL;//it is root.
		}
		/*condition 2*/
		else if(fatherNode->getRChild() == this)
		{
			return fatherNode;
		}
		/*condition*/
		else
		{
			while( fatherNode->getParent()->getRChild() != fatherNode)
			{
				fatherNode =fatherNode ->getParent();
				if(NULL == fatherNode )
				{
					return NULL;//it is root;
				}
			}
			return fatherNode->getParent();
		}
	}
	return NULL;
}

template <typename T>
BiTreeNode<T> *BiTreeNode<T>::getInorderSubsequence()				//获取中序后继
{
	/*
		condition 1: Node has right child.
		condition 2: Node hasn't right child,and it is its father left child.
		condition 3: Node hasn't right child,and it is its father right child.
	*/	
	/*condition 1*/
	if(NULL != this->getRChild())
	{
		BiTreeNode *tempNode = this->getRChild();
		while(NULL != tempNode->getLChild() )
		{
			tempNode=tempNode->getLChild();
		}
		return  tempNode;
	}
	/*condition 2*/
	else
	{
		BiTreeNode *fatherNode=this->getParent();
		if(NULL == fatherNode)//it is root.
		{
			return NULL;
		}
		else if(fatherNode->getLChild() == this)
		{
			return fatherNode;
		}
		else
		{
			while(fatherNode->getParent()->getLChild() !=fatherNode)
			{
				fatherNode=fatherNode->getParent();
				if(NULL == fatherNode)
				{
					return NULL;//it is root;
				}
			}
			return fatherNode->getParent();
		}
	}
}
/*-----------------------setdata------------------------*/
template <typename T>
void BiTreeNode<T>::setIndex(int index)
{
	m_iIndex = index;
}
template <typename T>
void BiTreeNode<T>::setData(T data)
{
	m_tData = data;
}
template <typename T>
void BiTreeNode<T>::setParenet(BiTreeNode *Node)
{
	m_pParent = Node;
}

template <typename T>
void BiTreeNode<T>::setLChild(BiTreeNode *Node)
{
	m_pLeftChild = Node;
}

template <typename T>
void BiTreeNode<T>::setRChild(BiTreeNode *Node)
{
	m_pRightChild = Node;
}

/*-----------------------else------------------------*/
template <typename T>
BiTreeNode<T> *BiTreeNode<T>::NodeSearch(int index)
{
	BiTreeNode<T> *tempNode = NULL;
	if(m_iIndex == index)
	{
		return this;
	}
	if(m_pLeftChild != NULL)
	{
		tempNode = m_pLeftChild->NodeSearch(index);
		if(tempNode != NULL)//match
		{
			return tempNode;
		}
	}

	if(m_pRightChild !=NULL)
	{
		tempNode = m_pRightChild->NodeSearch(index);
		if(tempNode != NULL)// match
		{
			return tempNode;
		}
	}


	return NULL;
}

/*statistcal children node heigh(includding me)*/
template <typename T>
int BiTreeNode<T>::NodeChildrenNodeHeigh()
{
	int heightLeft =0 ;
	int heightRight =0; 
	if(m_pLeftChild != NULL)
	{
		heightLeft += m_pLeftChild->NodeChildrenNodeHeigh();	
	}
	if(m_pRightChild != NULL)
	{
		heightRight += m_pRightChild->NodeChildrenNodeHeigh();
	}
	if(heightRight > heightLeft)
	{
		return ++heightRight;
	}
	else
	{
		return ++heightLeft;
	}
}

/*statistcal leaves node(includding me)*/
template <typename T>
int BiTreeNode<T>::NodeLeavesStatistics(int leaves)
{
	if(this->m_pLeftChild != NULL)
	{
		leaves = this->m_pLeftChild->NodeLeavesStatistics(leaves);
	}
	if(this->m_pRightChild != NULL)
	{
		leaves = this->m_pRightChild->NodeLeavesStatistics(leaves);
	}
	if(this->getLChild() == NULL && this->getRChild() == NULL)
	{
		leaves ++;
	}
	return leaves;	
}
/*statistcal children node(includding me)*/
template <typename T>
int BiTreeNode<T>::NodeChildrenStatistics()
{
	int iCnt=0;
	if(this->m_pLeftChild != NULL)
	{
		iCnt+=this->m_pLeftChild->NodeChildrenStatistics();
	}
	if(this->m_pRightChild!= NULL)
	{
		iCnt+=this->m_pRightChild->NodeChildrenStatistics();
	}
	iCnt++;
	return iCnt;
}

template <typename T>
int  BiTreeNode<T>::NodeDelete()
{
	int Times=0;
	if(this->m_pLeftChild != NULL)
	{
 		//delete this->getLChild();
		Times+=this->m_pLeftChild->NodeDelete();
		this->m_pLeftChild =NULL;
	}
	if(this->m_pRightChild!= NULL)
	{
		//delete this->getRChild();
		Times+=this->m_pRightChild->NodeDelete();
		this->m_pRightChild =NULL;
	}
	Times++;
	delete this;
	return Times;
}
/*-----------------------traversal------------------------*/
template <typename T>
void BiTreeNode<T>::NodePreorderTraversal()
{
	cout<<"Index:"<<this->getIndex()<<";Data:"<<this->getData()<<endl;

	if(this->getLChild() != NULL)
	{
		this->getLChild()->NodePreorderTraversal();
	}

	if(this->getRChild() != NULL)
	{
		this->getRChild()->NodePreorderTraversal();
	}
}

template <typename T>
void BiTreeNode<T>::NodeInorderTraversal()
{
	if(this->getLChild() != NULL)
	{
		this->getLChild()->NodeInorderTraversal();
	}

	cout<<"Index:"<<this->getIndex()<<";Data:"<<this->getData()<<endl;

	if(this->getRChild() != NULL)
	{
		this->getRChild()->NodeInorderTraversal();
	}
}

template <typename T>
void BiTreeNode<T>::NodeSubsequentTraversal()
{
	if(this->getLChild() != NULL)
	{
		this->getLChild()->NodeSubsequentTraversal();
	}

	if(this->getRChild() != NULL)
	{
		this->getRChild()->NodeSubsequentTraversal();
	}

	cout<<"Index:"<<this->getIndex()<<";Data:"<<this->getData()<<endl;
}

template <typename T>
int BiTreeNode<T>::getBalanceFactor()
{
	return m_iBalancefactor;
}

template <typename T>
bool BiTreeNode<T>::setBalanceFactor(int balance)
{
	m_iBalancefactor = balance.
}

#endif

