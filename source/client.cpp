#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <netdb.h>
#include <cstring>
#include <sys/wait.h>

#include "../include/mysocket.hpp"
#include "../include/files.hpp"
#include "../include/checker.hpp"
#include "../include/searchip.hpp"

struct client {
    char orders[256][256];
    int orders_size[256];
    struct sockaddr_in addr = {0};
    long long com = 0;
    int fd;
};

int main() {
    int status;
    int shell_fd[2];

    int check_pipe = pipe(shell_fd);
    CheckPipe(check_pipe);
    pid_t pid = fork();
    CheckPid(pid);
  
    if (pid == 0) {
        dup2(shell_fd[1], 1);
        close(shell_fd[0]);
        close(shell_fd[1]);
        execlp("ip", "ip", "-4", "addr", NULL);
    } else {
        close(shell_fd[1]);
        SearchInet(shell_fd[0]);
        wait(&status);
    }

    struct client clnt;
    int i;

    clnt.fd = socket(AF_INET, SOCK_STREAM, 0);

    clnt.addr.sin_family = AF_INET;
    clnt.addr.sin_port = htons(PORT);

    EstablishConnect(clnt.fd, &clnt.addr);

    while(!true) {
        i = clnt.com % 256;
        clnt.orders_size[i] = ReadString(clnt.fd, clnt.orders[i], 256);
        //CommandAnalyse(clnt.orders[i]);
        WriteString(clnt.orders[i], clnt.orders_size[i]);
        clnt.com++;
    }
   
    char buf[BUF];
    int file = OpenRead("data_client/client.jpg");
    ReadFromFileToFd(clnt.fd, file, buf, BUF);

    close(file);
    close(clnt.fd);
    return 0;
}
