/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2006-2013. All rights reserved.
 ******************************************************************************************/

#ifndef LIST_HPP
#define LIST_HPP

#include "ListNode.hpp"
#include <assert.h>
#include <iostream>

namespace dsa
{

typedef int Rank;  // 秩

// 列表模板类
template <typename T>
class List
{
protected:
    // 规模、头哨兵、尾哨兵, 哨兵对外不可见
    int _size;
    ListNodePosi(T) _header;
    ListNodePosi(T) _trailer;

public:

    List() { init(); }
    List(const List<T>& L) { copyNodes(L.first(), L._size); }
    List(const List<T>& L, int r, int n) { copyNodes(L[r], n); }
    List(ListNodePosi(T) p, int n) { copyNodes(p, n); }

    ~List()
    {
        clear();
        delete _header;
        delete _trailer;
    }

    /// 只读访问接口
    Rank size() const { return _size; }        // 规模
    bool empty() const { return _size <= 0; }  // 判空

    ListNodePosi(T) first() const { return _header->next; }  //首节点位置
    ListNodePosi(T) last() const { return _trailer->prev; }  //末节点位置

    // 重载下标操作符，以通过秩直接访问列表节点
    // O(n)，虽方便，效率低，需慎用
    T& operator[](Rank r) const
    {
        assert(0 <= r && r < _size);
        ListNodePosi(T) p = first();
        while (0 < r--)
            p = p->next;
        return p->data;
    }


    // 判断位置p是否对外合法, 将头、尾节点等同于nullptr
    bool valid(ListNodePosi(T) p) const { return p && (_trailer != p) && (_header != p); }

    // 判断列表是否已排序, 返回统计逆序相邻元素对的总数
    int disordered() const
    {
        int n = 0;
        ListNode<T>* p = first();
        for (int i = 0, iend = _size - 1; i < iend; p = p->next, i++)
            if (p->data > p->next->data)
                n++;
        return n;
    }

    // 无序列表查找
    ListNodePosi(T) find(T const& e) const { return find(e, _size, _trailer); }

    // 在无序列表内节点p（可能是trailer）的n个（真）前驱中，找到等于e的最后者
    ListNodePosi(T) find(T const& e, int n, ListNodePosi(T) p) const
    {
        assert(0 <= n && n <= _size);  // 对于p的最近的n个前驱，从右向左
        while (0 < n-- && p->prev)
            if (e == (p = p->prev)->data)
                return p;  // 逐个比对，直至命中或范围越界
        return nullptr;    // p越出左边界意味着区间内不含e，查找失败
    }

    // 在无序列表内节点p（可能是header）的n个（真）后继中，找到等于e的最前者
    ListNodePosi(T) find(T const& e, ListNodePosi(T) p, int n) const
    {
        assert(0 <= n && n <= _size);  // 对于p的最近的n个后继，从左向右
        int i = 0;
        while (i++ <= n && p->next)
            if (e == (p = p->next)->data)
                return p;  // 逐个比对，直至命中或范围越界
        return nullptr;    // p越出右边界意味着区间内不含e，查找失败
    }

    // 有序列表查找
    ListNodePosi(T) search(T const& e) const { return search(e, _size, _trailer); }

    // 在有序列表内节点p（可能是trailer）的n个（真）前驱中，找到不大于e的最后者
    // 失败时，返回区间左边界的前驱（可能是header） -- 调用者可通过valid()判断成功与否
    ListNodePosi(T) search(T const& e, int n, ListNodePosi(T) p) const
    {
        assert(0 <= n && n <= _size);
        std::cout << "searching for " << e << std::endl;
        while (0 <= n--) {  // 对于p的最近的n个前驱，从右向左逐个比较
            printf("  <%d>", p->prev->data);
            if (((p = p->prev)->data) <= e)
                break;  //直至命中、数值越界或范围越界
        }
        printf("\n");
        // assert: 至此位置p必符合输出语义约定——尽管此前最后一次关键码比较可能没有意义（等效于与-inf比较）
        return p;  // 返回查找终止的位置
    }

    // 从起始于位置p的n个元素中选出最大者
    ListNodePosi(T) selectMax(ListNodePosi(T) p, int n) const
    {
        ListNodePosi(T) max = p;
        for (ListNodePosi(T) cur = p; 1 < n; n--)
            if ((cur = cur->next)->data >= max->data)
                max = cur;
        return max;
    }

    // 整体最大者
    ListNodePosi(T) selectMax() const { return selectMax(_header->next, _size); }


