#include "ListNode.h"
template <typename T>
class List
{
private:
    /* data */
    int _size;
    ListNodePosi(T) header;
    ListNodePosi(T) trailer; //头部 尾部哨兵
protected:
    void init();
    int clear();
    void copyNodes(ListNodePosi(T), int);
    void merge(ListNodePosi(T), int, List<T> &, ListNodePosi(T), int); //有序区间列表归并
    void mergeSort(ListNodePosi(T) &, int);                            //对从p开始的连续n个节点进行归并排序
    void selectSort(ListNodePosi(T) &, int);
    void insertionSort(ListNodePosi(T) &, int);

public:
    List()
    {
        init();
    }
    List(List<T> const &L);
    List(List<T> const &L, int r, int n);
    List(ListNodePosi(T) p, int n); //复刢列表中自位置p起癿n顷
    ~List();

    int size() const { return _size; }
    bool empty() const { return _size <= 0; }
    T &operator[](int r) const;
    ListNodePosi(T) first() const { return header->succ; } //首节点位置
    ListNodePosi(T) last() const { return trailer->pred; } // pred;} //末节点位置
    bool valid(ListNodePosi(T) p)
    {
        return p && (trailer != p) && (header != p);
    }
    int disordered() const;
    ListNodePosi(T) find(T const &e) const
    {
        return find(e, _size, trailer);
    }

    ListNodePosi(T) find(T const &e, int n, ListNodePosi(T) p) const;
    ListNodePosi(T) search(T const &e) const
    {
        return search(e, _size, trailer);
    }

    ListNodePosi(T) search(T const &e, int n, ListNodePosi(T) p) const;
    ListNodePosi(T) selectMax(ListNodePosi(T) p, int n);
    ListNodePosi(T) selectMax()
    {
        return selectMax(header->succ, _size);
    }
    ListNodePosi(T) insertAsFirst(T const &e);
    ListNodePosi(T) insertAsLast(T const &e);
    ListNodePosi(T) insertBefore(ListNodePosi(T) p, T const &e);
    ListNodePosi(T) insertAfter(ListNodePosi(T) p, T const &e);

    T remove(ListNodePosi(T) p);
    void merge(List<T> &L);
    void sort(ListNodePosi(T) p, int n);
    void sort() { sort(first(), _size); }
    int deduplicate();
    int uniquify();
    void reverse();
    // 遍历
    void traverse(void (*)(T &));
    template <typename VST>
    void traverse(VST &);
};

template <typename T>
void List<T>::init()
{
    header = new ListNode<T>;
    trailer = new ListNode<T>;
    header->succ = trailer;
    header->pred = nullptr;
    trailer->pred = header;
    trailer->succ = nullptr;
    _size = 0;
}

template <typename T>
T &List<T>::operator[](int r) const
{
    ListNodePosi(T) p = first();
    while (0 < r--)
        p = p->succ;
    return p->data;
}

template <typename T>
ListNodePosi(T) List<T>::find(T const &e, int n, ListNodePosi(T) p) const
{
    while (0 < n--)
        if (e == (p = p->pred)->data)
            return p;
    return nullptr;
}

template <typename T>
ListNodePosi(T) List<T>::insertAsFirst(T const &e)
{
    _size++;
    return header->insertAsSucc(e);
}
template <typename T>
ListNodePosi(T) List<T>::insertAsLast(T const &e)
{
    _size++;
    return trailer->insertAspred(e);
}
template <typename T>
ListNodePosi(T) List<T>::insertBefore(ListNodePosi(T) p, T const &e)
{
    _size++;
    return p->insertAsPred(e);
}

template <typename T>
ListNodePosi(T) List<T>::insertAfter(ListNodePosi(T) p, T const &e)
{
    _size++;
    return p->insertAsSucc(e);
}
template <typename T>
ListNodePosi(T) ListNode<T>::insertAsPred(T const &e)
{
    ListNodePosi(T) x = new ListNode(e,pred,this);
    pred->succ = x;
    pred = x;
    return x;

}


template <typename T>
ListNodePosi(T) ListNode<T>::insertAsSucc(T const &e)
{
    ListNodePosi(T) x = new ListNode(e,this,succ);
    succ->pred = x;
    succ = x;
    return x;
}

template <typename T>
void List<T>::copyNodes (ListNodePosi(T) p, int n)
{
    init();
    while(n--)
    {
        insertAsLast(p->data);
        p = p->succ;
    }
}

template <typename T>
List<T>::List(ListNodePosi(T) p , int n)
{
    copyNodes(p,n);
}
template <typename T>
List<T>::List(List<T> const& L)
{
    copyNodes(L.first(),L._size);
}
template <typename T>
List<T>::List(List<T> const &L, int r, int n)
{
    copyNodes(L[r],n);
}


template <typename T> 
T List<T>::remove(ListNodePosi(T) p)
{
    T e = p->data;
    p->pred->succ = p ->succ;
    p->succ->pred = p ->pred;
    delete p;
    _size--;
    return  e;
}

template <typename T>
List<T>::~List()
{
    clear();
    delete header;
    delete trailer;

}
template <typename T>
int List<T>::clear()
{
    int oldSize = _size;
    while(0 < _size)
    {
        remove(header->succ);
    }
    return oldSize;

}


int main()
{
    cout<<"hello world!"<<endl;
    return 0;
}