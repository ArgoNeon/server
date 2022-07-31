#include <cstdio>
#include <cstdlib>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "../include/mysocket.hpp"
#include "../include/searchip.hpp"
#include "../include/files.hpp"

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
            perror("Search inet failed");
            return;
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
            perror("read ip failed");
            return -1;
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
            perror("read net failed");
            return -1;
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

int ReadServerIP(char *IP) {
    char buf[BUF1_SIZE];
    char space[CHAR_SIZE] = " ";
    char next[CHAR_SIZE] = "\n";
    ssize_t nread;
    int i = 0;

    while ((nread = read(0, buf, BUF1_SIZE)) > 0) {
        if (nread == -1) {
            ClearString(0);
            return -1;
        }
        if (i > INET_ADDRSTRLEN) {
            ClearString(0);
            return -1;
        }
        if ((buf[0] == space[0]) || (buf[0] == next[0]) || (buf[0] == EOF)) {
            IP[i] = '\0';
            i++;
            break;
        } else {
            IP[i] = buf[0];
            i++;
        }
    }
    return i;
}

