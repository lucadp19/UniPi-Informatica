#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int x;
    int y;
} point;

int cmp(const void* a, const void* b){
    point* p1 = (point*) a;
    point* p2 = (point*) b;

    if(p1->x == p2->x)
        return p2->y - p1->y;
    else
        return p1->x - p2->x;
}

int main(){
    int N;
    point* a;

    scanf("%d", &N);
    a = (point*) malloc(N*sizeof(point));

    for(int i = 0; i < N; i++){
        scanf("%d %d", &a[i].x, &a[i].y);
    }

    qsort(a, N, sizeof(point), cmp);

    for(int i = 0; i < N; i++)
        printf("%d %d\n", a[i].x, a[i].y);

    free(a);

    return 0;
}