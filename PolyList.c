#ifndef _LINKEDLIST_
#define _LINKEDLIST_
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct ListNodeType
{
  	float coef;
    int degree;
    struct ListNodeType* pLink;
} ListNode;
typedef struct LinkedListType
{
    int currentElementCount;	// ���� ����� ������ ����
    ListNode headerNode;		// ��� ���(Header Node)
} LinkedList;
LinkedList* createLinkedList();
int addLLElement(LinkedList* pList, int position, ListNode element);
int removeLLElement(LinkedList* pList, int position);
ListNode* getLLElement(LinkedList* pList, int position);
void clearLinkedList(LinkedList* pList);
int getLinkedListLength(LinkedList* pList);
void deleteLinkedList(LinkedList* pList);
int addPolyNodeLast(LinkedList* pList, float coef, int degree);//다항식 추가
LinkedList* polyAdd(LinkedList* pListA, LinkedList* pListB);//추가
void displayPolyList(LinkedList* pList);//추가
#endif
#ifndef _COMMON_LIST_DEF_
#define _COMMON_LIST_DEF_
#define TRUE		1
#define FALSE		0
#endif

LinkedList* createLinkedList()
{
    LinkedList* pList = NULL;
    pList = (LinkedList*)malloc(sizeof(LinkedList));
    if (pList == NULL)
    {
        printf("malloc failure\n");
        return (NULL);
    }
    memset(pList, 0, sizeof(LinkedList));
    return (pList);
}

int addLLElement(LinkedList* pList, int position, ListNode element)
{
    ListNode* pNode = NULL;
    ListNode* nextNode = NULL;
    if (pList != NULL)
    {
        if (position >= 0 && position <= pList->currentElementCount)
        {
            nextNode = (ListNode*)malloc(sizeof(ListNode));
            if (nextNode != NULL)
            {
                pNode = &(pList->headerNode);
                *nextNode = element;
                nextNode->pLink = NULL;
                for (int i = 0; i < position; i++)
                {
                    pNode = pNode->pLink;
                }
                nextNode->pLink = pNode->pLink;
                pNode->pLink = nextNode;
                (pList->currentElementCount)++;
                return (TRUE);
            }
        }
        else
        {
            printf("out of index\n");
        }
    }
    return (FALSE);
}

int removeLLElement(LinkedList* pList, int position)
{
    ListNode* pNode = NULL;
    ListNode* removeNode = NULL;

    if (pList != NULL)
    {
        if (position >= 0 && position < pList->currentElementCount)
        {
            pNode = &(pList->headerNode);
            for (int i = 0; i < position; i++)
            {
                pNode = pNode->pLink;
            }
            removeNode = pNode->pLink;
            pNode->pLink = removeNode->pLink;
            free(removeNode);
            pList->currentElementCount--;
            return (TRUE);
        }
    }
    return (FALSE);
}

ListNode* getLLElement(LinkedList* pList, int position)
{
    ListNode* pNode = NULL;

    if (pList != NULL)
    {
        pNode = &(pList->headerNode);
        if (position >= 0 && position < pList->currentElementCount)
        {
            for (int i = 0; i <= position; i++)
            {
                pNode = pNode->pLink;
            }
            return (pNode);
        }
    }
    return (NULL);
}

int getLinkedListLength(LinkedList* pList)
{
    if (pList != NULL)
    {
        return (pList->currentElementCount);
    }
    return (-1);
}

void clearLinkedList(LinkedList* pList)
{
    if (pList->headerNode.pLink)
    {
        while (removeLLElement(pList, 0));
    }
}

void deleteLinkedList(LinkedList* pList)
{
    if (pList != NULL)
    {
        clearLinkedList(pList);
        memset(pList, 0, sizeof(LinkedList));
        free(pList);
        pList = NULL;
    }
}

