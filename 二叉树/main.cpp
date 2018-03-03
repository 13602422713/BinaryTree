#include <iostream>
#include <vector>
#include "BinaryTree.h"
#include "BinarySearchTree.h"
#include "AVLTree.h"

using namespace std;


int main()
{
	/*初始化一个vec向量用于建树*/
	vector<int> Vec1;
	Vec1.push_back(41);
	Vec1.push_back(20);
	Vec1.push_back(65);
	Vec1.push_back(11);
	Vec1.push_back(29);
	Vec1.push_back(50);
	Vec1.push_back(91);
	Vec1.push_back(32);
	Vec1.push_back(72);
	Vec1.push_back(99);
	/*建立一颗搜索二叉树*/
	BinarySearchTree<int> BSTree(Vec1); 
	/*中序遍历*/
	BSTree.BSTreeInorderTraversal();
	/*排序并按顺序打印*/
	vector<int> Vec2 = BSTree.getResult();
	for(unsigned int i=0;i<Vec2.size();i++)
	{
		cout<<Vec2[i]<<" ";
	}
	cout<<endl;
	/*获取元素个数*/
	cout<<"size:"<<BSTree.getNowSize()<<endl;
	cout<<"width:"<<BSTree.getWidth()<<endl;
	cout<<"height:"<<BSTree.getHeight()<<endl;

	/*删除元素*/
//	BSTree.deleteMinNode();
//	BSTree.deleteMaxNode();
	BSTree.deleteNodeByData(50);
	//BSTree.deleteNodeByIndex(50);
	Vec2 = BSTree.getResult();
	for(unsigned int i=0;i<Vec2.size();i++)
	{
		cout<<Vec2[i]<<" ";
	}
	cout<<endl;
	cout<<"size:"<<BSTree.getNowSize()<<endl;

//	float Ldatas[11] = {0.0f,1.1f,2.2f,3.3f,4.4f,5.5f,6.6f,7.7f,8.8f,9.9f,10.1f};
//	float Rdatas[5] = {30.0f,31.1f,32.2f,33.3f,34.4f};
//	int Ldatas[11] = {0,1,2,3,4,5,6,7,8,9,10};
//	int Rdatas[5] = {30,31,32,33,34};
//	BinaryTree<int> *tree = new BinaryTree<int>(20);
//
//
//	//addLeftNodeByIndex()/addRightNodeByIndex check
//	for(int i=1;i<5;i++)
//	{
//		tree->addLeftNodeByIndex(i+1,Ldatas[i],i);
//	}
//	for(int i=1;i<5;i++)
//	{
//		tree->addRightNodeByIndex(i+5,Rdatas[i],i);
//	}
//	for(int i=1;i<5;i++)
//	{
//		tree->addLeftNodeByIndex(i+9,Rdatas[i],i+5);
//	}
//	tree->PreorderTraversal();
//	cout<<"tree size(except root):"<<tree->getNowSize()<<endl;
//
//	//getLeaves() check;
//	cout<<"tree leaves:"<<tree->getLeaves()<<endl;
//
//	//getHeight() check;
//	cout<<"getHeight():"<<tree->getHeight()<<endl;
//
//	//getWidth() check;
//	cout<<"getWidth():"<<tree->getWidth()<<endl;
//
//	//preorderTraversal()/InorderTraversal()/SubsequentTraversal() check
////	tree->PreorderTraversal();
////	tree->InorderTraversal();
////	tree->SubsequentTraversal();
//
//	//deleteNodeByIndex() check
//	tree->deleteNodeByIndex(2);
//	tree->PreorderTraversal();
//
//	//getNowSize() check
//	cout<<"tree size(except root):"<<tree->getNowSize()<<endl;
//	delete tree;
//	tree = NULL;

	//BinaryTree<int> *tree = new BinaryTree<int>(20,1,10);
	//tree->addLeftNodeByIndex(2,9,1);
	//tree->addRightNodeByIndex(3,6,1);
	//tree->addLeftNodeByIndex(4,8,2);
	//tree->addRightNodeByIndex(5,7,2);
	//tree->addLeftNodeByIndex(6,5,3);
	//tree->addRightNodeByIndex(7,4,3);
	////preorderTraversal()/InorderTraversal()/SubsequentTraversal() check
	//tree->PreorderTraversal();
	////tree->InorderTraversal();
	////tree->SubsequentTraversal();

	////getNowSize() check
	//cout<<"tree size(except root):"<<tree->getNowSize()<<endl;

	////getLeaves() check;
	//cout<<"tree leaves:"<<tree->getLeaves()<<endl;

	////getHeight() check;
	//cout<<"getHeight():"<<tree->getHeight()<<endl;

	////getWidth() check;
	//cout<<"getWidth():"<<tree->getWidth()<<endl;

	////deleteNodeByIndex() check
	//tree->deleteNodeByIndex(2);
	//tree->PreorderTraversal();

	////BiTreeNode<int> *PreNode=tree->getNodeByIndex(1)->getInorderPrecursor();
	////BiTreeNode<int> *SubNode=tree->getNodeByIndex(1)->getInorderSubsequence();
	////if(NULL!=PreNode)
	////{
	////	cout<<" inorder precursor is:"<<PreNode->getData()<<endl;
	////}
	////if(NULL!=SubNode)
	////{
	////	cout<<" inorder subsequence is:"<<SubNode->getData()<<endl;
	////}

	system("pause");
	return 0;
}