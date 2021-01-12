// AFTER => bof8.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define BUF_SIZE 8

// ASLR OFF
// STACK-PROTECTOR OFF
// STACK-EXECUTION OFF

char * binsh = "/bin/sh";

void vuln(void) {
    char buf[BUF_SIZE];

    if (setreuid(UID_BOF10, UID_BOF10)) {
        perror("setuid");
        exit(1);
    }
    if (setregid(UID_BOF10, UID_BOF10)) {
        perror("setgid");
        exit(1);
    }
    printf("system:%p\n", system);
    printf("binsh:%p\n", binsh);
    gets(buf);
    printf("Hello %s!\n", buf);
}

int main(void) {
    vuln();
    return 0;
}
