/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2006-2013. All rights reserved.
 ******************************************************************************************/

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <algorithm>
#include "../Utility.h"
//#include "../fibonacci/fibonacci.h"  // 引入Fib数列类
//#include "../PQ/PQ_ComplHeap.h"

namespace dsa {

#define DEFAULT_CAPACITY 5  // 默认的初始容量（实际应用中可设置为更大）

typedef int Rank;           // 秩

// 向量模板类
template <typename T>
class Vector
{
protected:
    Rank _size;     // 规模
    int _capacity;  // 容量
    T* _elem;       // 数据区

public:
    ///* 构造&析构 *///
    ~Vector() { delete[] _elem; }

    Vector() : _size(0), _capacity(3) { _elem = new T[_capacity]; }

    Vector(Rank n) : _capacity(n)
    {
        _elem = new T[_capacity];
        _size = 0;
    }

    Vector(Rank n, const T& v) : _capacity(n)
    {
        _elem = new T[_capacity];
        for (_size = 0; _size < n; _elem[_size++] = v)
            DO_NOTHING;
    }

    // 数组整体复制
    Vector(const T* A, Rank n) { copyFrom(A, 0, n); }
    // 数组区间复制
    Vector(const T* A, Rank lo, Rank hi) { copyFrom(A, lo, hi); }
    // 向量整体复制 
	// TODO: to check
    Vector(const Vector<T>& V) { copyFrom(V._elem, 0, V._size); }
    // 向量区间复制
    Vector(const Vector<T>& V, Rank lo, Rank hi) { copyFrom(V._elem, lo, hi); }
    // 重载赋值操作符，以便直接克隆向量
    Vector<T>& operator=(const Vector<T>& V)
    {
        if (_elem)
            delete[] _elem;              // 释放原有内容
        copyFrom(V._elem, 0, V.size());
        return *this;                    // 返回当前对象的引用，以便链式赋值
    }


    ///* 只读访问接口 const *///
    Rank size() const { return _size; }
    Rank capacity() const { return _capacity; }
    bool empty() const { return (_size == 0); }
    Rank find(const T& e) const { return find(e, 0, _size); }  // 无序查找
    Rank search(const T& e) const { return (0 >= _size) ? -1 : search(e, 0, _size); }  // 有序查找

    // 重载下标操作符，可以类似于数组形式引用各元素
    T& operator[](Rank r) const
    {
        assert(0 <= r && r < _size);
        return _elem[r];
    }

    // 判断向量是否已排序, 返回向量中逆序相邻元素对的总数
    int disordered() const
    {
        int n = 0;
        for (int i = 1; i < _size; i++)
            if (_elem[i - 1] > _elem[i])
                n++;
        return n; // 向量有序当且仅当n = 0
    }

    // 无序向量的顺序查找: 返回最后一个元素e的位置; 失败时，返回lo-1
    Rank find(const T& e, Rank lo, Rank hi) const
    {
        assert(0 <= lo && lo < hi && hi <= _size);
        while ((lo < hi--) && (e != _elem[hi])) // 从后向前，顺序查找
            DO_NOTHING;
        return hi;  // 若hi < lo，则意味着失败；否则hi即命中元素的秩
    }

    // 有序向量区间查找: 返回不大于e的最后一个节点的秩
    Rank search(const T& e, Rank lo, Rank hi, int type = SEARCH_BIN) const
    {
//        if (type == FIB_SEARCH)
//            return fibSearch(_elem, e, lo, hi);
//        else
            return binSearch(_elem, e, lo, hi);
    }


    ///* 可写访问接口 *///
    // 置乱
    void unsort() { unsort(0, _size); }
    void unsort(Rank lo, Rank hi)
    {
        T* V = _elem + lo;
        for (Rank i = hi - lo; i > 0; i--)
            std::swap(V[i - 1], V[rand() % i]);  // 随机交换
    }

    // 插入
    Rank insert(const T& e) { return insert(_size, e); }
    Rank insert(Rank r, const T& e)
    {
        assert(0 <= r && r <= _size);
        expand();  // 若有必要，扩容
        for (int i = _size; i > r; i--)
            _elem[i] = _elem[i - 1];
        _elem[r] = e;
        _size++;

        return r;
    }
    void push_back(const T& e) { insert(_size, e); }

