#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
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

    typedef int (*BKK)(Session *,  char *path_to_config);
    typedef int (*BKKCheck)(Session *,  uint8_t * , uint64_t);

    typedef struct{
        int check;
        int proc_return;
        int incallreturn;
    } ResultCheck;

    ResultCheck* lets_check(char * config, char * filename){
        ResultCheck* returned=(ResultCheck*)malloc(sizeof(ResultCheck));
        returned->incallreturn=0;
        returned->proc_return=0;
        returned->check=0;
        printf("starting checking...!\n");
        void* handle = dlopen("./libcv.so", RTLD_NOW);
        if (!handle){
            printf("\nerror opened\n");
            returned->incallreturn=1;
            return returned;
        }
        printf("\nsucces open so\n");
        BKK load = (BKK)(dlsym(handle, "v_create_session"));
        if (!load)
        {
            printf("\nerror opened symbol\n");
            returned->incallreturn=2;
            return returned;
        }
        Session sess;
        sess.id="my_session";
        if (!load(&sess, config)){
            printf("\nerror create session\n");
            returned->incallreturn=3;
            return returned;
        }
        printf("create session succesfully!\n");
        uint8_t **content;
        uint8_t * direct;
        FILE *fd = fopen(filename, "rb");
        uint64_t *content_size;
        if (fd != NULL) {
            fseek(fd, 0L, SEEK_END);
            uint64_t size = ((size_t) ftell(fd) );
            printf("%d\n", size);
            content_size = & size;
            printf("sucess open\n");
            rewind(fd);
            uint8_t * pointer =(uint8_t *) calloc(1, (*content_size));
            direct = pointer;
            content = & pointer;
            printf("%d\n", pointer);
            fread((*content), (*content_size), 1, fd);
            fclose(fd);
            printf("sucess\n");
        }
        else{
            printf("bullshit in input!");
            returned->incallreturn=4;
            return returned;
        }
        BKKCheck v_check = (BKKCheck)(dlsym(handle,"v_check"));
        if (!v_check) {
            printf("\nCould not find symbol v_check\n");
            dlclose(handle);
            returned->incallreturn=4;
            return returned;
        }
        void * pointSession = &sess;
        printf("size = %d ",*content_size );
        if (!v_check(pointSession, direct, *content_size)){
            printf("\nFAILED!\n");
            returned->check=-1;
            return returned;
        }
        returned->check=0;
        returned->proc_return=sess.last_error;
        printf("error code= %d", sess.last_error);
        return returned;
    };
