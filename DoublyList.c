#ifndef _DOUBLYLIST_
#define _DOUBLYLIST_

typedef struct DoublyListNodeType
{
	int data;
	struct DoublyListNodeType* pLLink;
	struct DoublyListNodeType* pRLink;
} DoublyListNode;

typedef struct DoublyListType
{
	int	currentElementCount;		// ���� ����� ������ ����
	DoublyListNode	headerNode;		// ��� ���(Header Node)
} DoublyList;

DoublyList* createDoublyList();
void deleteDoublyList(DoublyList* pList);
int addDLElement(DoublyList* pList, int position, DoublyListNode element);
int removeDLElement(DoublyList* pList, int position);
void clearDoublyList(DoublyList* pList);
int getDoublyListLength(DoublyList* pList);
DoublyListNode* getDLElement(DoublyList* pList, int position);
void displayDoublyList(DoublyList* pList);

#endif

#ifndef _COMMON_LIST_DEF_
#define _COMMON_LIST_DEF_

#define TRUE		1
#define FALSE		0

#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

DoublyList* createDoublyList()
{
  	DoublyList* pList = NULL;
  	pList = (DoublyList*)malloc(sizeof(DoublyList));
  	if (pList == NULL)
    {
        printf("malloc failure\n");
        return (NULL);
    }
  	memset(pList, 0, sizeof(DoublyList));
  	pList->headerNode.pRLink = &(pList->headerNode);//create할 때 headerNode의 멤버변수 값을 0으로 해야 하는지
  	pList->headerNode.pLLink = &(pList->headerNode);//아니면 pRLink, pLLink값을 headerNode의 주소값으로 해야하는지
  	return (pList);
}

int addDLElement(DoublyList* pList, int position, DoublyListNode element)
{
  	DoublyListNode* pNode = NULL;
	DoublyListNode* nextNode = NULL;
  
  	if (pList != NULL)
    {
      if (position >= 0 && position <= pList->currentElementCount)
      {
      	nextNode = (DoublyListNode*)malloc(sizeof(DoublyListNode));
        if (nextNode != NULL)
        {
          pNode = &(pList->headerNode);
          
          *nextNode = element;
          nextNode->pLLink = NULL;
          nextNode->pRLink = NULL;
          if (pList->currentElementCount == 0)//첫번째 case. node가 아무것도 없고 0번째에 노드 추가
          {
            pNode->pLLink = nextNode;
            pNode->pRLink = nextNode;
            nextNode->pLLink = pNode;
            nextNode->pRLink = pNode;
          }
          else
          {
            for(int i = 0; i < position; i++)
            {
              pNode = pNode->pRLink;
            }
            nextNode->pLLink = pNode;
            nextNode->pRLink = pNode->pRLink;
            pNode->pRLink = nextNode;
          }
          	(pList->currentElementCount)++;
			return (TRUE);
        }
      }
    }
  return (FALSE);
}

int removeDLElement(DoublyList* pList, int position)
{
	DoublyListNode* pNode = NULL;
  	DoublyListNode* removeNode = NULL;
  
  	if (pList != NULL)
    {
      if (position >= 0 && position < pList->currentElementCount)
      {
        pNode = &(pList->headerNode);
        for(int i = 0; i < position; i++)
        {
          pNode = pNode->pRLink;
        }
        removeNode = pNode->pRLink;
        pNode->pRLink = removeNode->pRLink;
        removeNode->pRLink->pLLink = pNode;
        memset(removeNode, 0, sizeof(DoublyListNode));
        free(removeNode);
		pList->currentElementCount--;
      	return (TRUE);
      }
    }
  return (FALSE);
}

void clearDoublyList(DoublyList* pList)
{
  if (pList->headerNode.pRLink != &(pList->headerNode))
  {
    while (removeDLElement(pList, 0));
  }
}

void deleteDoublyList(DoublyList* pList)
{
  if (pList != NULL)
  {
    clearDoublyList(pList);
    memset(pList, 0, sizeof(DoublyList));
    free(pList);
    pList = NULL;
  }
}

int getDoublyListLength(DoublyList* pList)
{
  if (pList != NULL)
  {
    return (pList->currentElementCount);
  }
  return (-1);
}

DoublyListNode* getDLElement(DoublyList* pList, int position)
{
  DoublyListNode* pNode = NULL;
  
  if (pList != NULL)
  {
    pNode = &(pList->headerNode);
    if (position >= 0 && position < pList->currentElementCount)
    {
      for (int i = 0; i <= position; i++)
      {
        pNode = pNode->pRLink;
      }
      return (pNode);
    }
  }
  return (NULL);
}

void displayDoublyList(DoublyList* pList)
{
  DoublyListNode* pNode = NULL;
  if (pList == NULL)
  {
    return ;
  }
  pNode = pList->headerNode.pRLink;
  for(int i = 0; i < pList->currentElementCount; i++)
  {
    printf("%d번째 : %d\n", i, pNode->data);
    pNode = pNode->pRLink;
  }
}

int main(void)
{
    DoublyList* p;
    DoublyListNode n = {1, 0, 0};
    DoublyListNode n2 = {2, 0, 0};
    DoublyListNode n3 = {3, 0, 0};
    // n = (ListNode*)malloc(sizeof(ListNode));
    // n2 = (ListNode*)malloc(sizeof(ListNode));
    // n3 = (ListNode*)malloc(sizeof(ListNode));
    p = createDoublyList();
	addDLElement(p, 0, n);
	displayDoublyList(p);
	addDLElement(p, 1, n2);
	displayDoublyList(p);
	addDLElement(p, 2, n3);
	displayDoublyList(p);
	removeDLElement(p, 2);
	displayDoublyList(p);
	printf("%d\n", getDLElement(p, 0)->data);
	clearDoublyList(p);
	displayDoublyList(p);
	deleteDoublyList(p);
}