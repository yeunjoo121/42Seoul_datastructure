#include "../../includes/bintree.h"

/*
==================================================================

					    BINARYTREE_CHECKER

==================================================================
*/
int deleteflag = 0;

BinTreeNode *find_parent(BinTree *tree,char *position)
{
    BinTreeNode *node = NULL;
    int str_len = 0;
    int i = 0;

    str_len = strlen(position);
    if (str_len == 0)
    {
        printf("[error] No input in position\n");
        return (FALSE);
    }
    node = tree->pRootNode;
    while (i < str_len - 1)
    {
        if (position[i] == 'l' || position[i] == 'L')
        {    
            node = node->pLeftChild;
        }
        else if (position[i] == 'r' || position[i] == 'R')
        {
            node = node->pRightChild;
        }
        else
        {
            printf("[error] invalid position value.\n");
            return (FALSE);
        }
        if (node == NULL)
        {
            printf("[error] No node existing in that position.\n");
            return (FALSE);
        }
        i++;
    }
    return (node);
}

BinTreeNode *getNode(BinTree *tree,char *position)
{
    BinTreeNode *node = NULL;
    BinTreeNode *preturn = NULL;
    int         i = strlen(position) - 1;

    if (!(node = find_parent(tree, position)))
    {
        printf("[error] Cannot find ParentNode of that position.\n");
        return (FALSE);
    }
    if (position[i] == 'r' || position[i] == 'R')
        preturn = getRightChildNodeBT(node);
    if (position[i] == 'l' || position[i] == 'L')
        preturn = getLeftChildNodeBT(node);
    if (preturn == NULL)
    {
        printf("[error] Failed to get a Node of that position.\n");
        return (FALSE);
    }
    return (preturn);
}

int     putNode(BinTree *tree,char *position, char value)
{
    BinTreeNode *node = NULL;
    int         str_len = 0;
    
    if (!(node = find_parent(tree, position)))
    {
        printf("[error] Cannot find ParentNode of that position.\n");
        return (FALSE);
    }
    str_len = strlen(position);
    
    // position에 lLrR이 아닌 값이 들어왔을 경우의 예외처리를 이어서.
    if (!(position[str_len - 1] == 'l' || position[str_len - 1] == 'L'
        || position[str_len - 1] == 'r' || position[str_len - 1] == 'R'))
    {
        printf("[error]✅ invalid position value.\n");
        return (FALSE);
    }
    // parent 노드의 leftchild에 노드를 넣는다.
    BinTreeNode ele;
    memset(&ele, 0, sizeof(BinTreeNode));
    ele.data = value;
    if (position[str_len - 1] == 'l' || position[str_len - 1] == 'L')
    {
        if (!insertLeftChildNodeBT(node, ele))
        {
            printf("[error] Failed to insert a node\n");
            return (FALSE);
        }
    }
    // parent 노드의 rightchild에 노드를 넣는다.
    if (position[str_len - 1] == 'r' || position[str_len - 1] == 'R')
    {
        if (!insertRightChildNodeBT(node, ele))
        {
            printf("[error] Failed to insert a node\n");
            return (FALSE);
        }
    }
    return (TRUE);
}

void    traversal(BinTree *tree)
{
    int option = 0;
    int err_flag = 1;

    while (1)
    {
        printf("=========================================================================\n");
        printf("Tree Traversal Option :\n   1 preorder    2 inorder    3 postorder   4 levelOrder    5 exit\n");
        scanf("%d", &option);
        if (option == 5)
        {
            printf("Exit : Terminate the test program\n");
            break;
        }
        switch (option)
        {
            case 1 :
                preorderTraversalBinTree(tree);
                break;
            case 2 :
                inorderTraversalBinTree(tree);
                break;
            case 3 :
                postorderTraversalBinTree(tree);
                break;
            // case 4 : 
            //     levelOrderTraversalBinTree(tree);
            //     break;
            default :
            {
                err_flag = 0;
                printf("[error] Invalid Command\n");
                break;
            }
        }
        if (err_flag == 0)
            printf("[error] Terminate the program.\n");
    }
}

void    set_Nodes(BinTree *tree)
{
    char    *position;
    char    value;
    int     n = 0;
    int     err_flag = 1;

    position = (char *)malloc(sizeof(char) * 100);
    while (1)
    {
        memset(position, 0, sizeof(char) * 100);
        printf("=========================================================================\n");
        printf("\nNode setting option :\n");
        printf("    1 : Insert Node    2 : Get Node    3 : Delete     4 : traversal     5 : Exit \n");
        scanf(" %d", &n);
        if (n == 5)
        {
            printf("Exit : Terminate the test program\n");
            break;
        }
        switch (n)
        {
            case 1 :
            {
                if (deleteflag == 1)
                {
                    printf("already tree deleted\n");
                    break;
                }
                printf("Enter the position and value.\n");
                printf("Position : ");
                scanf(" %s", position);
                printf("value : ");
                scanf(" %c", &value);
                printf("check position : %s\n", position);
                err_flag = putNode(tree, position, value);
                break;
            }
            case 2 :
            {
                BinTreeNode *node = NULL;
                if (deleteflag == 1)
                {
                    printf("already tree deleted\n");
                    break;
                }
                printf("Enter the position to find a node.\n");
                printf("Position : ");
                scanf(" %s", position);
                if ((node = getNode(tree, position)) == NULL)
                {
                    err_flag = 0;
                    break;
                }
                printf("Node : %c\n", node->data);
                break;
            }
            case 3 :
            {
                if (deleteflag == 1)
                {
                    printf("already tree deleted\n");
                    break;
                }
                deleteflag = 1;
                deleteBinTree(tree);
                break;
            }
            case 4 :
            {
                if (deleteflag == 1)
                {
                    printf("already tree deleted\n");
                    break;
                }
                traversal(tree);
                break;
            }
            default :
            {
                err_flag = 0;
                printf("[error] Invalid Command\n");
                break;
            }
        }
        if (err_flag == 0)
        {
            printf("[error] Terminate the program.\n");
            break;
        }
    }
    free(position);
}

void    test()
{
    BinTree *tree;
    BinTreeNode root;

    printf("===================TEST PROGRAM FOR BINARY TREE IMPLEMENTATION===================\n\n");

    root.data = 'a';
    tree = makeBinTree(root);
    printf(">> Set the Nodes\n\n");
    set_Nodes(tree);
    if (deleteflag == 0)
    {
        deleteBinTree(tree);
    }
}
BinTreeNode *makeNewNodeBT(int value)
{
    BinTreeNode *pNode = (BinTreeNode *)malloc(sizeof(BinTreeNode));
    if (pNode != NULL)
    {
        pNode->data = value;
        pNode->pLeftChild = 0;
        pNode->pRightChild = 0;
    }
    return (pNode);
}

int     main()
{
    test();
    system("leaks a.out");
    return (0);
}