    #include <pthread.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include <unistd.h> 

    static int x; // shared variable
    pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

    static void* myfun (void* arg){
        pthraed_mutex_lock(&mtx);
        pthread_cond_wait(&cond, &mtx);
        pthread_mutex_unlock(&mtx);

        while (true) {
            atomic_incr_x(1);
            sleep(1); 
        }
    }

    static int atomic_incr_x(int incr){
        static int x = 0;
        int res;

        pthread_mutex_lock(&mtx);
        res = (x += incr);
        pthread_mutex_unlock(&mtx);

        return res;
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
                atomic_incr_x(1);
                sleep(1);
            }
        }

        return 0;
    }
