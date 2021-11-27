#ifndef _ARRAY_STACK_
#define _ARRAY_STACK_
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct ArrayStackNodeType {
	char data;
} ArrayStackNode;

typedef struct ArrayStackType {
	int maxElementCount;		// �ִ� ���� ����
	int currentElementCount;	// ���� ������ ����
	ArrayStackNode *pElement;	// ��� ������ ���� 1���� array
} ArrayStack;

ArrayStack* createArrayStack(int maxElementCount);
int pushAS(ArrayStack* pStack, ArrayStackNode element);
ArrayStackNode* popAS(ArrayStack* pStack);
ArrayStackNode* peekAS(ArrayStack* pStack);
void deleteArrayStack(ArrayStack* pStack);
int isArrayStackFull(ArrayStack* pStack);
int isArrayStackEmpty(ArrayStack* pStack);

#endif

#ifndef _COMMON_STACK_DEF_
#define _COMMON_STACK_DEF_

#define TRUE		1
#define FALSE		0
#define ERROR -1

#endif
ArrayStack* createArrayStack(int maxElementCount)
{
    ArrayStack* pStack = NULL;

    if (maxElementCount < 0)
    {
        printf("[error] invalid value : maxElementCount\n");//invalid maxElementCount value
        return (pStack);
    }
    pStack = (ArrayStack*)malloc(sizeof(ArrayStack));//스택을 동적할당
    if (pStack == NULL)
    {
        printf("[error] malloc failure : pStack\n");
      	return (pStack);
    } // malloc failure handling
    memset(pStack, 0, sizeof(ArrayStack));//ArrayStack만큼 0으로 초기화
  	pStack->maxElementCount = maxElementCount;//maxElementCount만 값 넣기
  	pStack->pElement = (ArrayStackNode*)malloc(sizeof(ArrayStackNode));
  	if (pStack->pElement == NULL)//pElement 동적할당 실패
    {
      	printf("[error] malloc failure : pElement\n");
      	free(pStack);
      	return (NULL);
    }
  	memset(pStack->pElement, 0, sizeof(ArrayStackNode) * maxElementCount);
  	return (pStack);
}

int pushAS(ArrayStack* pStack, ArrayStackNode element)
{
  	int ret = FALSE;
    if (pStack == NULL)
    {
      	return (ret);
    }
  	if (isArrayStackFull(pStack) == 0)
    {
      	pStack->pElement[pStack->currentElementCount] = element;
      	pStack->currentElementCount++;
      	ret = TRUE;
    }
    else
    {
        printf("[error] Stack Overflow\n");
    }
	return (ret);
}

ArrayStackNode* popAS(ArrayStack* pStack)
{
  	ArrayStackNode *pNode = NULL;
  	
	if (pStack == NULL) 
  	{
   		printf("[error] Null parameter : pStack\n");
        return (pNode);
    }
  	if (isArrayStackEmpty(pStack) == 0)
    {
      pNode = (ArrayStackNode*)malloc(sizeof(ArrayStackNode));
      if (pNode == NULL)
      {
        printf("[error] malloc failure : pNode\n");
        return (pNode);
      }
      *pNode = pStack->pElement[pStack->currentElementCount - 1];
      pStack->pElement[pStack->currentElementCount - 1].data = 0;
      pStack->currentElementCount--;
    }
  	else
    {
      printf("[error] undefined behavior : Cannot try pop() on a Empty stack\n");
    }
  	return (pNode);
}

ArrayStackNode* peekAS(ArrayStack* pStack)
{
		if (pStack == NULL) 
  	{
  		printf("[error] Null parameter : pStack\n");
  	}
  	if (isArrayStackEmpty(pStack) == 0)
	  {
  		return (&(pStack->pElement[pStack->currentElementCount - 1]));
  	}
  	else
  	{
    	printf("[error] undefined behavior : Cannot try peek() on a Empty stack\n");
  	}
  	return (FALSE);
}

void deleteArrayStack(ArrayStack* pStack)
{
		
  	if (pStack == NULL)
    {
      printf("[error] Null parameter : pStack\n");
      return ;
    }
  	if (pStack->pElement != NULL)
    {
      free(pStack->pElement);
    }
	free(pStack);
}

int isArrayStackFull(ArrayStack* pStack)
{
  	int ret = FALSE;
  
  	if (pStack != NULL)
    {
      if (pStack->currentElementCount == pStack->maxElementCount)
      {
        ret = TRUE;
      }
    }
  	else
    {
      return (ERROR);
    }
  	return (ret);
}

int isArrayStackEmpty(ArrayStack* pStack)
{
  	if (pStack == NULL)
    {
      return (ERROR);
    }
  	if (pStack->currentElementCount == 0)
    {
    		return (TRUE);
    }
    return (FALSE);
}

void displayAS(ArrayStack* pStack)
{
    if (pStack != NULL && pStack->pElement != NULL)
    {
        for (int i = 0; i < pStack->currentElementCount; i++)
        {
            printf("%c\n", pStack->pElement[i].data);
        }
    }
}
int main(void)
{
    ArrayStack *st = createArrayStack(5);
    ArrayStackNode n1 = {'1'};
    ArrayStackNode n2 = {'2'};
    ArrayStackNode n3 = {'3'};
    ArrayStackNode *ret1 = {0};
    ArrayStackNode *ret2 = {0};
    ArrayStackNode *ret3 = {0};
    pushAS(st, n1);
    pushAS(st, n2);
    pushAS(st, n3);
    ret1 = peekAS(st);
    printf("%c\n", (*ret1).data);
    popAS(st);
    ret2 = peekAS(st);
    printf("%c\n", (*ret2).data);
}