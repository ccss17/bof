// AFTER => bof10.c
#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <dlfcn.h>
#define BUF_SIZE 8

// COMPILE $ gcc -fno-stack-protector bof11.c -o bof11
// SETUID  $ sudo chown root:root bof11
//         $ sudo chmod 4755 bof11
// EXPLOIT --> exp.py

void vuln(void) {
    char buf[BUF_SIZE];
    void (*printf_addr)() = dlsym(RTLD_NEXT, "printf");
    printf("printf() address : %p\n",printf_addr);

    if (setuid(0)) {
        perror("setuid");
        return 1;
    }
    gets(buf);
    printf("Hello %s!\n", buf);
}

int main(void) {
    vuln();
    return 0;
}
