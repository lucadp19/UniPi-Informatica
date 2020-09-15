#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
    int value;
    int l_u;
    int r_u;
    struct _node *left;
    struct _node *right;
} node;

typedef node* bst;

typedef struct {
    int left;
    int right;
} pair;

int max(int a, int b){
    if(a > b) return a;
    else return b;
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

pair compute_lr(bst tree){
    pair ans, l_ans, r_ans;

    if(tree == NULL){
        ans.left = -1;
        ans.right = -1;
        return ans;
    }

    l_ans = compute_lr(tree->left);
    r_ans = compute_lr(tree->right);
    tree->l_u = ans.left = l_ans.left + 1;
    tree->r_u = ans.right = r_ans.right + 1;

    return ans;
}

void print_nodes(bst tree){
    if(tree != NULL){
        print_nodes(tree->left);
        if(tree->l_u > tree->r_u)
            printf("%d\n", tree->value);
        print_nodes(tree->right);
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
    int N, value;
    pair rubbish;

    bst tree = NULL;

    scanf("%d", &N);
    for(int i = 0; i < N; i++){
        scanf("%d", &value);
        insert_in_bst(&tree, value);
    }

    rubbish = compute_lr(tree);
    print_nodes(tree);

    clean_tree(&tree);
    return 0;
}