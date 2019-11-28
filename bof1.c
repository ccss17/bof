#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define BUF_SIZE 128
#define KEY 0x61616161
#define G "\033[32m"
#define Y "\033[33m"
#define E "\033[0m"

// ASLR OFF
// COMPILE $ gcc -fno-stack-protector bof1.c -o bof1
// SETUID  $ sudo chown root:root bof1
//         $ sudo chmod 4755 bof1
// EXPLOIT $ (python -c "print 'aaaa'+'x'*140";cat) | ./bof1

void vuln() {
    int innocent;
    char buf[BUF_SIZE];

    puts(G "enter your name :)" E);
    gets(buf);
    printf("Hello " Y "%s" E "!\n", buf);

    if (innocent  == KEY) {
        if (setuid(0)) {
            perror("setuid");
            return 1;
        }
        system("/bin/sh");
    }
}

int main(){
    vuln();
    return 0;
}
