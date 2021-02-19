#include <stdio.h>
#include <stdlib.h>

// struct that defines a tree node
typedef struct _node{
    int value;
    struct _node *left;
    struct _node *right;
} node;

typedef node* bst;

// function to insert a node into a bst
void insert_in_bst(bst* tree, int value){
    if(*tree == NULL){ // we found a position to insert the new node
        bst new_node = (bst) malloc(sizeof(node));
        new_node->value = value;
        new_node->left = NULL;
        new_node->right = NULL;

        *tree = new_node;
    } else{ // otherwise we go to the left or to the right depending on value
        if(value <= (*tree)->value)
            insert_in_bst(&((*tree)->left), value);
        else insert_in_bst(&((*tree)->right), value);
    }
}

void print_kth_level(bst tree, int level, int k){
    if(tree != NULL){
        if(level == k)
            printf("%d\n", tree->value);
        else {
            print_kth_level(tree->left, level+1, k);
            print_kth_level(tree->right, level+1, k);
        }
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

int main(){
    int N, value, k;

    bst tree = NULL;

    scanf("%d", &N);
    for(int i = 0; i < N; i++){
        scanf("%d", &value);
        insert_in_bst(&tree, value);
    }
    scanf("%d", &k);

    // print_tree(tree, 0);
    print_kth_level(tree, 0, k);
    
    clean_tree(&tree);
    return 0;
}