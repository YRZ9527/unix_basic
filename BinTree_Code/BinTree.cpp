#include "BiTree.h"
#include "queue"
#include "stack"
#include "vector"
#include <iostream>
using namespace std;
///递归创建二叉树，如果是#表示空节点
BiNode *BiTree::create(string &s, int &pos)
{
    ++pos;
    BiNode *t;
    if ((unsigned)pos >= s.size())
        return NULL;
    else
    {
        if (s[pos] == '#')
            t = NULL;
        else
        {
            t = new BiNode;
            t->data = s[pos];
            t->lchild = create(s, pos);
            t->rchild = create(s, pos);
        }
        return t;
    }
}

void BiTree::createBiTree(string s)
{
    int pos = -1;
    root = create(s, pos);
}

void BiTree::preOrder()
{
    pre_Order(root);
    cout << endl;
}

void BiTree::pre_Order(BiNode *t)
{
    if (t != NULL)
    {
        cout << t->data << " ";
        pre_Order(t->lchild);
        pre_Order(t->rchild);
    }
}

void BiTree::inOrder()
{
    in_Order(root);
    cout << endl;
}

void BiTree::in_Order(BiNode *t)
{
    if (t != NULL)
    {
        in_Order(t->lchild);
        cout << " " << t->data << " ";
        in_Order(t->lchild);
    }
}

void BiTree::postOrder()
{
    post_Order(root);
    cout << endl;
}

void BiTree::post_Order(BiNode *t)
{
    if (t)
    {
        post_Order(t->lchild);
        post_Order(t->rchild);
        cout << t->data << " ";
    }
}

void BiTree::postOrder1()
{
    BiNode *p, *r;
    r = NULL;
    p = root;
    stack<BiNode *> my_stack;
    while (p != NULL || !my_stack.empty())
    {
        if (p)
        {
            my_stack.push(p);
            p = p->lchild;
        }
        else
        {
            p = my_stack.top();
            if (p->rchild != NULL && p->rchild != r)
            {
                p = p->rchild;
                my_stack.push(p);
                p = p->lchild;
            }
            else
            {
                p = my_stack.top();
                my_stack.pop();
                cout << p->data << ' ';
                r = p;
                p = NULL;
            }
        }
    }
    cout << endl;
}

void BiTree::levelOrder()
{
    if (root == NULL)
        return;
    queue<BiNode *> q;
    q.push(root);
    while (!q.empty())
    {
        BiNode *t;
        t = q.front();
        q.pop();
        cout << t->data << ' ';
        if (t->lchild != NULL)
            q.push(t->lchild);
        if (t->rchild != NULL)
            q.push(t->rchild);
    }
    cout << endl;
}