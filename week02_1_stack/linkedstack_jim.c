#include <stdio.h>
#include <stdlib.h>
#include "linkedstack.h"

LinkedStack* createLinkedStack()
{
	/*
		넘겨받는 아무 argument가 없다.
	*/
	LinkedStack*	newLinkedStack;

	newLinkedStack = (LinkedStack *)malloc(sizeof(newLinkedStack));
	if (newLinkedStack == NULL)
		return (FALSE);
	newLinkedStack->pTopElement = NULL;
	newLinkedStack->currentElementCount = 0;

	return (newLinkedStack);
}

int isLinkedStackFull(LinkedStack* pStack)
{
	if (pStack == NULL)
		return (FALSE);
	// linked인데 full을 확인 하는 이유는 무엇인가?
	return (FALSE);
}

int isLinkedStackEmpty(LinkedStack* pStack)
{
	if (pStack == NULL)
		return (FALSE);
	if (pStack->currentElementCount == 0)
		return (TRUE);
	return (FALSE);
}

StackNode* peekLS(LinkedStack* pStack)
{
	StackNode*	retStackNode;
	if (pStack == NULL)
		return (NULL);
	retStackNode = pStack->pTopElement;
	return (retStackNode);
}

int pushLS(LinkedStack* pStack, StackNode element)
{
	/*
		시작위치에 추가
		header 위치
		이유는 삭제를 빨리할 수 있게 만들기 위해
		ㅁ ㅁ ㅁ ㅁ ㅁ ㅁ
		ㅁ ㅇ ㅁ ㅁ ㅁ ㅁ
	*/
	StackNode*	newStackNode;

	if (pStack == NULL)
		return (FALSE);
	newStackNode = (StackNode *)malloc(sizeof(newStackNode));
	if (newStackNode == NULL)
		return (NULL);
	newStackNode->data = element.data;
	newStackNode->pLink = pStack->pTopElement;
	pStack->pTopElement = newStackNode;
	pStack->currentElementCount += 1;

	return (pStack->currentElementCount);
}

StackNode* popLS(LinkedStack* pStack)
{
	/*
		pop 된 노드의 free는 밖에서 해준다.
	*/
	StackNode*	retStackNode;

	if (pStack == NULL)
		return (FALSE);	
	retStackNode = pStack->pTopElement;
	pStack->pTopElement = pStack->pTopElement->pLink;
	pStack->currentElementCount -= 1;

	return (retStackNode);
}

void deleteLinkedStack(LinkedStack* pStack)
{
	/*
		각 노드 하나씩 pop하고서 free
	*/
	while(pStack)
		free(popLS(pStack));
	free(pStack);
}

bool isEmpty(LinkedStack *pStack)
{
	if (pStack == NULL)
	{
		printf("There are no stack");
		return (FALSE);
	}		
	if (pStack->currentElementCount == 0)
		return (TRUE);	
	return (FALSE);
}