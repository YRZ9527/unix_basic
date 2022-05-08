#ifndef __VECTOR__
#define __VECTOR__

typedef int Rank;
const int default_capacity = 3;

template <typename T>
class Vector
{
protected:
    int _size;
    int _capacity;
    T *_elem;
    void copyFrom(T const *A, int lo, int hi);
    void expand();
    void shrink();
    void bubble(int lo, int hi);
    void bubbleSort(int lo, int hi);
    int max(int lo, int hi);
    void selectSort(int lo, int hi);
    void merge(int lo, int hi);
    int partition(int lo, int hi); //轴点构造方法
    void quickSort(int lo, int hi);
    void heapSort(int lo, int hi);
public:
    Vector(int c = default_capacity, int s = 0, T v = 0)
    //容量为C，规模为S，所有元素初始为v
    {
        _elem = new T[_capacity = c];
        for(_size = 0; _size < s; _elem[_size++] = v);
    }
    Vector(T const* A, int lo, int hi){copyFrom( A, lo, hi);}  //数组区间复制
    Vector(T const* A, int n){copyFrom(A,0,n);}                //数组整体复制
    Vector(Vector<T> const&V, int lo, int hi){copyFrom(V._elem, lo, hi);} //向量区间复制
    Vector(Vector<T> const&V){copyFrom(V._elem,V._size);}                 //向量整体复制
    ~Vector(){delete[] _elem;} //
// 只读接口
    int size() const {return _size;}
    bool empty() const {return !_size;} //
    int disOrder() const ;
    int find(T const& e) {return find(e,0,_size);} //无序向量 整体查找
    
    int find(T const& e, int lo, int hi)const; //无序向量区间查找
// 可写接口
    T& operator[](int r)const; //重载下标运算符 引用各个元素
    Vector<T>& operator=(Vector<T> const&); // 重载赋值运算符 方便克隆向量
    T remove(int r); //
    int remove(int lo, int hi); //delete data from lo to hi
    int insert(int r, T const& e); //insert data
    int insert(T const& e){return insert(_size, e);} //insert data on the lastOrder
    void sort(int lo, int hi); //
    void sort(){sort(0,_size);}
    void unsort(int lo, int hi);
    void unsort(){unsort(0,_size);} //整体置乱
    int debduplicate(); // 无序去重
    int uniquify();     // 有序去重
    
//遍历  
    void traverse(void(*)(T&));  //遍历 （使用函数指针，只读或者局部性修改）
    template <typename VST>
    void traverse(VST&); //遍历 （使用函数对象 全剧修改
};


#endif