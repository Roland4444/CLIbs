#include <stdio.h>
#include <stdlib.h>
#include <check.h>
#include <dlfcn.h>

int printChar(char * t){
    printf("%s", t);
    return strlen(t);
}

START_TEST(printchar){
    char t[] = "test";
    printf("Starting test char * t   Input==>%s\n" , t );
    printf("\n=====>>>>>%d\n", strlen(t));
    ck_assert_int_eq(4, printChar(t));
}
END_TEST

struct input{
    int a;
    int b;
};

int structSumm(struct input inp){
    return (inp.a) + (inp.b);
}

int structSummPointer(struct input* inp){
    return (inp->a) + (inp->b);
}

START_TEST(lets_check_summ_wPointer){
    printf("STRUCT SUMM via POINTER TEST");
    struct input a;
    a.a=12;
    a.b=24;
    struct input *pa=&a;
    ck_assert_int_eq(36, structSummPointer(pa));
}
END_TEST;

START_TEST(struct_simpletest){
    printf("SIMPLE STRUCT SUMM");
    struct input inp;
    inp.a=4;
    inp.b=6;
    ck_assert_int_eq(10, structSumm(inp));
}
END_TEST

int SummwPointers(int* i1, int* i2)
{
    return *i1 + *i2;
}

START_TEST(check_summwPointers)
{
    printf("RAW SUMM w POINTERS TEST\n");
    int a =7;
    int b =12;
    int * ap = &a;
    int * bp = &b;
    ck_assert_int_eq(19, SummwPointers(ap, bp));
}
END_TEST

START_TEST(lets_simplesumm_test)
{
    printf("SIMPLE SUMM TEST STARTED!!!\n");
    typedef int (*simpleSumm)( int , int);
    void* handle = dlopen("./libsimpleSumm.so", RTLD_LAZY);
    if (!handle){
        printf("\nerror opened\n");
        return -2;
    }
    printf("\nsucces open so\n");
    simpleSumm load = (simpleSumm)(dlsym(handle, "simpleSumm"));
    if (!load)
    {
        printf("\nerror opened symbol\n");
        return -3;
    }
    ck_assert_int_eq(load(3,3), 6 );
}
END_TEST

START_TEST(lets_summwPointers_test)
{
    printf("SUMM TEST WITH POINTERS STARTED!!!\n");
    typedef int (*SummwPointers)( int *, int *);
    void* handle = dlopen("./libsummwPointers.so", RTLD_LAZY);
    if (!handle){
        printf("\nerror opened\n");
        return -2;
    }
    printf("\nsucces open so\n");
    SummwPointers load = (SummwPointers)(dlsym(handle, "SummwPointers"));
    if (!load)
    {
        printf("\nerror opened symbol\n");
        return -3;
    }
    int a=3;
    int b=3;
    int * ap = &a;
    int * bp = &b;
    ck_assert_int_eq(load(ap,bp), 6 );
    printf("RESULT = %d\n", load(ap,bp));
}
END_TEST

START_TEST(lets_wrappedsummwPointers_test)
{
    printf("SUMM TEST WITH WRAPPED TO POINTERS STARTED!!!\n");
    typedef int (*wswP)( int *, int *);
    void* handle = dlopen("./libwrappedToPointers.so", RTLD_LAZY);
    if (!handle){
        printf("\nerror opened\n");
        return -2;
    }
    printf("\nsucces open so\n");
    wswP load = (wswP)(dlsym(handle, "wswP"));
    if (!load)
    {
        printf("\nerror opened symbol\n");
        return -3;
    }
    int a=3;
    int b=3;
    int * ap = &a;
    int * bp = &b;
    ck_assert_int_eq(load(ap,bp), 6 );
    printf("RESULT = %d\n", load(ap,bp));
}
END_TEST


