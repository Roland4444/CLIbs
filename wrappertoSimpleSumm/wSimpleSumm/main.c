#include <dlfcn.h>
typedef int (*SimpleSumm)( int , int);
int wSimpleSumm(int a, int b){
    void* handle = dlopen("./libsimpleSumm.so", RTLD_NOW);
    if (!handle){
        printf("\nerror opened\n");
        return -2;
    }
    printf("\nsucces open so\n");
    SimpleSumm load = (SimpleSumm)(dlsym(handle, "simpleSumm"));
    if (!load)
    {
        printf("\nerror opened symbol\n");
        return -3;
    }

    return load(a,b);
};
