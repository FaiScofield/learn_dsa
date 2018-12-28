#ifndef REDBLACK_H
#define REDBLACK_H

#include "../BST/BST.h" // 基于BST实现RedBlack
#include "../UniPrint/print.h"

// RedBlack树模板类
template <typename T> class RedBlack : public BST<T> {

protected:

    /******************************************************************************************
     * RedBlack双黑调整算法：解决节点x与被其替代的节点均为黑色的问题
     * 分为三大类共四种情况：
     *    BB-1 ：2次颜色翻转，2次黑高度更新，1~2次旋转，不再递归
     *    BB-2R：2次颜色翻转，2次黑高度更新，0次旋转，不再递归
     *    BB-2B：1次颜色翻转，1次黑高度更新，0次旋转，需要递归
     *    BB-3 ：2次颜色翻转，2次黑高度更新，1次旋转，转为BB-1或BB2R
     ******************************************************************************************/
    void solveDoubleBlack(BinNodePosi(T) r)
    {
        BinNodePosi(T) p = r ? r->parent : this->_hot;
        if (!p) return; // r的父亲
        BinNodePosi(T) s = (r == p->lc) ? p->rc : p->lc; // r的兄弟
        if (IsBlack(s)) { // 兄弟s为黑
            BinNodePosi(T) t = NULL; // s的红孩子（若左、右孩子皆红，左者优先；皆黑时为NULL）
            if (IsRed(s->rc)) t = s->rc; // 右子
            if (IsRed(s->lc)) t = s->lc; // 左子
            if (t) { // 黑s有红孩子：BB-1
//                printf("  case BB-1: Child ("); print(s->lc->data);
//                printf(") of BLACK sibling ("); print(s->data); printf(") is RED\n");
                RBColor oldColor = p->color; // 备份原子树根节点p颜色，并对t及其父亲、祖父
                //  以下，通过旋转重平衡，并将新子树的左、右孩子染黑
                BinNodePosi(T) b = FromParentTo(p) = this->rotateAt(t); // 旋转
                if (HasLChild(*b)) { b->lc->color = RB_BLACK; updateHeight(b->lc); } // 左子
                if (HasRChild(*b)) { b->rc->color = RB_BLACK; updateHeight(b->rc); } // 右子
                b->color = oldColor; updateHeight(b); // 新子树根节点继承原根节点的颜色
//                printBinTree(b, 0, 0);
            } else { // 黑s无红孩子
                s->color = RB_RED; s->height--; // s转红
                if (IsRed(p)) { // BB-2R
//                    printf("  case BB-2R: Both children ("); print(s->lc);
//                    printf(") and ("); print(s->rc);
//                    printf(") of BLACK sibling ("); print(s);
//                    printf(") are BLACK, and parent ("); print(p);
//                    printf(") is RED\n"); // s孩子均黑，p红
                    p->color = RB_BLACK; // p转黑，但黑高度不变
//                    printBinTree(p, 0, 0);
                } else { // BB-2B
//                    printf("  case BB-2R: Both children ("); print(s->lc);
//                    printf(") and ("); print(s->rc);
//                    printf(") of BLACK sibling ("); print(s);
//                    printf(") are BLACK, and parent ("); print(p);
//                    printf(") is BLACK\n"); // s孩子均黑，p黑
                    p->height--; // p保持黑，但黑高度下降
//                    printBinTree(p, 0, 0);
                    solveDoubleBlack(p); // 递归上溯
                }
            }
        } else { // 兄弟s为红：BB-3
//            printf("  case BB-3: sibling ("); print(s); printf(" is RED\n"); // s红（双子俱黑）
            s->color = RB_BLACK; p->color = RB_RED; // s转黑，p转红
            BinNodePosi(T) t = IsLChild(*s) ? s->lc : s->rc; // 取t与其父s同侧
            this->_hot = p; FromParentTo(p) = this->rotateAt(t); // 对t及其父亲、祖父做平衡调整
//            printBinTree<T>(s, 0, 0);
            solveDoubleBlack(r); // 继续修正r处双黑——此时的p已转红，故后续只能是BB-1或BB-2R
        }
    }

    /******************************************************************************************
     * RedBlack双红调整算法：解决节点x与其父均为红色的问题。分为两大类情况：
     *    RR-1：2次颜色翻转，2次黑高度更新，1~2次旋转，不再递归
     *    RR-2：3次颜色翻转，3次黑高度更新，0次旋转，需要递归
     ******************************************************************************************/
    void solveDoubleRed(BinNodePosi(T) x) // x当前必为红
    {
        if (IsRoot(*x)) // 若已（递归）转至树根，则将其转黑，整树黑高度也随之递增
        {  this->_root->color = RB_BLACK; this->_root->height++; return;  } // 否则，x的父亲p必存在
        BinNodePosi(T) p = x->parent; if (IsBlack(p)) return; // 若p为黑，则可终止调整。否则
        BinNodePosi(T) g = p->parent; // 既然p为红，则x的祖父必存在，且必为黑色
        BinNodePosi(T) u = uncle (x); // 以下，视x叔父u的颜色分别处理
        if (IsBlack(u)) { // u为黑色（含NULL）时 /printf("  case RR-1:\n");
            if (IsLChild(*x) == IsLChild(*p)) // 若x与p同侧（即zIg-zIg或zAg-zAg），则
                p->color = RB_BLACK; // p由红转黑，x保持红
            else // 若x与p异侧（即zIg-zAg或zAg-zIg），则
                x->color = RB_BLACK; // x由红转黑，p保持红
            g->color = RB_RED; // g必定由黑转红
        // 以上虽保证总共两次染色，但因增加了判断而得不偿失
        // 在旋转后将根置黑、孩子置红，虽需三次染色但效率更高
            BinNodePosi(T) gg = g->parent; // 曾祖父（great-grand parent）
            BinNodePosi(T) r = FromParentTo(g) = this->rotateAt(x); // 调整后的子树根节点
            r->parent = gg; // 与原曾祖父联接
        } else { // 若u为红色 /printf("  case RR-2:\n");
            p->color = RB_BLACK; p->height++; // p由红转黑
            u->color = RB_BLACK; u->height++; // u由红转黑
            if (!IsRoot(*g)) g->color = RB_RED; // g若非根，则转红
            solveDoubleRed(g); // 继续调整g（类似于尾递归，可优化为迭代形式）
        }
    }

   // 更新节点x的高度
    int updateHeight(BinNodePosi(T) x)
    {
        x->height = max(stature(x->lc), stature(x->rc)); // 孩子一般黑高度相等，除非出现双黑
        //  红黑树中各节点左、右孩子的黑高度通常相等
        //  这里之所以取更大值，是便于在删除节点后的平衡调整过程中，正确更新被删除节点父亲的黑高度
        //  否则，rotateAt()会根据被删除节点的替代者（高度小一）设置父节点的黑高度
        return IsBlack(x) ? x->height++ : x->height; // 若当前节点为黑，则计入黑深度
    } // 因统一定义stature(NULL) = -1，故height比黑高度少一，好在不致影响到各种算法中的比较判断


public:
    // 插入（重写）
    // 无论e是否存在于原树中，返回时总有x->data == e
    BinNodePosi(T) insert(const T& e)
    {
        BinNodePosi(T) & x = this->search(e);
        if (x) return x; // 确认目标不存在（留意对this->_hot的设置）
        x = new BinNode<T>(e, this->_hot, NULL, NULL, -1); this->_size++; // 创建红节点x：以this->_hot为父，黑高度-1
        solveDoubleRed(x);
        return x ? x : this->_hot->parent; // 经双红修正后，即可返回
    }

    // 删除（重写）
    bool remove(const T& e)
    {
        BinNodePosi(T) & x = this->search(e);
        if (!x) return false; // 确认目标存在（留意this->_hot的设置）
        BinNodePosi(T) r = this->removeAt(x, this->_hot);
        if (! (--this->_size)) return true; // 实施删除
        // assert: this->_hot某一孩子刚被删除，且被r所指节点（可能是NULL）接替。以下检查是否失衡，并做必要调整
        if (! this->_hot) { // 若刚被删除的是根节点，则将其置黑，并更新黑高度
            this->_root->color = RB_BLACK; updateHeight(this->_root);
            return true;
        }
        // assert: 以下，原x（现r）必非根，this->_hot必非空
        if (BlackHeightUpdated(this->_hot)) return true; // 若所有祖先的黑深度依然平衡，则无需调整
        if (IsRed(r)) { // 否则，若r为红，则只需令其转黑
            r->color = RB_BLACK; r->height++;
            return true;
        }
        // assert: 以下，原x（现r）均为黑色
//        printBinTree(this->_hot, 0, 0);
        solveDoubleBlack(r);
        return true; // 经双黑调整后返回
    } // 若目标节点存在且被删除，返回true；否则返回false

//  BST::search()等其余接口可直接沿用
};





#endif //  REDBLACK_H