    // 删除
    T remove(Rank r)
    {
        assert(0 <= r && r < _size);
        T e = _elem[r];
        remove(r, r + 1);
        return e;
    }
    int remove(Rank lo, Rank hi)
    {
        if (lo == hi)
            return 0;       // 出于效率考虑，单独处理退化情况，比如remove(0, 0)
        while (hi < _size)  // [hi, _size)顺次前移hi - lo个单元
            _elem[lo++] = _elem[hi++];
        _size = lo;      // 更新规模，直接丢弃尾部[lo, _size = hi)区间
        shrink();        // 若有必要，则缩容
        return hi - lo;  // 返回被删除元素的数目
    }
    void pop_back() { remove(_size - 1); }
    void clear() { remove(0, _size); }

    // 无序向量重复元素删除（高效版）
    int deduplicate()
    {
        int oldSize = _size;            // 记录原规模
        Rank i = 1;                     // 从_elem[1]开始
        while (i < _size)               // 自前向后逐一考查各元素_elem[i]
            find(_elem[i], 0, i) < 0 ?  // 在其前缀中寻找与之雷同者（至多一个）
                i++ :
                remove(i);       // 若无雷同则继续考查其后继，否则删除雷同者
        return oldSize - _size;  // 向量规模变化量，即被删除元素总数
    }

    // 有序向量重复元素删除（高效版） O(n)
    int uniquify()
    {
        Rank i = 0, j = 0;              // 各对互异“相邻”元素的秩
        while (++j < _size)             // 逐一扫描，直至末元素
            if (_elem[i] != _elem[j])   // 跳过雷同者
                _elem[++i] = _elem[j];  // 发现不同元素时，向前移至紧邻于前者右侧
        _size = ++i;
        shrink();      // 直接截除尾部多余元素
        return j - i;  // 向量规模变化量，即被删除元素总数
    }

    // 排序
    void sort(int type = SORT_QUICK) { sort(0, _size, type); }
    void sort(Rank lo, Rank hi, int type = SORT_QUICK)
    {
        switch (type) {
        case SORT_BUBBLE:
            bubbleSort(lo, hi);
            break;
        case SORT_SELECT:
            selectionSort(lo, hi);
            break;
        case SORT_MERGE:
            mergeSort(lo, hi);
            break;
//        case SORT_HEAP:
//            heapSort(lo, hi);
//            break;
        case SORT_QUICK:
        default:
            quickSort(lo, hi);
            break;
        }
    }

    // 遍历
    void traverse(void(*) (T&)) // 借助函数指针机制遍历向量，只读或局部性修改
    {
        for (int i = 0; i < _size; ++i)
            visit(_elem[i]);
    }
    template <typename VST>
    void traverse(VST&) // 借助函数对象机制遍历向量, 可全局性修改
    {
        for (int i = 0; i < _size; ++i)
            visit(_elem[i]);
    }

    // 在[lo, hi]内找出最大元素
    Rank max(Rank lo, Rank hi)
    {
        Rank mx = hi;
        while (lo < hi--)               // 逆向扫描
            if (_elem[hi] > _elem[mx])  // 且严格比较
                mx = hi;  // 故能在max有多个时保证后者优先，进而保证selectionSort稳定
        return mx;
    }

protected:

    // 以数组区间A[lo, hi)为蓝本复制向量
    void copyFrom(const T* A, Rank lo, Rank hi)
    {
        _elem = new T[_capacity = 2 * (hi - lo)]; // 申请两倍空间
        _size = 0;
        while (lo < hi)
            _elem[_size++] = A[lo++];
    }

    // 向量空间不足时扩容
    // 递增策略，累计耗时O(n^2)，分摊耗时O(n)，装填因子~=100%
    // 倍增策略，累计耗时O(n)，分摊耗时O(1)，装填因子>50%
    void expand()
    {
        if (_size < _capacity)
            return;  // 尚未满员时，不必扩容
        if (_capacity < DEFAULT_CAPACITY)
            _capacity = DEFAULT_CAPACITY;  // 不低于最小容量

        T* oldElem = _elem;
        _elem = new T[_capacity <<= 1];  // 容量加倍
        for (int i = 0; i < _size; i++)
            _elem[i] = oldElem[i];  // 复制原向量内容（T为基本类型，或已重载赋值操作符'='）
        delete[] oldElem;  // 释放原空间
    }

