#include <stdio.h>
#include <stdlib.h>
#include "linkeddeque_jim.h"

LinkedDeque* createLinkedDeque()
{
	LinkedDeque*    newLinkedDeque;

	newLinkedDeque = (LinkedDeque *)malloc(sizeof(LinkedDeque));

	newLinkedDeque->currentElementCount = 0;
	newLinkedDeque->pFrontNode = (DequeNode*)NULL;
	newLinkedDeque->pRearNode = (DequeNode*)NULL;

	return (newLinkedDeque);
}

int isLinkedDequeEmpty(LinkedDeque* pDeque)
{
	/*
		둘다 널
	*/
	if (pDeque == NULL)
		return (FALSE);
	if (pDeque->currentElementCount == 0)
		return (TRUE);
	return (FALSE);
}

int insertFrontLD(LinkedDeque* pDeque, DequeNode element)
{
	/*
		currentElementCount++
		front에 추가
	*/
	DequeNode*	newDequeNode;
	if (pDeque == NULL)
		return (FALSE);
	newDequeNode = (DequeNode *)malloc(sizeof(newDequeNode));
	if (newDequeNode == NULL)
		return (FALSE);
	newDequeNode->data = element.data;
	// 처음으로 넣어준다면 L,R이 서로를 가리키게하고, Front,Rear 역시 동일
	// 처음일떄는 insertRear, insertFront 둘다 동일
	// 고려할 부분은 삭제할때 다 삭제되는 경우 Front,Rear NULL로 만들어야한다.
	// ㅁ = ㅁ = ㅁ = ㅁ 양끝도 연결되어있음
	// ㅇ ㅁ ㅁ ㅁ ㅁ
	if (pDeque->pFrontNode == NULL)
	{
		pDeque->pRearNode = newDequeNode;
		newDequeNode->pRLink = newDequeNode;
		newDequeNode->pLLink = newDequeNode;
		// pRLink, pLLink 서로를 가리키게 했을떄의 문제는?
	}
	else
	{
		/* code */
		newDequeNode->pLLink = pDeque->pFrontNode->pLLink;
		pDeque->pFrontNode->pLLink->pRLink = newDequeNode;
		pDeque->pFrontNode->pLLink = newDequeNode;
		newDequeNode->pRLink = pDeque->pFrontNode;
	}
	pDeque->pFrontNode = newDequeNode;	
	pDeque->currentElementCount++;

	return (pDeque->currentElementCount);
}

int insertRearLD(LinkedDeque* pDeque, DequeNode element)
{
	/*
		currentElementCount++
		front에 추가
	*/
	DequeNode*	newDequeNode;
	if (pDeque == NULL)
		return (FALSE);
	newDequeNode = (DequeNode *)malloc(sizeof(newDequeNode));
	if (newDequeNode == NULL)
		return (FALSE);
	newDequeNode->data = element.data;
	// 처음으로 넣어준다면 L,R이 서로를 가리키게하고, Front,Rear 역시 동일
	// 처음일떄는 insertRear, insertFront 둘다 동일
	// 고려할 부분은 삭제할때 다 삭제되는 경우 Front,Rear NULL로 만들어야한다.
	// ㅁ = ㅁ = ㅁ = ㅁ 양끝도 연결되어있음
	// ㅇ ㅁ ㅁ ㅁ ㅁ pRearNode
	if (pDeque->pRearNode == NULL)
	{
		pDeque->pRearNode = newDequeNode;
		newDequeNode->pRLink = newDequeNode;
		newDequeNode->pLLink = newDequeNode;
		// pRLink, pLLink 서로를 가리키게 했을떄의 문제는?
	}
	else
	{
		/* code */
		newDequeNode->pLLink = pDeque->pRearNode->pLLink;
		pDeque->pRearNode->pLLink->pRLink = newDequeNode;
		pDeque->pRearNode->pLLink = newDequeNode;
		newDequeNode->pRLink = pDeque->pRearNode;
	}
	pDeque->pRearNode = newDequeNode;
	pDeque->currentElementCount++;

	return (pDeque->currentElementCount);
}

DequeNode* deleteFrontLD(LinkedDeque* pDeque)
{
	/*
		하나도 없는 경우
		한개만 있다가 이제 0개가 되는 경우
		그외에 경우

		다음 것, 이전 것끼리 처리하도록 한다.
	*/
	if (pDeque == NULL || pDeque->currentElementCount == 0)
		return (NULL);
	// 1개만 있는 경우, 지우면 NULL을 가리키게 해줘야한다.
	// 2개 이상인 경우 공통사항은 무엇인가?	
	if (pDeque->currentElementCount == 1)
	{
		free(pDeque->pFrontNode);
		pDeque->pFrontNode = NULL;
		pDeque->pRearNode = NULL;
	}
	else
	{
		pDeque->pFrontNode->pRLink->pLLink = pDeque->pFrontNode->pLLink;
		pDeque->pFrontNode->pLLink->pRLink = pDeque->pFrontNode->pRLink;
		// 오른쪽 노드를 가리키게 하는것이 맞다고 생각. 다음 front가 될 흐름상 node이기 때문
		// 하지만 dequeue에서는 혹시 다른부분이 있는지 추가 확인이 필요함
		pDeque->pFrontNode = pDeque->pFrontNode->pRLink;
		free(pDeque->pFrontNode);
	}
	pDeque->currentElementCount--;
}

DequeNode* deleteRearLD(LinkedDeque* pDeque)
{
	/*
		하나도 없는 경우
		한개만 있다가 이제 0개가 되는 경우
		그외에 경우

		다음 것, 이전 것끼리 처리하도록 한다.
	*/
	if (pDeque == NULL || pDeque->currentElementCount == 0)
		return (NULL);
	// 1개만 있는 경우, 지우면 NULL을 가리키게 해줘야한다.
	// 2개 이상인 경우 공통사항은 무엇인가?	
	if (pDeque->currentElementCount == 1)
	{
		free(pDeque->pRearNode);
		pDeque->pRearNode = NULL;
		pDeque->pFrontNode = NULL;
	}
	else
	{
		pDeque->pRearNode->pRLink->pLLink = pDeque->pRearNode->pLLink;
		pDeque->pRearNode->pLLink->pRLink = pDeque->pRearNode->pRLink;
		// 오른쪽 노드를 가리키게 하는것이 맞다고 생각. 다음 front가 될 흐름상 node이기 때문
		// 하지만 dequeue에서는 혹시 다른부분이 있는지 추가 확인이 필요함
		pDeque->pRearNode = pDeque->pRearNode->pRLink;
		free(pDeque->pRearNode);
	}
	pDeque->currentElementCount--;
}

DequeNode* peekFrontLD(LinkedDeque* pDeque)
{
	if (pDeque == NULL || pDeque->currentElementCount == 0)
		return (NULL);
	return (pDeque->pFrontNode);
}

DequeNode* peekRearLD(LinkedDeque* pDeque)
{
	if (pDeque == NULL || pDeque->currentElementCount == 0)
		return (NULL);
	return (pDeque->pRearNode);
}

void deleteLinkedDeque(LinkedDeque* pDeque)
{
	/*
		deleteFront
		deleteRead 둘 중 하나 써서 0개 될때까지 반복
	*/
	if (pDeque == NULL)
		return exit(EXIT_FAILURE);
	while (pDeque->currentElementCount >= 0)
		deleteFrontLD(pDeque);
	free(pDeque);
}

