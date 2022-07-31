#ifndef SEARCHIP_HPP
#define SEARCHIP_HPP

void SearchInet(int fd);

int ReadIP(int fd, char *IP); 

int ReadNet(int fd, char *NET);

int ReadServerIP(char *IP);

#endif //   SEARCHIP_HPP
