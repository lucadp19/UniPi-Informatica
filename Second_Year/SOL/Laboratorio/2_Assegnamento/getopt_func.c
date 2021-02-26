#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

long isNumber(const char* s);

int arg_h(const char* file_name);
int arg_n(const char* arg);
int arg_m(const char* arg);
int arg_o(const char* arg);

int n_flag = 0;
int m_flag = 0;
int o_flag = 0;

int main(int argc, char *argv[]){
    int (*V[4]) (const char*) = {arg_h, arg_m, arg_n, arg_o};

    int opt;

    while((opt = getopt(argc, argv, "n:m:o:h")) != -1) {
        switch(opt){
            case '?':
                switch(optopt){
                    case 'n':
                        fprintf(stderr, "Option \"-n\" must be followed by a number.\n");
                        return -1;
                    case 'm':
                        fprintf(stderr, "Option \"-m\" must be followed by a number.\n");
                        return -1;
                    case 'o':
                        fprintf(stderr, "Option \"-o\" must be followed by a string.\n");
                        return -1;
                    default:
                        fprintf(stderr, "Unknown option \"-%c\".\n", optopt);
                }
            default:
                if(V[opt%4]( (optarg == NULL ? argv[0] : optarg) ) == -1){
                    fprintf(stderr, "Found error in argument: aborting.\n");
                    return -1;
                }
        }
    }

    return 0;
}

long isNumber(const char* s) {
    char* e = NULL;
    long val = strtol(s, &e, 0);
    if (e != NULL && *e == (char)0) 
        return val; 
    return -1;
}

int arg_h(const char* file_name){
    printf("%s -n <numero> -s <stringa> -m <numero> -h\n", file_name);
    return 0;
}

int arg_n(const char* arg){
    int n_val;

    if(n_flag){
        fprintf(stderr, "Option \"-n\" is set twice.\n");
        return -1;
    }
    else if((n_val = isNumber(arg)) == -1){
        fprintf(stderr, "Option \"-n\" must be followed by a number.\n");
        return -1;
    }

    n_flag = 1;
    printf("-n %d\n", n_val);

    return 0;
}

int arg_m(const char* arg){
    int m_val;

    if(m_flag){
        fprintf(stderr, "Option \"-m\" is set twice.\n");
        return -1;
    }
    else if((m_val = isNumber(arg)) == -1){
        fprintf(stderr, "Option \"-m\" must be followed by a number.\n");
        return -1;
    }

    m_flag = 1;
    printf("-m %d\n", m_val);

    return 0;
}

int arg_o(const char* arg){
    if(o_flag){
        fprintf(stderr, "Option \"-o\" is set twice.\n");
        return -1;
    }

    o_flag = 1;
    printf("-o %s", arg);

    return 0;
}