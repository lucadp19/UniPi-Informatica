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

int main(){
    int N, M;
    point* points;
    int rx_sx, rx_dx, ry_sx, ry_dx;

    scanf("%d %d", &N, &M);
    points = (point*) malloc(N*sizeof(point));

    for(int i = 0; i < N; i++)
        scanf("%d %d %d", &points[i].x, &points[i].y, &points[i].colour);

    qsort(points, N, sizeof(point), order_by_x);

    for(int k = 0; k < M; k++){
        int x_sx, x_dx, y_sx, y_dx, count;
        scanf("%d %d %d %d", &rx_sx, &ry_sx, &rx_dx, &ry_dx);

        // printf("rx_sx: %d; rx_dx: %d\n", rx_sx, rx_dx);
        if(rx_sx > points[N-1].x || rx_dx < points[0].x){
            // printf("ESCO A 1: ");
            printf("0\n");
            // printf("\n\n");
            continue;
        }
        
        x_sx = 0;
        x_dx = N-1;
        while(x_sx < N && points[x_sx].x < rx_sx) x_sx++;
        while(x_dx >= x_sx && points[x_dx].x > rx_dx) x_dx--;
        
        // printf("x_sx: %d; x_dx: %d\n", x_sx, x_dx);
        // printf("ORIGINAL ORDER: \n");
        // for(int i = 0; i < N; i++)
            // printf("%d: %d %d %d\n", i, points[i].x, points[i].y, points[i].colour);
        if(x_dx < x_sx){
            // printf("ESCO A 2: ");
            printf("0\n");
            // printf("\n\n");
            continue;
        }
        

        qsort(points+x_sx, x_dx - x_sx + 1, sizeof(point), order_by_y);

        // printf("ry_sx: %d; ry_dx: %d\n", ry_sx, ry_dx);
        if(ry_sx > points[x_dx].y || ry_dx < points[x_sx].y){
            // printf("ESCO A 3: ");
            printf("0\n");
            qsort(points+x_sx, x_dx - x_sx + 1, sizeof(point), order_by_x);
            // printf("\n\n");
            continue;
        }

        
        y_sx = x_sx;
        y_dx = x_dx;
        while(y_sx <= x_dx && points[y_sx].y < ry_sx) y_sx++;
        while(y_dx >= y_sx && points[y_dx].y > ry_dx) y_dx--;
        // printf("y_sx: %d; y_dx: %d\n", y_sx, y_dx); 
        // printf("ORDERED BY Y: \n");
        // for(int i = 0; i < N; i++)
            // printf("%d: %d %d %d\n", i, points[i].x, points[i].y, points[i].colour);
        if(y_dx < y_sx){
            // printf("ESCO A 4: ");
            printf("0\n");
            qsort(points+x_sx, x_dx - x_sx + 1, sizeof(point), order_by_x);
            // printf("\n\n");
            continue;
        }

        qsort(points+y_sx, y_dx - y_sx + 1, sizeof(point), order_by_colour);

        // printf("ORDERED BY COLOUR: \n");
        // for(int i = 0; i < N; i++)
            // printf("%d: %d %d %d\n", i, points[i].x, points[i].y, points[i].colour);

        count = 1;
        for(int i = y_sx+1; i <= y_dx; i++){
            if(points[i].colour != points[i-1].colour)
                count++;
        }

        // printf("COUNT!: ");
        // printf("ESCO A 5: ");
        printf("%d\n", count);
        qsort(points+x_sx, x_dx - x_sx + 1, sizeof(point), order_by_x);
        // printf("\n\n");        
    }
    return 0;
}