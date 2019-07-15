#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define BUF_SIZE 128

// COMPILE $ gcc bof0.c -o bof0

int main(){
    char buf[BUF_SIZE];
    puts("\033[32m" "enter your name :)" "\033[0m");
    gets(buf);
    printf("Hello " "\033[33m" "%s" "\033[0m" "!\n", buf);
    return 0;
}
