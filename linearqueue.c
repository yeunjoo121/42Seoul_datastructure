#ifndef _ARRAY_QUEUE_
#define _ARRAY_QUEUE_

typedef struct ArrayQueueNodeType
{
	char data;
} ArrayQueueNode;

typedef struct ArrayQueueType
{
	int maxElementCount;
	int currentElementCount;
	int front;
	int rear;
	ArrayQueueNode *pElement;
} ArrayQueue;

#include <stdio.h>
#include <stdlib.h>

ArrayQueue* createArrayQueue(int maxElementCount);
int enqueueAQ(ArrayQueue* pQueue, ArrayQueueNode element);
ArrayQueueNode *dequeueAQ(ArrayQueue* pQueue);
ArrayQueueNode *peekAQ(ArrayQueue* pQueue);
void deleteArrayQueue(ArrayQueue* pQueue);
int isArrayQueueFull(ArrayQueue* pQueue);
int isArrayQueueEmpty(ArrayQueue* pQueue);

#endif

#ifndef _COMMON_QUEUE_DEF_
#define _COMMON_QUEUE_DEF_

#define TRUE		1
#define FALSE		0

#endif

ArrayQueue* createArrayQueue(int maxElementCount)
{
  ArrayQueue *pReturn;
  
  pReturn = (ArrayQueue *)calloc(1, sizeof(ArrayQueue));
	if (pReturn == NULL)
  {
    printf("malloc error\n");
    return (NULL);
  }
  pReturn->pElement = (ArrayQueueNode*)calloc(maxElementCount, sizeof(ArrayQueueNode));
  if (pReturn->pElement == NULL)
  {
    printf("pElement malloc error\n");
    free(pReturn);
    return (NULL);
  }
  pReturn->maxElementCount = maxElementCount;
  return (pReturn);
}

int enqueueAQ(ArrayQueue* pQueue, ArrayQueueNode element)
{
  if (pQueue == NULL)
  {
    printf("pQueue is NULL\n");
    return (FALSE);
  }
  if (isArrayQueueFull(pQueue) == FALSE)
  {
    if (isArrayQueueEmpty(pQueue) == TRUE)
    {
      pQueue->pElement[pQueue->rear].data = element.data;
    }
    else
    {
      (pQueue->rear)++;
      pQueue->pElement[pQueue->rear].data = element.data;
    }
    (pQueue->currentElementCount)++;
  }
  else//pQueue is full
  {
    printf("pQueue is Full\n");
    return (FALSE);
  }
  return (TRUE);
}
  
ArrayQueueNode *dequeueAQ(ArrayQueue* pQueue)
{
  ArrayQueueNode *pNode;
  
  if (pQueue == NULL)
  {
    printf("pQueue is NULL\n");
    return (FALSE);
  }
  if (isArrayQueueEmpty(pQueue) == FALSE)
  {
    pNode = (ArrayQueueNode*)malloc(sizeof(ArrayQueueNode));
  	if (pNode == NULL)
 		{
    	printf("pNode malloc failure\n");
    	return (FALSE);
  	}
    pNode->data = pQueue->pElement[pQueue->front].data;
    pQueue->currentElementCount--;
    pQueue->front++;
  }
  else//queue is empty
  {
    printf("pQueue is empty\n");
    return (NULL);
  }
  return (pNode);
}

// 선형큐는 메모리 낭비가 심해서 원형큐를 쓴다.

ArrayQueueNode *peekAQ(ArrayQueue* pQueue)
{
  if (pQueue == NULL)
  {
    printf("pQueue is NULL\n");
    return (FALSE);
  }
  if (isArrayQueueEmpty(pQueue) == FALSE)
  {
  	return (&pQueue->pElement[pQueue->front]);
  }
  else//queue is empty
  {
    printf("pQueue is empty\n");
  }
  return (NULL);
}

void deleteArrayQueue(ArrayQueue* pQueue)
{
  if (pQueue != NULL)
  {
    if (pQueue->pElement != NULL)
    {
      free(pQueue->pElement);
      pQueue->pElement = NULL;
    }
    free(pQueue);
  }
}

int isArrayQueueFull(ArrayQueue* pQueue)
{
  if (pQueue == NULL)
    return (FALSE);
  if (pQueue->rear == pQueue->maxElementCount - 1 || pQueue->currentElementCount == pQueue->maxElementCount)
    return (TRUE);
  return (FALSE);
}

int isArrayQueueEmpty(ArrayQueue* pQueue)
{
  if (pQueue->currentElementCount != 0)
    return (FALSE);
  return (TRUE);
}

void displayQueue(ArrayQueue* pQueue)
{
  if (pQueue == NULL)
  {
    printf("pQueue is NULL\n");
    return ;
  }
  for (int i = pQueue->front; i <= pQueue->rear; i++)
  {
    printf("%d ", pQueue->pElement[i].data);
  }
  printf("\n");
}

int main()
{
  int maxElementCount = 5;
  ArrayQueue *AQ = createArrayQueue(maxElementCount);
  ArrayQueueNode AQN0 = {0};
  ArrayQueueNode AQN1 = {1};
  ArrayQueueNode AQN2 = {2};
  ArrayQueueNode AQN3 = {3};
  enqueueAQ(AQ, AQN0);
  enqueueAQ(AQ, AQN1);
  enqueueAQ(AQ, AQN2);
  enqueueAQ(AQ, AQN3);
  displayQueue(AQ);
  
  free(dequeueAQ(AQ));
  displayQueue(AQ);
  
  free(dequeueAQ(AQ));
  displayQueue(AQ);
  
  free(dequeueAQ(AQ));
  displayQueue(AQ);
  
  free(dequeueAQ(AQ));
  displayQueue(AQ);
  
  free(dequeueAQ(AQ));
  displayQueue(AQ);
  
  return (0);
}