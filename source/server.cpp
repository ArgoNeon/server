#include <cstdio>
#include <cstdlib>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/wait.h>

#include "../include/mysocket.hpp"
#include "../include/files.hpp"

struct server {
    int fd[32];
    struct sockaddr_in adr[32];
    struct sockaddr_in server_adr;

};

//sudo arp-scan --interface=wlp0s20f3 --localnet
int main() {
    char IP[INET_ADDRSTRLEN];
    char buf[BUF];
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
    
    int server = Socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in adr = {0};

    adr.sin_family = AF_INET;
    adr.sin_port = htons(PORT);
    Bind(server, (struct sockaddr *) &adr, sizeof adr);
    Listen(server, 5);
    socklen_t adrlen = sizeof adr;

  /*  check_pipe = pipe(shell_fd);
    CheckPipe(check_pipe);
    pid = fork();
    CheckPid;
    
    if (pid == 0)

*/
    int fd = Accept(server, (struct sockaddr *) &adr, &adrlen);
    Inet_ntop(AF_INET, &adr.sin_addr, IP, INET_ADDRSTRLEN);
    printf("Accept: %s", IP);

    int com;
    char command[256];

    while(!true) {
        write(1, "Input command: ", 16);
        com = ReadString(0, command, 256);
        SendString(fd, command, com);
    }

    int file = OpenWrite("data_server/server.jpg");
    ReadFromFdToFile(fd, file, buf, BUF);

    close(file);
    close(fd);
    close(server);
    return 0;
}
