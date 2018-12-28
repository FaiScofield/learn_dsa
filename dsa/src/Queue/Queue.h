#ifndef QUEUE_H
#define QUEUE_H

#include "../List/List.h" // 以List为基类

// 队列模板类（继承List原有接口）
template <typename T>
class Queue: public List<T> {
public:
    // size()、empty()以及其它开放接口均可直接沿用
    void enqueue (T const& e) { this->insertAsLast(e); } // 入队：尾部插入
    T dequeue() { return this->remove(this->first()); }  // 出队：首部删除
    T& front() { return this->first()->data; }           // 队首
};

#endif
