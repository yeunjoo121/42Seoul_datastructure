#ifndef _LINKED_STACK_
#define _LINKED_STACK_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct StackNodeType
{
	char data;
	struct StackNodeType* pLink;
} StackNode;

typedef struct LinkedStackType
{
	int currentElementCount;	// ���� ������ ����
	StackNode* pTopElement;		// Top ����� ������
} LinkedStack;

LinkedStack* createLinkedStack();
int pushLS(LinkedStack* pStack, StackNode element);
StackNode* popLS(LinkedStack* pStack);
StackNode* peekLS(LinkedStack* pStack);
void deleteLinkedStack(LinkedStack* pStack);
int isLinkedStackFull(LinkedStack* pStack);
int isLinkedStackEmpty(LinkedStack* pStack);

#endif

#ifndef _COMMON_STACK_DEF_
#define _COMMON_STACK_DEF_

#define TRUE		1
#define FALSE		0
#define ERROR		-1

#endif

LinkedStack* createLinkedStack()
{
  	LinkedStack* pStack = NULL;
    pStack = (LinkedStack*)malloc(sizeof(LinkedStack));
    if (pStack == NULL)
    {
        printf("[error] malloc failure : pStack\n");
        return (NULL);
    }
    memset(pStack, 0, sizeof(LinkedStack));
    return (pStack);
}

int		pushLS(LinkedStack* pStack, StackNode element)
{
  	StackNode *pNode = NULL;
  	if (pStack == NULL)
    {
      	printf("[error] Null parameter : pStack\n");
      	return (FALSE);
    }
  	pNode = (StackNode*)malloc(sizeof(StackNode));
  	if (pNode == NULL)
    {
      	printf("[error] malloc failure : pNode\n");
        return (FALSE);
      //malloc실패
    }
  	*pNode = element;
  	pNode->pLink = pStack->pTopElement;
  	pStack->pTopElement = pNode;
  	pStack->currentElementCount++;
    return (TRUE);
} // maxElementCount가 없다는 점이 인상적임
// pTopElement(헤더노드) 자체가 0번째 element (?)

StackNode* popLS(LinkedStack* pStack)
{
  	StackNode *delNode = NULL;
		if (pStack == NULL)
    {
      	printf("[error] Null parameter : pStack\n");
      	return (FALSE);//각자
    }
  	if (isLinkedStackEmpty(pStack) == TRUE)
    {
      	printf("[error] Stack Underflow\n");
      	return (delNode);//각자
    }
  	delNode = pStack->pTopElement;
  	pStack->pTopElement = delNode->pLink;
  	delNode->pLink = NULL; //어차피 반환할 노드니까 pLink를 널로.
  	pStack->currentElementCount--;
  	return (delNode);
}

StackNode* peekLS(LinkedStack* pStack)
{
  	if (pStack == NULL)
    {
      	printf("[error] Null parameter : pStack\n");
      	return (FALSE);//각자
    }
  	if (isLinkedStackEmpty(pStack) == TRUE)
    {
      	printf("[error] Stack is empty\n");
      	return (FALSE);//각자
    }
  	return (pStack->pTopElement);
}

void deleteLinkedStack(LinkedStack* pStack)
{
  	if (pStack == NULL)
    {
      	printf("[error] Null parameter : pStack\n");
    }
  	int index = pStack->currentElementCount;
  	for (int i = 0; i < index; i++)
    {
      	StackNode *pNode = popLS(pStack);
      	free(pNode);
    } // 상당히 괜찮은 아이디어. 하나씩 노드 pop() 해오고 그걸 매번 free() 해준다.
  	free(pStack);
}

/*
    while (pStack->currentElementCount) // currElement는 pop()할때마다 하나씩 줄음
    {
      	StackNode *pNode = popLS(pStack);
      	free(pNode);
    } // 상당히 괜찮은 아이디어. 하나씩 노드 pop() 해오고 그걸 매번 free() 해준다.
  	free(pStack);
*/

int isLinkedStackEmpty(LinkedStack* pStack)
{
  if (pStack == NULL)
  {
    	printf("[error] Null parameter : pStack\n");
    	return (FALSE);
  }
  if (pStack->currentElementCount == 0)
  {
    	
    	return (TRUE);
  }
  return (FALSE);
}

int isLinkedStackFull(LinkedStack* pStack)
{
  	return (FALSE);
}

void displayLS(LinkedStack* pStack)
{
    StackNode *pNode = pStack->pTopElement;
    for(int i = 0; i < pStack->currentElementCount; i++)
    {
        printf("%c\n", pNode->data);
        pNode = pNode->pLink;
    }
}

int main(void)
{
    LinkedStack *p = NULL;
    p = createLinkedStack();
    StackNode n1 = {'1', NULL};
    StackNode n2 = {'2', NULL};
    StackNode n3 = {'3', NULL};

    pushLS(p, n1);
    pushLS(p, n2);
    pushLS(p, n3);
    displayLS(p);
    deleteLinkedStack(p);
    system("leaks a.out");
    displayLS(p);
}