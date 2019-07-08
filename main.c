#include <stdio.h>
#include <string.h>
#include "stree.h"


static void process_name(MNode *node){
    printf("%06d %s\n", node->movie.id, node->movie.name);
}

static void process_id(MNode *node){
    printf("%d ", node->movie.id);
}

void stree(){
    STree *stree = stree_init();
    Movie m1;
    m1.id = 98;
    strcpy(m1.name, "Once Upon A Time In Hollywood");
    strcpy(m1.about, "Once Upon A Time In Hollywood");

    Movie m2;
    m2.id = 34;
    strcpy(m2.name, "The Price of Salt");
    strcpy(m2.about, "The Price of Salt");

    Movie m3;
    m3.id = 69;
    strcpy(m3.name, "Mad Man");
    strcpy(m3.about, "Mad Man");

    Movie m4;
    m4.id = 112;
    strcpy(m4.name, "Breaking Bad");
    strcpy(m4.about, "Breaking Bad");

    Movie m5;
    m5.id = 21;
    strcpy(m5.name, "The Name of Rose");
    strcpy(m5.about, "The Name of Rose");

    Movie m6;
    m6.id = 100;
    strcpy(m6.name, "You Belong to Me");
    strcpy(m6.about, "You Belong to Me");

    stree_add(stree, &m1);
    stree_add(stree, &m2);
    stree_add(stree, &m3);
    stree_add(stree, &m4);
    stree_add(stree, &m5);
    stree_add(stree, &m6);

    // 获取二叉树中id的最大最小值
    printf("Max: %d, Min: %d\n\n", stree_get_max(stree)->movie.id, stree_get_min(stree)->movie.id);

    stree_process(stree, process_name); // 升序输出
    printf("\n");

    stree_process(stree, process_id);
    printf("\n");

    stree_delete_by_id(stree, 100); // 删除树叶
    stree_process(stree, process_id);
    printf("\n");
    stree_delete_by_id(stree, 98); // 删除有两个儿子的结点
    stree_process(stree, process_id);
    printf("\n");
    stree_delete_by_id(stree, 34); // 删除有两个儿子的结点
    stree_process(stree, process_id);
    printf("\n");
    stree_delete_by_id(stree, 69); // 删除只有一个儿子的结点
    stree_process(stree, process_id);
    printf("\n");

    stree_clear(stree);
}

int main() {
    stree();
    return 0;
}