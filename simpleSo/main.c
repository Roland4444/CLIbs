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

    int summ(int i1, int i2)
    {
        return i1 + i2;
    }

    Result letsSumm(Input flow){
        Result res= (Result)malloc(sizeof(resultStruct));
        res-> error = 0;
        res->result = (flow->a) + (flow->b);
        return res;
    }
