#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>

#include "../include/mysocket.hpp"
#include "../include/files.hpp"

#define BUF 65536

int main() {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in adr = {0};
    adr.sin_family = AF_INET;
    adr.sin_port = htons(PORT);
    Inet_pton(AF_INET, "192.168.31.112", &adr.sin_addr);
    Connect(fd, (struct sockaddr *) &adr, sizeof adr);

    char buf[BUF];
    int file = OpenRead("data_client/miku.png");
    ReadFromFileToFd(fd, file, buf, BUF);

    close(file);
    close(fd);
    return 0;
}
