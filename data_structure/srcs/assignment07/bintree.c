#include "../../includes/bintree.h"

//BinTree create해서 root노드 값 넣고 BinTree 주소값 리턴
BinTree* makeBinTree(BinTreeNode rootNode)
{
    BinTree *bt;

    bt = (BinTree *)malloc(sizeof(BinTree));
    if (bt != NULL)
    {
        bt->pRootNode = (BinTreeNode *)malloc(sizeof(BinTreeNode));
        if (bt->pRootNode != NULL)
        {
          *(bt->pRootNode) = rootNode;
          bt->pRootNode->pLeftChild = 0;
          bt->pRootNode->pRightChild = 0;
        }
        else
        {
            free(bt);//이미 할당된 bt free
            bt = NULL;//주소값을 계속 갖고 있어 원치 않는 값 가리킬 때 대비
            printf("makeBinTree: Malloc NODE Failed\n");
            return (NULL);
        }
    }
    else
    {
        printf("makeBinTree: Malloc TREE Failed\n");
        return (NULL);
    }
    return (bt);
}
//인자로 들어온 BinTree의 루트 노드를 반환하는 함수.
BinTreeNode* getRootNodeBT(BinTree* pBinTree)
{
    if (pBinTree != NULL)
    {
        if (pBinTree->pRootNode != NULL)
        {
            return (pBinTree->pRootNode);
        }
        else
        {
            printf("getRootNode: pRootNode is NUll\n");
            return (NULL);
        }
    }
    else
    {
        printf("getRootNode: pBinTree is NUll\n");
        return (NULL);
    }
}
//인자로 받은 부모 노드의 왼쪽 자식이 element의 값을 가지도록 왼쪽 노드를 삽입하는 함수.
BinTreeNode* insertLeftChildNodeBT(BinTreeNode* pParentNode, BinTreeNode element)
{
    BinTreeNode *tmpbtn;//왼쪽 자식 노드를 위한 포인터

    tmpbtn = 0;
    if (pParentNode != NULL)
    {
        if (pParentNode->pLeftChild == NULL)
        {
            tmpbtn = (BinTreeNode *)malloc(sizeof(BinTreeNode));
            if (tmpbtn != NULL)
            {
                *tmpbtn = element;
                tmpbtn->pLeftChild = 0;
                tmpbtn->pRightChild = 0;
                pParentNode->pLeftChild = tmpbtn;
                return (tmpbtn);
            }
            else
            {
                printf("insert left: Malloc Error\n");
                return (NULL);
            }
        }
        else
        {
            printf("insert left: Already Exist\n");
            return (NULL);
        }
    }
    else
    {
        printf("insert left: pParentNode is NULL\n");
        return (NULL);
    }
}
//인자로 받은 부모 노드의 오른쪽 자식이 element의 값을 가지도록 오른쪽 노드를 삽입하는 함수.
BinTreeNode* insertRightChildNodeBT(BinTreeNode* pParentNode, BinTreeNode element)
{
    BinTreeNode *tmpbtn;//오른쪽 자식 노드를 위한 포인터

    tmpbtn = 0;
    if (pParentNode != NULL)
    { 
        if (pParentNode->pRightChild == NULL)
        {
            tmpbtn = (BinTreeNode *)malloc(sizeof(BinTreeNode));
            if (tmpbtn != NULL)
            {
                *tmpbtn = element;
                tmpbtn->pRightChild = 0;
                tmpbtn->pLeftChild = 0;
                pParentNode->pRightChild = tmpbtn;
                return (tmpbtn);
            }
            else
            {
                printf("insert right: Malloc Error\n");
                return (NULL);
            }
        }
        else
        {
            printf("insert right: Already Exist\n");
            return (NULL);
        }
    }
    else
    {
        printf("insert right: pParentNode is NULL\n");
        return (NULL);
    }
}
//인자로 받은 노드의 왼쪽 자식 주소를 반환하는 함수. 
BinTreeNode* getLeftChildNodeBT(BinTreeNode* pNode)
{
    if (pNode != NULL)
    {
        if (pNode->pLeftChild != NULL)
        {
            return (pNode->pLeftChild);
        }
        else
        {
            printf("getLeftChildNodeBt : pNode->pLeftChild is NULL\n");
            return (NULL);
        }
    }
    else
    {
        printf("getLeftChildNodeBt : pNode is NULL\n");
        return (NULL);
    }
}
//인자로 받은 노드의 오른쪽 자식 주소를 반환하는 함수. 
BinTreeNode* getRightChildNodeBT(BinTreeNode* pNode)
{
    if (pNode != NULL)
    {
        if (pNode->pRightChild != NULL)
        {
            return (pNode->pRightChild);
        }
        else
        {
            printf("getRightChildNodeBT : pNode->pRightChild is NULL\n");
            return (NULL);
        }
    }
    else
    {
        printf("getRightChildNodeBT : pNode is NULL\n");
        return (NULL);
    }
}
//인자로 받은 pBinTree의 모든 노드와 pBinTree를 할당 해제하는 함수
void deleteBinTree(BinTree* pBinTree)
{
    if (pBinTree != NULL)
    {
        if (pBinTree->pRootNode != NULL)
        {
            deleteBinTreeNode(pBinTree->pRootNode);
        }
        free(pBinTree);
        pBinTree = 0;
    }
}
//노드를 재귀적으로 삭제하는 함수.
void deleteBinTreeNode(BinTreeNode* pNode)
{
    if (pNode != NULL)
    {
        if (pNode->pLeftChild != NULL)//
            deleteBinTreeNode(pNode->pLeftChild);
        if (pNode->pRightChild != NULL)//
            deleteBinTreeNode(pNode->pRightChild);
        free(pNode);
        pNode = 0;
    }
}

