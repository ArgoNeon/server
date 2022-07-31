#include <cstdio>
#include <cstdlib>
#include <unistd.h>

void CheckPipe(int check_pipe) {
    if (check_pipe == -1) {
        perror("pipe failed");
    }
}

void CheckPid(pid_t pid) {
    if (pid == -1) {
        perror("pid failed");
    } 
}

void CheckServerIP(int server_ip) {
    if (server_ip == -1) {
        write(1, "read server ip failed\n", 22);
    }
}
