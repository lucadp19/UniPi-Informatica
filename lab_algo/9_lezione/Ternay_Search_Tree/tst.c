#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
    int value;
    struct _node *left;
    struct _node *centre;
    struct _node *right;
} node;

typedef node* tst;

void insert_in_tst(tst* tree, int value){
    if(*tree == NULL){
        tst new_node = (tst) malloc(sizeof(node));
        new_node->value = value;
        new_node->left = NULL;
        new_node->centre = NULL;
        new_node->right = NULL;

        *tree = new_node;
    } else{
        if(value < (*tree)->value)
            insert_in_tst(&((*tree)->left), value);
        else if(value % (*tree)->value == 0)
            insert_in_tst(&((*tree)->centre), value);
        else insert_in_tst(&((*tree)->right), value);
    }
}


int three_sons(tst tree){
    int three = 0;

    if(tree == NULL) return 0;
    if(tree->left != NULL && tree->centre != NULL && tree->right != NULL){
        three = 1;
        // printf("Nodo %d ha tre figli\n", tree->value);
    }   
    
    return three + three_sons(tree->left) + three_sons(tree->centre) + three_sons(tree->right);
}

void clean_tree(tst* tree){
    if(*tree != NULL){
        clean_tree(&((*tree)->left));
        clean_tree(&((*tree)->centre));
        clean_tree(&((*tree)->right));
        free(*tree);
    }
}

void print_tree(tst tree, int dpt){
    if(tree != NULL){
        printf("%d: %d\n", dpt, tree->value);
        print_tree(tree->left, dpt+1);
        print_tree(tree->centre, dpt+1);
        print_tree(tree->right, dpt+1);
    }
}

int main(){
    int N, value;

    tst tree = NULL;

    scanf("%d", &N);
    for(int i = 0; i < N; i++){
        scanf("%d", &value);
        insert_in_tst(&tree, value);
    }

    // print_tree(tree, 0);

    printf("%d\n", three_sons(tree));
    clean_tree(&tree);
    return 0;
}