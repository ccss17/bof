// AFTER => bof9.c
#include <stdio.h>
#define BUF_SIZE 8

// ASLR OFF
// STACK-PROTECTOR OFF
// STACK-EXECUTION OFF

void vuln(void) {
    char buf[BUF_SIZE];
    gets(buf);
    printf("Hello %s!\n", buf);
}

int main(void) {
    vuln();
    return 0;
}
