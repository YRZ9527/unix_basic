#include "iostream"
#include "vector.h"

using namespace std;
template <typename T>

void Vector<T>::copyFrom(T const *A, int lo, int hi)
{
    _elem = new T[_capacity = 2 * (hi - lo)];
    _size = 0; //分配空间、规模清零
    while (lo < hi)
    {
        _elem[_size++] = A[lo++];
    }
}
template <typename T>
//重载赋值操作符
Vector<T> &Vector<T>::operator=(Vector<T> const &V)
{
    if (_elem)
        delete[] _elem;
    copyFrom(V._elem, 0, V.size());
    return *this;
}

template <typename T>

void Vector<T>::expand()
{
    if (_size < _capacity)
        return; // not Full
    if (_capacity < default_capacity)
        _capacity = default_capacity; // 不低于最低容量
    T *oldElem = _elem;
    _elem = new T[_capacity << 1]; // 容量加倍
    for (int i = 0; i < _size; i++)
    {
        _elem[i] = oldElem[i];
    }
    delete[] oldElem;
}

template <typename T>
void Vector<T>::shrink()
{
    if (_capacity < default_capacity << 1)
        return;
    if (_size << 2 > _capacity)
        return;
    T *oldElem = _elem;
    _elem = new T[_capacity >>= 1];
    for (int i = 0; i < _size; i++)
        _elem[i] = oldElem[i];
    delete[] oldElem;
}

//重载[]运算符
template <typename T>
T &Vector<T>::operator[](int r) const
{
    return _elem[r];
}

template <typename T>
void Vector<T>::unsort(int lo, int hi)
{
    T *V = _elem + lo;
    for (int i = hi - lo; i > 0; i--)
    {
        swap(V[i - 1], V[rand() % i]);
    }
}
template <typename T>
static bool lt(T *a, T *b) { return lt(*a, *b); }
// less than
template <typename T>
static bool lt(T &a, T &b) { return a < b; }
// less than
template <typename T>
static bool eq(T *a, T *b) { return eq(*a, *b); }
// equal
template <typename T>
static bool eq(T &a, T &b) { return a == b; }
template <typename T>
int Vector<T>::find(T const &e, int lo, int hi) const
{
    while ((lo < hi--) && (e != _elem[hi]))
        ;
    return hi;
}
// insert data to the vector
template <typename T>
int Vector<T>::insert(int r, T const &e)
{
    //倒序 从前往后移动
    expand();
    for (int i = _size; i > r; i--)
    {
        _elem[i] = _elem[i - 1];
        _elem[r] = e;
        _size++;
        return r;
    }
}

//删除
template <typename T>
int Vector<T>::remove(int lo, int hi)
{
    if (lo == hi)
        return 0;
    while (hi < _size)
        _elem[lo++] = _elem[hi++];
    _size = lo;
    shrink();
    return hi - lo;
}

template <typename T>
T Vector<T>::remove(int r)
{
    T e = _elem[r];
    remove(r, r + 1);
    return e;
}
// 去重
template <typename T>
int Vector<T>::debduplicate()
{
    int oldSize = _size;
    int i = 0;
    while (i < _size)
    {
        (find(_elem[i], 0, i) < 0) ? i++ : remove(i);
        return oldSize - _size;
    }
}

//遍历
template <typename T>
void Vector<T>::traverse(void (*visit)(T &))
{
    for (int i = 0; i < _size; i++)
    {
        visit(_elem[i]);
    }
}
template <typename T>
template <typename VST>
void Vector<T>::traverse(VST &visit)
{
    for (int i = 0; i < _size; i++)
        visit(_elem[i]);
}

template <typename T>
//
struct Increase
{
    virtual void operator()(T &e) { e++; }
};
//
template <typename T>
void increase(Vector<T> &V)
{
    V.traverse(Increase<T>());
}

template <typename T>
int Vector<T>::disOrder() const
{
    int n = 0;
    for (int i = 0; i < _size; i++)
        if (_elem[i - 1] > _elem[i])
            n++;
    return n;
}
template <typename T>
int Vector<T>::uniquify()
{
    int oldSize = _size;
    int i = 1;
    while (i < _size)
    {
        _elem[i - 1] = _elem[i] ? remove(i) : i++;
        return oldSize - _size;
    }
}

template <typename T>
static int binSearch(T *A, T const &e, int lo, int hi)
{
    while (lo < hi)
    {
        int mi = (lo + hi) >> 1;
        if (e < A[mi])
            hi = mi;
        else if (e > A[mi])
            lo = mi + 1;
        else
            return mi;
    }
    return -1;
}
template <typename T>
void Vector<T>::bubbleSort(int lo, int hi)
{
    while (!bubble(lo, hi--))
        ;
}
template <typename T>
bool Vector<T>::bubble(int lo, int hi)
{
    bool sorted = true;
    while (++lo < hi)
    {
        if (_elem[lo - 1] > _elem[lo])
            sorted = false;
        swap(_elem[lo - 1], _elem[lo]);
    }
    return sorted;
}
template <typename T>
void Vector<T>::mergeSort(int lo, int hi)
{
    if (hi - lo < 2)
        return;
    //单元素区间自然有序 否则
    int mi = (lo + hi) >> 1;
    //对前半段排序 后续归并
    mergeSort(lo, mi);
    mergeSort(mi, hi);
    merge(lo, mi, hi);
}
template <typename T>
void Vector<T>::merge(int lo, int mi, int hi)
{
    T *A = _elem + lo; //合并之后的向量A[0,hi-lo] = _elem[lo,hi]
    int lb = mi - lo;
    T *B = new T[lb]; //前一半为B[0,lb] = _elem[lo,mi]
    for (int i = 0; i < lb; B[i] = A[i++])
        ;
    int lc = hi - mi;
    T *C = _elem + mi; // c[0,lc] =_elem[mi,hi]
    for (int i = 0, j = 0, k = 0; (j < lb) || (k < lc); j++)
    {
        if ((j < lb) && (!(k < lc) || (B[j] <= C[k])))
            A[i++] = B[j++];
        if ((k < lc) && (!(j < lb) || (C[k] < B[j])))
            A[i++] = C[k++];
    }
    delete [] B;
}
int main()
{
    cout << "hello" << endl;
    return 0;
}