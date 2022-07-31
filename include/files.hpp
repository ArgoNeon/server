#ifndef FILES_HPP
#define FILES_HPP

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

ssize_t Read(int fd, char *buf, ssize_t count);

ssize_t Write(int fd, char *buf, ssize_t count); 

int OpenRead(const char *pathname);

int OpenWrite(const char *pathname);

void ReadFromFdToFile(int fd, int file, char *buf, size_t buf_size);

void ReadFromFileToFd(int fd, int file, char *buf, size_t buf_size);

#endif  //FILES_HPP
