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
    int size;
} queue;


graph read_graph(int N);
void delete_graph(graph G, int N);
void print_graph(graph G, int N);

int* dfs(graph G, int N, int src);
void recursive_dfs(graph G, int src, int* colours);
void iterative_dfs(graph G, int N, int src, int* colours);

void queue_init(queue* Q, int capacity);
void queue_delete(queue* Q);
void queue_pushBack(queue* Q, int value);
int queue_popFront(queue* Q);
int queue_isEmpty(queue* Q);

int* bfs(graph G, int N, int src);

 
int main(){
    int N;
    graph G;

    scanf("%d", &N);
    G = read_graph(N);

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

void print_graph(graph G, int N){
    for(int i = 0; i < N; i++){
        printf("%d: ", i);
        for(int j = 0; j < G[i].degree; j++)
            printf("%d ", G[i].adj[j]);
        printf("\n");
    } printf("\n");
}

/* --- VISITS --- */

// DFS
int* dfs(graph G, int N, int src){
    int* colours = (int*) malloc(N * sizeof(int));
    for(int i = 0; i < N; i++) colours[i] = 0;

    colours[src] = 1;

    recursive_dfs(G, src, colours);
    // iterative_dfs(G, N, src, colours);

    return colours;
}

void recursive_dfs(graph G, int src, int* colours){
    int dest;

    for(int i = 0; i < G[src].degree; i++){
        dest = G[src].adj[i];
        if(colours[dest] == 0){
            colours[dest] = 1;
            recursive_dfs(G, dest, colours);
        }
    }
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

/* --- IMPLEMENTARE OPERAZIONI CODA --- */

// Assuming the queue isn't circular
void queue_init(queue* Q, int capacity){
    Q->capacity = capacity;
    Q->values = (int*) malloc(capacity * sizeof(int));
    Q->head = 0;
    Q->tail = 0;
}

void queue_delete(queue* Q){
    free(Q->values);
}

void queue_pushBack(queue* Q, int value){
    // it works iff the queue is not full
    Q->values[Q->tail++] = value;
}

int queue_popFront(queue* Q){
    // it works under the assumption that the queue is not empty
    int front = Q->values[Q->head++];
    return front;
}

int queue_isEmpty(queue* Q){
    return Q->head == Q->tail;
}


// BFS
int* bfs(graph G, int N, int src){
    int* colours = (int*) malloc(sizeof(int) * N);
    queue Q;
    int current, dest;

    for(int i = 0; i < N; i++) colours[i] = 0;
    colours[src] = 1;

    queue_init(&Q, N);
    queue_pushBack(&Q, src);

    while(!queue_isEmpty(&Q)){
        current = queue_popFront(&Q);
        for(int i = 0; i < G[current].degree; i++){
            dest = G[current].adj[i];
            if(colours[dest] == 0){
                colours[dest] = 1;
                queue_pushBack(&Q, dest);
            }
        }
    }

    queue_delete(&Q);
    return colours;
}