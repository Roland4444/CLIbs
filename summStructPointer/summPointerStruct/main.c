struct input{
    int a;
    int b;
};

int structSummPointer(struct input* inp){
    return (inp->a) + (inp->b);
}
