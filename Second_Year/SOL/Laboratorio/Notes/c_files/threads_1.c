    #include <pthread.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include <unistd.h> 

    static int x; // shared variable

    static void* myfun (void* arg){
        while (true) {
            printf("Second thread: x = %d\n", ++x);
            sleep(1); 
        }
    }

    int main(){
        pthread_t tid;
        int err;

        if( (err = pthread_create(&tid, NULL, &myfun, NULL)) != 0 ) {
            // dealing with errors
            perror("thread");
            exit(EXIT_FAILURE);
        } else { // second thread has been created
            while (true){
                printf("First thread: x = %d\n", ++x);
                sleep(1);
            }
        }

        return 0;
    }