    /// 可写访问接口
    ///
    ListNodePosi(T) insertAsFirst(T const& e)
    {
        _size++;
        return _header->insertAsNext(e);
    }

    ListNodePosi(T) insertAsLast(T const& e)
    {
        _size++;
        return _trailer->insertAsPrev(e);
    }

    ListNodePosi(T) insertAfter(ListNodePosi(T) p, T const& e)
    {
        _size++;
        return p->insertAsNext(e);
    }

    ListNodePosi(T) insertBefore(ListNodePosi(T) p, T const& e)
    {
        _size++;
        return p->insertAsPrev(e);
    }

    // 删除合法节点p，返回其数值
    T remove(ListNodePosi(T) p)
    {
        T e = p->data;
        p->prev->next = p->next;
        p->next->prev = p->prev;
        delete p;
        _size--;
        return e;
    }

    void merge(List<T>& L) { merge(first(), size, L, L.first(), L._size); }  //全列表归并

    // 列表区间排序
    void sort(ListNodePosi(T) p, int n)
    {
        switch (rand() % 3) {  // 随机选取排序算法。可根据具体问题的特点灵活选取或扩充
        case 1:
            insertionSort(p, n);
            break;  // 插入排序
        case 2:
            selectionSort(p, n);
            break;  // 选择排序
        default:
            mergeSort(p, n);
            break;  // 归并排序
        }
    }

    // 列表整体排序
    void sort() { sort(first(), _size); }

    // 剔除无序列表中的重复节点
    int deduplicate()
    {
        if (_size < 2)
            return 0;         // 平凡列表自然无重复
        int oldSize = _size;  // 记录原规模
        ListNodePosi(T) p = _header;
        Rank r = 0;                                // p从首节点开始
        while (_trailer != (p = p->next)) {         // 依次直到末节点
            ListNodePosi(T) q = find(p->data, r, p);  // 在p的r个（真）前驱中查找雷同者
            q ? remove(q) : r++;  // 若的确存在，则删除之；否则秩加一
        }  // assert: 循环过程中的任意时刻，p的所有前驱互不相同
        return oldSize - _size;  // 返回列表规模变化量，即被删除元素总数
    }

    // 成批剔除重复元素，效率更高
    int uniquify()
    {
        if (_size < 2)
            return 0;         // 平凡列表自然无重复
        int oldSize = _size;  // 记录原规模
        ListNodePosi(T) p = first();
        ListNodePosi(T) q;                   // p为各区段起点，q为其后继
        while (_trailer != (q = p->next))  // 反复考查紧邻的节点对(p, q)
            if (p->data != q->data)
                p = q;  // 若互异，则转向下一区段
            else
                remove(q);       // 否则（雷同），删除后者
        return oldSize - _size;  // 列表规模变化量，即被删除元素总数
    }

    // 前后倒置
    void reverse()
    {
        ListNodePosi(T) p = _header;
        ListNodePosi(T) q = _trailer;           // 头、尾节点
        for (int i = 1; i < _size; i += 2)  //（从首、末节点开始）由外而内，捉对地
            std::swap((p = p->next)->data, (q = q->prev)->data);  // 交换对称节点的数据项
    }


    // 遍历
    // 遍历，依次实施visit操作（函数指针，只读或局部性修改）
    void traverse(void (*visit)(T&))
    {
        for (ListNodePosi(T) p = _header->next; p != _trailer; p = p->next)
            visit(p->data);
    }

    // 遍历，依次实施visit操作（函数对象，可全局性修改）
    template <typename VST>
    void traverse(VST& visit)
    {
        for (ListNodePosi(T) p = _header->next; p != _trailer; p = p->next)
            visit(p->data);
    }


protected:
    // 列表初始化，在创建列表对象时统一调用
    void init()
    {
        _header = new ListNode<T>;   // 创建头哨兵节点
        _trailer = new ListNode<T>;  // 创建尾哨兵节点
        _header->next = _trailer;
        _trailer->prev = _header;
        _size = 0;  // 记录规模
    }

    // 清空列表
    int clear() //! TODO 验证正确性
    {
        int oldSize = _size;
        while (0 < _size)
            remove(_header->next);  // 反复删除首节点，直至列表变空
        return oldSize;
    }

