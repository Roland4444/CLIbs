#ifndef EXPORT_INCLUDED
#define EXPORT_INCLUDED
#include <stdint.h>

typedef struct {
    uint32_t a;
    uint32_t b;
} inputStruct;

typedef struct{
    uint32_t result;
    uint32_t error;
} resultStruct;

typedef resultStruct* Result;
typedef inputStruct* Input;

Result letsSumm(Input flow);

#endif // EXPORT_INCLUDED
