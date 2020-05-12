#include <stdio.h>
#include <stdlib.h>

typedef struct _edges{
    int degree;
    int* adj;
} edges;
typedef edges* graph;


graph read_graph(int N);
void delete_graph(graph G, int N);

int* dfs(graph G, int N, int src);
void iterative_dfs(graph G, int N, int src, int* colours);

int is_connected(int N, int* colours);

 
int main(){
    int N;
    graph G;
    int* colours;

    scanf("%d", &N);
    G = read_graph(N);
    
    colours = dfs(G, N, 0);
    printf("%d", is_connected(N, colours));
    free(colours);

    delete_graph(G, N);
    return 0;
}


graph read_graph(int N){
    graph G = (graph) malloc(sizeof(edges) * N);

    for(int i = 0; i < N; i++){
        scanf("%d", &G[i].degree);
        G[i].adj = (int*) malloc(sizeof(int) * G[i].degree);
        for(int j = 0; j < G[i].degree; j++)
            scanf("%d", &G[i].adj[j]);        
    }

    return G;
}

void delete_graph(graph G, int N){
    for(int i = 0; i < N; i++)
        free(G[i].adj);
    free(G);
}

/* --- VISITS --- */

// DFS
int* dfs(graph G, int N, int src){
    int* colours = (int*) malloc(N * sizeof(int));
    for(int i = 0; i < N; i++) colours[i] = 0;

    colours[src] = 1;

    // recursive_dfs(G, src, colours);
    iterative_dfs(G, N, src, colours);

    return colours;
}

void iterative_dfs(graph G, int N, int src, int* colours){
    int* stack = (int *) malloc(N * sizeof(int));
    int stack_size, current, dest;

    stack[0] = src;
    stack_size = 1;

    while(stack_size > 0){
        current = stack[--stack_size];
        for(int i = 0; i < G[current].degree; i++){
            dest = G[current].adj[i];
            if(colours[dest] == 0){
                colours[dest] = 1;
                stack[stack_size++] = dest;
            }
        }
    }

    free(stack);
}

int is_connected(int N, int* colours){
    for(int i = 0; i < N; i++)
        if(colours[i] == 0)
            return 0;
    return 1;
}