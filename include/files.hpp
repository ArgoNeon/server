#ifndef FILES_HPP
#define FILES_HPP

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int OpenRead(const char *pathname);

int OpenWrite(const char *pathname);

void ReadFromFdToFile(int fd, int file, char *buf, size_t buf_size);

void ReadFromFileToFd(int fd, int file, char *buf, size_t buf_size);

#endif  //FILES_HPP
