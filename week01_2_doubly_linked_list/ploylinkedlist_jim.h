#ifndef _POLYLINKEDLIST_
#define _POLYLINKEDLIST_

typedef struct PolynomialListNodeType
{
	int	coef;
	int	degree;
	struct PolynomialListNodeType*	pLink;
} PolyListNode;

typedef struct PolynomialListType
{
	int currentElementCount;	// ���� �����?? ������ ����
	PolyListNode headerNode;	// ���?? ���??(Header Node)
} PolyLinkedList;

PolyLinkedList*	createPolyLinkedList();

int	addPolyLLElement(PolyLinkedList* pList, int position, PolyListNode element);
PolyLinkedList*	sumPolyLinkedList(PolyLinkedList* pAList, PolyLinkedList* pBList);
int getPolyLinkedListLength(PolyLinkedList* pList);
void displayPolyLinkedList(PolyLinkedList* pList);
PolyListNode*	getLLElement(PolyLinkedList* pList, int position);

#endif

#ifndef _COMMON_PLOY_LIST_DEF_
#define _COMMON_PLOY_LIST_DEF_

#define TRUE		1
#define FALSE		0

#endif