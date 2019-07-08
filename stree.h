//
// Created by Once on 2019/7/8.
//

#ifndef DATALGORITHM_STREE_H
#define DATALGORITHM_STREE_H

// 数据对象
typedef struct movie{
    int id; // 关键字，唯一键，按id排序
    char name[128];
    char about[512];
} Movie;

// 树结点
typedef struct mnode{
    Movie movie;
    struct mnode *left; // 左儿子
    struct mnode *right; // 右儿子
} MNode;

// 二叉树ADT
typedef struct stree{
    MNode *root;
    unsigned int size;
} STree;

// 二叉树算法操作声明
extern STree *stree_init();
extern int stree_is_full(STree *stree);
extern int stree_is_empty(STree *stree);
extern MNode *stree_get_max(STree *stree);
extern MNode *stree_get_min(STree *stree);
extern int stree_add(STree *stree, Movie *movie);
extern int stree_delete_by_id(STree *stree, int id);
extern int stree_clear(STree *stree);
// 排序：按id升序排列每个元素分别执行一个函数
extern void stree_process(STree *stree, void (*process)(MNode *mnode));

#endif //DATALGORITHM_STREE_H
