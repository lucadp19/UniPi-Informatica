#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


long isNumber(const char* s);
void print_help(const char* file_name);

int main(int argc, char *argv[]){
    int n_flag = 0;
    int m_flag = 0;
    int o_flag = 0;

    int n_val = -1;
    int m_val = -1;
    char* o_val = NULL;

    int opt;

    while((opt = getopt(argc, argv, "n:m:o:h")) != -1) {
        switch(opt){
            case 'n':
                if(n_flag){
                    fprintf(stderr, "Option \"-n\" is set twice.\n");
                    return -1;
                }
                else if((n_val = isNumber(optarg)) == -1){
                    fprintf(stderr, "Option \"-n\" must be followed by a number.\n");
                    return -1;
                }
                n_flag = 1;
                break;
            case 'm':
                if(m_flag){
                    fprintf(stderr, "Option \"-m\" is set twice.\n");
                    return -1;
                }
                else if((m_val = isNumber(optarg)) == -1){
                    fprintf(stderr, "Option \"-m\" must be followed by a number.\n");
                    return -1;
                }
                m_flag = 1;
                break;
            case 'o':
                if(o_flag){
                    fprintf(stderr, "Option \"-o\" is set twice.\n");
                    return -1;
                }
                o_flag = 1;
                o_val = optarg;
                break;
            case 'h':
                print_help(argv[0]);
                return 0;
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
                        fprintf(stderr, "Unknown option \"-%c\".\n");
                }
        }
    }
    
    if(n_flag) printf("-n %d ", n_val);
    if(m_flag) printf("-m %d ", m_val);
    if(o_flag) printf("-o %s ", o_val);

    if(n_flag || m_flag || o_flag) printf("\n");

    return 0;
}

long isNumber(const char* s) {
    char* e = NULL;
    long val = strtol(s, &e, 0);
    if (e != NULL && *e == (char)0) 
        return val; 
    return -1;
}

void print_help(const char* file_name){
    printf("%s -n <numero> -s <stringa> -m <numero> -h\n", file_name);
}