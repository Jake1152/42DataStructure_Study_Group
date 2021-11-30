#include <stdio.h>
#include <stdlib.h>

#include "doublylist.h"
static DoublyListNode	*createDoublyListNode(int data);
static DoublyList		*reverseLinkedList(DoublyList* pList);

int main()
{
	DoublyList		*testDoublyList;

	DoublyListNode	*addedDoublyListNode;

	for (int i =0; i < 5; i++)
	{
		addedDoublyListNode = createDoublyListNode(i);
		printf("addDLElement(testDoublyList, i, addedDoublyListNode) : %d\n", addDLElement(testDoublyList, i, *addedDoublyListNode));
		displayDoublyList(testDoublyList);
	}
	
	printf("\n\ntestDoublyList->headerNode.data %d\n", testDoublyList->headerNode.data);
	displayDoublyList(testDoublyList);

	return (0);
}

static DoublyListNode	*createDoublyListNode(int data)
{
	DoublyListNode *newDoublyListNode;

	newDoublyListNode = malloc(sizeof(newDoublyListNode));
	if (newDoublyListNode == NULL)
		return (NULL);
	newDoublyListNode->pRLink = NULL;
	newDoublyListNode->pLLink = NULL;
	newDoublyListNode->data = data;

	return (newDoublyListNode);
}

DoublyList* createDoublyList()
{
	/*
		lLink
		rLink
		data초기화는?x
	*/
	DoublyList		*newDoublyList;
	DoublyListNode	*newDoublyListNode;
	// newDoublyListNode *가 안붙어도 되는가?

	newDoublyList = malloc(sizeof(newDoublyList));
	// newDoublyList = (DoublyList *)malloc(sizeof(newDoublyList));
	if (newDoublyList == NULL)
		return (NULL);
	// newDoublyList = createDoublyListNode;
	newDoublyListNode = malloc(sizeof(DoublyListNode));
	if (newDoublyList == NULL)
		return (NULL);
	newDoublyListNode->pLLink = NULL;
	newDoublyListNode->pRLink = NULL;
	//  동적할당을 해주어야하는가?
	newDoublyList->headerNode = *newDoublyListNode;
	newDoublyList->currentElementCount = 0;

	return (newDoublyList);
}

void displayDoublyList(DoublyList* pList)
{
	DoublyListNode	*curDoublyListNode;
	// DoublyListNode	curDoublyListNode;
	// curDoublyListNode.pLLink = &pLLink;

	if (pList == NULL)
		exit(EXIT_FAILURE);
	curDoublyListNode = &(pList->headerNode);
	while (curDoublyListNode)
	{
		printf("%d ", curDoublyListNode->data);
		curDoublyListNode = curDoublyListNode->pRLink;
	}
	printf("\n");
}

int getDoublyListLength(DoublyList* pList)
{
	if (pList == NULL)
		return (FALSE);
	return (pList->currentElementCount);
}

DoublyListNode* getDLElement(DoublyList* pList, int position)
{
	/*
		양방향으로 연결 되어있으니까 어디로 접근하는게 빠를지 생각해보는것도 좋을거 같다.
		원형과 차이는 무엇이라고 할 수 있는가?
		어디가 진짜 head인가?
		head가 가리키는 곳은 어디인가?
		마지막에 추가되는 것?
	
		position위치가 중간인지 여부를 파악해서 뒤에서부터 접근할것인지 앞에서부터 할 것인지 정한다.
	*/
	DoublyListNode	*curDoublyListNode;

	printf("in getDLElement\n\n");
	// printf("pList->currentElementCount %d\n", pList->currentElementCount);
	if (pList == NULL)
	{
		printf("pList is NULL\n");
		return (NULL);
	}
	if (position < 0 || position > pList->currentElementCount)
	{
		printf("position is under 0 or over currentElementCount\n");
		return (NULL);
	}
	printf("pList->currentElementCount %d\n", pList->currentElementCount);
	// headerNode의 주소값을 가지고 있게해도 되는가?
	curDoublyListNode = &(pList->headerNode);
	// 왼쪽에서 오른쪽으로 순회  start to mid
	if (position < (pList->currentElementCount-1)/2)
	{
		while (position > 0)
		{
			curDoublyListNode = curDoublyListNode->pRLink;
			position--;
		}
	}
	// 오른쪽에서 왼쪽으로 순회
	// end -> mid
	else
	{
		while (pList->currentElementCount - position > 0)
		{
			curDoublyListNode = curDoublyListNode->pLLink;
			position++;
			// 길이 7 찾는 위치 인덱스 6 (7번째)
			// 7 6 5 4
		}
	}
	printf("End of getDLElement\n");
	return (curDoublyListNode);
}

