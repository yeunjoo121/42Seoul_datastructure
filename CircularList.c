#ifndef _CircularLIST_
#define _CircularLIST_
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct ListNodeType
{
    int data;
    struct ListNodeType* pLink;
} ListNode;
typedef struct CircularListType
{
    int currentElementCount;	// ���� ����� ������ ����
    ListNode headerNode;		// ��� ���(Header Node)
} CircularList;
CircularList* createCircularList();
int addLLElement(CircularList* pList, int position, ListNode element);
int removeLLElement(CircularList* pList, int position);
ListNode* getLLElement(CircularList* pList, int position);
void clearCircularList(CircularList* pList);
int getCircularListLength(CircularList* pList);
void deleteCircularList(CircularList* pList);
#endif
#ifndef _COMMON_LIST_DEF_
#define _COMMON_LIST_DEF_
#define TRUE		1
#define FALSE		0
#endif

CircularList* createCircularList()
{
    CircularList* pList = NULL;
    pList = (CircularList*)malloc(sizeof(CircularList));
    if (pList == NULL)
    {
        printf("malloc failure\n");
        return (NULL);
    }
    memset(pList, 0, sizeof(CircularList));
    return (pList);
}

int addLLElement(CircularList* pList, int position, ListNode element)
{
    ListNode* pNode = NULL;
    ListNode* nextNode = NULL;
    if (pList != NULL)
    {
        if (position >= 0 && position <= pList->currentElementCount)
        {
          nextNode = (ListNode*)malloc(sizeof(ListNode));
          //case나눠서
            if (nextNode != NULL)
            {
                pNode = &(pList->headerNode);
                *nextNode = element;
                nextNode->pLink = NULL;
            	if (pList->currentElementCount == 0)//첫번째 case. node가 아무것도 없고 0번째에 노드 추가할 때
          		{
            		pNode->pLink = nextNode;
                	nextNode->pLink = nextNode;
          		}
              	else if (position == 0 && pList->currentElementCount > 0)//2번째 case. node가 1개 이상이고 0번째에 노드 추가할 때
                {
                  	nextNode->pLink = pNode->pLink;
                  	pNode->pLink = nextNode;
                  	for(int i = 0; i < pList->currentElementCount; i++)
                    {
                      pNode = pNode->pLink;
                    }
                  	pNode->pLink = nextNode;
                }
              	else//3번째 case. node가 1개 이상이고 0번째가 아닌 position에 노드 추가할 때
                {
                  	for (int i = 0; i < position; i++)
                	{
                    	pNode = pNode->pLink;
                	}
                	nextNode->pLink = pNode->pLink;
                	pNode->pLink = nextNode;
                }
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

int removeLLElement(CircularList* pList, int position)
{
    ListNode* pNode = NULL;
    ListNode* removeNode = NULL;

    if (pList != NULL)
    {
        if (position >= 0 && position < pList->currentElementCount)
        {
            pNode = &(pList->headerNode);
          	if (pList->currentElementCount == 1)//case 1. 리스트에 노드 1개있고 이 0번째 노드 지울때.
            {
				removeNode = pNode->pLink;
              	memset(removeNode, 0, sizeof(ListNode));//removenode값 초기화
              	free(removeNode);
              	pNode->pLink = NULL;
            }
          	else if (pList->currentElementCount > 1 && position == 0)//리스트에 노드 1개 이상 있고 0번째 노드 지울때
            {
				removeNode = pNode->pLink;
              	pNode->pLink = removeNode->pLink;
              	for(int i = 0; i < pList->currentElementCount; i++)
                {
                  pNode = pNode->pLink;
                }
              	pNode->pLink = removeNode->pLink;
              	memset(removeNode, 0, sizeof(ListNode));
              	free(removeNode);
            }
          	else//3번째 case. 리스트에 노드 1개 이상 있고 첫번째가 아닌 노드 삭제.
            {
				for (int i = 0; i < position; i++)
				{
					pNode = pNode->pLink;
				}
				removeNode = pNode->pLink;
				pNode->pLink = removeNode->pLink;
				free(removeNode);
            }
            pList->currentElementCount--;
            return (TRUE);
        }
    }
    return (FALSE);
}

ListNode* getLLElement(CircularList* pList, int position)
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

int getCircularListLength(CircularList* pList)
{
    if (pList != NULL)
    {
        return (pList->currentElementCount);
    }
    return (-1);
}

void clearCircularList(CircularList* pList)
{
    if (pList->headerNode.pLink != NULL)
    {
        while (removeLLElement(pList, 0));
    }
}

void deleteCircularList(CircularList* pList)
{
    if (pList != NULL)
    {
        clearCircularList(pList);
        memset(pList, 0, sizeof(CircularList));
        free(pList);
        pList = NULL;
    }
}

void	displayCircularList(CircularList* pList)
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
    CircularList* p;
    ListNode n;
    ListNode n2;
    ListNode n3;
    // n = (ListNode*)malloc(sizeof(ListNode));
    // n2 = (ListNode*)malloc(sizeof(ListNode));
    // n3 = (ListNode*)malloc(sizeof(ListNode));
    n.data = 1;
    n.pLink = NULL;
    n2.data = 2;
    n2.pLink = NULL;
    n3.data = 3;
    n3.pLink = NULL;
    p = createCircularList();
	addLLElement(p, 0, n);
    displayCircularList(p);
    // addLLElement(p, 1, n2);
    // displayCircularList(p);
	// addLLElement(p, 2, n3);
    // displayCircularList(p);
	removeLLElement(p, 0);
	displayCircularList(p);
}