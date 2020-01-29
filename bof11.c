// AFTER => bof10.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define BUF_SIZE 8

// ASLR ON
// STACK-PROTECTOR OFF
// STACK-EXECUTION OFF
// EXPLOIT --> exp_bof11.py

void vuln(void) {
    char buf[BUF_SIZE] = {'\0'};
    memset(buf, 0, sizeof(buf));
    printf("printf() address : %p\n", printf);

    if (setreuid(UID_BOF12, UID_BOF12)) {
        perror("setuid");
        exit(1);
    }
    if (setregid(UID_BOF12, UID_BOF12)) {
        perror("setgid");
        exit(1);
    }
    unsigned short mistake = -128;
    fgets(buf, mistake, stdin);
    printf("Hello %s\n", buf);
}

int main(void) {
    vuln();
    return 0;
}
