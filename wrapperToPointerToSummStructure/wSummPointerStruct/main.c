#include <dlfcn.h>
typedef int (*structSummPointer)(struct input* inp);
int wstructSummPointer(struct input* inp){
    void* handle = dlopen("./libsummPointerStruct.so", RTLD_LAZY);
    if (!handle){
        printf("\nerror opened\n");
        return -2;
    }
    printf("\nsucces open so\n");
    structSummPointer load = (structSummPointer)(dlsym(handle, "structSummPointer"));
    if (!load)
    {
        printf("\nerror opened symbol\n");
        return -3;
    }
    return load(inp);
}
