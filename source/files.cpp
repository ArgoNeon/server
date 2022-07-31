#include <cstdio>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "../include/files.hpp"

ssize_t Read(int fd, char *buf, ssize_t count) {
    ssize_t nread;
    while((nread = read(fd, buf, count)) > 0) {
        if (nread == -1) {
            perror("read failed");
            exit(EXIT_FAILURE);
        }
    }
    return nread;
}

ssize_t Write(int fd, char *buf, ssize_t count) {
    ssize_t nwrite;
    while((nwrite = write(fd, buf, count)) > 0) {
        if (nwrite == -1) {
            perror("write failed");
            exit(EXIT_FAILURE);
        }
    }
    return nwrite;
}

int OpenRead(const char *pathname) {
    int file = open(pathname, O_RDONLY);
    if (file == -1) {
        perror("Open for read failed");
        exit(EXIT_FAILURE);
    }
    return file;
}

int OpenWrite(const char *pathname) {
    int file = open(pathname, O_CREAT|O_WRONLY|O_TRUNC, 0777);
    if (file == -1) {
        perror("Open for write failed");
        exit(EXIT_FAILURE);
    }
    return file; 
}

void ReadFromFdToFile(int fd, int file, char *buf, size_t buf_size) {
    size_t nread = read(fd, buf, buf_size);
    
    if (nread == -1) {
        perror("Read from fd to file failed");
        exit(EXIT_FAILURE);
    }

    while(nread > 0) {
        write(file, buf, nread);
        nread = read(fd, buf, buf_size);
        if (nread == -1) {
            perror("Read from fd to file failed");
            exit(EXIT_FAILURE);
        }
    }
}

void ReadFromFileToFd(int fd, int file, char *buf, size_t buf_size) {
    size_t nread = read(file, buf, buf_size);

    if (nread == -1) {
        perror("Read from file to fd failed");
        exit(EXIT_FAILURE);
    }

    while (nread > 0) {
        write(fd, buf, nread);
        nread = read(file, buf, buf_size);
        if (nread == -1) {
            perror("Read from file to fd failed");
            exit(EXIT_FAILURE);
        }
     }
}
