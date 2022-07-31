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

void SearchInet(int fd) {    
    char IP[INET_ADDRSTRLEN + 4];
    char NET[INET_ADDRSTRLEN];
    char next[CHAR_SIZE] = "\n";
    char buf[BUF1_SIZE] = "";
    char colon[COLON_SIZE] = ": ";
    char inet[INET_SIZE] = "inet ";
    int i = 0;
    int ip;
    int net;

    ssize_t nread;
    while((nread = read(fd, buf, BUF1_SIZE)) > 0) {
        if (nread == -1) {
            perror("read failed");
            exit(EXIT_FAILURE);
        }
        if (inet[i] == buf[0]) {
            i++;
            if (i == INET_SIZE - 1) {
                ip = ReadIP(fd, IP);
                write(1, IP, ip);
                write(1, next, CHAR_SIZE);
                i = 0;
            }
        } else {
            if (colon[i] == buf[0]) {
                i++;
                if (i == COLON_SIZE - 1) {
                    net = ReadNet(fd, NET);
                    write(1, NET, net);
                    write(1, colon, COLON_SIZE);
                    i = 0;
                }
            } else {
                i = 0;
            }
        }
    }
}

int ReadIP(int fd, char *IP) {
    char space[CHAR_SIZE] = " ";
    char buf[BUF1_SIZE] = "";
    ssize_t nread;
    int i = 0;

    while((nread = read(fd, buf, BUF1_SIZE)) > 0) {
       if (nread == -1) {
            perror("read failed");
            exit(EXIT_FAILURE);
        }
       if (buf[0] == space[0]) {
            IP[i] = '\0';
            i++;
            break;
       }
       IP[i] = buf[0];
       i++;
    }
    return i;
}

int ReadNet(int fd, char *NET) {
    const int buf_size = 1;
    const int colon_size = 2;
    char colon[COLON_SIZE] = ":";
    char buf[BUF1_SIZE] = "";
    ssize_t nread;
    int i = 0;

    while((nread = read(fd, buf, buf_size)) > 0) {
       if (nread == -1) {
            perror("read failed");
            exit(EXIT_FAILURE);
        }
       if (buf[0] == colon[0]) {
            NET[i] = '\0';
            i++;
            break;
       }
       NET[i] = buf[0];
       i++;
    }
    return i;
}

void CheckPipe(int check_pipe) {
    if (check_pipe == -1) {
        perror("pipe failed");
        exit(EXIT_FAILURE);
    }
}

void CheckPid(pid_t pid) {
    if (pid == -1) {
        perror("pid failed");
        exit(EXIT_FAILURE);
    } 
}
