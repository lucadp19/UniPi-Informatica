#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
    int colour;
} point;

int order_by_x(const void* p, const void* q){
    return ((point*) p)->x - ((point*) q)->x;
}

int order_by_y(const void* p, const void* q){
    return ((point*) p)->y - ((point*) q)->y;
}

int order_by_colour(const void* p, const void* q){
    return ((point*) p)->colour - ((point*) q)->colour;
}

int is_inbetween(int x, int a, int b){
    // assumption: a < b
    return  ((x >= a) && (x <= b));
}

int main(){
    int N, M;
    point* points;
    int rx_sx, rx_dx, ry_sx, ry_dx, count, already_counted;

    scanf("%d %d", &N, &M);
    points = (point*) malloc(N*sizeof(point));

    for(int i = 0; i < N; i++)
        scanf("%d %d %d", &points[i].x, &points[i].y, &points[i].colour);

    qsort(points, N, sizeof(point), order_by_colour);

    for(int k = 0; k < M; k++){
        scanf("%d %d %d %d", &rx_sx, &ry_sx, &rx_dx, &ry_dx);

        if(is_inbetween(points[0].x, rx_sx, rx_dx) && is_inbetween(points[0].y, ry_sx, ry_dx)){
            count = 1; 
            already_counted = 1;
        } else {
            count = 0; 
            already_counted = 0;
        }

        for(int i = 1; i < N; i++){
            if(points[i].colour != points[i-1].colour)
                already_counted = 0;
            
            if(!already_counted && is_inbetween(points[i].x, rx_sx, rx_dx) && is_inbetween(points[i].y, ry_sx, ry_dx)){
                already_counted = 1;
                count++;
            }
        }
        
        printf("%d\n", count);
    }
    return 0;
}