    // 装填因子过小时压缩向量所占空间
    void shrink()
    {
        if (_capacity < DEFAULT_CAPACITY << 1)
            return;  // 不致收缩到DEFAULT_CAPACITY以下
        if (_size << 2 > _capacity)
            return;  // 以25%为界

        T* oldElem = _elem;
        _elem = new T[_capacity >>= 1];  // 容量减半
        for (int i = 0; i < _size; i++)
            _elem[i] = oldElem[i];  // 复制原向量内容
        delete[] oldElem;           // 释放原空间
    }


    // Fibonacci查找算法（版本B）：在有序向量的区间[lo, hi)内查找元素e
    // 有A、B两种版本，B虽华丽，A更实用（但返回值有待与接口统一）
    // 有多个命中元素时，总能保证返回最秩最大者；查找失败时，能够返回失败的位置
//    Rank fibSearch(T* A, const T& e, Rank lo, Rank hi) const
//    {
//        assert(0 <= lo && lo < hi && hi <= _size);
//        printf("FIB search (B)\n");
//        Fib cFib(hi - lo);  // 用O(log_phi(n=hi-lo)时间创建Fib数列
//        while (lo < hi) {   // 每步迭代仅仅做一次比较判断，有两个分支
//            for (int i = 0; i < lo; i++)
//                printf("     ");
//            if (lo >= 0)
//                for (int i = lo; i < hi; i++)
//                    printf("....^");
//            else
//                printf("<<<<|");
//            printf("\n");
//            while (hi - lo < cFib.get())
//                cFib.prev();  // 通过向前顺序查找（分摊O(1)）——至多迭代几次？
//            Rank mi = lo + cFib.get() - 1;  // 确定形如Fib(k) - 1的轴点
//            (e < A[mi]) ? hi = mi : lo = mi + 1;  // 比较后确定深入前半段[lo, mi)或后半段(mi, hi)
//        }                                         // 成功查找不能提前终止
//        for (int i = 0; i < lo - 1; i++)
//            printf("     ");
//        if (lo > 0)
//            printf("....|\n");
//        else
//            printf("<<<<|\n");

//        return --lo;  // 循环结束时，lo为大于e的元素的最小秩，故lo-1即不大于e的元素的最大秩
//    }

    // 二分查找算法（版本C）：在有序向量的区间[lo, hi)内查找元素e
    // 有多个命中元素时，总能保证返回秩最大者；查找失败时，能够返回失败的位置
    Rank binSearch(T* A, T const& e, Rank lo, Rank hi) const
    {
        assert(0 <= lo && lo < hi && hi <= _size);
        printf("BIN search (C)\n");
        while (lo < hi) {  // 每步迭代仅需做一次比较判断，有两个分支
            for (int i = 0; i < lo; i++)
                printf("     ");
            if (lo >= 0)
                for (int i = lo; i < hi; i++)
                    printf("....^");
            printf("\n");
            Rank mi = (lo + hi) >> 1;             // 以中点为轴点
            (e < A[mi]) ? hi = mi : lo = mi + 1;  // 经比较后确定深入[lo, mi)或[mi+1, hi)
        }                                         // 成功查找后不提前终止,以查找重复元素中最大秩者
        for (int i = 0; i < lo - 1; i++)
            printf("     ");
        if (lo > 0)
            printf("....|\n");
        else
            printf("<<<<|\n");

        return --lo;  // 循环结束时，lo为大于e的元素的最小秩，故lo-1即不大于e的元素的最大秩
    }


    // 冒泡排序中的单次扫描交换, 将最大元素移至区间末尾. 最好O(n),最坏O(n^2)
    Rank bubble(Rank lo, Rank hi)
    {
        Rank last = lo;                       // 最后一次扫描交换的位置
        while (++lo < hi)                     // 自左向右，逐一检查各对相邻元素
            if (_elem[lo - 1] > _elem[lo]) {  // 若逆序，则
                last = lo;                    // 意味着尚未整体有序，并需要
                std::swap(_elem[lo - 1], _elem[lo]);  // 通过交换使局部有序
            }
        return last;  // 返回右侧的逆序对位置
    }

    // 冒泡排序算法. 最好O(n),最坏O(n^2)
    void bubbleSort(Rank lo, Rank hi)
    {
        while (bubble(lo, hi--))
            DO_NOTHING;
    }

