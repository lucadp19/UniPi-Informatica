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

// IF AND ONLY IF THE INITIAL TREE ISN'T EMPTY
int bst_max(bst tree){
    if(tree->right == NULL)
        return tree->value;
    return bst_max(tree->right);
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

int second_to_max(bst tree){
    bst parent = NULL;
    bst curr = tree;

    while(curr->right != NULL){
        parent = curr;
        curr = curr->right;
    }

    if(curr->left == NULL)
        return parent->value;
    else
        return bst_max(curr->left);
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

    bst tree = NULL;

    scanf("%d", &N);
    for(int i = 0; i < N; i++){
        scanf("%d", &value);
        insert_in_bst(&tree, value);
    }

    printf("%d\n", second_to_max(tree));
    clean_tree(&tree);
    return 0;
}