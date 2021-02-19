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

// Sorts in increasing order
void increasing_sort(bst tree){
    if(tree != NULL){
        increasing_sort(tree->left);
        printf("%d\n", tree->value);
        increasing_sort(tree->right);
    }
}

// Sorts in decreasing order
void decreasing_sort(bst tree){
    if(tree != NULL){
        decreasing_sort(tree->right);
        printf("%d\n", tree->value);
        decreasing_sort(tree->left);
    }
}

// Returns the height of the entire tree
int height(bst tree){
    if(tree == NULL) return -1; // se il programma lo richiede, modificala in 0
    return max(height(tree->left), height(tree->right)) + 1;
}

// Returns the depth of the node with value "value"
// If the node isn't in the tree, it returns -1
int depth(bst tree, int value, int dpt){
    if(tree == NULL) return -1;
    if(tree->value == value) return dpt;

    if(value <= tree->value)
        return depth(tree->left, value, dpt+1);
    else
        return depth(tree->right, value, dpt+1);
}

// Looks for a node with key "value" in a tree and returns the pointer to that node
// If there isn't such a node, it returns NULL
// Can be used as a scheme for other functions
bst find(bst tree, int value){
    if(tree == NULL || tree->value == value) return tree;

    if(value <= tree->value)
        return find(tree->left, value);
    else
        return find(tree->right, value);
}

// IF AND ONLY IF THE INITIAL TREE ISN'T EMPTY
int bst_min(bst tree){
    if(tree->left == NULL)
        return tree->value;
    return bst_min(tree->left);
}

// IF AND ONLY IF THE INITIAL TREE ISN'T EMPTY
int bst_max(bst tree){
    if(tree->right == NULL)
        return tree->value;
    return bst_min(tree->right);
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
    // DO SOMETHING
    clean_tree(&tree);
    return 0;
}