void reverseLinkedList(LinkedList* pList)
{
  ListNode *pNode = NULL;
  ListNode *pCurrentNode = NULL;
  ListNode *pPrevNode = NULL;
  
  if (pList != NULL)
  {
    pNode = pList->headerNode.pLink;
    while (pNode != NULL)
    {
      pPrevNode = pCurrentNode;
      pCurrentNode = pNode;
      pNode = pNode->pLink;
      pCurrentNode->pLink = pPrevNode;
    }
    pList->headerNode.pLink = pCurrentNode;
  }
}

int addPolyNodeLast(LinkedList* pList, float coef, int degree)
{
	int ret = FALSE;
  
  	ListNode node = {0, };
  	node.coef = coef;
  	node.degree = degree;
  	if (pList != NULL)
    {
      int length = getLinkedListLength(pList);
      ret = addLLElement(pList, length, node);
    }
  	return ret;
}

LinkedList* polyAdd(LinkedList* pListA, LinkedList* pListB)
{
  	LinkedList* pResult = NULL;
  	ListNode* pNodeA = NULL;
  	ListNode* pNodeB = NULL;
  
  	pResult = createLinkedList();
  	if (pResult == NULL)
    {
      return (NULL);//malloc 실패
    }
	pNodeA = pListA->headerNode.pLink;
    pNodeB = pListB->headerNode.pLink;
  	while (pNodeA != NULL && pNodeB != NULL)//case가 3개로 나뉨.
    {
      if (pNodeA->degree > pNodeB->degree)//A가 B보다 차수가 클때
      {
        addPolyNodeLast(pResult, pNodeA->coef, pNodeA->degree);
        pNodeA = pNodeA->pLink;
      }
      else if (pNodeA->degree < pNodeB->degree)//B가 A보다 차수가 클 때
      {
        addPolyNodeLast(pResult, pNodeB->coef, pNodeB->degree);
        pNodeB = pNodeB->pLink;
      }
      else//A와 B가 차수가 같을 때
      {
        addPolyNodeLast(pResult, pNodeA->coef + pNodeB->coef, pNodeA->degree);
        pNodeA = pNodeA->pLink;
        pNodeB = pNodeB->pLink;
      }
    }
  	while (pNodeA != NULL)//pNodeA만 현재 남아있음 남은 노드 처리 부분.
    {
      	addPolyNodeLast(pResult, pNodeA->coef, pNodeA->degree);
      	pNodeA = pNodeA->pLink;
    }
  	while (pNodeB != NULL)
    {
      	addPolyNodeLast(pResult, pNodeB->coef, pNodeB->degree);
      	pNodeB = pNodeB->pLink;
    }
  	return (pResult);
}

void	displayPolyList(LinkedList* pList)
{
    ListNode* pNode = NULL;
    if (pList == NULL)
	{
        return ;
	}
    pNode = pList->headerNode.pLink;
    for (int i = 0; i < pList->currentElementCount; i++)
    {
        printf("%fx%d", pNode->coef, pNode->degree);
        pNode = pNode->pLink;
      	if (pNode != NULL)
        {
          	printf(" + ");
        }
    }
	printf("\n");
}

int main(void)
{
    LinkedList *p1, *p2;
	LinkedList *ret;
    ListNode n = {3, 3, 0};
    ListNode n2 = {2, 1, 0};
    ListNode n3 = {1, 0, 0};
    ListNode n4 = {2, 3, 0};
    ListNode n5 = {2, 2, 0};


    p1 = createLinkedList();
	p2 = createLinkedList();
	addPolyNodeLast(p1, n.coef, n.degree);
	addPolyNodeLast(p1, n2.coef, n2.degree);
	addPolyNodeLast(p1, n3.coef, n3.degree);
	addPolyNodeLast(p2, n4.coef, n4.degree);
	addPolyNodeLast(p2, n5.coef, n5.degree);

	displayPolyList(p1);
	displayPolyList(p2);

	ret = polyAdd(p1, p2);
	displayPolyList(ret);
}