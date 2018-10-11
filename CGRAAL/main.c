//https://stackoverflow.com/questions/14884126/build-so-file-from-c-file-using-gcc-command-line
//SO==>
//gcc -c -fPIC hello.c -o hello.o
//gcc hello.o -shared -o libhello.so
//
int summary(int a, int b){
	return a+b;
}
