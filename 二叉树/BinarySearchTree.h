#ifndef _BINARYSEARCHTREE_H
#define _BINARYSEARCHTREE_H

#include <iostream>
#include <queue>
#include <vector>
#include "BinaryTree.h"
#include "BiTreeNode.h"


template <typename T>
class BinarySearchTree:public BinaryTree<T>
{
public:
	BinarySearchTree(int size,int rootIndex,T data);
	BinarySearchTree(vector<T> vect);
	virtual ~BinarySearchTree();

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

	//search
	bool searchNode(T data,BiTreeNode<T>** node);

	//sort
	bool sortToVec();
	bool sort(BiTreeNode<T> *pNode);

	//pinrtf
	void BSTreePreorderTraversal();										//先序遍历
	void BSTreeInorderTraversal();										//中序遍历
	void BSTreeSubsequentTraversal();									//后序遍历

private:
	vector<T>  m_tVec;	
};

template <typename T>
BinarySearchTree<T>::BinarySearchTree(int size,int rootIndex,T data):BinaryTree(size,int rootIndex,T data)
{

}

template <typename T>
BinarySearchTree<T>::BinarySearchTree(vector<T> vect):BinaryTree((int)vect.size(),0,vect[0])
{
	unsigned int size = vect.size();
	for(unsigned int i=1;i<size;i++)
	{
		this->addNode(i,vect[i]);
	}
}

template <typename T>
BinarySearchTree<T>::~BinarySearchTree()
{
	
}

template <typename T>
vector<T> BinarySearchTree<T>::getResult()
{
	sortToVec();
	return m_tVec;
}

template <typename T>
bool BinarySearchTree<T>::addNode(int index,T data)
{
	if(IsTreeFull())
	{
		return false;
	}
	insert(index,data,m_pRoot);
	return true;
}

template <typename T>
bool BinarySearchTree<T>::insert(int index,T data, BiTreeNode<T> *pNode)
{
	//recursion
	if(data < pNode->getData())
	{
		if(pNode ->getLChild() != NULL)
		{
			if(insert(index,data,pNode->getLChild()))
				return true;
		}
		else
		{
			if(addLeftNodeByNode(index,data,pNode))
				return true;
		}
	}
	else
	{
		if(pNode ->getRChild() != NULL)
		{
			if(insert(index,data,pNode->getRChild()))
				return true;
		}
		else
		{
			if(addRightNodeByNode(index,data,pNode))
				return true;
		}		
	}
	return false;
}

template <typename T>
bool BinarySearchTree<T>::deleteMinNode()
{
	if(IsTreeEmpty())
		return false;

	BiTreeNode<T> *pNode = m_pRoot;
	while(pNode->getLChild() != NULL)
	{
		pNode = pNode->getLChild();
	}
	if(pNode==m_pRoot)
	{
		pNode = m_pRoot->getRChild();
		while(pNode->getLChild()!=NULL)
		{
			pNode = pNode->getLChild();
		}
	}

	deleteNodeByNode(pNode);
	return true ;
}

template <typename T>
bool BinarySearchTree<T>::deleteMaxNode()
{
	if(IsTreeEmpty())
		return false;

	BiTreeNode<T> *pNode = m_pRoot;
	while(pNode->getRChild() != NULL)
	{
		pNode = pNode->getRChild(); 
	}
	if(pNode==m_pRoot)
	{
		pNode = m_pRoot->getLChild();
		while(pNode->getRChild()!=NULL)
		{
			pNode = pNode->getRChild();
		}
	}

	deleteNodeByNode(pNode);
	return true;
}

template <typename T>
bool BinarySearchTree<T>::deleteNodeByIndex(int index)
{
	BiTreeNode<T> *pNode = getNodeByIndex(index);
	if(NULL != pNode)
	{
		/*there are 3 condition in the following:
			1、The node has no child.
			2、The node only has left child or right child.
			3、The node both has left and right child,so make the target node replaced by precursor,and then delete precursor by useing condition 2 function.
		*/
		/*condition 1:no child*/
		if(NULL == pNode->getRChild() && NULL == pNode->getLChild())
		{
			if(pNode!=m_pRoot)
			{				
				BiTreeNode<T> *pfatherNode= pNode->getParent();
				if(pfatherNode->getLChild() == pNode)
				{
					pfatherNode->setLChild(NULL);
				}
				else
				{
					pfatherNode->setRChild(NULL);
				}
				this->m_iSize--;
				delete pNode;
			}
			else 
				return false;//only root left
		}
		/*condition 3:The node both has left and right child*/
		else if(NULL != pNode->getRChild() && NULL != pNode->getLChild())
		{
			BiTreeNode<T> *preNode = pNode->getInorderPrecursor();
			pNode->setIndex(preNode->getIndex());
			pNode->setData(preNode->getData());
			pNode = preNode;
		}
		/*condition 2: The node only has left child or right child.*/
		if(NULL == pNode->getRChild())
		{
			BiTreeNode<T> *pfatherNode= pNode->getParent();
			if(pfatherNode->getLChild() == pNode )//Target node is father left son.
			{
				pfatherNode->setLChild(pNode->getLChild());//Target node left son link to it fater.
			}
			else//Target node is father right son.
			{
				pfatherNode->setRChild( pNode->getLChild());//Target node left son link to it father.
			}
			pNode->setLChild(NULL);
			this->m_iSize--;
			delete pNode;
		}
		else if(NULL == pNode->getLChild())
		{
			BiTreeNode<T> *pfatherNode=pNode->getParent();
			if(pfatherNode->getLChild() == pNode )//Target node is father left son.
			{
				pfatherNode->setLChild(pNode->getRChild());//Target node left son link to it fater.
			}
			else//Target node is father right son.
			{
				pfatherNode->setRChild( pNode->getRChild());//Target node left son link to it father.
			}
			pNode->setRChild(NULL);
			this->m_iSize--;
			delete pNode;
		}
		return true;
	}
	else
		return false;//if(NULL != pNode); there are no such node!
}
template <typename T>
bool BinarySearchTree<T>::deleteNodeByNode(BiTreeNode<T> *pNode)
{
	return false;
}

