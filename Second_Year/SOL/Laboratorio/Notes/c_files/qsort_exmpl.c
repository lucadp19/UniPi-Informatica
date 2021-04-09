    #include <stdlib.h>

    int cmp_int(void* ptr1, void* ptr2){
        // casting both pointers to int* and then deferencing them to get the int value
        int n = *(int*)ptr1;
        int m = *(int*)ptr2;
        // n - m = 0 if they are equal, > 0 if n > m and < 0 otherwise, as requested
        return n - m;
    }
    int cmp_float(void* ptr1, void* ptr2){
        // casting both pointers to float* and then deferencing them to get the float value
        float x = *(float*)ptr1;
        float y = *(float*)ptr2;

        // x - y = 0 if they are equal, > 0 if x > y and < 0 otherwise, as requested
        return x - y;
    }

    int main(int argc, char* argv[]){
        int array_int[] = {2, 3, 1, 8, -4};
        float array_float[] = {3.14, 2.1828, -1.61};

        // sorting the two arrays with different types
        qsort(array_int, 5, sizeof(int), cmp_int);
        qsort(array_float, 3, sizeof(float), cmp_float);
    }