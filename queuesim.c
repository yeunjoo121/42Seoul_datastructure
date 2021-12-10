#ifndef _SIM_DEF_
#define _SIM_DEF_
typedef enum SimStatusType { arrival, start, end } SimStatus;
typedef struct SimCustomerType
{
    SimStatus status;
    int arrivalTime;    // 도착 시각.
    int serviceTime;    // 서비스 시간.
    int startTime;      // 시작 시각.
    int endTime;        // 종료 시각: 시작 시각 + 서비스 시간.
} SimCustomer;
#endif
///////linkeddeque
#ifndef _LINKED_DEQUE_
#define _LINKED_DEQUE_
typedef struct DequeNodeType
{
    SimCustomer data;
    struct DequeNodeType* pRLink;
    struct DequeNodeType* pLLink;
} DequeNode;
typedef struct LinkedDequeType
{
    int currentElementCount;
    DequeNode* pFrontNode;
    DequeNode* pRearNode;
} LinkedDeque;
#include <stdio.h>
#include <stdlib.h>
LinkedDeque* createLinkedDeque();
int insertFrontLD(LinkedDeque* pDeque, DequeNode element);
int insertRearLD(LinkedDeque* pDeque, DequeNode element);
DequeNode* deleteFrontLD(LinkedDeque* pDeque);
DequeNode* deleteRearLD(LinkedDeque* pDeque);
DequeNode* peekFrontLD(LinkedDeque* pDeque);
DequeNode* peekRearLD(LinkedDeque* pDeque);
void deleteLinkedDeque(LinkedDeque* pDeque);
int isLinkedDequeFull(LinkedDeque* pDeque);
int isLinkedDequeEmpty(LinkedDeque* pDeque);
#endif
#ifndef _COMMON_QUEUE_DEF_
#define _COMMON_QUEUE_DEF_
#define TRUE        1
#define FALSE       0
#endif
LinkedDeque* createLinkedDeque()
{
  LinkedDeque *pReturn;
  pReturn = (LinkedDeque *)calloc(1, sizeof(LinkedDeque));
  if (pReturn == NULL)
  {
    printf("malloc failure\n");
    return (NULL);
  }
  return (pReturn);
}
int insertFrontLD(LinkedDeque* pDeque, DequeNode element)
{
  DequeNode *pNode;
  if (pDeque == NULL)
  {
    printf("pDeque is NULL\n");
    return (FALSE);
  }
  pNode = (DequeNode*)calloc(1, sizeof(DequeNode));
  if (pNode == NULL)
  {
    printf("pNode malloc failure\n");
    return (FALSE);
  }
  pNode->data = element.data;
  if (isLinkedDequeEmpty(pDeque) == TRUE)
  {
    pDeque->pFrontNode = pNode;
    pDeque->pRearNode = pNode;
  }
  else
  {
    pDeque->pFrontNode->pLLink = pNode;
    pNode->pRLink = pDeque->pFrontNode;
    pDeque->pFrontNode = pNode;
  }
  (pDeque->currentElementCount)++;
  return (TRUE);
}
int insertRearLD(LinkedDeque* pDeque, DequeNode element)
{
  DequeNode *pNode;
  if (pDeque == NULL)
  {
    printf("pDeque is NULL\n");
    return (FALSE);
  }
  pNode = (DequeNode*)calloc(1, sizeof(DequeNode));
  if (pNode == NULL)
  {
    printf("pNode malloc failure\n");
    return (FALSE);
  }
  pNode->data = element.data;
  if (isLinkedDequeEmpty(pDeque) == TRUE)
  {
    pDeque->pFrontNode = pNode;
    pDeque->pRearNode = pNode;
  }
  else
  {
    pDeque->pRearNode->pRLink = pNode;
    pNode->pLLink = pDeque->pRearNode;
    pDeque->pRearNode = pNode;
  }
  (pDeque->currentElementCount)++;
  return (TRUE);
}
DequeNode* deleteFrontLD(LinkedDeque* pDeque)
{
  DequeNode *pReturn;
  if (pDeque == NULL)
  {
    printf("pDeque is NULL\n");
    return (NULL);
  }
  if (isLinkedDequeEmpty(pDeque) == TRUE)
  {
    printf("FLD: pDeque is Empty\n");
    return (NULL);
  }
  else
  {
    pReturn = pDeque->pFrontNode;
        pDeque->pFrontNode = pDeque->pFrontNode->pRLink;
    pReturn->pRLink = NULL;
    if (pDeque->currentElementCount == 1)
    {
      pDeque->pRearNode = NULL;
    }
    else
    {
      pDeque->pFrontNode->pLLink = NULL;
    }
  }
  (pDeque->currentElementCount)--;
  return (pReturn);
}
DequeNode* deleteRearLD(LinkedDeque* pDeque)
{
  DequeNode *pReturn;
  if (pDeque == NULL)
  {
    printf("pDeque is NULL\n");
    return (NULL);
  }
  if (isLinkedDequeEmpty(pDeque) == TRUE)
  {
    printf("RLD: pDeque is Empty\n");
    return (NULL);
  }
  else
  {
    pReturn = pDeque->pRearNode;
        pDeque->pRearNode = pDeque->pRearNode->pLLink;
    pReturn->pLLink = NULL;
    if (pDeque->currentElementCount == 1)
    {
      pDeque->pFrontNode = NULL;
    }
    else
    {
      pDeque->pRearNode->pRLink = NULL;
    }
  }
  (pDeque->currentElementCount)--;
  return (pReturn);
}
DequeNode* peekFrontLD(LinkedDeque* pDeque)
{
  if (pDeque == NULL)
  {
    printf("pDeque is NULL\n");
    return (NULL);
  }
  if (isLinkedDequeEmpty(pDeque) == TRUE)
  {
    return (NULL);
  }
  return (pDeque->pFrontNode);
}
DequeNode* peekRearLD(LinkedDeque* pDeque)
{
  if (pDeque == NULL)
  {
    printf("pDeque is NULL\n");
    return (NULL);
  }
  if (isLinkedDequeEmpty(pDeque) == TRUE)
  {
    printf("peekRearLD: pDeque is Empty\n");
    return (NULL);
  }
  return (pDeque->pRearNode);
}
void deleteLinkedDeque(LinkedDeque* pDeque)
{
  if (pDeque == NULL)
  {
    printf("pDeque is NULL\n");
    return ;
  }
  while (isLinkedDequeEmpty(pDeque) == FALSE)
  {
    DequeNode *pNode = deleteFrontLD(pDeque);
    pNode->pRLink = NULL;
    pNode->pLLink = NULL;
    free(pNode);
  }
  free(pDeque);
}
int isLinkedDequeFull(LinkedDeque* pDeque)
{
  if (pDeque == NULL)
  {
    printf("pDeque is NULL\n");
  }
  return (FALSE);
}
int isLinkedDequeEmpty(LinkedDeque* pDeque)
{
  if (pDeque == NULL)
  {
    printf("pDeque is NULL\n");
  }
  if (pDeque->currentElementCount == 0 && pDeque->pFrontNode == NULL && pDeque->pRearNode == NULL)
  {
    return (TRUE);
  }
  return (FALSE);
}
// 고객의 상태를 출력.
void printSimCustomer(int currentTime, SimCustomer customer)
{
  printf("%d시에 들어온 고객의 %d시의 고객 상태는 ", customer.arrivalTime, currentTime);
  switch (customer.status)
  {
    case arrival:
      printf("고객 도착\n");
      break;
    case start:
      printf("고객 서비스 시작\n");
      break;
    case end:
      printf("고객 서비스 종료\n");
      break;
    default:
      ;
  }
}
// 대기 열의 상태를 출력.
void printWaitQueueStatus(int currentTime, LinkedDeque *pWaitQueue)
{
  int cnt = 0;
  if (pWaitQueue == NULL || isLinkedDequeEmpty(pWaitQueue) == 1)
  {
    printf("현재 %d시, 대기자 수는 0명 입니다.\n", currentTime);
    return ;
  }
  DequeNode* curr = peekFrontLD(pWaitQueue);
  while (curr != NULL)
  {
    cnt++;
    curr = curr->pRLink;
  }
  printf("현재 %d시, 대기자 수는 %d명 입니다.\n", currentTime, cnt);
}
// 최종 시뮬레이션 결과(통계치) 출력.
void printReport(LinkedDeque *pWaitQueue, int serviceUserCount, int totalWaitTime)
{
    printf("평균 대기시간: %f\n", (double)totalWaitTime / serviceUserCount);
  int cnt = 0;
  DequeNode* curr = peekFrontLD(pWaitQueue);
  if (pWaitQueue == NULL || isLinkedDequeEmpty(pWaitQueue) == 1 || serviceUserCount <= 0)
  {
    return ;
  }
  while (curr != NULL)
  {
    cnt++;
    curr = curr->pRLink;
  }
  printf("서비스를 받지 못하고 돌아가는 사람은 %d명 입니다.\n", cnt);
}