    // 列表内部方法：复制列表中自位置p起的n项
    // p合法，且至少有n-1个真后继节点
    void copyNodes(ListNodePosi(T) p, int n)
    {
        init();        // 创建头、尾哨兵节点并做初始化
        while (n--) {  // 将起自p的n项依次作为末节点插入
            insertAsLast(p->data);
            p = p->next;
        }
    }

    // 列表的选择排序算法：对起始于位置p的n个元素排序
    void selectionSort(ListNodePosi(T) p, int n)
    {
        // valid(p) && rank(p) + n <= size
        printf("SelectionSort ...\n");
        ListNodePosi(T) head = p->prev;
        ListNodePosi(T) tail = p;
        for (int i = 0; i < n; i++)
            tail = tail->next;  // 待排序区间为(head, tail)
        while (1 < n) {         // 在至少还剩两个节点之前，在待排序区间内
            ListNodePosi(T) max = selectMax(head->next, n);  // 找出最大者（歧义时后者优先）
            insertBefore(tail, remove(max));  // 将其移至无序区间末尾（作为有序区间新的首元素）
            // swap(tail->prev->data, selectMax(head->next, n)->data);
            tail = tail->prev;
            n--;
        }
    }

    // 有序列表的归并：当前列表中自p起的n个元素，与列表L中自q起的m个元素归并
    void merge(ListNodePosi(T)& p, int n, List<T>& L, ListNodePosi(T) q, int m)
    {
        // assert:  this.valid(p) && rank(p) + n <= size && this.sorted(p, n)
        //          L.valid(q) && rank(q) + m <= L._size && L.sorted(q, m)
        // 注意：在归并排序之类的场合，有可能 this == L && rank(p) + n = rank(q)
        ListNodePosi(T) pp = p->prev;  //借助前驱（可能是header），以便返回前 ...
        while (0 < m)               //在q尚未移出区间之前
            if ((0 < n) && (p->data <= q->data))  //若p仍在区间内且v(p) <= v(q)，则
            {
                if (q == (p = p->next))
                    break;
                n--;
            }     // p归入合并的列表，并替换为其直接后继
            else  //若p已超出右界或v(q) < v(p)，则
            {
                insertBefore(p, L.remove((q = q->next)->prev));
                m--;
            }          //将q转移至p之前
        p = pp->next;  //确定归并后区间的（新）起点
    }

    // 列表的归并排序算法：对起始于位置p的n个元素排序
    // 注意：排序后，p依然指向归并后区间的（新）起点
    void mergeSort(ListNodePosi(T)& p, int n)
    {  // valid(p) && rank(p) + n <= size
        printf("\tMERGEsort [%d]\n", n);
        if (n < 2)
            return;      //若待排序范围已足够小，则直接返回；否则...
        int m = n >> 1;  //以中点为界
        ListNodePosi(T) q = p;
        for (int i = 0; i < m; i++)
            q = q->next;  //均分列表
        mergeSort(p, m);
        mergeSort(q, n - m);           //对前、后子列表分别排序
        merge(p, m, *this, q, n - m);  //归并
    }

    // 列表的插入排序算法：对起始于位置p的n个元素排序
    void insertionSort(ListNodePosi(T) p, int n)
    {
        assert(valid(p) && n <= _size);
        printf("InsertionSort ...\n");
        for (int r = 0; r < n; r++) {                     // 逐一为各节点
            insertAfter(search(p->data, r, p), p->data);  // 查找适当的位置并插入
            p = p->next;
            remove(p->prev);  // 转向下一节点
        }
    }


};  // List

}  // namespace dsa

#endif  // LIST_HPP


//// 前后倒置2
// void reverse_I() {
//   if(_size < 2) return; // 平凡情况
//   for(ListNodePosi(T) p = header; p; p = p->prev) //自前向后，依次
//      swap(p->prev, p->next); //交换各节点的前驱、后继指针
//   swap(header, trailer); //头、尾节点互换
//}

//// 前后倒置3
// void reverse_II() {
//   if(_size < 2) return; // 平凡情况
//   ListNodePosi(T) p; ListNodePosi(T) q;
//   for(p = header, q = p->next; p != trailer; p = q, q = p->next)
//      p->prev = q; // 自前向后，依次颠倒各节点的前驱指针
//   trailer->prev = nullptr; // 单独设置尾节点的前驱指针
//   for(p = header, q = p->prev; p != trailer; p = q, q = p->prev)
//      q->next = p; // 自前向后，依次颠倒各节点的后继指针
//   header->next = nullptr; // 单独设置头节点的后继指针
//   swap(header, trailer); // 头、尾节点互换
//}
