#include <dlfcn.h>
typedef int (*printChar)(char * t);
int wprintChar(char * inp){
    void* handle = dlopen("./libprintChar.so", RTLD_LAZY);
    if (!handle){
        printf("\nerror opened\n");
        return -2;
    }
    printf("\nsucces open so\n");
    printChar load = (printChar)(dlsym(handle, "printChar"));
    if (!load)
    {
        printf("\nerror opened symbol\n");
        return -3;
    }
    return load(inp);
}
