#ifndef _LINKEDLIST_
#define _LINKEDLIST_

typedef struct ListNodeType
{
	int data;
	struct ListNodeType* pLink;
} ListNode;


// **
typedef struct LinkedListType
{
	int currentElementCount;	// ���� ����� ������ ����
	ListNode headerNode;		// ��� ���(Header Node)
} LinkedList;
// (&headerNode)
typedef struct PolynomialListType
{
	int currentElementCount;	// ���� ����� ������ ����
	PolyListNode headerNode;	// ��� ���(Header Node)
} PolyLinkedList;

typedef struct PolynomialListNodeType
{
	int	coef;
	int	degree;
	struct PolynomialListNodeType*	pLink;
} PolyListNode;

LinkedList* createLinkedList();
int addLLElement(LinkedList* pList, int position, ListNode element);
int removeLLElement(LinkedList* pList, int position);
ListNode* getLLElement(LinkedList* pList, int position);

void clearLinkedList(LinkedList* pList);
int getLinkedListLength(LinkedList* pList);
void deleteLinkedList(LinkedList* pList);

/* add polynomial */
PolyLinkedList*	createPolyLinkedList();

int	addPolyLLElement(PolyLinkedList* pList, int position, PolyListNode element);
PolyLinkedList*	sumPolyLinkedList(PolyLinkedList* pAList, PolyLinkedList* pBList);
int getPolyLinkedListLength(PolyLinkedList* pList);
void 

/*
- getPloyLLElement(PolyLinkedList* pList, int position);
- 
- 
*/
#endif

#ifndef _COMMON_LIST_DEF_
#define _COMMON_LIST_DEF_

#define TRUE		1
#define FALSE		0

#endif