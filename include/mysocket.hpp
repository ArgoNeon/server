#ifndef MYSOCKET_HPP
#define MYSOCKET_HPP

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUF 65536
#define PORT 8080
#define BUF1_SIZE 1
#define CHAR_SIZE 2
#define INET_SIZE 6
#define COLON_SIZE 3

int Socket(int domain, int type, int protocol);

void Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

void Listen(int sockfd, int backlog);

int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

int Connect(int socket, const struct sockaddr *addr, socklen_t addrlen);

void Inet_pton(int af, const char *src, void *dst);

void GetHostName(char *hostname, size_t len);

struct hostent *GetHostInfo(char *hostname);

const char *Inet_ntop(int af, const void *src, char *dst, size_t cnt);

int ReadIP(int fd, char *IP);

int ReadNet(int fd, char *NET);

void SearchInet(int fd);

void CheckPipe(int check_pipe);

void CheckPid(pid_t pid);

#endif  //MYSOCKET_HPP
