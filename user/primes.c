#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void prime_filter(int* pl);

int
main(int argc, char *argv[])
{
    int pr[2];
    pipe(pr);
    if (fork() == 0) {
        prime_filter(pr);
    }
    else {
        for (int i = 2; i <= 35; i++) {
            write(pr[1], &i, 4);
        }
        close(pr[1]);
        int status;
        wait(&status);
    }
    exit(0);
}

void prime_filter(int* pl) {
    close(pl[1]);
    int n, i;
    int pr[2];
    int flag = 0;
    pipe(pr);
    read(pl[0], &n, 4);
    printf("prime %d\n", n);
    
    while (read(pl[0], &i, 4) != 0) {
        if ((i % n) != 0) {
            if (!flag) {
                flag = 1;
                if (fork() == 0) {
                    prime_filter(pr);
                    return;
                }
            }
            write(pr[1], &i, 4);
        }
    }
    close(pr[1]);
    int status;
    wait(&status);
}