///////
// 고객 도착 큐에 고객 추가.
void insertCustomer(int arrivalTime, int processTime, LinkedDeque *pQueue)
{
  if (pQueue == NULL)
  {
    printf("pQueue is NULL\n");
    return ;
  }
  if (arrivalTime < 0 || processTime < 0)
  {
    printf("Negative time is wrong\n");
    return ;
  }
  DequeNode pNode;
  pNode.data.status = arrival;
  pNode.data.arrivalTime = arrivalTime;
  pNode.data.serviceTime = processTime;
  pNode.data.startTime = 0;
  pNode.data.endTime = 0;
  // 대기 도착 큐에 넣기
  if (insertRearLD(pQueue, pNode) == 0)
  {
    printf("insertRear failure\n");
    return ;
  }
}
// 고객 도착 처리.
void processArrival(int currentTime, LinkedDeque *pArrivalQueue, LinkedDeque *pWaitQueue)
{
  if (pArrivalQueue == NULL)
  {
    printf("pArrivalQueue is NULL\n");
    return ;
  }
  if (isLinkedDequeEmpty(pArrivalQueue) == 1)//빈 리스트이면
  {
    return ;
  }
  while (isLinkedDequeEmpty(pArrivalQueue) == 0)
  {
    if (currentTime != peekFrontLD(pArrivalQueue)->data.arrivalTime)
    {
        break;
    }
    else
    {
        insertRearLD(pWaitQueue, *(deleteFrontLD(pArrivalQueue)));
    }
  }
}
// 서비스 시작 처리.
DequeNode* processServiceNodeStart(int currentTime, LinkedDeque *pWaitQueue)
{
  if (pWaitQueue == NULL || isLinkedDequeEmpty(pWaitQueue) == 1)
  {
    return (NULL);
  }
  DequeNode* pServiceNode = deleteFrontLD(pWaitQueue);
  pServiceNode->data.status = start;
  pServiceNode->data.startTime = currentTime;
  return (pServiceNode);
}
// 서비스 종료 처리.
DequeNode* processServiceNodeEnd(int currentTime, DequeNode *pServiceNode, int *pServiceUserCount, int *pTotalWaitTime)
{
  int endTime = pServiceNode->data.startTime + pServiceNode->data.serviceTime;
  if (endTime == currentTime)
  {
    pServiceNode->data.endTime = endTime;
    pServiceNode->data.status = end;
    //여기서 고객의 상태 출력
    if (pServiceNode != NULL)
      printSimCustomer(currentTime, pServiceNode->data);

    (*pServiceUserCount)++;
    (*pTotalWaitTime) = (*pTotalWaitTime) + (pServiceNode->data.startTime - pServiceNode->data.arrivalTime);//waiting time 더하기
    free(pServiceNode);
    return NULL;
  }
  return pServiceNode;
}

