#include <stdlib.h>
#include <stdio.h>
extern "C"
{
    // A function adding two integers and returning the result
    const char * letsprintCharPtr(const char * input){
        printf("%s", input);
        return input;
    }
}
