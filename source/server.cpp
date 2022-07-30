#include <cstdio>
#include <cstdlib>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>

#include "../include/mysocket.hpp"
#include "../include/files.hpp"

int main() {
    int server = Socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in adr = {0};
    adr.sin_family = AF_INET;
    adr.sin_port = htons(PORT);
    Bind(server, (struct sockaddr *) &adr, sizeof adr);
    Listen(server, 5);
    socklen_t adrlen = sizeof adr;
    int fd = Accept(server, (struct sockaddr *) &adr, &adrlen);

    char hostname[256];
    struct hostent *host_info;
    char IP[INET_ADDRSTRLEN];
    GetHostName(hostname, sizeof(hostname));
    host_info = GetHostInfo(hostname);
    Inet_ntop(AF_INET, (const void *) host_info->h_addr_list[0], IP, INET_ADDRSTRLEN);
    printf("Current Host Name: %s\n", hostname);
    printf("Host IP: %s\n", IP);

    char buf[BUF];
    int file = OpenWrite("data_server/server.png");
    ReadFromFdToFile(fd, file, buf, BUF);

    close(file);
    close(fd);
    close(server);
    return 0;
}
