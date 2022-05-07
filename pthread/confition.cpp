/*   ----------------------------------------------------------------
使用条件变量实现一个同步队列，队列作为生产者线程和消费者线程的共享资源
-------------------------------------------------------------------*/
#include "iostream"
#include "thread"
#include "mutex"
#include "list"
#include "functional"
#include "condition_variable"
using namespace std;

class SyncQueue
{
public:
    SyncQueue(int maxSize) : m_maxSize(maxSize){}
    void put(int& x);
    int take();
    bool isEmpty();
    bool isFull();
    int size();
private:
    list<int> m_queue; //存放队列数据
    mutex m_mutex;     //互斥锁
    condition_variable m_notEmpty;
    condition_variable m_notFull;
    int m_maxSize;
};
void SyncQueue::put(int& x)
{
    unique_lock<mutex> locker(m_mutex);
      m_notFull.wait(locker, [this]() {
        return m_queue.size() != m_maxSize;
    });
    m_queue.push_back(x);
    cout<<x<<":被生产"<<endl;
    m_notEmpty.notify_one();

}
int SyncQueue::take()
{
    unique_lock<mutex> locker(m_mutex);
    m_notEmpty.wait(locker, [this]() {
        return !m_queue.empty();
    });
    int x = m_queue.front();
    m_queue.pop_front();
    m_notFull.notify_one();
    cout<<x<<":被消费"<<endl;
    return x;
}
bool SyncQueue::isEmpty() 
{
    lock_guard<mutex> locker(m_mutex);
    return m_queue.empty();
}
bool SyncQueue::isFull() 
{
    lock_guard<mutex> locker(m_mutex);
    return m_queue.size() == m_maxSize;
}
int SyncQueue::size()
{
    lock_guard<mutex> locker(m_mutex);
    return m_queue.size();
}


int main()
{
     SyncQueue taskQ(50);
    auto produce = bind(&SyncQueue::put, &taskQ, placeholders::_1);
    auto consume = bind(&SyncQueue::take, &taskQ);
    thread t1[3];
    thread t2[3];
    for (int i = 0; i < 3; ++i)
    {
        t1[i] = thread(produce, i+100);
        t2[i] = thread(consume);
    }

    for (int i = 0; i < 3; ++i)
    {
        t1[i].join();
        t2[i].join();
    }
    return 0;
}