#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
    int value;
    struct _node *left;
    struct _node *right;
} node;

typedef struct {
    int max_path;
    int min_key;
} pair;

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

int min(int a, int b){
    if(a < b) return a;
    else return b;
}

int min_3(int a, int b, int c){
    if(a < b && a < c)
        return a;
    else if(b < a && b < c)
        return b;
    else
        return c;
}

pair max_path_min_key(bst tree){
    pair ans;
    pair left_ans, right_ans;

    if(tree->left == NULL && tree->right == NULL) {
        ans.min_key = tree->value;
        ans.max_path = tree->value;
        return ans;
    }

    if(tree->left != NULL && tree->right == NULL) {
        left_ans = max_path_min_key(tree->left);
        ans.max_path = left_ans.max_path + tree->value;
        ans.min_key = min(left_ans.min_key, tree->value);
        return ans;
    }

    if(tree->left == NULL && tree->right != NULL) {
        right_ans = max_path_min_key(tree->right);
        ans.max_path = right_ans.max_path + tree->value;
        ans.min_key = min(right_ans.min_key, tree->value);
        return ans;
    }

    left_ans = max_path_min_key(tree->left);
    right_ans = max_path_min_key(tree->right);

    if(left_ans.max_path > right_ans.max_path){
        ans.max_path = left_ans.max_path + tree->value;
        ans.min_key = min(left_ans.min_key, tree->value);
    } 
    else if(left_ans.max_path < right_ans.max_path){
        ans.max_path = right_ans.max_path + tree->value;
        ans.min_key = min(right_ans.min_key, tree->value);
    } 
    else{
        ans.max_path = left_ans.max_path + tree->value;
        ans.min_key = min_3(left_ans.min_key, right_ans.min_key, tree->value);
    }

    return ans;
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
    if(N == 0)
        printf("0\n");
    else
        printf("%d\n", max_path_min_key(tree).min_key);
    clean_tree(&tree);
    return 0;
}