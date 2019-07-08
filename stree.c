//
// Created by Once on 2019/7/8.
//

#include "stree.h"
#include <stdlib.h>
#include <string.h>

STree *stree_init(){
    STree *stree = (STree*)malloc(sizeof(STree));
    if(!stree){
        perror("alloc mem for stree error");
        return NULL;
    }
    stree->root = NULL;
    stree->size = 0;
    return stree;
}

int stree_is_full(STree *stree){
    MNode *node = (MNode*)malloc(sizeof(MNode));
    if(!node)
        return 1;
    free(node);
    return 0;
}

int stree_is_empty(STree *stree){
    if(!stree)
        return 1;
    return stree->size == 0;
}

// 寻找极值，compare：1最大值，0最小值，root为子树的根
static MNode *extreme_node(MNode *root, int compare){
    if(compare){
        if(root->right){
            return extreme_node(root->right, compare);
        }
        else
            return root;
    }
    else{
        if(root->left)
            return extreme_node(root->left, compare);
        else
            return root;
    }
}

MNode *stree_get_max(STree *stree){
    if(stree == NULL || stree->size == 0)
        return NULL;
    return extreme_node(stree->root, 1);
}

MNode *stree_get_min(STree *stree){
    if(stree == NULL || stree->size == 0)
        return NULL;
    return extreme_node(stree->root, 0);
}

// 使用先序遍历
static MNode *node_add(STree *stree, MNode *root, Movie *movie){
    if(!root){
        MNode *node = (MNode*)malloc(sizeof(MNode));
        if(!node){
            perror("alloc mem for mnode failed");
            return NULL;
        }
        node->movie.id = movie->id;
        strcpy(node->movie.name, movie->name);
        strcpy(node->movie.about, movie->about);
        node->left = node->right = NULL;
        stree->size++;
        if(!stree->root)
            stree->root = node;
        return node;
    }
    if(root->movie.id > movie->id){
        root->left = node_add(stree, root->left, movie);
        return root;
    }
    else if(root->movie.id < movie->id){
        root->right = node_add(stree, root->right, movie);
        return root;
    }
    // 关键字重复的情况，这里采取直接替换原值的方式，相当于更新原数据
    else{
        strcpy(root->movie.name, movie->name);
        strcpy(root->movie.about, movie->about);
        return root;
    }
}

int stree_add(STree *stree, Movie *movie){
    if(stree == NULL || movie == NULL)
        return 0;
    return node_add(stree, stree->root, movie) == NULL;
}

/**
 * 删除结点的三种情况：
 * 1、树叶结点
 * 2、只有一个儿子的结点
 * 3、有两个儿子的结点：需要找右子树的最小值结点
 * 使用先序遍历的方式
 * */
static MNode *delete_node(STree *stree, MNode *root, int id){
    if(!root)
        return NULL;
    if(root->movie.id == id){
        // 树叶结点
        if(root->right == NULL && root->left == NULL){
            free(root);
            root = NULL;
            stree->size--;
            return root;
        }
        // 有一个儿子的结点
        else if((unsigned int)(root->left == NULL) ^ (unsigned int)(root->right == NULL)){
            MNode *node = root->left == NULL ? root->right : root->left;
            root->movie.id = node->movie.id;
            strcpy(root->movie.name, node->movie.name);
            strcpy(root->movie.about, node->movie.about);
            free(node);
            root->left = root->right = NULL;
            stree->size--;
            return root;
        }
        // 有两个儿子：先替换再去删除
        else{
            MNode *node = extreme_node(root->right, 0);
            root->movie.id = node->movie.id;
            strcpy(root->movie.name, node->movie.name);
            strcpy(root->movie.about, node->movie.about);
            MNode *left = delete_node(stree, root->right, node->movie.id);
            root->right = left;
            return root;
        }
    }
    else if(root->movie.id > id){
        MNode *node = delete_node(stree, root->left, id);
        root->left = node;
        return root;
    }
    else{
        MNode *node = delete_node(stree, root->right, id);
        root->right = node;
        return root;
    }
}

int stree_delete_by_id(STree *stree, int id){
    if(stree == NULL || stree->size == 0)
        return 0;
    stree->root = delete_node(stree, stree->root, id);
    return 1;
}

// 使用后序遍历
static void delete_node_all(MNode *root){
    if(!root)
        return;
    delete_node_all(root->left);
    delete_node_all(root->right);
    free(root);
}

int stree_clear(STree *stree){
    if(stree == NULL)
        return 0;
    if(stree->size != 0)
        delete_node_all(stree->root);
    free(stree);
    return 1;
}

// 排序：按id升序排列每个元素分别执行一个函数
// 使用中序遍历
static void process_node(MNode *root, void (*process)(MNode *mnode)){
    if(!root)
        return;
    process_node(root->left, process);
    process(root);
    process_node(root->right, process);
}

void stree_process(STree *stree, void (*process)(MNode *mnode)){
    if(stree == NULL || stree->size == 0 || process == NULL)
        return;
    process_node(stree->root, process);
}