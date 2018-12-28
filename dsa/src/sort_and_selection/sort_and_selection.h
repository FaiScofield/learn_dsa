#ifndef SORT_AND_SELECTION_H
#define SORT_AND_SELECTION_H

#include "../Vector/Vector.h"
#include "../UniPrint/print.h"

// 基于快速排序划分的k选取算法
// 最坏O(n²)
template <typename T> void quickSelect(Vector<T> & A, Rank k) {
    for (Rank lo = 0, hi = A.size() - 1; lo < hi;) {
        Rank i = lo, j = hi;
        T pivot = A[lo];
        while (i < j) { // O(hi - lo + 1) = O(n)
            while ((i < j) && (pivot <= A[j])) j--;
            A[i] = A[j];
            while ((i < j) && (A[i] <= pivot)) i++;
            A[j] = A[i];
        } // assert: i == j
        A[i] = pivot;
        if (k <= i) hi = i - 1;
        if (i <= k) lo = i + 1;
        print(A);
        for (int i = 0; i < lo; i++) printf("     ");
        for (int i = lo; i <= hi; i++) printf("-----");
        printf("\n");
    } // A[k] is now a pivot
}

// O(n)
template <typename T> void linearSelect(Vector<T> & A, Rank k) {
    // sort

    // divide


}

// 中位数算法
// 向量S1[lo1, lo1 + n1)和S2[lo2, lo2 + n2)分别有序，数据项可能重复
template <typename T> T median_I(Vector<T>& S1, int lo1, int n1, Vector<T>& S2, int lo2, int n2) {
   if (n1 > n2) return median (S2, lo2, n2, S1, lo1, n1); // 确保n1 <= n2
   for (int i = 0; i < lo1; i++) printf("    ."); for (int i = 0; i < n1; i++) print (S1[lo1+i]); for (int i = lo1 + n1; i < S1.size(); i++) printf("    ."); printf("\n");
   for (int i = 0; i < lo2; i++) printf("    ."); for (int i = 0; i < n2; i++) print (S2[lo2+i]); for (int i = lo2 + n2; i < S2.size(); i++) printf("    .");  printf("\n--\n");
   if (n2 < 6) // 递归基：1 <= n1 <= n2 <= 5
      return trivialMedian (S1, lo1, n1, S2, lo2, n2);
   // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // /
   //                 lo1            lo1 + n1/2      lo1 + n1 - 1
   //                  |                 |                 |
   //                  X >>>>>>>>>>>>>>> X >>>>>>>>>>>>>>> X
   //  Y .. trimmed .. Y >>>>>>>>>>>>>>> Y >>>>>>>>>>>>>>> Y .. trimmed .. Y
   //  |               |                 |                 |               |
   //  lo2     lo2 + (n2-n1)/2       lo2 + n2/2     lo2 + (n2+n1)/2    lo2 + n2 -1
   // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // /
   if (2 * n1 < n2) // 若两个向量的长度相差悬殊，则长者（S2）的两翼可直接截除
      return median (S1, lo1, n1, S2, lo2 + (n2 - n1 - 1) / 2, n1 + 2 - (n2 - n1) % 2);
   // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // /
   //     lo1                  lo1 + n1/2              lo1 + n1 - 1
   //      |                       |                       |
   //      X >>>>>>>>>>>>>>>>>>>>> X >>>>>>>>>>>>>>>>>>>>> X
   //                              |
   //                             m1
   // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // /
   //                             mi2b
   //                              |
   //  lo2 + n2 - 1         lo2 + n2 - 1 - n1/2
   //      |                       |
   //      Y <<<<<<<<<<<<<<<<<<<<< Y ...
   //                                 .
   //                                .
   //                               .
   //                              .
   //                             .
   //                            .
   //                           .
   //                          ... Y <<<<<<<<<<<<<<<<<<<<< Y
   //                              |                       |
   //                        lo2 + (n1-1)/2               lo2
   //                              |
   //                             mi2a
   // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // /
   int mi1  = lo1 + n1 / 2;
   int mi2a = lo2 + (n1 - 1) / 2;
   int mi2b = lo2 + n2 - 1 - n1 / 2;
   if (S1[mi1] > S2[mi2b]) // 取S1左半、S2右半
      return median (S1, lo1, n1 / 2 + 1, S2, mi2a, n2 - (n1 - 1) / 2);
   else if (S1[mi1] < S2[mi2a]) // 取S1右半、S2左半
      return median (S1, mi1, (n1 + 1) / 2, S2, lo2, n2 - n1 / 2);
   else // S1保留，S2左右同时缩短
      return median (S1, lo1, n1, S2, mi2a, n2 - (n1 - 1) / 2 * 2);
}


// 中位数算法（高效版）
// 序列S1[lo1, lo1 + n)和S2[lo2, lo2 + n)分别有序，n > 0，数据项可能重复
template <typename T> T median_II(Vector<T>& S1, int lo1, Vector<T>& S2, int lo2, int n) {
   printf("median\n");
   for (int i = 0; i < lo1; i++) printf("    ."); for (int i = 0; i < n; i++) print (S1[lo1+i]); for (int i = lo1 + n; i < S1.size(); i++) printf("    ."); printf("\n");
   for (int i = 0; i < lo2; i++) printf("    ."); for (int i = 0; i < n; i++) print (S2[lo2+i]); for (int i = lo2 + n; i < S2.size(); i++) printf("    .");  printf("\n--\n");
   if (n < 3) return trivialMedian (S1, lo1, n, S2, lo2, n); // 递归基
   int mi1 = lo1 + n / 2, mi2 = lo2 + (n - 1) / 2; // 长度（接近）减半
   if (S1[mi1] < S2[mi2])
      return median (S1, mi1, S2, lo2, n + lo1 - mi1); // 取S1右半、S2左半
   else if (S1[mi1] > S2[mi2])
      return median (S1, lo1, S2, mi2, n + lo2 - mi2); // 取S1左半、S2右半
   else
      return S1[mi1];
}

// 众数查找算法：T可比较可判等
template <typename T> bool majority(Vector<T> A, T& maj) {
    maj = majorityElementCandidate(A);   // 必要性：选出候选者maj
    return majorityElementCheck(A, maj); // 充分性：验证maj是否的确当选
}

// 验证候选者是否确为众数
template <typename T> bool majorityElementCheck(Vector<T> A, T maj) {
    int occurrence = 0;                 // maj在A[]中出现的次数
    for (int i = 0; i < A.size(); i++)  // 逐一遍历A[]的各个元素
        if (A[i] == maj) occurrence++;  // 每遇到一次maj，均更新计数器
    printf("%d found with %d/%d occurrence(s)\n", maj, occurrence, A.size());
    return 2 * occurrence > A.size();   // 根据最终的计数值，即可判断是否的确当选
}

// 选出具备必要条件的众数候选者
template <typename T> T majorityElementCandidate(Vector<T> A) {
    T maj; // 众数候选者
    // 线性扫描：借助计数器c，记录maj与其它元素的数量差额
    for (int c = 0, i = 0; i < A.size(); i++) {
        // 每当c归零，都意味着此时的前缀P可以剪除,众数候选者改为新的当前元素
        if (0 == c) { maj = A[i]; c = 1; }
        // 否则,相应地更新差额计数器
        else maj == A[i] ? c++ : c--;
    }
    // 至此，原向量的众数若存在，则只能是maj —— 尽管反之不然
    return maj;
}

template <typename T> void hellSelect(Vector<T> & A, Rank k) {

}

#endif //  SORT_AND_SELECTION_H