    // 选择排序算法. O(n^2)
    void selectionSort(Rank lo, Rank hi)
    {
//        printf("\tSelectionSort [%d, %d)\n", lo, hi);
        while (lo < --hi)  // 将[hi]与[lo, hi]中的最大者交换
            std::swap(_elem[max(lo, hi)], _elem[hi]);
    }

    // 有序向量的归并算法, 各自有序的子向量[lo, mi)和[mi, hi)
    // 归并后得到完整的有序向量[lo, hi)
    void merge(Rank lo, Rank mi, Rank hi)
    {
        T* A = _elem + lo;  // 合并后的向量A[0, hi-lo) = _elem[lo, hi)
        int lb = mi - lo;
        T* B = new T[lb];  // 前子向量B[0, lb) = _elem[lo, mi)
        for (Rank i = 0; i < lb; B[i] = A[i++])
            ;  // 复制前子向量
        int lc = hi - mi;
        T* C = _elem + mi;  // 后子向量C[0, lc) = _elem[mi, hi)
        for (Rank i = 0, j = 0, k = 0; (j < lb) || (k < lc);) {
            // B[j]和C[k]中的小者续至A末尾
            if ((j < lb) && (!(k < lc) || (B[j] <= C[k])))
                A[i++] = B[j++];
            if ((k < lc) && (!(j < lb) || (C[k] < B[j])))
                A[i++] = C[k++];
        }
        delete[] B;  // 释放临时空间B
    }

    // 归并排序算法. O(n*log(n))
    //! TODO 有内存泄露
    void mergeSort(Rank lo, Rank hi)
    {
        assert(0 <= lo && lo < hi && hi <= _size);
        printf("\tMergeSort [%d, %d)\n", lo, hi);
        if (hi - lo < 2)
            return;              // 单元素区间自然有序，否则...
        int mi = (lo + hi) / 2;  // 以中点为界
        mergeSort(lo, mi);       // 分别排序
        mergeSort(mi, hi);
        merge(lo, mi, hi);  // 归并
    }

    // 轴点构造算法(版本C)：通过调整元素位置构造区间[lo, hi]的轴点，并返回其秩. O(n)
    Rank partition(Rank lo, Rank hi)
    {
        //        std::swap(_elem[lo], _elem[lo + rand()%(hi-lo+1)]); // 任选一个元素与首  元素交换
        T pivot = _elem[lo];  // 以首元素为候选轴点——经以上交换，等效于随机选取
        int mi = lo;
        // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        //   [ ---- < [lo] ----- ] [ ----- [lo] <= --- ] [ ----- unknown ----- ]
        // X x . . . . . . . . . x . . . . . . . . . . . x . . . . . . . . . . x
        // |                     |                       |                     |
        // lo (pivot)            mi                      k                     hi
        // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        for (int k = lo + 1; k <= hi; k++)  // 自左向右扫描
            if (_elem[k] < pivot)           // 若当前元素_elem[k]小于pivot，则
                std::swap(_elem[++mi], _elem[k]);  // 将_elem[k]交换至原mi之后，使L子序列向右扩展
        // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        //   [ --------- < [lo] ---------- ] [ ----------- [lo] <= ----------- ]
        // X x . . . . . . . . . . . . . . x . . . . . . . . . . . . . . . . . x
        // |                               |                                   |
        // lo                              mi                                  hi
        // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        std::swap(_elem[lo], _elem[mi]);  // 候选轴点归位

        return mi;  // 返回轴点的秩
    }

    // 快速排序算法. O(n*log(n))
    void quickSort(Rank lo, Rank hi)
    {
        if (hi - lo < 2)
            return;  // 单元素区间自然有序，否则...
        printf("\tQuickSort [%d, %d)\n", lo, hi);
        Rank mi = partition(lo, hi - 1);  // 在[lo, hi-1]内构造轴点
        quickSort(lo, mi);                // 对前缀递归排序
        quickSort(mi + 1, hi);            // 对后缀递归排序
    }