template <typename T>
bool BinarySearchTree<T>::deleteNodeByData(T data)
{
	BiTreeNode<T> *pNode = m_pRoot;
	if(searchNode(data,&pNode))
	{
		/*there are 3 condition in the following:
			1、The node has no child.
			2、The node only has left child or right child.
			3、The node both has left and right child,so make the target node replaced by precursor,and then delete precursor by useing condition 2 function.
		*/
		/*condition 1:no child*/
		if(NULL == pNode->getRChild() && NULL == pNode->getLChild())
		{
			if(pNode!=m_pRoot)
			{				
				BiTreeNode<T> *pfatherNode= pNode->getParent();
				if(pfatherNode->getLChild() == pNode)
				{
					pfatherNode->setLChild(NULL);
				}
				else
				{
					pfatherNode->setRChild(NULL);
				}
				this->m_iSize--;
				delete pNode;
			}
			else 
				return false;//only root left
		}
		/*condition 3:The node both has left and right child*/
		else if(NULL != pNode->getRChild() && NULL != pNode->getLChild())
		{
			BiTreeNode<T> *preNode = pNode->getInorderPrecursor();
			pNode->setIndex(preNode->getIndex());
			pNode->setData(preNode->getData());
			pNode = preNode;
		}
		/*condition 2: The node only has left child or right child.*/
		if(NULL == pNode->getRChild())
		{
			BiTreeNode<T> *pfatherNode= pNode->getParent();
			if(pfatherNode->getLChild() == pNode )//Target node is father left son.
			{
				pfatherNode->setLChild(pNode->getLChild());//Target node left son link to it fater.
			}
			else//Target node is father right son.
			{
				pfatherNode->setRChild( pNode->getLChild());//Target node left son link to it father.
			}
			pNode->setLChild(NULL);
			this->m_iSize--;
			delete pNode;
		}
		else if(NULL == pNode->getLChild())
		{
			BiTreeNode<T> *pfatherNode=pNode->getParent();
			if(pfatherNode->getLChild() == pNode )//Target node is father left son.
			{
				pfatherNode->setLChild(pNode->getRChild());//Target node left son link to it fater.
			}
			else//Target node is father right son.
			{
				pfatherNode->setRChild( pNode->getRChild());//Target node left son link to it father.
			}
			pNode->setRChild(NULL);
			this->m_iSize--;
			delete pNode;
		}
		return true;
	}
	else
		return false;//if(searchNode(data,&pNode)); there are no such node!
}


template <typename T>
bool BinarySearchTree<T>::searchNode(T data,BiTreeNode<T>** node)
{
	BiTreeNode<T> *pNode = m_pRoot;

	if(data>m_pRoot->getData())
	{
		while(data>pNode->getData())
		{
			if(pNode->getRChild() != NULL)
			{
				pNode = pNode->getRChild();
			}
			else
			{
				return false;
			}
		}
		while(data<pNode->getData())
		{
			if(pNode->getLChild() != NULL)
			{
				pNode = pNode->getLChild();
			}
			else
			{
				return false;
			}				
		}
		*node = pNode;
		return true;
	}
	else 
	{
		while(data<pNode->getData())
		{
			if(pNode->getLChild() != NULL)
			{
				pNode = pNode->getLChild();
			}
			else
			{
				return false;
			}				
		}	
		while(data>pNode->getData())
		{
			if(pNode->getRChild() != NULL)
			{
				pNode = pNode->getRChild();
			}
			else
			{
				return false;
			}
		}
		*node = pNode;
		return true;
	}
}

template <typename T>
bool BinarySearchTree<T>::sortToVec()
{
	m_tVec.clear();
	sort(m_pRoot);
	return true;
}

template <typename T> 
bool BinarySearchTree<T>::sort( BiTreeNode<T> *pNode)
{
	if(pNode->getLChild() != NULL)
	{
		sort(pNode->getLChild());
	}

	m_tVec.push_back(pNode->getData());

	if(pNode->getRChild() != NULL)
	{
		sort(pNode->getRChild());
	}

	return true;
}

template <typename T>
void BinarySearchTree<T>::BSTreePreorderTraversal()
{
	PreorderTraversal();
}

template <typename T>
void BinarySearchTree<T>::BSTreeInorderTraversal()
{
	InorderTraversal();
}

template <typename T>
void BinarySearchTree<T>::BSTreeSubsequentTraversal()
{
	SubsequentTraversal();
}

#endif 
