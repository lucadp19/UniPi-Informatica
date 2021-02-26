#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

// Debugging macro
#ifdef DEBUG
#define dbgprint(...) \
    _debug_printf(__FILE__, __LINE__, __VA_ARGS__)

int _debug_printf(const char* file, const int line, const char* fmt, ...){
    va_list argp;
    va_start (argp, fmt);

    fprintf(stderr, ">>> DBG: [%s : %d]\n", file, line);
    vfprintf(stderr, fmt, argp);
    fprintf(stderr, "<<<\n");

    va_end(argp);
    return 0;
}

#elif
#define dbgprint(...)

#endif