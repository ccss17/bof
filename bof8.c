// AFTER => bof7.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define BUF_SIZE 8

// ASLR OFF
// STACK-PROTECTOR OFF
// STACK-EXECUTION ON

void vuln() {
    char buf[BUF_SIZE];

    if (setreuid(UID_BOF9, UID_BOF9)) {
        perror("setuid");
        exit(1);
    }
    if (setregid(UID_BOF9, UID_BOF9)) {
        perror("setgid");
        exit(1);
    }
    gets(buf);
    printf("Hello %s[%p]!\n", buf, buf);
    printf("(env:SHELLCODE -> %p)\n", getenv("SHELLCODE"));
}

int main() {
    vuln();
    return 0;
}
