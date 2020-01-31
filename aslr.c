#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define CMD_SIZE 128
#define ECHO "echo %d"
#define PIPE " | "
#define TEE_ASLR "tee /proc/sys/kernel/randomize_va_space"

int main(int c, char *v[])
{
    if (c < 2) {
        return 1;
    }
    if (setreuid(0, 0)) {
        perror("setuid");
        exit(1);
    }
    if (setregid(0, 0)) {
        perror("setgid");
        exit(1);
    }
    char cmd[CMD_SIZE];
    sprintf(cmd, ECHO PIPE TEE_ASLR, atoi(v[1]));
    system(cmd);
    return 0;
}