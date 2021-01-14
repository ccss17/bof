// AFTER => bof9.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define BUF_SIZE 8

// ASLR ON
// STACK-PROTECTOR OFF
// STACK-EXECUTION ON

void vuln(char * arg) {
    char buf[BUF_SIZE];

    if (setreuid(UID_BOF11, UID_BOF11)) {
        perror("setuid");
        exit(1);
    }
    if (setregid(UID_BOF11, UID_BOF11)) {
        perror("setgid");
        exit(1);
    }
    strcpy(buf, arg);
    printf("Hello %s[%p]!\n", buf, buf);
    printf("(env:SHELLCODE -> %p)\n", getenv("SHELLCODE"));
}

int main(int argc, char *argv[]) {
    vuln(argv[1]);
    return 0;
}

