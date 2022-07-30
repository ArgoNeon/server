#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <netdb.h>

#include "../include/mysocket.hpp"
#include "../include/files.hpp"

int main() {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr = {0};
    struct sockaddr_in client_addr = {0}; 

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(PORT);

    char hostname[256];
    struct hostent *host_info;
    char IP[INET_ADDRSTRLEN];
    GetHostName(hostname, sizeof(hostname));
    host_info = GetHostInfo(hostname);
    Inet_ntop(AF_INET, (const void *) host_info->h_addr_list[0], IP, INET_ADDRSTRLEN);
    printf("Current Host Name: %s\n", hostname);
    printf("Host IP: %s\n", IP);

    Inet_pton(AF_INET, "192.168.31.112", &server_addr.sin_addr);
    Connect(fd, (struct sockaddr *) &server_addr, sizeof server_addr);
    //192.168.31.112
   
    char buf[BUF];
    int file = OpenRead("data_client/miku.png");
    ReadFromFileToFd(fd, file, buf, BUF);

    close(file);
    close(fd);
    return 0;
}
