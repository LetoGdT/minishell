#include <stdio.h>
#include <execinfo.h>
#include <stdio.h>
void* __callstack[128];
int __i, __frames;
char** __strs;
void *__addr;
#define malloc(X) (__addr = malloc(X)); \
                printf("MALLOCED %p\n", __addr); \
                printf("%s:%d\n", __FILE__, __LINE__); \
                __frames = backtrace(__callstack, 128); \
                __strs = backtrace_symbols(__callstack, __frames); \
                for (__i = 0; __i < __frames; ++__i) { \
                    printf("%s\n", __strs[__i]); \
                } \
                free(__strs);