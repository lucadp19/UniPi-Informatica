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

int max(int a, int b){
    if(a > b) return a;
    else return b;
}


// il programma chiede che l'altezza di un albero vuoto sia 0
// anche se nelle lezioni teoriche abbiamo detto che l'altezza di una foglia e' 0,
//      mentre l'altezza di un albero vuoto e' -1
int height(bst tree){
    if(tree == NULL) return 0;
    return max(height(tree->left), height(tree->right)) + 1;
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

    // print_tree(tree, 0);

    printf("%d\n", height(tree));
    clean_tree(&tree);
    return 0;
}