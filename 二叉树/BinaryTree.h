#ifndef _BINARYTREE_H
#define _BINARYTREE_H

#include <iostream>
#include <queue>
#include "BiTreeNode.h"
using namespace std;

template <typename T>
class BinaryTree
{
public:
	BinaryTree(int size,int index,T data);
	BinaryTree(int size);
	virtual ~BinaryTree();
	bool IsTreeEmpty();												//树是否为空
	bool IsTreeFull();												//树的容量是否已满
	//search	
	BiTreeNode<T> *getNodeByIndex(int index);						//通过索引搜索节点
	int getLeaves();												//获取树的叶子数
	int getHeight();												//获取树的高度(包含根节点)
	int getWidth();										            //获取树的宽度(包含根节点)
	int getNowSize();											    //获取树现在的节点数（包含根节点）
	int getMaxSize();												//获取树的最大节点数
	//add/delete
	bool addLeftNodeByIndex(int newIndex,T data,int searchIndex);	//添加左子树（使用索引）
	bool addRightNodeByIndex(int newIndex,T data,int searchIndex);  //添加右子树（使用索引）
	bool addLeftNodeByNode(int index,T data,BiTreeNode<T> *pNode);  //添加左子树（使用节点地址）
	bool addRightNodeByNode(int index,T data,BiTreeNode<T> *pNode); //添加右子树（使用节点地址）

	virtual bool deleteNodeByIndex(int index);						//删除节点（使用索引）
	virtual bool deleteNodeByNode(BiTreeNode<T> *pNode);			//删除节点（使用地址）

	//traversal
	void PreorderTraversal();										//先序遍历
	void InorderTraversal();										//中序遍历
	void SubsequentTraversal();										//后序遍历

protected:
	BiTreeNode<T> *m_pRoot;											//tree root
	int m_iSize;													//Tree now nodes size (without root)
	int m_iMaxSize;													//Tree max nodes size (without root) 
};

template <typename T>
BinaryTree<T>::BinaryTree(int size,int index,T data)
{
	m_pRoot = new BiTreeNode<T>(index,data);
	m_pRoot->setLChild(NULL);
	m_pRoot->setRChild(NULL);
	m_pRoot->setParenet(NULL);
	m_iSize = 1;
	m_iMaxSize = size;	
}

template <typename T>
BinaryTree<T>::BinaryTree(int size)
{
	m_pRoot = new BiTreeNode<T>(0,0);
	m_pRoot->setLChild(NULL);
	m_pRoot->setRChild(NULL);
	m_pRoot->setParenet(NULL);
	m_iSize = 1;
	m_iMaxSize = size;
}


template <typename T>
BinaryTree<T>::~BinaryTree()
{
	if(NULL != m_pRoot)
		delete m_pRoot;
	m_pRoot=NULL;
}

template <typename T>
bool BinaryTree<T>::IsTreeEmpty()
{
	if(m_iSize == 0)
		return true;
	return false;	
}

template <typename T>
bool BinaryTree<T>::IsTreeFull()
{
	if(m_iSize >= m_iMaxSize)
		return true;
	return false;
}

//search
template <typename T>
BiTreeNode<T> *BinaryTree<T>::getNodeByIndex(int index)
{
	if(NULL == m_pRoot)
	{
		return NULL;
	}
	return m_pRoot->NodeSearch(index);
}

template <typename T>
int BinaryTree<T>::getLeaves()
{	
	if(NULL == m_pRoot)
	{
		return 0;
	}
	return m_pRoot->NodeLeavesStatistics();
}

template <typename T>
int BinaryTree<T>::getWidth()
{
	if(NULL == m_pRoot)
	{
		return 0;
	}
	int maxWidth=1;				//save max width
	int parentWidth=0;			//save this width
	int childrenWidth=0;		//save next width
	queue<BiTreeNode<T>*> stdQueue;
	BiTreeNode<T> *tempNode = m_pRoot;
	if(tempNode -> getLChild() != NULL)
	{
		stdQueue.push(tempNode -> getLChild());
		parentWidth ++;
	}
	if(tempNode -> getRChild() != NULL)
	{
		stdQueue.push(tempNode ->getRChild());
		parentWidth ++;
	}

	while(!stdQueue.empty())
	{
		while(parentWidth>0)
		{
			tempNode = stdQueue.front();
			stdQueue.pop();
			if(tempNode -> getLChild() != NULL)
			{
				stdQueue.push(tempNode -> getLChild());
				childrenWidth ++;
			}
			if(tempNode -> getRChild() != NULL)
			{
				stdQueue.push(tempNode ->getRChild());
				childrenWidth ++;
			}
			parentWidth --;
		}
		parentWidth = childrenWidth;
		if(parentWidth > maxWidth)
		{
			maxWidth = parentWidth;
		}
		childrenWidth =0;
	}

//	result =  m_pRoot->NodeChildrenNodeWidth(&child);
	return maxWidth;
}


