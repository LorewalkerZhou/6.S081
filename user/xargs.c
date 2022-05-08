#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    char *new_argv[argc];
    for (int i = 1; i < argc; i++) {
        new_argv[i - 1] = argv[i];
    }
    char buf[512], *p;
    int status;
    while(gets(buf, 512)) {
        int len = strlen(buf);
        if (len == 0) {
            break;
        }
        p = buf;
        for (int i = 0; i < len; i++) {
            if (buf[i] == '\n') {
                // buf[i - 1] = 0;
                buf[i] = 0;
                new_argv[argc - 1] = p;
                if (fork() == 0) {
                    exec(new_argv[0], new_argv);
                }
                wait(&status);
                p = buf + i + 1;
            }
        }
    }
    exit(0);
}