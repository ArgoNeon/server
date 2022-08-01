#include <cstdio>
#include <cstdlib>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <cstring>

#include "../include/mysocket.hpp"
#include "../include/searchip.hpp"
#include "../include/checker.hpp"

void EstablishConnect(int fd, struct sockaddr_in *server_addr) {
    char IP[INET_ADDRSTRLEN];
    char exit_arr[5] = "exit";
    int server_ip;
    int connect = -1;
    int pton = -1;

    while (connect != 0) {
        write(1, "Input server ip: ", 17);
        server_ip = ReadServerIP(IP);
        CheckServerIP(server_ip);
        if (server_ip == -1)
            continue;
        if(strncmp(IP, exit_arr, 4) == 0)
                return;
        pton = Inet_pton(AF_INET, IP, &server_addr->sin_addr);
        if(pton == -1) 
            continue;
        connect = Connect(fd, (struct sockaddr *) server_addr, sizeof (*server_addr));
    }
}

int Socket(int domain, int type, int protocol) {
    int res = socket(domain, type, protocol);
    if (res == -1) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    return res;
}

void Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
    int res = bind(sockfd, addr, addrlen);
    if (res == -1) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
}

void Listen(int sockfd, int backlog) {
    int res = listen(sockfd, backlog);
    if (res == -1) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }
}

int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen) {
    int res = accept(sockfd, addr, addrlen);
    if (res == -1) {
        perror("accept failed");
        exit(EXIT_FAILURE);
    }
    return res;    
}

int Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
    int res = connect(sockfd, addr, addrlen);
    if (res == -1) {
        perror("connect failed");
        return -1;
    }
    return 0;
}

int Inet_pton(int af, const char *src, void *dst) {
    int res = inet_pton(af, src, dst);
    if (res == 0) {
        printf("inet_pton failed: src does not contain a character string representing a valid network  address  in the  specified  address  family\n");
        return -1;
    }
    if (res == -1) {
        perror("inet_pton failed");
        return -1;
    }
    return 0;
}

void GetHostName(char *hostname, size_t len) {
    int name = gethostname(hostname, len);
    if (name == -1) {
        perror("gethostname failed");
        exit(EXIT_FAILURE);
    }
}

struct hostent *GetHostInfo(char *hostname) {
    struct hostent *host_info;
    host_info = gethostbyname(hostname);
    if (host_info == NULL) {
        perror("gethostbyname failed");
        exit(EXIT_FAILURE);
    }
    return host_info;    
}

const char *Inet_ntop(int af, const void *src, char *dst, size_t cnt) {
    const char *res = inet_ntop(af, src, dst, cnt);
    if (res == NULL) {
        perror("inet_ntop failed");
        exit(EXIT_FAILURE);
    }
    return res;
}

