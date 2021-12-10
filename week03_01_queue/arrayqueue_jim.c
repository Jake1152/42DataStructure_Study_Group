#include <stdio.h>
#include <stdlib.h>
#include "arrayqueue_jim.h"

/*
	- 다시 짜야할 부분 
	circular array
	첫번째랑 마지막 둘다 가리켜야한다.
	추가 삭제할때마다
	시작 인덱스와 마지막 인덱스를 가리켜야한다.
*/

int main(int argc, char *argv[])
{
	ArrayQueue* 	curArrayQueue;
	int				maxElementCount;
	char			input_ch;
	ArrayQueueNode	element;

	maxElementCount = 42;
	if (argc >= 1 && argc > 0)
		maxElementCount = atoi(argv[1]);
	// argv[2] command	
	curArrayQueue = createArrayQueue(maxElementCount);
	input_ch = 'a';
	while (input_ch <= 'z')
	{
		element.data = 'a';
		enqueueAQ(curArrayQueue, element);
	}
	/*

		while (input_ch <= 'z')
		{
			element.data = 'a';
			enqueueAQ(curArrayQueue, element);
		}
	*/
	/*
		int enqueueAQ(ArrayQueue* pQueue, );
		ArrayQueueNode *dequeueAQ(ArrayQueue* pQueue);
		ArrayQueueNode *peekAQ(ArrayQueue* pQueue);
		void deleteArrayQueue(ArrayQueue* pQueue);
		int isArrayQueueFull(ArrayQueue* pQueue);
		int isArrayQueueEmpty(ArrayQueue* pQueue);
	*/
	return (0);
}

ArrayQueue* createArrayQueue(int maxElementCount)
{
	ArrayQueue      *newArrayQueue;
	ArrayQueueNode  *newArrayQueueNode;

	if (maxElementCount <= 0)
		return (NULL);
	newArrayQueue = (ArrayQueue *)malloc(sizeof(ArrayQueue));
	if (newArrayQueue == NULL)
		return (NULL);
	newArrayQueueNode = (ArrayQueueNode *)malloc(sizeof(ArrayQueueNode) * maxElementCount);
	if (newArrayQueueNode == NULL)
	{
		free(newArrayQueue);
		return (NULL);
	}
	newArrayQueue->currentElementCount = 0;
	newArrayQueue->maxElementCount = maxElementCount;
	newArrayQueue->front = 0; // idx니까 숫자가 나은가 e.g) -1	
	newArrayQueue->rear = 0;
	newArrayQueue->pElement = newArrayQueueNode;
	return (newArrayQueue);
}

int isArrayQueueFull(ArrayQueue* pQueue)
{
	/*
		front == rear
		만약 맨끝이 아니라면?
	*/
	if (pQueue == NULL)
		return (FALSE);
	if (pQueue->maxElementCount == pQueue->currentElementCount)
		// || (pQueue->front == pQueue->rear && pQueue->rear == pQueue->maxElementCount-1))
		return (TRUE);
	return (FALSE);
}

int isArrayQueueEmpty(ArrayQueue* pQueue)
{
	if (pQueue == NULL)
		return (FALSE);
	if (pQueue->currentElementCount == 0)
		return (TRUE);
	return (FALSE);
}

ArrayQueueNode *peekAQ(ArrayQueue* pQueue)
{
	if (pQueue == NULL)
		return (FALSE);
	if (pQueue->currentElementCount > 0)
		return (pQueue->front);
	return (FALSE);
}

int enqueueAQ(ArrayQueue* pQueue, ArrayQueueNode element)
{
	/*
		array queue
		rear로 들어가서 front로 나온다.
		풀이 될 수 있다.
		그런 부분은 어떻게 처리할 것인가?
		circular array로 처리
	*/
	if (pQueue == NULL)
		return (FALSE);
	if (isArrayQueueFull == TRUE)
		return (FALSE);	
	pQueue->pElement[pQueue->rear] = element;
	pQueue->rear = (pQueue->rear + 1) % pQueue->maxElementCount;
	pQueue->currentElementCount += 1;

	return (pQueue->currentElementCount);
}

ArrayQueueNode *dequeueAQ(ArrayQueue* pQueue)
{
	int	prev_idx;

	if (pQueue == NULL)
		return (FALSE);
	if (isArrayQueueEmpty == TRUE)
		return (FALSE);
	// 길이 7자리에서 마지막 인덱스에 있던 값을 삭제했다.
	// 원형이므로 front는 0번 노드를 가리킨다.
	// 이전에 front-1을 하였는데 그러면 0 - 1 => -1이 된다.
	// 그래서 간편하게 prev_idx를 사용
	prev_idx = pQueue->front;
	pQueue->front = (pQueue->front + 1) % pQueue->maxElementCount;	
	pQueue->currentElementCount -= 1;
	// rear가 가리키는 부분을 바꿔야한다.?
	/*
		처음에 위치를 할당할때부터 mod연산자를 쓴다.
		어떻게 위치를 넣는가?
		maxElementCount 갯수를 처리해야하다.
		pQueue[]
	*/

	return (&(pQueue->pElement[prev_idx]));
}

void deleteArrayQueue(ArrayQueue* pQueue)
{
	if (pQueue == NULL)
		return (FALSE);
	free(pQueue->pElement);
	free(pQueue);
}
