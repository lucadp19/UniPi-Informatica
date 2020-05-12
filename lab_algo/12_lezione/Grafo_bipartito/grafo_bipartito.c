#include <stdio.h>
#include <stdlib.h>

typedef struct _edges{
    int degree;
    int* adj;
} edges;
typedef edges* graph;

typedef struct _queue{
    int* values;
    int capacity;
    int head;
    int tail;
} queue;


graph read_graph(int N);
void delete_graph(graph G, int N);

int is_bipartite_dfs(graph G, int N, int src);
int is_bipartite_iterative_dfs(graph G, int src, int* colours, int* stack);

 
int main(){
    int N;
    graph G;
    int is_bipartite;

    scanf("%d", &N);
    G = read_graph(N);

    is_bipartite = is_bipartite_dfs(G, N, 0);
    printf("%d\n", is_bipartite);

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

int is_bipartite_dfs(graph G, int N, int src){
    int is_bipartite;
    int* colours = (int*) malloc(N * sizeof(int));
    int* stack = (int *) malloc(N * sizeof(int));
    for(int i = 0; i < N; i++) colours[i] = 0;

    colours[src] = 1;

    is_bipartite = is_bipartite_iterative_dfs(G, src, colours, stack);
    
    free(stack);
    free(colours);
    return is_bipartite;
}

int is_bipartite_iterative_dfs(graph G, int src, int* colours, int* stack){
    int stack_size, current, dest, new_colour;

    stack[0] = src;
    stack_size = 1;

    while(stack_size > 0){
        int i = 0;
        current = stack[--stack_size];

        if(colours[current] == 1)
            new_colour = 2;
        else new_colour = 1;

        while(i < G[current].degree){
            dest = G[current].adj[i];
            if(colours[dest] == 0){
                colours[dest] = new_colour;
                stack[stack_size++] = dest;
            } else if(colours[dest] != new_colour)
                return 0;
            
            i++;
        }
    }

    return 1;    
}