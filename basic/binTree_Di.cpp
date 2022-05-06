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