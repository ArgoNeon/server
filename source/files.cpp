#include <cstdio>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include "../include/files.hpp"

void ClearString(int fd) {
    char buf[1] = "";
    ssize_t nread;
    while(buf[0] != '\n') {
        nread = read(fd, buf, 1);
    }
}

int ReadString(int fd, char *str, ssize_t str_size) {
    char buf[1];
    ssize_t nread;
    int i = 0;
    while(1) { 
        nread = read(fd, buf, 1);
        if (nread == -1) {
            perror("read failed");
            return -1;
        }
       
        if (i == str_size - 1) {
            str[i] = '\0';
            ClearString(fd);
            return i;
        }

        if (buf[0] == '\n' || buf[0] == '\0'){
            str[i] = '\0';
            i++;
            return i;
        }
        str[i] = buf[0];
        i++;
    }
    return i;
}

int WriteString(char *str, ssize_t str_size) {
    ssize_t nwrite = write(1, str, str_size);
    if (nwrite == -1) {
        perror("write failed");
        return -1;
    }
    write(1, "\n", 1);
    return nwrite;
}

int SendString(int fd, char *str, ssize_t str_size) {
    ssize_t nwrite = write(fd, str, str_size);
    if (nwrite == -1) {
        perror("write failed");
        return -1;
    }
    return nwrite;
}

int OpenRead(const char *pathname) {
    int file = open(pathname, O_RDONLY);
    if (file == -1) {
        perror("Open for read failed");
        errno;
    }
    return file;
}

int OpenWrite(const char *pathname) {
    int file = open(pathname, O_CREAT|O_WRONLY|O_TRUNC, 0777);
    if (file == -1) {
        perror("Open for write failed");
        errno;
    }
    return file; 
}

void ReadFromFdToFile(int fd, int file, char *buf, size_t buf_size) {
    size_t nread = 1;
    ssize_t nwrite;
    while(nread > 0) {
        nread = read(fd, buf, buf_size);
        if (nread == -1) {
            perror("Read from fd failed");
            return;
        }
        nwrite = write(file, buf, nread);
        if (nwrite == -1) {
            perror("Write to file failed");
            return;
        }
    }
}

void ReadFromFileToFd(int fd, int file, char *buf, size_t buf_size) {
    size_t nread = 1;
    ssize_t nwrite;
    while(nread > 0) {
        nread = read(file, buf, buf_size);
        if (nread == -1) {
            perror("Read from fd failed");
            return;
        }
        nwrite = write(fd, buf, nread);
        if (nwrite == -1) {
            perror("Write to file failed");
            return;
        }
    }
}