START_TEST(lets_simpleStruct_test)
{
    struct input{
        int a;
        int b;
    };
    printf("##############3SUMM TEST WITH SIMPLE STRUCT!!!\n");
    typedef int (*structSumm)(struct input inp);
    void* handle = dlopen("./libsummStruct.so", RTLD_LAZY);
    if (!handle){
        printf("\nerror opened\n");
        return -2;
    }
    printf("\nsucces open so\n");
    structSumm load = (structSumm)(dlsym(handle, "structSumm"));

    ck_assert(load);
    struct input a;
    a.a=4;
    a.b=12;
    ck_assert_int_eq(load(a), 16 );
    printf("RESULT = %d\n", load(a));
}
END_TEST

START_TEST(lets_StructPointer_test)
{
    struct input{
        int a;
        int b;
    };
    printf("SUMM TEST WITH POINTER TO STRUCT!!!\n");
    typedef int (*structSummPointer)(struct input* inp);
    void* handle = dlopen("./libsummPointerStruct.so", RTLD_LAZY);
    if (!handle){
        printf("\nerror opened\n");
        return -2;
    }
    printf("\nsucces open so\n");
    structSummPointer load = (structSummPointer)(dlsym(handle, "structSummPointer"));

    ck_assert(load);
    struct input a;
    a.a=4;
    a.b=12;
    struct input *pa=&a;
    ck_assert_int_eq(16, load(pa));
    printf("RESULT = %d\n", load(pa));
}
END_TEST


START_TEST(lets_wStructPointer_test)
{
    struct input{
        int a;
        int b;
    };
    printf("WRAPPED SUMM TEST WITH POINTER TO STRUCT!!!\n");
    typedef int (*wstructSummPointer)(struct input* inp);
    void* handle = dlopen("./libwSummPointerStruct.so", RTLD_LAZY);
    if (!handle){
        printf("\nerror opened\n");
        return -2;
    }
    printf("\nsucces open so\n");
    wstructSummPointer load = (wstructSummPointer)(dlsym(handle, "wstructSummPointer"));

    ck_assert(load);
    struct input a;
    a.a=4;
    a.b=12;
    struct input *pa=&a;
    ck_assert_int_eq(16, load(pa));
    printf("RESULT = %d\n", load(pa));
}
END_TEST


START_TEST(lets_callprintChar_test)
{

    printf("PrintChar wrapped TEST T!!!\n");
    typedef int (*wprintChar)(char * inp);
    void* handle = dlopen("./libcallPrintChar.so", RTLD_LAZY);
    if (!handle){
        printf("\nerror opened\n");
        return -2;
    }
    printf("\nsucces open so\n");
    wprintChar load = (wprintChar)(dlsym(handle, "wprintChar"));

    ck_assert(load);
    char t[]="inputdata";
    ck_assert_int_eq(9, load(t));
    printf("\n\nLENGTHJ==%d\n\n", load(t));

}
END_TEST

Suite * test(void)
{
    Suite *s;
    TCase *tc_core;
    s=suite_create("test case");
    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, lets_simplesumm_test );
    tcase_add_test(tc_core, check_summwPointers);
    tcase_add_test(tc_core, lets_summwPointers_test);
    tcase_add_test(tc_core, lets_wrappedsummwPointers_test);
    tcase_add_test(tc_core, struct_simpletest);
    tcase_add_test(tc_core, lets_simpleStruct_test);
    tcase_add_test(tc_core, lets_check_summ_wPointer);
    tcase_add_test(tc_core, lets_StructPointer_test);
    tcase_add_test(tc_core, lets_wStructPointer_test);
    tcase_add_test(tc_core, printchar);
    tcase_add_test(tc_core, lets_callprintChar_test);
    suite_add_tcase(s, tc_core);
    return s;
}
int main()
{
    int numbert_failed;
    Suite *s;
    SRunner *sr;

    s = test();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    numbert_failed=srunner_ntests_failed(sr);
    srunner_free(sr);
    return (numbert_failed==0) ? EXIT_SUCCESS : EXIT_FAILURE;
    return 0;
}
