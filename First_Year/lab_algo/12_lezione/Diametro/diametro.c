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

void queue_init(queue* Q, int capacity);
void queue_delete(queue* Q);
void queue_pushBack(queue* Q, int value);
int queue_popFront(queue* Q);
int queue_isEmpty(queue* Q);

int diameter(graph G, int N);
int* bfs(graph G, int N, int src);

int main(){
    int N;
    graph G;

    scanf("%d", &N);
    G = read_graph(N);

    printf("%d\n", diameter(G, N));

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

/* --- IMPLEMENTARE OPERAZIONI CODA --- */

void queue_init(queue* Q, int capacity){
    Q->capacity = capacity;
    Q->values = (int*) malloc(capacity * sizeof(int));
    Q->head = 0;
    Q->tail = -1;
    Q->size = 0;
}

void queue_delete(queue* Q){
    free(Q->values);
}

void queue_pushBack(queue* Q, int value){
    // it works iff the queue is not full
    if(Q->size < Q->capacity){
        Q->tail = (Q->tail + 1) % Q->capacity;
        Q->values[Q->tail] = value;
        Q->size++;
    }
}

int queue_popFront(queue* Q){
    // it works under the assumption that the queue is not empty
    int front = Q->values[Q->head];
    Q->head = (Q->head + 1) % Q->capacity;
    Q->size--;
    return front;
}

int queue_isEmpty(queue* Q){
    return Q->size == 0;
}


// BFS
int* distance_bfs(graph G, int N, int src){
    int* distance = (int*) malloc(sizeof(int) * N);
    queue Q;
    int current, dest;

    for(int i = 0; i < N; i++) distance[i] = -1;
    distance[src] = 0;

    queue_init(&Q, N);
    queue_pushBack(&Q, src);

    while(!queue_isEmpty(&Q)){
        current = queue_popFront(&Q);
        for(int i = 0; i < G[current].degree; i++){
            dest = G[current].adj[i];
            if(distance[dest] == -1){
                distance[dest] = 1 + distance[current];
                queue_pushBack(&Q, dest);
            }
        }
    }

    queue_delete(&Q);
    return distance;
}

int diameter(graph G, int N){
    int d = 0;
    int i = 0;
    int j = 0;
    int* dist;

    while(i < N){
        dist = distance_bfs(G, N, i);

        // printf("%d: ", i);
        // for(int k = 0; k < N; k++)
        //     printf("%d ", dist[k]);
        // printf("\n");

        j = 0;
        while(j < N){
            if(dist[j] == -1){
                free(dist);
                return -1;
            } else if (dist[j] > d)
                d = dist[j];
            
            j++;
        }

        i++;
        free(dist);
    }

    return d;
}