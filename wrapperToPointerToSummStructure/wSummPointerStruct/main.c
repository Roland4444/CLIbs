// The functions contained in this file are pretty dummy
// and are included only as a placeholder. Nevertheless,
// they *will* get included in the shared library if you
// don't remove them :)
//
// Obviously, you 'll have to write yourself the super-duper
// functions to include in the resulting library...
// Also, it's not necessary to write every function in this file.
// Feel free to add more files in this project. They will be
// included in the resulting library.

// A function adding two integers and returning the result
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
