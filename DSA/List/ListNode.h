#ifndef __LISTNODE__
#define __LISTNODE__
typedef int Rank;
#define ListNodePosi(T) ListNode<T>*
#include"iostream"
#include"string"
using namespace std;
template <typename T>
struct ListNode
{
    T data;
    ListNodePosi(T) pred;
    ListNodePosi(T) succ;

    ListNode(){}
    ListNode(T e, ListNodePosi(T) p = nullptr, ListNodePosi(T) s = nullptr) : data(e), pred(p), succ(s) {} 
    ListNodePosi(T) insertAsPred(T const& e);  //当前节点之前插入新节点
    ListNodePosi(T) insertAsSucc(T const& e);  //当前节点之后插入新节点
    
};

#endif