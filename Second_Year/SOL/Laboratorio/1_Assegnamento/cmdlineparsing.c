#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long isNumber(const char* s);
void print_help();
int is_prefix(const char* a, const char* b, size_t len);

int main(int argc, char* argv[]){
    if(argc == 1) return 0;
    int i = 1;
 
    int rec_n = 0;
    int n_num = 0;

    int rec_m = 0;
    int m_num = 0;

    int rec_s = 0;
    char* s_str = NULL;

    while(i < argc){
        // printf("argv[%d] = %s\n", i, argv[i]);

        // -n option
        if(is_prefix("-n", argv[i], 2)){
            // printf("matched -n\n");

            if(rec_n == 1) {
                printf("-n option was set twice.\n");
                return -1;
            }

            rec_n = 1;
            // -n then space
            if(argv[i][2] == '\0'){
                if(i + 1 < argc){
                    n_num = isNumber(argv[i+1]);
                    if(n_num == -1){
                        printf("-n must be followed by a number\n");
                        return -1;
                    } else {
                        i += 2;
                        continue;
                    }
                } else {
                    printf("-n must be followed by a number.\n");
                    return -1;
                }
            } 
            // -n without space
            else {
                n_num = isNumber(argv[i] + 2);
                if(n_num == -1){
                    printf("-n must be followed by a number.\n");
                    return -1;
                } else {
                    i++;
                    continue;
                }
            }
        }
        
        // -m option
        if(is_prefix("-m", argv[i], 2)){
            // printf("matched -m\n");

            if(rec_m == 1) {
                printf("-m option was set twice.\n");
                return -1;
            }

            rec_m = 1;
            // -m then space
            if(argv[i][2] == '\0'){
                if(i + 1 < argc){
                    m_num = isNumber(argv[i+1]);
                    if(m_num == -1){
                        printf("-m must be followed by a number.\n");
                        return -1;
                    } else {
                        i += 2;
                        continue;
                    }
                } else {
                    printf("-m must be followed by a number.\n");
                    return -1;
                }
            } 
            // -m without space
            else {
                m_num = isNumber(argv[i] + 2);
                // printf("%s", argv[i]+2);
                if(m_num == -1){
                    printf("-m must be followed by a number.\n");
                    return -1;
                } else { 
                    i++; 
                    continue;
                }
            }
        }

        // -s option
        if(is_prefix("-s", argv[i], 2)){
            // printf("matched -s\n");

            if(rec_s == 1) {
                printf("-s option was set twice.\n");
                return -1;
            }

            rec_s = 1;
            // -m then space
            if(argv[i][2] == '\0'){
                if(i + 1 < argc){
                    s_str = argv[i+1];
                    i += 2;
                    continue;
                } else {
                    printf("-s must be followed by a string.\n");
                    return -1;
                }
            } 
            // -s without space
            else {
                s_str = argv[i] + 2;
                i++;
                continue;
            }
        }
        
        // -h option
        if(is_prefix("-h", argv[i], 2)){
            // printf("matched -h\n");
            print_help();
            return 0;
        }

        // unknown option
        if(is_prefix("-", argv[i], 1)){
            if (argv[i][1] == '\0')
                printf("a single - is an unrecognized option.\n");
            else
                printf("option -%c is not recognized.\n", argv[i][1]);
            return -1;
        }
    }

    if(rec_n) printf("-n %d ", n_num);
    if(rec_m) printf("-m %d ", m_num);
    if(rec_s) printf("-s %s ", s_str);

    if(rec_n || rec_m || rec_s) printf("\n");
    return 0;
}

void print_help(){
    printf("cmdlineparsing -n <numero> -s <stringa> -m <numero> -h\n");
}

int is_prefix(const char* a, const char* b, size_t len){
    return strncmp(a, b, len) == 0 ? 1 : 0;
}

long isNumber(const char* s) {
    char* e = NULL;
    long val = strtol(s, &e, 0);
    if (e != NULL && *e == (char)0) 
        return val; 
    return -1;
}