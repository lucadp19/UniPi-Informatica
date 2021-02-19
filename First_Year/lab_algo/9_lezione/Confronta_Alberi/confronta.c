#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
    int value;
    struct _node *left;
    struct _node *right;
} node;

typedef node* bst;

void insert_in_bst(bst* tree, int value){
    if(*tree == NULL){
        bst new_node = (bst) malloc(sizeof(node));
        new_node->value = value;
        new_node->left = NULL;
        new_node->right = NULL;

        *tree = new_node;
    } else{
        if(value <= (*tree)->value)
            insert_in_bst(&((*tree)->left), value);
        else insert_in_bst(&((*tree)->right), value);
    }
}

void clean_tree(bst* tree){
    if(*tree != NULL){
        clean_tree(&((*tree)->left));
        clean_tree(&((*tree)->right));
        free(*tree);
    }
}

void print_tree(bst tree, int dpt){
    if(tree != NULL){
        printf("%d: %d\n", dpt, tree->value);
        print_tree(tree->left, dpt+1);
        print_tree(tree->right, dpt+1);
    }
}

int compare_keys(bst a, bst b, int key){
    if(a->value == b->value && a->value == key)
        return 1;
    if(a->value != b->value)
        return 0;
    
    if(key < a->value)
        return compare_keys(a->left, b->left, key);
    else return compare_keys(a->right, b->right, key);
}

int main(){
    int N, value, K;

    bst a = NULL;
    bst b = NULL;

    scanf("%d %d", &N, &K);
    for(int i = 0; i < N; i++){
        scanf("%d", &value);
        insert_in_bst(&a, value);
    }
    for(int i = 0; i < N; i++){
        scanf("%d", &value);
        insert_in_bst(&b, value);
    }

    // print_tree(tree, 0);

    printf("%d", compare_keys(a, b, K));
    clean_tree(&a);
    clean_tree(&b);
    return 0;
}