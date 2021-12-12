#include "../../includes/bintree.h"

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

BinTreeNode* insertLeftChildNodeBT(BinTreeNode* pParentNode, BinTreeNode element)
{
    BinTreeNode *tmpbtn;

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

BinTreeNode* insertRightChildNodeBT(BinTreeNode* pParentNode, BinTreeNode element)
{
    BinTreeNode *tmpbtn;

    tmpbtn = 0;
    if (pParentNode != NULL)
    { 
        if (pParentNode->pRightChild == NULL)
        {
            tmpbtn = (BinTreeNode *)malloc(sizeof(BinTreeNode));
            if (tmpbtn)
            {
                *tmpbtn = element;
                tmpbtn->pRightChild = 0;
                tmpbtn->pRightChild = 0;
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
void deleteBinTree(BinTree* pBinTree)
{
    if (pBinTree != NULL)
    {
        if (pBinTree->pRootNode != NULL)
        {
            deleteBinTreeNode(pBinTree->pRootNode);
        }
        memset(pBinTree, 0, sizeof(BinTree));
        free(pBinTree);
        pBinTree = 0;
    }
}

void deleteBinTreeNode(BinTreeNode* pNode)
{
    if (pNode != NULL)
    {
        if (pNode->pLeftChild != NULL)
            deleteBinTreeNode(pNode->pLeftChild);
        if (pNode->pRightChild != NULL)
            deleteBinTreeNode(pNode->pRightChild);
        memset(pNode, 0, sizeof(BinTreeNode));
        free(pNode);
        pNode = 0;
    }
}

/*
========================================================================

                                PREORDER

========================================================================
*/

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
    LinkedDeque *pQueue;
    DequeNode tmpQueueNode;

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
            DequeNode *temp;
            DequeNode tempQueueNode;

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
            temp = temp->pRLink;
            free(deleteFrontLD(pQueue));
        }
    }
    else
    {
        printf("binTree is NULL");
    }
    deleteLinkedDeque(pQueue);//없으면 오류남
    printf("\n");
}