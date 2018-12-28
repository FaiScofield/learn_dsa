#ifndef KDTREE_H
#define KDTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define MAX_DIM 3


struct KdNode{
    double data[MAX_DIM];
    struct KdNode *left, *right;
};

inline double dist(struct KdNode *a, struct KdNode *b, int dim)
{
    double t, d = 0;
    while (dim--) {
        t = a->data[dim] - b->data[dim];
        d += t * t;
    }
    return d;
}

inline void swap(struct KdNode *x, struct KdNode *y) {
    double tmp[MAX_DIM];
    memcpy(tmp,  x->data, sizeof(tmp));
    memcpy(x->data, y->data, sizeof(tmp));
    memcpy(y->data, tmp,  sizeof(tmp));
}


/* see quickselect method */
struct KdNode* find_median(struct KdNode *start, struct KdNode *end, int idx)
{
    if (end <= start) return NULL;
    if (end == start + 1)
        return start;

    struct KdNode *p, *store, *md = start + (end - start) / 2;
    double pivot;
    while (1) {
        pivot = md->data[idx];

        swap(md, end - 1);
        for (store = p = start; p < end; p++) {
            if (p->data[idx] < pivot) {
                if (p != store)
                    swap(p, store);
                store++;
            }
        }
        swap(store, end - 1);

        /* median has duplicate values */
        if (store->data[idx] == md->data[idx])
            return md;

        if (store > md) end = store;
        else        start = store;
    }
}

struct KdNode* make_tree(struct KdNode *t, int len, int i, int dim)
{
    struct KdNode *n;

    if (!len) return NULL;

    if ((n = find_median(t, t + len, i))) {
        i = (i + 1) % dim;
        n->left  = make_tree(t, n - t, i, dim);
        n->right = make_tree(n + 1, t + len - (n + 1), i, dim);
    }
    return n;
}

/* global variable, so sue me */
int visited;

void nearest(struct KdNode *root, struct KdNode *nd, int i, int dim,
             struct KdNode **best, double *best_dist)
{
    if (!root) return;

    double d, dx, dx2;
    d = dist(root, nd, dim);
    dx = root->data[i] - nd->data[i];
    dx2 = dx * dx;

    visited++;

    if (!*best || d < *best_dist) {
        *best_dist = d;
        *best = root;
    }

    /* if chance of exact match is high */
    if (!*best_dist) return;

    if (++i >= dim) i = 0;

    nearest(dx > 0 ? root->left : root->right, nd, i, dim, best, best_dist);
    if (dx2 >= *best_dist) return;
    nearest(dx > 0 ? root->right : root->left, nd, i, dim, best, best_dist);
}

#endif // KDTREE_H
