#include <cstdio>
#include <cstdlib>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "../include/mysocket.hpp"

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

void Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
    int res = connect(sockfd, addr, addrlen);
    if (res == -1) {
        perror("connect failed");
        exit(EXIT_FAILURE);
    }
}

void Inet_pton(int af, const char *src, void *dst) {
    int res = inet_pton(af, src, dst);
    if (res == 0) {
        printf("inet_pton failed: src does not contain a character string representing a valid network  address  in the  specified  address  family\n");
        exit(EXIT_FAILURE);
    }
    if (res == -1) {
        perror("inet_pton failed");
        exit(EXIT_FAILURE);
    }
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