template <typename T>
int BinaryTree<T>::getHeight()
{
	if(NULL == m_pRoot)
		return 0;
	return m_pRoot->NodeChildrenNodeHeigh();//including root 
}

template <typename T>
int BinaryTree<T>::getNowSize()
{
	if(NULL == m_pRoot)
	{
		return 0;
	}
	//return m_iSize;//quickly get Size
	return m_pRoot ->NodeChildrenStatistics();//including root
}

template <typename T>
int BinaryTree<T>::getMaxSize()
{
	return m_iMaxSize ;
}

//add/delete
template <typename T>
bool BinaryTree<T>::addLeftNodeByIndex(int newIndex,T data,int searchIndex)
{
	if(NULL == m_pRoot)
	{
		return false;
	}
	BiTreeNode<T> *tempNode;
	tempNode = m_pRoot->NodeSearch(searchIndex);//find the node that index  is = searchIndex
	if(tempNode!=NULL)
	{
		return addLeftNodeByNode(newIndex,data,tempNode);
	}
	return false;
}
template <typename T>
bool BinaryTree<T>::addRightNodeByIndex(int newIndex,T data,int searchIndex)
{
	if(NULL == m_pRoot)
	{
		return false;
	}
	BiTreeNode<T> *tempNode ;
	tempNode = m_pRoot->NodeSearch(searchIndex);
	if(tempNode!=NULL)
	{
		return addRightNodeByNode(newIndex,data,tempNode);
	}
	return false;
}
template <typename T>
bool BinaryTree<T>::addLeftNodeByNode(int index,T data,BiTreeNode<T> *pNode)
{
	BiTreeNode<T> *pNodeCopy = pNode;//make a copy of pNode to protect the pNode being changed by accidentally
	if(IsTreeFull())
	{
		return false ;
	}
	if(pNodeCopy -> getLChild() == NULL)
	{
		BiTreeNode<T> *newNode = new BiTreeNode<T>(index,data);
		pNodeCopy->setLChild(newNode);
		newNode->setParenet(pNodeCopy);
	}
	else 
	{
		return false ;
	}

	m_iSize++;
	return true;
}

template <typename T>
bool BinaryTree<T>::addRightNodeByNode(int index,T data,BiTreeNode<T> *pNode)
{
	BiTreeNode<T> *pNodeCopy = pNode;//make a copy of pNode to protect the pNode being changed by accidentally
	if(IsTreeFull())
	{
		return false ;
	}
	if(pNodeCopy -> getRChild() == NULL)
	{
		BiTreeNode<T> *newNode = new BiTreeNode<T>(index,data);
		pNodeCopy->setRChild(newNode);
		newNode->setParenet(pNodeCopy);
	}
	else 
	{
		return false ;
	}

	m_iSize++;
	return true;
}


template <typename T>
bool BinaryTree<T>::deleteNodeByIndex(int index)
{
	if(IsTreeEmpty())
	{
		return false;
	}

	BiTreeNode<T> *deleteNode = m_pRoot->NodeSearch(index);
	if(deleteNode != NULL)
	{
		if(deleteNode == m_pRoot)
		{
			cout<<"BinaryTree<T>::deleteNodeByIndex():"<<index<<"是根节点不能删除"<<endl;
			return false;
		}
		return deleteNodeByNode(deleteNode);
	}
	return false;
}
template <typename T>
bool BinaryTree<T>::deleteNodeByNode(BiTreeNode<T> *pNode)
{
	if(IsTreeEmpty())
		return false;

	if(pNode!=NULL)
	{
		/*clear parent Node L/RChild*/ 
		BiTreeNode<T> *parentNode = pNode->getParent();
		if(parentNode != NULL)
		{
			if(parentNode->getLChild() == pNode)
			{
				parentNode->setLChild(NULL);
			}
			else
			{
				parentNode->setRChild(NULL);
			}
		}
		/*delete node*/
		int SizeDec;//use to caculate how much Node was delete
		SizeDec = pNode->NodeDelete();
		m_iSize-=SizeDec;
		return true;
	}
	return false;
}

//traversal
template <typename T>
void BinaryTree<T>::PreorderTraversal()
{
	cout<<"PerorderTraversal:"<<endl;
	if(NULL == m_pRoot)
	{
		return ;
	}
	m_pRoot ->NodePreorderTraversal();
}
template <typename T>
void BinaryTree<T>::InorderTraversal()
{
	cout<<"InorderTraversal:"<<endl;
	if(NULL == m_pRoot)
	{
		return ;
	}
	m_pRoot ->NodeInorderTraversal();
}
template <typename T>
void BinaryTree<T>::SubsequentTraversal()
{
	cout<<"SubsequentTraversal:"<<endl;
	if(NULL == m_pRoot)
	{
		return ;
	}
	m_pRoot ->NodeSubsequentTraversal();
}

#endif 

