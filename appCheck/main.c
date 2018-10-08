#include <stdio.h>
#include <stdlib.h>
#include <check.h>
#include <dlfcn.h>

int SummwPointers(int* i1, int* i2)
{
    return *i1 + *i2;
}

START_TEST(check_summwPointers)
{
    int a =7;
    int b =12;
    int * ap = &a;
    int * bp = &b;
    ck_assert_int_eq(19, SummwPointers(ap, bp));
}
END_TEST

START_TEST(lets_simplesumm_test)
{
    typedef int (*simpleSumm)( int , int);
    void* handle = dlopen("./1.so", RTLD_LAZY);
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

START_TEST(lets_simplesumm_test2)
{
    typedef int (*simpleSumm)( int , int);
    void* handle = dlopen("./1.so", RTLD_LAZY);
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

Suite * test(void)
{
    Suite *s;
    TCase *tc_core;
    s=suite_create("test case");

    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, lets_simplesumm_test );
    tcase_add_test(tc_core, lets_simplesumm_test2);
    tcase_add_test(tc_core, check_summwPointers);
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
