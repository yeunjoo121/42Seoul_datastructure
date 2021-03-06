#ifndef _LINKEDLIST_
#define _LINKEDLIST_
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct ListNodeType
{
    int data;
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

void	displayLinkedList(LinkedList* pList)
{
    ListNode* pNode = NULL;
    if (pList == NULL)
	{
        return ;
	}
    pNode = pList->headerNode.pLink;
    for (int i = 0; i < pList->currentElementCount; i++)
    {
        printf("%d번째: %d\n", i, pNode->data);
        pNode = pNode->pLink;
    }
}

int main(void)
{
    LinkedList* p;
    ListNode n;
    ListNode n2;
    ListNode n3;
    n.data = 1;
    n.pLink = NULL;
    n2.data = 2;
    n2.pLink = NULL;
    n3.data = 3;
    n3.pLink = NULL;
    p = createLinkedList();
	addLLElement(p, 0, n);
    displayLinkedList(p);
    addLLElement(p, 1, n2);
    displayLinkedList(p);
    addLLElement(p, 2, n3);
    displayLinkedList(p);
    reverseLinkedList(p);
    displayLinkedList(p);
}