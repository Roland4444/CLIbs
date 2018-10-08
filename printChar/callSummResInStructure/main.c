struct input{
    int a;
    int b;
};

struct result{
    char  t[400];
    int result;
};

struct result summStructReturn(struct input inp){
    struct result rrr;
    rrr.result = (inp . a) + (inp . b);
    strcpy(rrr.t, "OK");
    return rrr;
};
