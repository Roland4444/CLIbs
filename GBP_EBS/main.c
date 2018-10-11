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
    typedef int (*v_check)(Session *,  uint8_t * , uint64_t);

    typedef struct{
        int checkResult;
        int lastErrorInSession;
        int ResultLoadingSoSymbols;
    } ResultCheck;

    ResultCheck* lets_check(char * config, char * filename){
        ResultCheck* returned=(ResultCheck*)malloc(sizeof(ResultCheck));
        returned->ResultLoadingSoSymbols=0;
        returned->lastErrorInSession=0;
        returned->checkResult=0;
        void* handle = dlopen("./libcv.so", RTLD_NOW);
        if (!handle){
            returned->ResultLoadingSoSymbols=1;
            return returned;
        }
        BKK load_ = (BKK)(dlsym(handle, "v_create_session"));
        if (!load_)
        {
            returned->ResultLoadingSoSymbols=2;
            return returned;
        }
        Session sess;
        sess.id="my_session";
        if (!load_(&sess, config)){
            returned->ResultLoadingSoSymbols=3;
            return returned;
        }
        uint8_t **content;
        uint8_t * direct;
        FILE *fd = fopen(filename, "rb");
        uint64_t *content_size;
        if (fd != NULL) {
            fseek(fd, 0L, SEEK_END);
            uint64_t size = ((size_t) ftell(fd) );
            content_size = & size;
            rewind(fd);
            uint8_t * pointer =(uint8_t *) calloc(1, (*content_size));
            direct = pointer;
            content = & pointer;
            fread((*content), (*content_size), 1, fd);
            fclose(fd);
        }
        else{
            returned->ResultLoadingSoSymbols=4;
            return returned;
        }
        v_check load = (v_check)(dlsym(handle,"v_check"));
        if (!load) {
            dlclose(handle);
            returned->ResultLoadingSoSymbols=5;
            return returned;
        }
        Session * pointSession = &sess;
        if (!load(pointSession, direct, *content_size)){
            returned->checkResult=-1;
            return returned;
        }
        returned->lastErrorInSession=sess.last_error;
        return returned;
    };