    // 堆排序. O(n*log(n))
    //    void heapSort(Rank lo, Rank hi) {
    //        assert(0 <= lo  && lo < hi && hi <= size);
    //        printf("\tHEAPsort [%3d, %3d)\n", lo, hi);
    //        PQ_ComplHeap<T> H(_elem+lo, hi-lo); // 将待排序区间建成一个完全二叉堆，O(n)
    //        while (!H.empty()) {                // 反复地摘除最大元并归入已排序的后缀，直至堆空
    //            _elem[--hi] = H.delMax();       // 等效于堆顶与末元素对换后下滤
    ////            for (int i = lo; i < hi; i++)
    ////                print(H[i]);
    ////            print(_elem[hi]); printf("\n");
    //        }
    //    }
};  // Vector


// 随机置乱向量，使各元素等概率出现于各位置
template <typename T>
void permute(Vector<T>& V)
{
    for (int i = V.size(); i > 0; i--)       // 自后向前
        std::swap(V[i - 1], V[rand() % i]);  // V[i-1]与V[0,i)中某一随机元素交换
}


/*
// vector_partition
// 有A、A1、B、B1、C共5个版本
// 轴点构造算法a1：通过调整元素位置构造区间[lo, hi]的轴点，并返回其秩
// 版本A：基本形式
template <typename T>
Rank Vector<T>::partition(Rank lo, Rank hi) {
   std::swap (_elem[lo], _elem[lo + rand() % (hi - lo + 1) ]); // 任选一个元素与首元素交换
   T pivot = _elem[lo]; // 以首元素为候选轴点——经以上交换，等效于随机选取
   while (lo < hi) { // 从向量的两端交替地向中间扫描
      while ((lo < hi) && (pivot <= _elem[hi])) // 在不小于pivot的前提下
         hi--; // 向左拓展右端子向量
      _elem[lo] = _elem[hi]; // 小于pivot者归入左侧子序列
      while ((lo < hi) && (_elem[lo] <= pivot)) // 在不大于pivot的前提下
         lo++; // 向右拓展左端子向量
      _elem[hi] = _elem[lo]; // 大于pivot者归入右侧子序列
   } // assert: lo == hi
   _elem[lo] = pivot; // 将备份的轴点记录置于前、后子向量之间
   return lo; // 返回轴点的秩
}
// 轴点构造算法a1：通过调整元素位置构造区间[lo, hi]的轴点，并返回其秩
// 版本A1：与版本A等价，可直接转至与版本B等价的版本B1
template <typename T>
Rank Vector<T>::partition(Rank lo, Rank hi) {
   std::swap (_elem[lo], _elem[lo + rand() % (hi-lo+1) ]); // 任选一个元素与首元素交换
   T pivot = _elem[lo]; // 以首元素为候选轴点——经以上交换，等效于随机选取
   while (lo < hi) { // 从向量的两端交替地向中间扫描
      while ((lo < hi) && (pivot <= _elem[hi])) // 在不小于pivot的前提下
         hi--; // 向左拓展右端子向量
      if (lo < hi) _elem[lo++] = _elem[hi]; // 小于pivot者归入左侧子向量
      while ((lo < hi) && (_elem[lo] <= pivot)) // 在保证不大于pivot的前提下
         lo++; // 向右拓展左端子向量
      if (lo < hi) _elem[hi--] = _elem[lo]; // 大于pivot者归入右侧子向量
   } // assert: lo == hi
   _elem[lo] = pivot; // 将备份的轴点记录置于前、后子向量之间
   return lo; // 返回轴点的秩
}
// 轴点构造算法b：通过调整元素位置构造区间[lo, hi]的轴点，并返回其秩
// 版本B：可优化处理多个关键码雷同的退化情况
template <typename T>
Rank Vector<T>::partition(Rank lo, Rank hi) {
   std::swap (_elem[lo], _elem[lo + rand() % (hi - lo + 1) ]); // 任选一个元素与首元素交换
   T pivot = _elem[lo]; // 以首元素为候选轴点——经以上交换，等效于随机选取
   while (lo < hi) { // 从向量的两端交替地向中间扫描
      while (lo < hi)
         if (pivot < _elem[hi]) // 在大于pivot的前提下
            hi--; // 向左拓展右端子向量
         else // 直至遇到不大于pivot者
            { _elem[lo++] = _elem[hi]; break; } // 将其归入左端子向量
      while (lo < hi)
         if (_elem[lo] < pivot) // 在小于pivot的前提下
            lo++; // 向右拓展左端子向量
         else // 直至遇到不小于pivot者
            { _elem[hi--] = _elem[lo]; break; } // 将其归入右端子向量
   } // assert: lo == hi
   _elem[lo] = pivot; // 将备份的轴点记录置于前、后子向量之间
   return lo; // 返回轴点的秩
}
// 轴点构造算法b1：通过调整元素位置构造区间[lo, hi]的轴点，并返回其秩
 // 版本B1：版本B的等价形式，可直接转至与版本A等价的版本A1
template <typename T>
Rank Vector<T>::partition(Rank lo, Rank hi) {
   std::swap (_elem[lo], _elem[lo + rand() % (hi-lo+1) ]); // 任选一个元素与首元素交换
   T pivot = _elem[lo]; // 以首元素为候选轴点——经以上交换，等效于随机选取
   while (lo < hi) { // 从向量的两端交替地向中间扫描
      while ((lo < hi) && (pivot < _elem[hi])) // 在大于pivot的前提下
         hi--; // 向左拓展右端子向量
      if (lo < hi) _elem[lo++] = _elem[hi]; // 不大于pivot者归入左端子向量
      while ((lo < hi) && (_elem[lo] < pivot)) // 在小于pivot的前提下
         lo++; // 向右拓展左端子向量
      if (lo < hi) _elem[hi--] = _elem[lo]; // 不小于pivot者归入右端子向量
   } // assert: lo == hi
   _elem[lo] = pivot; // 将备份的轴点记录置于前、后子向量之间
   return lo; // 返回轴点的秩
}
*/

/*
// vector_search_binary
// 二分查找算法（版本A）：在有序向量的区间[lo, hi)内查找元素e，0 <= lo <= hi <= _size
// 有多个命中元素时，不能保证返回秩最大者；查找失败时，简单地返回-1，而不能指示失败的位置
// O(logn)
// template <typename T>
// static Rank binSearch_A(T* A, const T & e, Rank lo, Rank hi) {
//    printf("BIN search (A)\n");
//    while (lo < hi) {               // 每步迭代可能要做两次比较判断，有三个分支
//        for (int i = 0; i < lo; i++)
//            printf("     ");
//        if (lo >= 0)
//            for (int i = lo; i < hi; i++)
//                printf("....^");
//        printf("\n");
//        Rank mi = (lo + hi) >> 1;   // 以中点为轴点
//        if (e < A[mi]) hi = mi;     // 深入前半段[lo, mi)继续查找
//        else if (A[mi] < e)
//            lo = mi + 1;            // 深入后半段(mi, hi)继续查找
//        else
//            return mi;              // 在mi处命中
//        if (lo >= hi) {
//            for (int i = 0; i < mi; i++)
//                printf("     ");
//            if (mi >= 0)
//                printf("....|\n");
//            else
//                printf("<<<<|\n");
//        }
//    }           // 成功查找可以提前终止
//    return -1;  // 查找失败
//}

// 二分查找算法（版本B）：在有序向量的区间[lo, hi)内查找元素e，0 <= lo <= hi <= _size
// 有多个命中元素时，不能保证返回秩最大者；查找失败时，简单地返回-1，而不能指示失败的位置
// template <typename T>
// static Rank binSearch_B(T* A, T const& e, Rank lo, Rank hi) {
//    printf("BIN search (B)\n");
//    while (1 < hi - lo) { // 每步迭代仅需做一次比较判断，有两个分支；成功查找不能提前终止
//        for (int i = 0; i < lo; i++)
//            printf("     ");
//        if (lo >= 0)
//            for (int i = lo; i < hi; i++)
//                printf("....^");
//        printf("\n");
//        Rank mi = (lo + hi) >> 1;       // 以中点为轴点
//        e < A[mi] ? hi = mi : lo = mi;  // 经比较后确定深入[lo, mi)或[mi, hi)
//   } // 出口时hi = lo + 1，查找区间仅含一个元素A[lo]
//        for (int i = 0; i < lo; i++)
//            printf("     ");
//        if (lo >= 0)
//            printf("....|\n");
//        else
//            printf("<<<<|\n");
//    return (e == A[lo]) ? lo : -1 ;   // 查找成功时返回对应的秩；否则统一返回-1
//}


// 将e作为秩为r元素插入,  0 <= r <= size
// 有序向量插入：V.insert(1+V.search(e), e)
// template <typename T>
// Rank Vector<T>::insert(Rank r, const T& e) {
//    assert(0 <= r && r <= _size);
//    expand(); // 若有必要，扩容
//    for (int i = _size; i > r; i--)
//        _elem[i] = _elem[i-1];  // 自后向前，后继元素顺次后移一个单元
//    _elem[r] = e; _size++;      // 置入新元素并更新容量
//    return r;                   // 返回秩r
//}


// vector_search_binary_c
// 黄金查找, 有A、B、C三种版本，C最完善
// Fibonacci查找算法（版本A）：在有序向量的区间[lo, hi)内查找元素e，0 <= lo <= hi <= _size
// 有多个命中元素时，不能保证返回秩最大者；失败时，简单地返回-1，而不能指示失败的位置
// template <typename T>
// static Rank fibSearch_A(T* A, T const& e, Rank lo, Rank hi) {
//    printf("FIB search (A)\n");
//    Fib cFib(hi - lo);                               // 用O(log_phi(n=hi-lo)时间创建Fib数列
//    while (lo < hi) {                               // 每步迭代可能要做两次比较判断，有三个分支
//        for (int i = 0; i < lo; i++) printf("     ");
//        if (lo >= 0)
//            for (int i = lo; i < hi; i++) printf("....^");
//        else printf("<<<<|");
//        printf("\n");
//        while (hi - lo < cFib.get()) cFib.prev();     //
//        通过向前顺序查找（分摊O(1)）——至多迭代几次？ Rank mi = lo + cFib.get() - 1; //
//        确定形如Fib(k) - 1的轴点 if (e < A[mi]) hi = mi;                     // 深入前半段[lo,
//        mi)继续查找 else if (A[mi] < e) lo = mi + 1;            // 深入后半段(mi, hi)继续查找 else
//        return mi;                             // 在mi处命中 if (lo >= hi) {
//            for (int i = 0; i < mi; i++) printf("     ");
//            if (mi >= 0) printf("....|\n");
//            else printf("<<<<|\n");
//        }
//    }           // 成功查找可以提前终止
//    return -1;  // 查找失败
//}
*/

/*
// vector_bubble
// 一趟扫描交换 O(n^2)
template <typename T>
bool Vector<T>::bubble(Rank lo, Rank hi)
{
   bool sorted = true;                  // 整体有序标志
   while (++lo < hi)                    // 自左向右，逐一检查各对相邻元素
      if (_elem[lo-1] > _elem[lo]) {    // 若逆序，则
         sorted = false;                // 意味着尚未整体有序，并需要
         std::swap(_elem[lo-1], _elem[lo]);  // 通过交换使局部有序
      }
   return sorted;                       // 返回有序标志
}
*/

/*
// 有序向量重复元素剔除算法（低效版） O(n^2)
template <typename T>
int Vector<T>::uniquify() {
   int oldSize = _size; int i = 1; // 当前比对元素的秩，起始于首元素
   while (i < _size) // 从前向后，逐一比对各对相邻元素
      _elem[i-1] == _elem[i] ? remove(i) : i++; // 若雷同，则删除后者；否则，转至后一元素
   return oldSize - _size; // 向量规模变化量，即被删除元素总数
}

// 删除无序向量中重复元素（错误版）
template <typename T>
int Vector<T>::deduplicate() {
   int oldSize = _size; // 记录原规模
   for (Rank i = 1; i < _size; i++) { // 逐一考查_elem[i]
      Rank j = find(_elem[i], 0, i); // 在_elem[i]的前驱中寻找与之雷同者（至多一个）
      if (0 <= j) remove (j); // 若存在，则删除之（但在此种情况，下一迭代不必做i++）
   }
   return oldSize - _size; // 向量规模变化量，即被删除元素总数
}

// 删除无序向量中重复元素（繁琐版）
template <typename T>
int Vector<T>::deduplicate() {
   int oldSize = _size; // 记录原规模
   int i = -1; // 从最前端开始
   while (++i < _size - 1) { // 从前向后，逐一
      int j = i + 1; // assert: _elem[0, i]中不含重复元素
      while (j < _size)
         if (_elem[i] == _elem[j]) remove(j); // 若雷同，则删除后者
         else j++; // 并继续扫描
   }
   return oldSize - _size; // 向量规模变化量，即被删除元素总数
}
*/

}
#endif  // VECTOR_HPP