int main(void)
{
  int tick = 0; // 시스템 시각
  LinkedDeque *pArrivalQueue = createLinkedDeque();; // 고객 도착 큐
  LinkedDeque *pWaitQueue = createLinkedDeque(); // 고객 대기 큐
  DequeNode *pServiceNode = NULL; // 서비스 노드
  int endtime = 10;//종료 시간
  int totalWaitTime = 0;//총 대기 시간
  int userCount = 0;//총 유저 수
  insertCustomer(0, 3, pArrivalQueue);
  insertCustomer(2, 2, pArrivalQueue);
  insertCustomer(4, 1, pArrivalQueue);
  insertCustomer(6, 1, pArrivalQueue);
  insertCustomer(8, 3, pArrivalQueue);
  for(int currentTime = 0; currentTime < endtime; currentTime++)
  {
    //processArrival;
    processArrival(currentTime, pArrivalQueue, pWaitQueue);
    if (pServiceNode != NULL)
    {
      pServiceNode = processServiceNodeEnd(currentTime, pServiceNode, &userCount, &totalWaitTime);
    }
    if (pServiceNode == NULL)
    {
      pServiceNode = processServiceNodeStart(currentTime, pWaitQueue);
      if (pServiceNode != NULL)
          printSimCustomer(currentTime, pServiceNode->data);
    }
    printWaitQueueStatus(currentTime, pWaitQueue);
  };
  printReport(pWaitQueue, userCount, totalWaitTime);
  return (0);
}