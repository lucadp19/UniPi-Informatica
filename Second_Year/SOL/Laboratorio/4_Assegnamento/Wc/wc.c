#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <getopt.h>
#include "../Utils/utils.h"

#define PRINT_WC(n, w, b, file) do { \
        if(no_flag) \
            printf("%4d %4d %4d ", n, w, b); \
        else {  \
            if(l_flag == 1) \
                printf("%4d ", n);  \
            if(w_flag == 1) \
                printf("%4d ", w);  \
        } \
        printf("%s\n", (file == NULL) ? "" : file); \
    } while(0)

void wc(int* newlines, int* words, int* bytes, const char* file_name);

int main(int argc, char* argv[]){
    int no_flag = 1;
    int w_flag = 0;
    int l_flag = 0;

    int opt;
    while ((opt = getopt(argc, argv, "wl")) != -1){
        switch (opt) {
        case 'w':
            no_flag = 0;
            w_flag = 1;
            break;
        case 'l':
            no_flag = 0;
            l_flag = 1;
            break;
        case '?':
            fprintf(stderr, "Option \"%c\" not recognized.", optopt);
            return -1;
        }
    }

    // Total
    int total_words = 0;
    int total_newlines = 0;
    int total_bytes = 0;

    // Single-file count
    int words, newlines, bytes;

    // Number of files
    int nfiles = (argc - optind);
    
    // If zero files are passed, read from stdin
    if(nfiles == 0){
        wc(&newlines, &words, &bytes, NULL);
        PRINT_WC(newlines, words, bytes, NULL);
    }

    // Exec wc for every file passed
    for(int i = optind; i < argc; i++){
        wc(&newlines, &words, &bytes, argv[i]);
        total_newlines += newlines;
        total_words += words;
        total_bytes += bytes;

        PRINT_WC(newlines, words, bytes, argv[i]);
    }

    // If more than one file, print total
    if(nfiles > 1)
        PRINT_WC(total_newlines, total_words, total_bytes, "total");

    return 0;
}

void wc(int* newlines, int* words, int* bytes, const char* file_name){
    *newlines = 0;
    *words = 0;
    *bytes = 0;

    FILE *input;
    if(file_name == NULL) input = stdin;
    else FOPEN_ERR(input, file_name, "r");

    int is_word = 0;
    char c;
    while((c = fgetc(input)) != EOF){
        (*bytes)++;
        // found a non-space character after a space
        //      => new word
        if(!isspace(c) && !is_word){
            is_word = 1;
            (*words)++;
        }
        // found a space after a word
        if(isspace(c) && is_word)
            is_word = 0;
        // found a newline
        if(c == '\n')
            (*newlines)++;
    }

    if(file_name != NULL) fclose(input);
}