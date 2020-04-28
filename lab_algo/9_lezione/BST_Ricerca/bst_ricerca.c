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

int depth(bst tree, int value, int dpt){
    if(tree == NULL) return -1;
    if(tree->value == value) return dpt;

    if(value <= tree->value)
        return depth(tree->left, value, dpt+1);
    else
        return depth(tree->right, value, dpt+1);
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
    int N, value, res;

    bst tree = NULL;

    scanf("%d", &N);
    for(int i = 0; i < N; i++){
        scanf("%d", &value);
        insert_in_bst(&tree, value);
    }

    // print_tree(tree, 0);

    scanf("%d", &value);
    while(value >= 0){
        res = depth(tree, value, 0);
        if(res == -1)
            printf("NO\n");
        else 
            printf("%d\n", res);
        scanf("%d", &value);
    }
    clean_tree(&tree);
    return 0;
}