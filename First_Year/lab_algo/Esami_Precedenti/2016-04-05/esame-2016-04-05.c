#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* string;

typedef struct _node{
    string key;
    int value;
    struct _node *left;
    struct _node *right;
} node;

typedef node* bst;

int max(int a, int b){
    if(a > b) return a;
    else return b;
}

void insert_in_bst(bst* tree, string key, int value){
    if(*tree == NULL){
        bst new_node = (bst) malloc(sizeof(node));
        new_node->key = key;
        new_node->value = value;
        new_node->left = NULL;
        new_node->right = NULL;

        *tree = new_node;
    } else{
        if(strcmp(key, (*tree)->key) <= 0)
            insert_in_bst(&((*tree)->left), key, value);
        else insert_in_bst(&((*tree)->right), key, value);
    }
}

int max_in_subtree(bst tree){
    // Assumption: tree != NULL
    int l_max = -1; 
    int r_max = -1;
    if(tree->left != NULL)
        l_max = max_in_subtree(tree->left);
    if(tree->right != NULL)
        r_max = max_in_subtree(tree->right);
    
    return max(tree->value, max(l_max, r_max));
}

int find_and_max(bst tree, string key){
    // Assumption: tree != NULL
    int cmp = strcmp(key, tree->key);
    if(cmp == 0)
        return max_in_subtree(tree);
    else if(cmp < 0)
        return find_and_max(tree->left, key);
    else return find_and_max(tree->right, key);
}


void clean_tree(bst* tree){
    if(*tree != NULL){
        clean_tree(&((*tree)->left));
        clean_tree(&((*tree)->right));
        free((*tree)->key);
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
    string key;

    bst tree = NULL;

    scanf("%d", &N);
    for(int i = 0; i < N; i++){
        key = (string) malloc(101*sizeof(char));
        scanf("%s", key);
        scanf("%d", &value);
        insert_in_bst(&tree, key, value);
    }

    scanf("%s", key);

    printf("%d\n", find_and_max(tree, key));
    
    clean_tree(&tree);
    return 0;
}