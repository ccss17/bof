// AFTER => bof8.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define BUF_SIZE 1

// COMPILE $ gcc -fno-stack-protector bof9.c -o bof9
// SETUID  $ sudo chown root:root bof9
//         $ sudo chmod 4755 bof9
// EXPLOIT $ 

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fputs("\033[31m" "error :( this program needs some arguments\n" "\033[0m", stderr);
        return 1;
    }
    char buf[BUF_SIZE];

    if (setuid(0)) {
        perror("setuid");
        return 1;
    }
    strcpy(buf, argv[1]);
    printf("Hello %s[%p]!\n", buf, buf);
    printf("(func:SYSTEM -> %p)\n", system);
    printf("(func:binsh -> %p)\n", getenv("binsh"));

    return 0;
}
