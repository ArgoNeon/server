#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <netdb.h>
#include <sys/wait.h>

#include "../include/mysocket.hpp"
#include "../include/files.hpp"
#include "../include/checker.hpp"
#include "../include/searchip.hpp"

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

    int fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr = {0};
    struct sockaddr_in client_addr = {0}; 

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(PORT);
    
    char IP[INET_ADDRSTRLEN];
    int server_ip;
    int connect = -1;

    while (connect != 0) {
        write(1, "Input server ip: ", 17);
        server_ip = ReadServerIP(IP);
        CheckServerIP(server_ip);
        if (server_ip == -1)
            continue;
        Inet_pton(AF_INET, IP, &server_addr.sin_addr);
        connect = Connect(fd, (struct sockaddr *) &server_addr, sizeof server_addr);
    }
    //192.168.31.112
   
    char buf[BUF];
    int file = OpenRead("data_client/client.jpg");
    ReadFromFileToFd(fd, file, buf, BUF);

    close(file);
    close(fd);
    return 0;
}
