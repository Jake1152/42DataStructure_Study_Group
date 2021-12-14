#include <stdlib.h>
#include <stdio.h>
#include "bintree.h"

int main()
{
	BinTree*	firstBinTree;	
	BinTreeNode	*rootNode[10];

	rootNode[0] = (BinTreeNode	*)malloc(sizeof(BinTreeNode));
	if (rootNode[0] == NULL)
	{
		printf("Fail to malloc in main()\n");
		exit(EXIT_FAILURE);
	}
	rootNode[0]->data = 'z';
	printf("firstBinTree->pRootNode address : %p\n", &(firstBinTree->pRootNode));
	printf("rootNode[0] address : %p\n", rootNode[0]);
	firstBinTree = makeBinTree(*rootNode[0]);
	printf("firstBinTree->pRootNode address : %p\n", &(firstBinTree->pRootNode));
	printf("firstBinTree->pRootNode->data : %c\n", firstBinTree->pRootNode->data);
	printf("firstBinTree->pRootNode->visited : %d\n", firstBinTree->pRootNode->visited);
	// for (int i = 1; i < 10; i++)
	// {
	// 	rootNode[i] = (BinTreeNode	*)malloc(sizeof(BinTreeNode));
	// 	if (rootNode == NULL)
	// 	{
	// 		printf("Failt to malloc in main()\n");
	// 		exit(EXIT_FAILURE);
	// 	}
	// 	rootNode[i]->data = 'a' + i;
		
	// }
	return (0);
}

BinTree* makeBinTree(BinTreeNode rootNode)
{
	BinTree*	newBinTree;

	newBinTree = (BinTree*)malloc(sizeof(BinTreeNode));
	if (newBinTree == NULL)
		return (NULL);
	// printf("rootNode address : %p\n", &rootNode);
	// printf("newBinTree->pRootNode address in makeBinTree: %p\n", &rootNode);
	rootNode.visited = 0;
	newBinTree->pRootNode = &rootNode;	
	// printf("newBinTree->pRootNode address after allocation in makeBinTree: %p\n", &rootNode);
	return (newBinTree);
}

BinTreeNode* getRootNodeBT(BinTree* pBinTree)
{
	if (pBinTree)
		return (pBinTree->pRootNode);
	return (NULL);
}


// BinTreeNode *newElement;
// malloc
// newElement
// insertLeftChildNodeBT(pParentNode, element)
BinTreeNode* insertLeftChildNodeBT(BinTreeNode* pParentNode, BinTreeNode element)
{
	/*
		이진탐색트리도 아니고 다른 균형 트리도 아니다
		그러므로 우선 왼쪽에 넣기만 해도 되는가?
		넣으려는 위치에 특정 노드가 있으면 어떻게 할 것인가?
		새로 들어오는 노드 밑으로 넣어준다.
	*/
	// &element == NULL 굳이 필요 없는지?
	BinTreeNode*	newBinTreeNode;

	//element를 parameter로 할때 포인터가 없으므로 로컬변수라 의미가 없다.
	// 넣
	if (pParentNode == NULL)
		return (NULL);
	
	newBinTreeNode = (BinTreeNode*)malloc(sizeof(BinTreeNode));
	if (newBinTreeNode == NULL)
		return (NULL);
	newBinTreeNode = &element;
	newBinTreeNode->pLeftChild = pParentNode->pLeftChild;
	pParentNode->pLeftChild = newBinTreeNode;
	return (newBinTreeNode);
}

BinTreeNode* insertRightChildNodeBT(BinTreeNode* pParentNode, BinTreeNode element)
{
	BinTreeNode*	newBinTreeNode;

	if (pParentNode == NULL)
		return (NULL);
	
	newBinTreeNode = (BinTreeNode*)malloc(sizeof(BinTreeNode));
	if (newBinTreeNode == NULL)
		return (NULL);
	newBinTreeNode = &element;
	newBinTreeNode->pRightChild = pParentNode->pRightChild;
	pParentNode->pRightChild = newBinTreeNode;
	return (newBinTreeNode);
}

BinTreeNode* getLeftChildNodeBT(BinTreeNode* pNode)
{
	if (pNode == NULL)
		return (NULL);
	return (pNode->pLeftChild);
}

BinTreeNode* getRightChildNodeBT(BinTreeNode* pNode)
{
	BinTreeNode*	curBinTreeNode;

	if (pNode == NULL)
		return (NULL);
	return (pNode->pLeftChild);
}

void deleteBinTreeNode(BinTreeNode* pNode)
{
	/*
		디렉토리 삭제와 같다.
		현재 디렉토리리를 삭제하면 하위 디렉토리도 딸려서 삭제된다.
		root는 마지막에 삭제되어야하므로 후위순회한다.
	*/
	if (pNode == NULL)
	{
		printf("pNode is NULL\n");
		exit(EXIT_FAILURE);
	}
	deleteBinTreeNode(pNode->pLeftChild);
	deleteBinTreeNode(pNode->pRightChild);
	free(pNode);
	pNode = NULL;
}

void deleteBinTree(BinTree* pBinTree)
{
	/*
		어떻게 순회할것인가?
		후위순회?
		말단 노드부터가게해서 free
		root를 중간에 잃으면 다른 것들을 따로 연결해줘야해서
		후위 순회가 간편할것으로 생각
		부모노드에서 free된 자식 노드를 안가리키고 다른 곳을 가리키게할려면 어떻게 해야하는가?
	*/
	// BinTreeNode*	curBinTreeNode;
	// BinTreeNode*	tmp;

	// /*
	// 	- get left
	// 	- get right
	// 	- get root
	// */
	// if (pBinTree == NULL)
	// 	return (NULL);
	// curBinTreeNode = pBinTree->pRootNode;
	// while (curBinTreeNode)
	// {
	// 	free(getLeftChildNodeBT(curBinTreeNode));
	// 	free(getRightChildNodeBT(curBinTreeNode));
	// 	free(getRootNodeBT(curBinTreeNode));
	// }
	// pBinTree->pRootNode = NULL;
	// return (curBinTreeNode);
}
