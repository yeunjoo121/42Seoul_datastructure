#ifndef _LINKED_STACK_
#define _LINKED_STACK_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//여기서 Maze구조체 필요
typedef struct  StackNodeType
{
    int dx;
    int dy;
    char direction;
    struct StackNodeType* pLink;
}   MapPosition;
typedef struct LinkedStackType
{
    int currentElementCount;
    MapPosition* pTopElement;
} LinkedStack;
//////////////////maze구조체
LinkedStack* createLinkedStack();
MapPosition* popLSMapPosition(LinkedStack* pStack);
MapPosition* peekLSMapPosition(LinkedStack* pStack);
void                    deleteLinkedStack(LinkedStack* pStack);
int                     isLinkedStackFull(LinkedStack* pStack);
int                     isLinkedStackEmpty(LinkedStack* pStack);
///////maze
///////maze
#endif
#ifndef _COMMON_STACK_DEF_
#define _COMMON_STACK_DEF_
#define TRUE        1
#define FALSE       0
#define ERROR       -1
#define HEIGHT      8
#define WIDTH       8
#endif
int     direction[4][2] = { 1, 0, 0, -1, -1, 0, 0, 1 };
char    cardinal_point[4] = { 'S', 'W', 'N', 'E' };
int     mazeArray[HEIGHT][WIDTH] =
{
    0, 0, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 0, 1, 1, 1, 1,
    1, 1, 1, 0, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 1, 1, 1, 1, 1, 0
};
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
int     pushLSMapPosition(LinkedStack* pStack, MapPosition data)
{
    MapPosition* ps = NULL;
    if (pStack == NULL)
    {
        printf("[error] Null parameter : pStack\n");
        return (FALSE);
    }
    ps = (MapPosition*)malloc(sizeof(MapPosition));
    if (ps == NULL)
    {
        printf("[error] malloc failure : ps\n");
        return (FALSE);
        //malloc실패
    }
    *ps = data;
    ps->pLink = pStack->pTopElement;
    pStack->pTopElement = ps;
    pStack->currentElementCount++;
    return (TRUE);
} // maxElementCount가 없다는 점이 인상적임
// pTopElement(헤더노드) 자체가 0번째 element (?)
MapPosition* popLSMapPosition(LinkedStack* pStack)
{
    MapPosition* delNode = NULL;
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
MapPosition* peekLSMapPosition(LinkedStack* pStack)
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
        MapPosition* pNode = popLSMapPosition(pStack);
        free(pNode);
    } // 상당히 괜찮은 아이디어. 하나씩 노드 pop() 해오고 그걸 매번 free() 해준다.
    free(pStack);
}
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
void    showPath(LinkedStack* pStack, int mazeArray[HEIGHT][WIDTH])
{
    MapPosition* p;
    printf("This is a path of the Maze\n");
    p = pStack->pTopElement;
    for (int i = 0; i < pStack->currentElementCount; i++)
    {
        printf("(%d, %d) %c\n", p->dx, p->dy, p->direction);
        p = p->pLink;
    }
}
void    findPath(int mazeArray[HEIGHT][WIDTH], MapPosition startPos, MapPosition endPos, LinkedStack* pStack)
{
    if (pStack->currentElementCount != 0 && pStack->pTopElement->dx == endPos.dx && pStack->pTopElement->dy == endPos.dy)
    {
        showPath(pStack, mazeArray);
        return;
    }
    //if (pStack->currentElementCount)
    for (int i = 0; i < 4; i++)
    {
        //px에는 direction[i][1] py에는 direction[i][0]을 더한다.
        int px = pStack->pTopElement->dx + direction[i][1];
        int py = pStack->pTopElement->dy + direction[i][0];
        if (HEIGHT >= py && py >= 0 && WIDTH >= px && px >= 0)
        {
            if (mazeArray[py][px] == 0)
            {
                MapPosition current;
                memset(&current, 0, sizeof(MapPosition));
                current.dx = px;
                current.dy = py;
                current.direction = 0;
                pStack->pTopElement->direction = cardinal_point[i];
                pushLSMapPosition(pStack, current);
                mazeArray[py][px] = 2;
                findPath(mazeArray, startPos, endPos, pStack);
                mazeArray[py][px] = 0;
                MapPosition* delNode;
                delNode = popLSMapPosition(pStack);
                free(delNode);
            }
        }
    }
}
void    printMaze(int mazeArray[HEIGHT][WIDTH])
{
    printf("This is a Map of the Maze\n");
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            printf("%d ", mazeArray[i][j]);
        }
        printf("\n");
    }
}
int main(void)
{
    LinkedStack* p = createLinkedStack();
    MapPosition startPos = { 0, };
    MapPosition endPos = { 7, 7, 0, };
    printMaze(mazeArray);
    if (mazeArray[startPos.dy][startPos.dx] != 0)
    {
        printf("start position error");
        return (0);
    }
    mazeArray[startPos.dy][startPos.dx] = 2;
    pushLSMapPosition(p, startPos);
    findPath(mazeArray, startPos, endPos, p);
    mazeArray[startPos.dy][startPos.dx] = 0;
    return (0);
}