int addDLElement(DoublyList* pList, int position, DoublyListNode element)
{
	/*
		position이 0이거나 마지막번째일때를 별도로 처리해줘야하는가?
		header노드가 가리키는 곳을 바꿔야하므로 필요할 것으로 생각
	*/
	DoublyListNode	*prevDoublyListNode;
	DoublyListNode	*newDoublyListNode;

	if (pList == NULL)
		return (FALSE);
	if (position < 0 || position > pList->currentElementCount)
		return (NULL);
	// getElement사용
	// DoublyListNode* getDLElement(DoublyList* pList, int position)
	newDoublyListNode = createDoublyListNode(element.data);
	if (pList->currentElementCount == 0)
	{
		pList->headerNode = *newDoublyListNode;
		pList->currentElementCount += 1;
		return (pList->currentElementCount);
	}
	printf("\nbefore assign prevNode\n\n");
	if (position == 0)
	{
		prevDoublyListNode = getDLElement(pList, pList->currentElementCount - 1);
		pList->headerNode = *newDoublyListNode;
	}
	else
		prevDoublyListNode = getDLElement(pList, position - 1);
	printf("after assign prevNode\n");
	newDoublyListNode->pLLink = prevDoublyListNode;
	printf("after assign pLLink\n");
	newDoublyListNode->pRLink = prevDoublyListNode->pRLink;
	printf("after assign pRLink\n");	
	prevDoublyListNode->pRLink->pLLink = newDoublyListNode;
	printf("after assign prevDoublyListNode->pRLink->pLLink\n");
	// 별도로 element를 *가 있는 DoublyListNode로 만든다음에 할당해야하는가?
	prevDoublyListNode->pRLink = newDoublyListNode;
	printf("after assign element address \n");
	pList->currentElementCount += 1;

	return (pList->currentElementCount);
}

int removeDLElement(DoublyList* pList, int position)
{
	DoublyListNode	*prevDoublyListNode;
	DoublyListNode	*curDoublyListNode;
	DoublyListNode	*nextDoublyListNode;

	if (pList == NULL)
		return (FALSE);
	if (pList->currentElementCount >= position)
		return (FALSE);
	// position == 0;
	// headerNode가 가리키는 것을 바꾸어주어야한다.
	/*

	*/
	if (position == 0)
		curDoublyListNode->pRLink;
	curDoublyListNode = getDLElement(pList, position);
	prevDoublyListNode = curDoublyListNode->pLLink;
	nextDoublyListNode = curDoublyListNode->pRLink;

	prevDoublyListNode->pRLink = curDoublyListNode->pRLink;
	nextDoublyListNode->pLLink = curDoublyListNode->pLLink;
	free(curDoublyListNode);

	pList->currentElementCount -= 1;

	return (pList->currentElementCount);
}

void deleteDoublyList(DoublyList* pList)
{
	/*
		- 노드하나씩 free
		- 마지막으로 pList free
	*/
	if (pList == NULL)
		exit(EXIT_FAILURE);
	clearDoublyList(pList);	
	free(pList);
}

void clearDoublyList(DoublyList* pList)
{
	if (pList == NULL)
		return (NULL);
	while (pList->currentElementCount != 0)
		removeDLElement(pList, 0);
}

static DoublyList		*reverseLinkedList(DoublyList* pList)
{
	/*
		- 역순으로 만든다.
		- header노드의 위치를 가지고 있어야한다.(이미 가지고 있다.)
			- header노드가 마지막에 있던 노드를 가장 먼저 가리켜야한다.
			- 마지막인지 기준은 가리키는 곳이 NULL이면 마지막 노드
		- 첫번째 노드는 NULL을 가리키게 한다.
	*/
	DoublyList		*reversedDoublyList;
	DoublyListNode	*curDoublyListNode;

	if (pList == NULL)
		return (NULL);
	if (pList->currentElementCount == 0)
		return (createDoublyListNode(NULL));	

	curDoublyListNode = &(pList->headerNode);
	while (curDoublyListNode != NULL)
	{
		curDoublyListNode->pLLink;
	}
	/*
		python sorted느낌으로 할려면? 추가작업 필요
	*/
	return (reversedDoublyList);
}
