#include "iostream"
using namespace std;

typedef struct treeNode
{
    char data;
    struct treeNode *LChild;
    struct treeNode *RChild;
} TREE, *LPTREE;

LPTREE creatNode(char data)
{
    LPTREE newNode = new (TREE);
    newNode->data = data;
    newNode->LChild = NULL;
    newNode->RChild = NULL;
    return newNode;
}

void insertNode(LPTREE parentNode, LPTREE LChild, LPTREE RChild)
{
    parentNode->LChild = LChild;
    parentNode->RChild = RChild;
}

void printCurNodeData(LPTREE CurNode)
{
    cout << "，" << CurNode->data;
}

//递归法遍历
//先序 根左右

void preOrder(LPTREE root)
{
    if (root)
    {
        printCurNodeData(root);
        preOrder(root->LChild);
        preOrder(root->RChild);
    }
}

void minOrder(LPTREE root)
{
    if (root)
    {
        minOrder(root->LChild);
        printCurNodeData(root);
        minOrder(root->RChild);
    }
}

void lastOrder(LPTREE root)
{
    if (root)
    {
        lastOrder(root->LChild);
        lastOrder(root->RChild);
        printCurNodeData(root);
    }
}

//非递归
void preOrderStack(LPTREE root)
{

    if (root == NULL)
        return;
    LPTREE stack[10];
    int stackTop = -1;
    LPTREE pMove = root;
    while (stackTop != -1 || pMove)
    {
        while (pMove)
        {
            //把路径入栈
            cout << pMove->data;
            stack[++stackTop] = pMove;
            pMove = pMove->LChild;
        }
        if (stackTop != -1)
        {
            pMove = stack[stackTop];
            stackTop--;
            pMove = pMove->RChild;
        }
    }
}

//
void minOrderStack(LPTREE root)
{
    if(root == NULL) return; 
    LPTREE stack[10];
    int stackTop = -1;
    
    LPTREE pMove = root;
    while(stackTop != -1 || pMove )
    {
        //走到最左边 把走过的入栈
        while(pMove)
        {
            stack[++stackTop] = pMove;
            pMove = pMove->RChild;
        }

        if(stackTop != -1)
        {
            pMove = stack[stackTop--];
            cout<<pMove->data;
            pMove = pMove->RChild;
        }
    } 
    
}
int main()
{

    LPTREE A = creatNode('A');
    LPTREE B = creatNode('B');
    LPTREE C = creatNode('C');
    LPTREE D = creatNode('D');
    LPTREE E = creatNode('E');
    LPTREE F = creatNode('F');
    LPTREE G = creatNode('G');

    insertNode(A, B, C);
    insertNode(B, D, NULL);
    insertNode(D, NULL, G);
    insertNode(C, E, F);
    // preOrder(A);
    // cout << "next" << endl;
    // minOrder(A);
    // cout << "next" << endl;
    // lastOrder(A);

    preOrderStack(A);
    return 0;
}