#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main()
{
    int a =7;
    int b =12;
    assert(SummwPointers(&a, &b)==19);
    printf("must printed!");
}
int SummwPointers(int* i1, int* i2)
{
    return *i1 + *i2;
}

