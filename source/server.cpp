#include <cstdio>
#include <cstdlib>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "../include/mysocket.hpp"
#include "../include/files.hpp"

#define BUF 65536

int main() {
    int server = Socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in adr = {0};
    adr.sin_family = AF_INET;
    adr.sin_port = htons(8080);
    Bind(server, (struct sockaddr *) &adr, sizeof adr);
    Listen(server, 5);
    socklen_t adrlen = sizeof adr;
    int fd = Accept(server, (struct sockaddr *) &adr, &adrlen);

    char buf[BUF];
    int file = OpenWrite("data_server/server.png");
    ReadFromFdToFile(fd, file, buf, BUF);

    close(file);
    close(fd);
    close(server);
    return 0;
}
