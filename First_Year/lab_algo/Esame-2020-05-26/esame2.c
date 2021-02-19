#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
    int value;
    int colour;
    struct _node *left;
    struct _node *right;
} node;

typedef node* bst;

typedef struct {
    int prop_holds;
    int red_height; 
} bool_int;

int max(int a, int b){
    if(a > b) return a;
    else return b;
}

int abs(int a){
    if(a < 0) return -a;
    else return a;
}

void insert_in_bst(bst* tree, int value, int colour){
    bst new_node;

    if(*tree == NULL){
        new_node = (bst) malloc(sizeof(node));
        new_node->value = value;
        new_node->colour = colour;
        new_node->left = NULL;
        new_node->right = NULL;

        *tree = new_node;
    } else{
        if(value <= (*tree)->value)
            insert_in_bst(&((*tree)->left), value, colour);
        else insert_in_bst(&((*tree)->right), value, colour);
    }
}

// bool_int red_height(bst tree){
//     bool_int res;
//     bool_int red_h_l, red_h_r;

//     if(tree == NULL){ // caso base: albero vuoto
//         res.prop_holds = 1;
//         res.red_height = 0;
//         return res;
//     }

//     red_h_l = red_height(tree->left);
//     if(!red_h_l.prop_holds){
//         res.prop_holds = 0;
//         // se la proprieta' non vale per il figlio sinistr
//         // allora e' inutile calcolare l'altezza del padre
//         res.red_height = 0;
//         return res;
//     }

//     red_h_r = red_height(tree->right);
//     if(!red_h_r.prop_holds){
//         res.prop_holds = 0;
//         // se la proprieta' non vale per il figlio destro
//         // allora e' inutile calcolare l'altezza del padre
//         res.red_height = 0;
//         return res;
//     }

//     // la condizione vale per il figlio sinistro e per il figlio destro
//     // dunque controllo che valga per la radice

//     // proprieta' da verificare: differenza tra le altezze rosse dei figli in valore assoluto <= 1
//     if(abs(red_h_l.red_height - red_h_r.red_height) <= 1)
//         res.prop_holds = 1;
//     else 
//         res.prop_holds = 0;
    
//     // calcolo l'altezza rossa della radice
//     res.red_height = max(red_h_l.red_height, red_h_r.red_height);
//     // se la radice e' rossa aggiungo 1 all'altezza
//     if(tree->colour == 0) // colore rosso
//         res.red_height += 1;

//     return res;
// }

int Min(bst tree, int* min){
    int minDx = 0;
    int minSx = 0;
    int sommaSx, sommaDx;
    int dist;

    if(tree == NULL){
        *min = 0;
        return 1;
    }

    sommaSx = Min(tree->left, &minSx);
    sommaDx = Min(tree->right, &minDx);

    if(minDx > minSx){
        *min += minDx;
    } else *min += minSx;
    if(tree->colour == 0)
        *min += 1;
    
    dist = abs(minDx - minSx);
    return (dist <= 1) && sommaDx && sommaSx;
}

// funzione che libera la memoria dell'albero
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
    int N, value, colour;
    int res;

    bst tree = NULL;

    scanf("%d", &N);
    for(int i = 0; i < N; i++){
        scanf("%d", &value);
        scanf("%d", &colour);
        insert_in_bst(&tree, value, colour);
    }
    int k;
    res = Min(tree, &k);

    if(res)
        printf("TRUE\n");
    else
        printf("FALSE\n");
    
    clean_tree(&tree);
    return 0;
}