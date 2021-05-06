    #include <pthread.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include <unistd.h> 

    static int x; // shared variable
    pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

    static void* myfun (void* arg){
        while (true) {

            pthread_mutex_lock(&mtx);
            printf("Second thread: x = %d\n", ++x);
            pthread_mutex_unlock(&mtx);

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
                pthread_mutex_lock(&mtx);
                printf("First thread: x = %d\n", ++x);
                pthread_mutex_unlock(&mtx);

                sleep(1);
            }
        }

        return 0;
    }