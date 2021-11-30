#include <stdio.h>
#include <stdlib.h>
#include "ploylinkedlist.h"

PolyLinkedList*	createPolyLinkedList()
{
	/*
		poly타입 생성
	*/
	PolyLinkedList*	newPolyLinkedList;
	PolyListNode*	newPolyListNode;

	newPolyListNode = (PolyListNode *)malloc(sizeof(PolyListNode));
	// void
	// (PolyListNode *)
	if (newPolyListNode == NULL)
	{
		printf("failed allocate newPolyListNode");
		return (NULL);
	}
	newPolyLinkedList = (PolyListNode *)malloc(sizeof(PolyLinkedList));
	// void *-> 
	// void *-> (PolyListNode *) -> promotion 자동 프로모션이 된다
	// float, double	
	if (newPolyLinkedList == NULL)
	{
		printf("failed allocate newPolyLinkedList");
		return (NULL);
	}
	newPolyListNode->pLink = NULL;
	newPolyLinkedList->currentElementCount = 0;
	newPolyLinkedList->headerNode = *newPolyListNode;

	return (newPolyLinkedList);
}

int getPolyLinkedListLength(PolyLinkedList* pList)
{
	if (pList == NULL)	
		return (NULL);
	return (pList->currentElementCount);
}

int	addPolyLLElement(PolyLinkedList* pList, int position, PolyListNode element)
{
	/*
		- 내림차순으로 기준 잡는가?
	*/
	PolyListNode	*newListNode;
	PolyListNode	*prevListNode;

	if (pList == NULL)
		return (FALSE);
	if (position >= pList->currentElementCount)
		return (FALSE);
	if (position == 0)
	{
		pList->headerNode = element;
		pList->headerNode.pLink = NULL;
	}
	else
		prevListNode = getLLElement(pList, position - 1);
		element.pLink = prevListNode->pLink;
		prevListNode->pLink = &element;
	pList->currentElementCount += 1;
	return (TRUE);

	return (pList->currentElementCount);
}

PolyListNode*	getLLElement(PolyLinkedList* pList, int position)
{
	int				idx;
	PolyListNode	*curListNode;

	if (pList == NULL)
		return (NULL);
	if (position >= pList->currentElementCount)
		return (NULL);
	idx = 0;
	curListNode = pList->headerNode.pLink;
	// 왜 headerNode.pLink 인가 "->pLink"가 아니라?
	// 정의한 변수를 기준으로 해서 그렇다 pList를 기준
	// headerNode
	while(idx < position)
	{
		curListNode = curListNode->pLink;
		idx++;
	}
	return (curListNode);
}

PolyLinkedList*	sumPolyLinkedList(PolyLinkedList* pAList, PolyLinkedList* pBList)
{
	PolyLinkedList*	resultPolyLinkedList;
	PolyListNode*	aPolyListNode;
	PolyListNode*	bPolyListNode;
	PolyListNode*	newPolyListNode;
	int				position;

	if (pAList == NULL || pBList == NULL)
		return (NULL);
	resultPolyLinkedList = createPolyLinkedList();
	/*
		둘다 내림차순으로 정렬되어있다는 가정하에 진행된다.
		두 PolyLinkedList가 모두 NULL에 이를때까지 반복한다.
		각 각 1개씩 번갈아 가면서 순회한다.
		더 계수가 높으면 resultPolyLinkedList에 추가
		- 추가 고려사항
			- 계수가 0 이면 안넣어야한다.
			- 애초에 정렬되어서 안들어올 수 있다.
			- 별도로 정렬확인, 정렬하는 함수가 필요하다.
	*/
	aPolyListNode = &(pAList->headerNode);
	bPolyListNode = &(pBList->headerNode);
	position = 0;
	
	// 한개가 NULL이 아니면?
	while (aPolyListNode != NULL || bPolyListNode != NULL)
	{
		// malloc typecasting, pointer type으로 declaration하지 않는 경우 주소 연산자로 하면 될까?
		newPolyListNode = (PolyListNode *)malloc(sizeof(PolyListNode));
		if (newPolyListNode == NULL)
			return (NULL);
		// 2개 Linked List의 차수가 같은 경우
		if ((aPolyListNode != NULL && bPolyListNode != NULL) || aPolyListNode->degree == bPolyListNode->degree)
		{
			if (aPolyListNode->coef + bPolyListNode->coef == 0)
			{
				free(newPolyListNode);
				aPolyListNode = aPolyListNode->pLink;
				bPolyListNode = bPolyListNode->pLink;
				continue ;
			}	
			newPolyListNode->degree = aPolyListNode->degree;
			newPolyListNode->coef = aPolyListNode->coef + bPolyListNode->coef;
			aPolyListNode = aPolyListNode->pLink;
			bPolyListNode = bPolyListNode->pLink;
		}
		else if (aPolyListNode != NULL && (bPolyListNode == NULL || aPolyListNode->degree > bPolyListNode->degree))
		{
			newPolyListNode->degree = aPolyListNode->degree;
			newPolyListNode->coef = aPolyListNode->coef;			
			aPolyListNode = aPolyListNode->pLink;
		}
		else if (bPolyListNode != NULL && (aPolyListNode == NULL || aPolyListNode->degree < bPolyListNode->degree))
		{
			newPolyListNode->degree = bPolyListNode->degree;
			newPolyListNode->coef = bPolyListNode->coef;
			bPolyListNode = bPolyListNode->pLink;
		}
		addPolyLLElement(resultPolyLinkedList, position, (*newPolyListNode));
		position += 1;
	}

	return (resultPolyLinkedList);
}

void displayPolyLinkedList(PolyLinkedList* pList)
{
	PolyListNode *curPolyListNode;

	if (pList == NULL)
		exit(EXIT_FAILURE);
	curPolyListNode = &(pList->headerNode);
	while (curPolyListNode)
	{
		if (curPolyListNode->degree == 0)
			printf("(%d)", curPolyListNode->coef, curPolyListNode->degree);
		else
			printf("(%d)x^(%d) ", curPolyListNode->coef, curPolyListNode->degree);
		// 다음 항이 있으면 + 기호추가 (음수인지도 봐야하나?)
		if (curPolyListNode->pLink != NULL && curPolyListNode->pLink->coef > 0)
			printf("+ ");		
		else if (curPolyListNode->pLink != NULL && curPolyListNode->pLink->coef < 0)
			printf("- ");
		curPolyListNode = curPolyListNode->pLink;
	}
}

int main()
{
	/*
		coef
		dimension
		- 
	*/

	return (0);
}