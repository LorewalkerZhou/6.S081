#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    int pread[2];
    int pwrite[2];
    pipe(pread);
    pipe(pwrite);
    char* buf;
    buf = " ";

    if (fork() == 0) {
        close(pread[0]);
        close(pwrite[1]);
        int pid = getpid();
        read(pwrite[0], buf, 1);
        printf("%d: received ping\n", &pid);
        write(pread[1], " ", 1);
    } else {
        close(pread[1]);
        close(pwrite[0]);
        int pid = getpid();
        write(pwrite[1], " ", 1);
        read(pread[0], buf, 1);
        printf("%d: received pong\n", &pid);
    }
    exit(0);
}