/*
========================================================================

                                PREORDER

========================================================================
*/
//전위 순회
void preorderTraversalBinTree(BinTree *binTree)
{
    if (binTree != NULL)
    {
        preorderTraversalBinTreeNode(binTree->pRootNode);
        printf("\n");
    }
}

void preorderTraversalBinTreeNode(BinTreeNode *binTreeNode)
{
    if (binTreeNode != NULL)
    {
        printf("%c", binTreeNode->data);
        preorderTraversalBinTreeNode(binTreeNode->pLeftChild);
        preorderTraversalBinTreeNode(binTreeNode->pRightChild);
    } 
}

/*
========================================================================

                                INORDER

========================================================================
*/

void inorderTraversalBinTree(BinTree *binTree)
{
    if (binTree != NULL)
    {
        inorderTraversalBinTreeNode(binTree->pRootNode);
        printf("\n");
    }
}

void inorderTraversalBinTreeNode(BinTreeNode *binTreeNode)
{
    if (binTreeNode != NULL)
    {
        inorderTraversalBinTreeNode(binTreeNode->pLeftChild);
        printf("%c", binTreeNode->data);
        inorderTraversalBinTreeNode(binTreeNode->pRightChild);
    }
}

/*
========================================================================

                                POSTORDER

========================================================================
*/

void postorderTraversalBinTree(BinTree *binTree)
{
    if (binTree != NULL)
    {
        postorderTraversalBinTreeNode(binTree->pRootNode);
        printf("\n");
    }
}

void postorderTraversalBinTreeNode(BinTreeNode *binTreeNode)
{
    if (binTreeNode != NULL)
    {
        postorderTraversalBinTreeNode(binTreeNode->pLeftChild);
        postorderTraversalBinTreeNode(binTreeNode->pRightChild);
        printf("%c", binTreeNode->data);
    }
}

/*
========================================================================

                                LEVEL

========================================================================
*/

void levelOrderTraversalBinTree(BinTree *binTree)
{
    LinkedDeque *pQueue;//이진 노드 저장할 큐(덱)
    DequeNode tmpQueueNode;//루트 노드를 저장할 큐노드. 큐노드 안에는 이진노드 들어감.
    // element에 이진 노드 포인터 있음.

    pQueue = 0;
    if (binTree != NULL)
    {
        pQueue = createLinkedDeque();
        tmpQueueNode.data = binTree->pRootNode; 
        tmpQueueNode.pLLink = 0;
        tmpQueueNode.pRLink = 0;
        insertRearLD(pQueue, tmpQueueNode);
        while (isLinkedDequeEmpty(pQueue) == FALSE)
        {
            DequeNode *temp;//큐의 front 노드 주소가 들어갈 포인터
            DequeNode tempQueueNode;//temp에 저장된 이진 노드의 왼쪽 오른쪽 자식의 값이 들어갈 변수

            temp = peekFrontLD(pQueue);
            printf("%c", temp->data->data);
            if (temp->data->pLeftChild != NULL)
            {
                tempQueueNode.data = temp->data->pLeftChild;
                tempQueueNode.pRLink = 0;
                tempQueueNode.pLLink = 0;
                insertRearLD(pQueue, tempQueueNode);
            }
            if (temp->data->pRightChild != NULL)
            {
                tempQueueNode.data= temp->data->pRightChild;
                tempQueueNode.pRLink = 0;
                tempQueueNode.pLLink = 0;
                insertRearLD(pQueue, tempQueueNode);
            }
            free(deleteFrontLD(pQueue));//
        }
    }
    else
    {
        printf("binTree is NULL");
    }
    deleteLinkedDeque(pQueue);//없으면 오류남
    printf("\n");
}