#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
    int value;
    struct _node *left;
    struct _node *right;
} node;

typedef node* bst;

int max(int a, int b){
    if(a > b) return a;
    else return b;
}

void swap(int* a, int* b){
    int t = *a;
    *a = *b;
    *b = t;
}

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

int lca(bst tree, int x, int y){
    // Assumpion: x < y
    if(x <= tree->value && tree->value <= y)
        return tree->value;
    if(x > tree->value)
        return lca(tree->right, x, y);
    else return lca(tree->left, x, y);
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

int main(){
    int N, value;
    int x, y;

    bst tree = NULL;

    scanf("%d", &N);
    for(int i = 0; i < N; i++){
        scanf("%d", &value);
        insert_in_bst(&tree, value);
    }
    scanf("%d %d", &x, &y);
    // Ensuring x < y
    if(x > y)
        swap(&x, &y);

    printf("%d\n", lca(tree, x, y));
    clean_tree(&tree);
    return 0;
}