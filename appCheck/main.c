#include <stdio.h>
#include <stdlib.h>
#include <check.h>
#include <dlfcn.h>

struct input{
    int a;
    int b;
};

int structSumm(struct input inp){
    return (inp.a) + (inp.b);
}

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
