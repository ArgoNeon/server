#ifndef MYSOCKET_HPP
#define MYSOCKET_HPP

#include <sys/types.h>
#include <sys/socket.h>

#define BUF 65536
#define PORT 8080

int Socket(int domain, int type, int protocol);

void Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

void Listen(int sockfd, int backlog);

int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

void Connect(int socket, const struct sockaddr *addr, socklen_t addrlen);

void Inet_pton(int af, const char *src, void *dst);

void GetHostName(char *hostname, size_t len);

struct hostent *GetHostInfo(char *hostname);

const char *Inet_ntop(int af, const void *src, char *dst, size_t cnt);

#endif  //MYSOCKET_HPP
