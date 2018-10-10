#include <stdio.h>
#include <stdlib.h>
#include <check.h>
#include <dlfcn.h>
const char * bad_item ="./EE45AEAAD1A31B1B1A45F4B38C98BE62893E590A47C1166061B0B1C52163531C.wav";
const char * good_item ="./web_logitech_back_65-dB.wav";
const char * config= "./cv_configuration.json";
const char * badConfig= "./cv_configuration.json0000";
const char * wav5= "./5.wav";
const char * longfile = "./a2002011001_e02_16kHz.wav";

int printInt(int a){
    printf("%d", a);
    return a;
}

typedef struct{
        int check;
        int proc_return;
        int incallreturn;
} ResultCheck;

typedef struct{
    int major;
    int minor;
    int build;
} Version;

typedef struct{
    Version version;
    char *id;
    void *payment;
    int last_error;
} Session;

typedef struct {
    int result;
    int error_code;
} simpleResult;

typedef struct {
    int a;
    int b;
} input;

typedef struct {
    char  t[400];
    int result;
} result;

simpleResult* getSummInPointer(input* input){
    simpleResult res;
    simpleResult* pres;
    res.result = (input -> a) + (input -> b);
    res.error_code =0;
    simpleResult *p = &res;
    printf("\n\nRESULT=%d\n\n", p->result);
    printf("\n\nERROR=%d\n\n", p->error_code);
    pres = &res;
    return pres;
};

result summStructReturn(input *inp){
    result rrr;
    rrr.result = (inp -> a) + (inp -> b);
    strcpy(rrr.t, "OK");
    return rrr;
};


START_TEST(interop_test){
    printf("\n\nTEST Interop\n\n");
    typedef ResultCheck* (*lets_check)(char*  , char *);
    void* handle = dlopen("./libCHF_EBS.so", RTLD_LAZY);
    ck_assert(handle);
    printf("\nsucces open so\n");
    lets_check load = (lets_check)(dlsym(handle, "lets_check"));
    ck_assert(load);

    printf("\n\nBAD ITEM MUST FAILED CHECK!!!\n\n");
    ResultCheck* resPtr=load(config, bad_item);
    printResult(resPtr);
    ck_assert_uint_eq(resPtr->incallreturn,0);
    ck_assert_uint_ne(resPtr->check,0);

    printf("\n\nGOOD ITEM MUST PASSED CHECK!!!\n\n");
    resPtr=load(config, longfile);
    printResult(resPtr);
    ck_assert_uint_eq(resPtr->incallreturn,0);
    ck_assert_uint_eq(resPtr->check,0);
}
END_TEST

START_TEST(interop_test_GBP){
    printf("\n\nTEST Interop GBP!!!\n\n");
    typedef ResultCheck* (*lets_check)(char*  , char *);
    void* handle = dlopen("./libGBP_EBS.so", RTLD_LAZY);
    ck_assert(handle);
    printf("\nsucces open so\n");
    lets_check load = (lets_check)(dlsym(handle, "lets_check"));
    ck_assert(load);

    printf("\n\nBAD ITEM MUST FAILED CHECK!!!\n\n");
    ResultCheck* resPtr=load(config, bad_item);
    printResult(resPtr);
    ck_assert_uint_eq(resPtr->incallreturn,0);
    ck_assert_uint_ne(resPtr->check,0);

    printf("\n\nGOOD ITEM MUST PASSED CHECK!!!\n\n");
    resPtr=load(config, longfile);
    printResult(resPtr);
    ck_assert_uint_eq(resPtr->incallreturn,0);
    ck_assert_uint_eq(resPtr->check,0);
}
END_TEST

void printResult(ResultCheck* ptr){
    printf("\nCHECK=%d\n", ptr->check);
    printf("\nIN CALL RETURN=%d\n", ptr->incallreturn);
    printf("\nPROC RETURN=%d\n", ptr->proc_return);
};


START_TEST(libcv_init_and_test){
    printf("LIBCV INIT TEST!!!");
    Session * session = (Session*)malloc(sizeof(Session));
    char * config = "./cv_configuration.json";
    typedef int (*v_create_session)(struct Session*  , char *);
    void* handle = dlopen("./libcv.so", RTLD_LAZY);
    ck_assert(handle);
    printf("\nsucces open so\n");
    v_create_session load = (v_create_session)(dlsym(handle, "v_create_session"));
    ck_assert(load);
    ck_assert_uint_gt(load(session, config),0);
}
END_TEST

START_TEST(io_viaStructPointersStructure){
    printf("\n\nTESTING CPP SO\n\n");
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
    Input input_str=(input*)malloc(sizeof(inputStruct));
    input_str->a=4;
    input_str->b=8;

    typedef Result (*letsSumm)(Input);
    void* handle = dlopen("./libsimpleSo.so", RTLD_LAZY);
    if (!handle){
        printf("\nerror opened\n");
        return -2;
    }
    printf("\nsucces open so\n");
    letsSumm load = (letsSumm)(dlsym(handle, "letsSumm"));
    ck_assert(load);

    resultStruct* r = load(input_str);
    ck_assert_int_eq(12, r->result);
}
END_TEST

int printChar(char * t){
    printf("%s", t);
    return strlen(t);
}

START_TEST(structresultTest){
    printf("\n\nTesting RESULT SUMM IN STRUCTURE!!!\n\n");
    input a ;
    input *ap = &a;
    result resss;
    a.a=12;
    a.b=14;
    resss = summStructReturn(ap);
    ck_assert_int_eq(26, resss.result);
    printf("\n%s\n", resss.t);
}
END_TEST

START_TEST(printIntOnly){
    printf("\n\nPRINTING SIMPLE INT  ==>!!\n\n");
    int a = 5;
    ck_assert_int_eq(5, printInt(a) );

}
END_TEST

START_TEST(printchar){
    char t[] = "test";
    printf("Starting test char * t   Input==>%s\n" , t );
    printf("\n=====>>>>>%d\n", strlen(t));
    ck_assert_int_eq(4, printChar(t));
}
END_TEST


int structSumm(input inp){
    return (inp.a) + (inp.b);
}

int structSummPointer(input* inp){
    return (inp->a) + (inp->b);
}

START_TEST(lets_check_summ_wPointer){
    printf("STRUCT SUMM via POINTER TEST");
    input a;
    a.a=12;
    a.b=24;
    input *pa=&a;
    ck_assert_int_eq(36, structSummPointer(pa));
}
END_TEST;

START_TEST(struct_simpletest){
    printf("SIMPLE STRUCT SUMM");
    input inp;
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


START_TEST(lets_printchars)
{
    printf("PRINT CHARS\n");
    typedef const char* (*letsprintCharPtr)(const char *);
    void* handle = dlopen("./libletsprintCharPtr.so", RTLD_LAZY);
    ck_assert(handle);
    printf("\nsucces open so\n\n\n\n");
    letsprintCharPtr load = (letsprintCharPtr)(dlsym(handle, "letsprintCharPtr"));
    ck_assert(load);
    const char * text = "some text";
    printf("OUTNEXT=>>\n\n");
    load(text);
    printf("\nOUT FINISHED!!\n\n");
    printf("%s", load(text));

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
    tcase_add_test(tc_core, structresultTest);
    tcase_add_test(tc_core, printIntOnly);
    tcase_add_test(tc_core, io_viaStructPointersStructure);
    tcase_add_test(tc_core, lets_printchars);
    tcase_add_test(tc_core, libcv_init_and_test);
    tcase_add_test(tc_core, interop_test);
    tcase_add_test(tc_core, interop_test_GBP);
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
