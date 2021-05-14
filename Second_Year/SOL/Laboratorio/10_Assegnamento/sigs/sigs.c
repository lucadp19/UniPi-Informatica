#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <unistd.h>
#include <signal.h>

#include "lib.h"

volatile sig_atomic_t count = 0;
volatile sig_atomic_t stop = 0;
volatile sig_atomic_t stop_count = 0;

void sigtstp_handler(int signum){
    stop = 1;
    stop_count++;
}

void sigint_handler(int signum){
    count++;
}

int main(){
    char ans;
    struct sigaction s_int;
    struct sigaction s_tstp;
    memset(&s_int, 0, sizeof(s_int));
    memset(&s_tstp, 0, sizeof(s_tstp));
    
    s_int.sa_handler = sigint_handler;
    s_tstp.sa_handler = sigtstp_handler;

    CHECK_NOT_EQ( sigaction(SIGINT, &s_int, NULL), -1, "Error while setting SIGINT handler");
    CHECK_NOT_EQ( sigaction(SIGTSTP, &s_tstp, NULL), -1, "Error while setting SIGTSTP handler");

    while(true){
        if(stop == 1){
            printf("\nNumber of SIGINTs till now: %d\n", count);
            stop = 0;
            if(stop_count >= 3){
                alarm(10);
                printf("Do you want to keep going? (y/n): ");
                scanf(" %c", &ans);
                if(ans == 'y') alarm(0);
                else exit(EXIT_SUCCESS);
            }
        }
    }

}